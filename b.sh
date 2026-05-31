rm -rf build
mkdir build && cd build
cmake ..
make
cd ..

cp build/dtos_kernel.elf iso/boot/

xorriso -as mkisofs -b limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label iso -o dtOS.iso

./limine_bin/limine bios-install dtOS.iso
