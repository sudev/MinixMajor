---
layout: page
title: "Immediate Files"
subtitle: "Progress"
category: doc
date: 2013-06-05 12:00:00
order: 5
---

###Creating a I_IMMEDIATE flag bit for i_mode 

In order to distinguish between immediate file and regular file/inode in MFS we need to define a new variable `I_IMMEDIATE` in i_mode. Flags bits defined for i_mode are as shown below. It is defined inside the file `/src/include/minix/const.h `.
{% highlight C %}
/* Flag bits for i_mode in the inode. */
#define I_TYPE          0170000	/* this field gives inode type */
#define I_UNIX_SOCKET	0140000 /* unix domain socket */
#define I_SYMBOLIC_LINK 0120000	/* file is a symbolic link */
#define I_REGULAR       0100000	/* regular file, not dir or special */
#define I_BLOCK_SPECIAL 0060000	/* block special file */
#define I_DIRECTORY     0040000	/* file is a directory */
#define I_CHAR_SPECIAL  0020000	/* character special file */
#define I_NAMED_PIPE    0010000	/* named pipe (FIFO) */
#define I_SET_UID_BIT   0004000	/* set effective uid_t on exec */
#define I_SET_GID_BIT   0002000	/* set effective gid_t on exec */
#define I_SET_STCKY_BIT 0001000	/* sticky bit */ 
#define ALL_MODES       0007777	/* all bits for user, group and others */
#define RWX_MODES       0000777	/* mode bits for RWX only */
#define R_BIT           0000004	/* Rwx protection bit */
#define W_BIT           0000002	/* rWx protection bit */
#define X_BIT           0000001	/* rwX protection bit */
#define I_NOT_ALLOC     0000000	/* this inode is free */
{% endhighlight %}

Now we add a line `#define I_IMMEDIATE    0110000 ` to define the new variable `I_IMMEDIATE`. When we create a new immediate file we will set `I_IMMEDIATE` instead of `I_REGULAR` for i_mode bits of inode and hence we distinguish regular and immediate files.

###Creating O_CREATI open flag

Open flags for POSIX system calls are defined inside the file ` src/sys/sys/fcntl.h `. Shown below are some of the open flags defined in the file, we will have to add a new O_CREATI flag here such that it won't interfere with other flag bits.

{% highlight C %}

/* Oflag values for open().  POSIX Table 6-4. */
#define O_CREAT        00100	/* creat file if it doesn't exist */
#define O_EXCL         00200	/* exclusive use flag */
#define O_NOCTTY       00400	/* do not assign a controlling terminal */
#define O_TRUNC        01000	/* truncate flag */

{% endhighlight %}

###Creating an immediate file

A file can be created using either open or creat system call. File `/src/servers/vfs/open.c` of VFS handles the open and creat system call.

Function `do_open()` inside open.c handles the open system call.

{% highlight C linenos=table %}

/*===========================================================================*
 *				do_open					     *
 *===========================================================================*/
int do_open()
{
/* Perform the open(name, flags,...) system call.
 * syscall might provide 'name' embedded in message when not creating file */

  int create_mode;		/* is really mode_t but this gives problems */
  int open_mode = 0;		/* is really mode_t but this gives problems */
  int r = OK;
  char fullpath[PATH_MAX];
  vir_bytes vname;
  size_t vname_length;

  open_mode = (mode_t) job_m_in.mode;
  create_mode = job_m_in.c_mode;

  /* If O_CREAT is set, open has three parameters, otherwise two. */
  if (open_mode & O_CREAT) {
	vname = (vir_bytes) job_m_in.name1;
	vname_length = (size_t) job_m_in.name1_length;
	r = fetch_name(vname, vname_length, fullpath);
  } else {
	vname = (vir_bytes) job_m_in.name;
	vname_length = (size_t) job_m_in.name_length;
	create_mode = 0;
	if (copy_name(vname_length, fullpath) != OK) {
		/* Direct copy failed, try fetching from user space */
		if (fetch_name(vname, vname_length, fullpath) != OK)
			r = err_code;
	}
  }

  if (r != OK) return(err_code); /* name was bad */
  return common_open(fullpath, open_mode, create_mode);
}
{% endhighlight %}

`do_open()` receives either two or three arguments *(only during creation of a new file)* . Variable `open_mode` indicates the open flags which is an argument to open system call. `Line 20` checks if `open_mode` contains `O_CREAT` flag, if it's true we need to create a new file. Here we make a slight change to facilitate the creation of immediate file. Message structure is same for creation of both regular file and immediate file i.e. three arguments to open system call. For more information about Minix message structure refer [this](../ref/message.html).

{% highlight C %}

  if ((open_mode & O_CREAT) | (open_mode & O_CREATI) ) {
	vname = (vir_bytes) job_m_in.name1;
	vname_length = (size_t) job_m_in.name1_length;
	r = fetch_name(vname, vname_length, fullpath);
  }
{% endhighlight %}
 
A function `common_open()` is a common interface for both the open and creat system call. Open system call calls the `common_open()`  after finding absolute path,  open_mode and create mode *(in case of new file creation)*.

{% highlight C  %}
  /* If O_CREATE is set, try to make the file. */
  if (oflags & O_CREAT) {
        omode = I_REGULAR | (omode & ALLPERMS & fp->fp_umask);
    vp = new_node(&resolve, oflags, omode);
    r = err_code;
    if (r == OK) exist = FALSE;   /* We just created the file */
    else if (r != EEXIST) {     /* other error */
        if (vp) unlock_vnode(vp);
        unlock_filp(filp);
        return(r);
    }
    else exist = !(oflags & O_EXCL);/* file exists, if the O_EXCL
                      flag is set this is an error */
  } else {
    /* Scan path name */
    resolve.l_vmnt_lock = VMNT_READ;
    resolve.l_vnode_lock = VNODE_OPCL;
    if ((vp = eat_path(&resolve, fp)) == NULL) {
        unlock_filp(filp);
        return(err_code);
    }
{% endhighlight %}

Above given code block checks if `O_CREAT` flag was set and creates a new file in that situation. Now we will change this code block to support immediate files.

{% highlight C %}

  /* If O_CREATE is set, try to make the file. */
  if (oflags & O_CREAT) {
        omode = I_REGULAR | (omode & ALLPERMS & fp->fp_umask);
    vp = new_node(&resolve, oflags, omode);
    r = err_code;
    if (r == OK) exist = FALSE;   /* We just created the file */
    else if (r != EEXIST) {     /* other error */
        if (vp) unlock_vnode(vp);
        unlock_filp(filp);
        return(r);
    	}
    	else exist = !(oflags & O_EXCL);/* file exists, if the O_EXCL flag is set this is an error */
  } 
  /* if O_CREATI flag is set, create an immediate file instead */
  else if (oflags & O_CREATI) {
        omode = I_IMMEDIATE | (omode & ALLPERMS & fp->fp_umask); 
        /* Omode is calculate by ORing I_IMMEDIATE and (omode - mask) */
	vp = new_node(&resolve, oflags, omode);
    r = err_code;
    if (r == OK) exist = FALSE;   /* We just created the file */
    else if (r != EEXIST) {     /* other error */
        if (vp) unlock_vnode(vp);
        unlock_filp(filp);
        return(r);
    }
  else {
      /* Scan path name */
    resolve.l_vmnt_lock = VMNT_READ;
    resolve.l_vnode_lock = VNODE_OPCL;
    if ((vp = eat_path(&resolve, fp)) == NULL) {
        unlock_filp(filp);
        return(err_code);
    }
{% endhighlight %}

We have to given the flag `I_IMMEDIATE` instead of `I_REGULAR` to omode so that we can differentiate regular and immediate file using these flag bits of `i_mode`. The function `new_node()` creates new vnode for the file. *(vnode is virtual abstraction of inode in VFS)*

