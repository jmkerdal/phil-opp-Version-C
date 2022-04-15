rm -r build

mkdir -p build/x86_64
nasm -felf64 src/asm/boot.asm -o build/x86_64/boot.o
nasm -felf64 src/asm/long_mode_init.asm -o build/x86_64/long_mode_init.o
nasm -felf64 src/asm/multiboot_header.asm -o build/x86_64/multiboot_header.o

cc -m64 -masm=intel -c src/main.c -o build/x86_64/main.o -I src/h
cc -m64 -masm=intel -c src/c/tools.c -o build/x86_64/tools.o -I src/h
cc -m64 -masm=intel -c src/c/clavier.c -o build/x86_64/clavier.o -I src/h
cc -m64 -masm=intel -c src/c/vga.c -o build/x86_64/vga.o -I src/h

#ld -n -T src/arch/x86_64/linker.ld -o build/kernel-x86_64.bin patsubst src/arch/x86_64/%.asm, build/arch/x86_64/%.o, wildcard src/arch/x86_64/*.asm

ld -n -T src/link/linker.ld -o build/kernel-x86_64.bin build/x86_64/boot.o \
    build/x86_64/long_mode_init.o build/x86_64/multiboot_header.o \
    build/x86_64/main.o \
    build/x86_64/tools.o build/x86_64/clavier.o build/x86_64/vga.o

mkdir -p build/isofiles/boot/grub
cp build/kernel-x86_64.bin build/isofiles/boot/kernel.bin
cp src/link/grub.cfg build/isofiles/boot/grub
grub-mkrescue -o build/os-x86_64.iso build/isofiles 2> /dev/null
#rm -r build/isofiles

qemu-system-x86_64 -cdrom build/os-x86_64.iso
