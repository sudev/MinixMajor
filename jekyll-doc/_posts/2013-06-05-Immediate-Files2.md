---
layout: page
title: "Immediate Files"
subtitle: "Design"
category: doc
date: 2013-06-05 12:00:00
order: 4
---

Implementing this involves several key steps. First, you need to define an additional flag (e.g. for an i_mode member variable of an inode) that marks your file and inode as immediate.  Then you need to think about the different file operations that are affected by immediate files, and modify them to support these files.  If you think a bit, you should come up with a number of operations, including (but not limited to) creating, deleting, reading and writing a file.  Specifically, here are some requirements:   

* Whenever you create a new file using "open" system call with O_CREATI, this new file should be marked as immediate.

* Whenever you delete or unlink an immediate file, you have to make sure that the code does not try to free data blocks for them, since there are none.  You have to make sure that you do NOT follow the block pointers in the inode, since those are not used and generally invalid. For the pointers, check out member i_zone in inode.h

* Similarly, when you read from an immediate file, just retrieve the data from the inode itself.

* Check out files from the current file system to see how current operations are performed, and where the code needs to be changed.  Make sure to check to see which functions are already implemented, and reuse existing functions whenever possible.



