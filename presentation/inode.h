struct inode {
  mode_t i_mode;
  nlink_t i_nlinks;
  uid_t i_uid;
  gid_t i_gid;
  off_t i_size;
  time_t i_atime;
  time_t i_mtime;
  time_t i_ctime;
  zone_t i_zone[V2_NR_TZONES];
.....
};
