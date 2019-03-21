# Multiboot kernel project

This project produce a minimal kernel wich is mutliboot compliant.
Building the project produce the kernel.exe file.

###### Test with Qemu
This is the fastest way to test the kernel without installing anything 
````
qemu-system-x86_64.exe --kernel kernel.exe
````
of course it is possible to install the kernel on a hard disk [virtual or physical] with Grub installed.


