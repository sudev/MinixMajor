##Introduction to Design of VFS in Minix Operating System. 

The MINIX Virtual File system is built in a distributed, multiserver, manner. It consists of a top-level VFS process and separate FS process for each mounted partition.    

Picture Page 24  2.1 


The top-level VFS process receives the requests from user programs through system calls. If actual file system operation is involved the VFS requests the corresponding FS process to do the job. This dependency is depicted by [Figure].

	[Own]
	The top level VFS is the virtualization layer here which will requests from the process and routes the request to specific filesystem server. 
	[/Own]

##Major steps in execution of system call 

Let's consider system call **stat()** with an argument **/usr/web/index.html**. 

Assume 

*  a ext2 partition mounted at /usr
* root filesystem is Minix filesystem

###Steps

1. The user process calls the stat() function of the POSIX library which builds the stat request message and sends it to the VFS process.   
(a) The VFS process copies the path name from userspace.   

2. The VFS first issues a lookup for the path name. It determines that the given path is absolute, therefore the root FS process has to be requested to perform
the lookup.   
(b) The root FS process copies the path name from the VFS’ address space.   

3. During the lookup in the root FS process the root directory has to be read in order to find the string ”usr”. Let us assume that this information is not in the
buffer cache. The root FS asks the Driver process to read the corresponding block from the disk.   

4. The driver reads the block and transfers back to the FS process. It reports OK.   
(c) The driver copies the disk content into the FS’ buffer cache.    

5. The root FS process examines the ”usr” directories inode data and realizes that there is a partition mounted on this directory. It sends the EENTER MOUNT message to the VFS that also contains the number of characters that were processed during the lookup.    

6. The VFS looks up in the virtual mount table which FS process is responsible for the ”/usr” partition. The lookup has to be continued in that FS process ( "/usr" Mininx filesystem partition). The VFS sends the lookup request and with the rest of the path name.      
d. The ”/usr” FS process copies the path name from the VFS’ address space.    

7. The FS process that handles the ”/usr” partition continues the lookup of the path name. It needs additional information from the disk, therefore it asks
the driver process to read the given block and transfer it into the FS process buffer cache.    

8. The driver reads the disk and transfers back to the FS process. It reports success.  
  (e) The driver copies the disk content into the ”/usr” FS process’ buffer cache.    

9. The "/usr" FS process finishes the lookup and transfers back the inode’s details to the VFS.   

10. The VFS has all the necessary information in order to issue the actual REQ STAT request. The FS process is asked to perform the stat() operation.   

11. The FS process fills in the stat buffer. Let us assume that all the information needed for this operation is in the FS process’ buffer cache, therefore no
interaction is involved with the Driver process. The FS copies back to the user process’ address space. It reports success for the VFS.   
  (f) The FS process copies the stat buffer to the caller process’ address space.   

12. The VFS receives the response message from the FS process and sends the return value back to the POSIX library. The function reports success back to the user process.   




