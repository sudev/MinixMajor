# Introduction

Different kinds of people use computers now than sev­eral decades ago, but operating systems have not fully kept pace with this change. Early users expected the computer to crash often; reboots came as naturally as waiting for the neighborhood TV re­pairman to come replace the picture tube on their home TVs. All that has changed and operating systems need to change with the times.Modern computer users are from a broad cross-section of society. Most of them have a set of mental expectations that we call The TV model.   
It goes like this:   
* You buy the device.   
* You turn it on.   
* It works perfectly for the next 10 years.     
Most electronic devices fit this model well, the one exception being the personal computer. In addition to mind-numbing complexity (e.g., even networking experts have trouble configuring a wireless base station, despite the 500-page manual), they are prone to crashes and blue screens of death, issues unheard of with other electronic devices.     

Most modern computer users want their systems to work all the time and never crash, ever. In engineering terms, this requires a mean time to failure (MTTF) appre­ciably longer than the expected lifetime of the computer.The average user virtually never complains that the com­puter itself is too slow (e.g., it cannot update a spread­sheet fast enough), although complaints about the speed of the Web are common. Over time, the relationship be­tween speed and reliability has reversed. Most users now consider the reliability of the computer to be far more im­portant than its speed, the reverse of 40 years ago.     
 
Yet operating system reliability is still poor. To make the research challenge more explicit, consider a device driver that contains a fatal bug such as a store through an invalid pointer or an infinite loop. In commodity op­erating systems, when this bug is triggered, it crashes or hangs the entire system because the buggy code is run­ning in kernel mode. All user programs that were run­ning at the time the bug struck are killed, all user work is lost, and all FTP, Web, and e-mail transfers are abruptly aborted.   

Studies have shown that software contains about 6-16 bugs per 1000 lines of code, it is simply infeasible to get all code to be correct. Therefore, the MINIX 3 was designed in such a way that certain major faults are properly isolated, defects are detected, and failing components can be replaced on the fly, often transparent to applications and without user intervention or loss of data or work.


