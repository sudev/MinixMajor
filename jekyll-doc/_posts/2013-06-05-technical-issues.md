---
layout: page
title: "Technical Issues"
category: doc
date: 2013-06-05 12:00:00
order: 7
---

# Selecting the version
One of the important questions was which version of MINIX to work on. It would have been much easier to implement immediate files in MINIX 3.1(book version) with only MFS, but we were unable to setup the networking environment for it. Also, our primary aim was to understand the VFS of MINIX. Owing to the above reasons, we had to look for other versions of MINIX. We were able to install MINIX 3.2.1 properly and work on it. With the inclusion of VFS and more functionalities, the complexity of the code increased tremendously from 3.1 to 3.2.1. If the aim was only to implement immediate files , the advise would be to go with MINIX 3.1.

# Installation and Networking

* A considerable amount of time was spent on the installation and setting up of MINIX 3 in a Virtual Machine. The major issue was selecting the appropriate software to run it on(Qemu , Virtual Box, etc.).  
* We found that Qemu completely crashes reporting an error after a few steps of the Minix installation proccess. An error was filed on this behalf [Qemu crashes while installing MINIX 3](https://bbs.archlinux.org/viewtopic.php?id=172296).
* The installation went fine in Virtual Box, but the setting up part was a bit tricky. We had to install Openssh server for the networking between the host OS and the virtual machine. We were unsuccessful due to the restrictions in the college firewall for FTP packets. Upon request, a port was opened and FTP packets were allowed for our IPs and all the required packages were installed.

# Documentation Issues   

Understanding the existing code was a tedious one. There was no proper documentation or support for newbies. We found it hard to get satisfying replies from the mailing list or the MINIX groups. [Balazs Gerofi's Master's Thesis](http://www.minix3.org/theses/gerofi-minix-vfs.pdf) was really helpful in understanding the VFS of MINIX.
