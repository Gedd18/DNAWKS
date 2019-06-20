Set-Variable Grub2Dir "C:\Program Files\grub-2.02-for-windows"

Write-Output $Grub2Dir
#grub-mkimage.exe -d $Grub2Dir/i386-pc -p /Grub2/BIOS -o Core.img -O i386-pc biosdisk part_msdos fat exfat ext2 ntfs normal iso9660 search_fs_file
grub-install.exe --boot-directory=D:\ --target=i386-pc //./PHYSICALDRIVE1

#mount the vhd disk by powwershell command

qemu-system-x86_64.exe -drive media=disk,file=\\.\PhysicalDrive2,format=raw


