---
layout: page
title: "Conclusion"
category: doc
date: 2013-06-05 12:00:00
order: 8
---

A critical study of the MINIX 3 Virtual File System was done and the results of the study are summarized here. The MINIX Virtual File system is built in a distributed, multiserver manner, which is a substantially different architecture compared to other UNIX-like solutions. An abstract layer has been designed and implemented, which is in charge of controlling the overall mechanism of the VFS by issuing accurate requests for the appropriate FS servers during the system calls.It is also in charge of maintaining abstract data structures that are independent from the underlying file system drivers and are playing important roles within the Virtual File system’s functionality. In order to achieve this, several data structures and functions operating on them had to be designed and added to the former FS server. The communication with underlying file system drivers also had to be implemented. The MFS implementation had to be separated from the original code and some part of it was rewritten to cooperate with the Virtual Layer. The communication according to the VFS/FS interface also had to be implemented.  

Second part of the project was implementing support for immediate files in MINIX 3 File System. A proper design for its implementation was framed and documented in the previous chapters. Although the implementation was not complete, the process was helpful in understanding the VFS better.