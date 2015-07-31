# os_tiny

# Readme:
## Instruction
- This is an tiny toy OS.
- It include some basic components of OS,such memory,semaphore.

## requirements
- gcc
- qemu-system-i386

## How to use?
1. Download it
2. Cd in the working folder
3. run source2img.sh
4. run qemu `qemu-system-i386 -fda ./output/a_boot2C.img`

## Debugging
1. run `qemu-system-i386 -fda ./output/a_boot2C.img -s -S`
2. run `gdb ./output/myOS.elf`
3. run `target remote :1234`
4. do what you want

## Thanks
^_^