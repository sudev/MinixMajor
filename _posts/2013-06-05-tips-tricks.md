---
layout: page
title: "Tricks of the trade"
category: doc
date: 2013-06-05 12:00:00
order: 6
---

##Installing Minix
Let's start this by first installing the latest version of Minix, Minix 3.2.1. Download the install CDROM image as an ISO file from the Minix project [webpage](http://www.minix3.org/download/). We will need to first decide how we will want to install Minix, on physical hardware (a real machine), or on a simulator/virtual machine such as Qemu, Virtual Box, Bochs, or VMWare. While a native install runs a bit faster, a VM install has the advantage that we can easily restart or reset machines, while not worrying about instability in our Minix code affecting the stability of our machine.

We didn't have much success using Qemu [(especially running Qemu over Arch Linux ended up in qemu crash)](https://bbs.archlinux.org/viewtopic.php?id=172296)and we couldn't actually run Minix over Qemu with a network between the host machine and Minix. 

One of the other alternatives to Qemu is VirtualBox. We were able to install and run Minix 3.2.1 using VirtualBox *( VirtualBox 4.3 )*. We did make lot of changes from Minix 3 official documentation [Running on VirtualBox](http://wiki.minix3.org/UsersGuide/RunningOnVirtualBox). Please see our reference section for detailed information on installing [Running Minix 3 on VirtualBox](../ref/install.html). We recommend you to use VirtualBox even though we never tried to install Minix 3 over VMWare or Bochs.

##Preparing a Minix Development Environment

Once we have installed Minix, there are a few things that we want to do to make the system more usable. The first is to get the network to work. The way how networking is set up depends on our target platform. For ViritualBox it was pretty straight forward network configurations which didn't require many additional steps after the Minix 3 installation. 

In order to establish a ssh connection between host machine and Minix 3 you will have to have a openssh server running in both host and Minix 3. Installing openssh server in Minix is a bit tricky especially when you are sitting behind a network with firewall restrictions on ftp. Please see reference section on [how to establish a ssh connection](../ref/install.html#enable-ssh-with-host-machine) for more details. Make use of scp/rsync/ssh to transfer files to and from host machine and Minix 3. 

VirtualBox has a feature to [share a host folder with virtual machine](https://www.virtualbox.org/manual/ch04.html). Follow the Minix wiki for instructions on [how to setup a shared folder](http://wiki.minix3.org/UsersGuide/RunningOnVirtualBox#Shared_Folders). It's easier to develop on a shared folder in host system than editing source file inside virtual machine. 

Once the network is active, it's recommended to install a few other applications to make our life easier. For example, we might want an editor (such as vim), openssh (to exchange files between Minix and the outside world), or a new shell (such as bash). Some of this might have been installed as part of your basic Minix package. Also, check out the source code of Minix that is located in `/usr/src` and get a feeling for which parts of the OS are located under which directories.

[VirtualBox Snapshots](http://www.virtualbox.org/manual/ch01.html#snapshots) this feature was too usefull for us to version control during development. taking regular snapshots of virtual machine is adviced so that in case if Minix crashes during boot or you get some unexpected error you can always go to previous development stage.

Using a good IDE will help you to track down all the variable and function definition with speed and ease. One way to do this is to use [Minix LXR](http://www.cise.ufl.edu/~cop4600/cgi-bin/lxr/http/blurb.html) and a text editor *(It's possible to track variable definitions in emacs and vim)*. Eclipse *(eclipse + eclipse cdt)* is very easy to understand IDE with feature to find function and variable definitions by a mouse hover/click. 

Links:      
[Rsync](http://ss64.com/bash/rsync.html)     
[Ssh](http://www.openbsd.org/cgi-bin/man.cgi?query=ssh&sektion=1)   
[Eclipse CDT](http://www.eclipse.org/cdt/)
