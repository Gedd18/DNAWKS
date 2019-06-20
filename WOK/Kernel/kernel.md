# Multiboot kernel project

This project produce a minimal kernel wich is mutliboot compliant.
Building the project produce the kernel.exe file.

###### Test with Qemu
This is the fastest way to test the kernel without installing anything 
````
qemu-system-x86_64.exe --kernel kernel.exe
````
of course it is possible to install the kernel on a hard disk [virtual or physical] with Grub installed.


###### Script to create Grub image

After intalling Grub2 for windows 2.02, you can create a custom image to install it on disk.
````
grub-mkimage.exe -d [Grub2Dir]/i386-pc -p /Grub2/BIOS -o Core.img -O i386-pc biosdisk part_msdos fat exfat ext2 ntfs normal iso9660 search_fs_file
````

Also you can install Grub2 on your usb key or a virtual device.

````
grub-install.exe --boot-directory=D:\ --target=i386-pc //./PHYSICALDRIVE1
````

> Be sure to know exactly wath you are doing using PHYSICALLDRIVE !!
> You can make  damage on your physicall boot disk

To launch grub with physicall or virtual device

````
qemu-system-x86_64.exe -drive media=disk,file=\\.\PhysicalDrive2,format=raw
````s