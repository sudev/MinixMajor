---
layout: page
title: "Tricks of the trade"
category: doc
date: 2013-06-05 12:00:00
order: 6
---

##Installing Minix
You'll start this project by first installing the latest version of Minix, Minix 3.2.1. You can download the install CDROM image as an ISO file from the Minix project [webpage](http://www.minix3.org/download/). You will need to first decide how you will want to install Minix, on physical hardware (a real machine), or on a simulator/virtual machine such as Qemu, Virtual Box, Bochs, or VMWare. While a native install runs a bit faster, a VM install has the advantage that you can easily restart or reset machines, while not worrying about instability in your Minix code affecting the stability of your machine.

We didn't have much success using Qemu [(especially running Qemu over Arch Linux ended up in qemu crash)](https://bbs.archlinux.org/viewtopic.php?id=172296). And we couldn't actually run Minix over Qemu with a network between the host machine and Minix. 

One of the other alternatives to Qemu is VirtualBox. We were able to install and run Minix 3.2.1 using VirtualBox *( VirtualBox 4.3 )*. We did make lot of changes from Minix 3 official documentation [Running on VirtualBox](http://wiki.minix3.org/UsersGuide/RunningOnVirtualBox). Please see our reference section for detailed information on installing [Running Minix 3 on VirtualBox](../ref/install.html). We recommend you to use VirtualBox even we never tried to install Minix 3 over VMWare or Bochs.

##Preparing a Minix Development Environment

Once you have installed Minix, there are a few things that you want to do to make the system more usable. The first is to get the network to work. The way how networking is set up depends on your target platform. For ViritualBox it was pretty straight forward network configurations which didn'trequire many additional steps after the Minix 3 installation. 

In order to establish a ssh connection between host machine and Minix 3 you will have to have a openssh server running in both host and Minix 3. Installing openssh server in Minix is a bit tricky especially when you are sitting behind a network with firewall restrictions on ftp. Please see reference section on [how to establish a ssh connection](../ref/install.html#enable-ssh-with-host-machine) for more details.
