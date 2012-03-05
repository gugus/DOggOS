#--
# Creer une image de disquette bootable
# avec bochs / qemu et grub
#--

dd if=/dev/zero of=floppyA bs=1024 count=1440
mkfs floppyA


mkdir /mnt/loop
mount -o loop -t ext2 floppyA /mnt/loop

mkdir /mnt/loop/grub

cp stage* /mnt/loop/grub

cat > /mnt/loop/grub/menu.lst << EOF
title=DOggOS
root (fd0)
kernel /kernel
boot
EOF

cp kernel /mnt/loop
umount /mnt/loop

grub --device-map=/dev/null << EOF
device (fd0) floppyA
root (fd0)
setup (fd0)
quit
EOF

