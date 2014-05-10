---
layout: page
title: "Immediate Files"
subtitle: "Design"
category: doc
date: 2013-06-05 12:00:00
order: 4
---

Implementing immediate file involves several key steps. First, we need to define an additional flag (e.g. for an i_mode member variable of an inode) that marks our file and inode as immediate.  Then we need to think about the different file operations that are affected by immediate files, and modify them to support these files.  If we think a bit, we should come up with a number of operations, including (but not limited to) creating, deleting, reading and writing a file.  Specifically, here are some requirements:   

* Whenever we create a new file using "open" system call with O_CREATI flag, this new file should be marked as immediate in its inode.

* Whenever we delete or unlink an immediate file, we have to make sure that the code does not try to free data blocks for them, since there are none. We have to make sure that we do NOT follow the block pointers in the inode, since those are not used and generally invalid.

* Similarly, when we read from an immediate file, just retrieve the data from the inode itself.

* Check out files from the current file system to see how current operations are performed, and where the code needs to be changed.  Make sure to check to see which functions are already implemented, and reuse existing functions whenever possible.



