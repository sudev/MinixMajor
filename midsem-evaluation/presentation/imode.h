 
/* Flag bits for i_mode in the inode. */
#define I_TYPE          0170000 /* this field gives inode type */
#define I_UNIX_SOCKET   0140000 /* unix domain socket */
#define I_SYMBOLIC_LINK 0120000 /* file is a symbolic link */
#define I_REGULAR       0100000 /* regular file, not dir or special */
#define I_BLOCK_SPECIAL 0060000 /* block special file */
#define I_DIRECTORY     0040000 /* file is a directory */
#define I_CHAR_SPECIAL  0020000 /* character special file */
#define I_NAMED_PIPE    0010000 /* named pipe (FIFO) */
#define I_SET_UID_BIT   0004000 /* set effective uid_t on exec */
#define I_SET_GID_BIT   0002000 /* set effective gid_t on exec */
#define I_SET_STCKY_BIT 0001000 /* sticky bit */ 
#define ALL_MODES       0007777 /* all bits for user, group and others */
#define RWX_MODES       0000777 /* mode bits for RWX only */
#define R_BIT           0000004 /* Rwx protection bit */
#define W_BIT           0000002 /* rWx protection bit */
#define X_BIT           0000001 /* rwX protection bit */
#define I_NOT_ALLOC     0000000 /* this inode is free */
....

