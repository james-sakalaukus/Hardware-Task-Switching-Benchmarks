all:
	@echo -n "\nBuilding kernel"
	@nasm -f elf -o loader.o loader.s
	@echo -n "."
	@nasm -f elf -o gdtS.o gdt.S
	@echo -n "."
	@gcc -o clib.o -c clib.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include
	@echo -n "."
	@gcc -o screen.o -c screen.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include
	@echo -n "."
	@gcc -o gdt.o -c gdt.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include
	@echo -n "."
	@gcc -o kernel.o -c kernel.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include
	@echo -n "."
	@ld -T linker.ld -o kernel.bin loader.o gdt.o gdtS.o screen.o clib.o kernel.o
	@echo "done!\n"
clean:
	@rm *.o 2> /dev/null
	@rm kernel.bin
install:
	@echo -n "\nInstalling."
	@cp ./kernel.bin /boot/
	@echo ".done!\n"
