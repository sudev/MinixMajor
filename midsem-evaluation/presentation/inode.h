
EXTERN struct inode {
  u16_t i_mode;		/* file type, protection, etc. */
  u16_t i_nlinks;		/* how many links to this file */
  u16_t i_uid;			/* user id of the file's owner */
  u16_t i_gid;			/* group number */
  i32_t i_size;			/* current file size in bytes */
  u32_t i_atime;		/* time of last access (V2 only) */
  u32_t i_mtime;		/* when was file data last changed */
  u32_t i_ctime;		/* when was inode itself changed (V2 only)*/
  u32_t i_zone[V2_NR_TZONES]; /* zone numbers for direct, ind, and dbl ind */
....
}
