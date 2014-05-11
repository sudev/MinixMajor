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




