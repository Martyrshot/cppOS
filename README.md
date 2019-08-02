# funOS
A project to practice and develop operating system ideas.

## Prereqs:
Make sure the qemu is installed! I am developing and testing using the version from homebrew. I also use a toolchain provided by the bootloader author for compiling 32bit x86.
`$ brew install qemu`

`$ brew install nasm`

`$ brew tap zanders3/homebrew-gcc_cross_compilers`

`$ brew install --debug i386-elf-gcc`

## How to run:
`$ make`

That's it!


## Sources
The bootloader was created following this guide: http://3zanders.co.uk/2017/10/13/writing-a-bootloader/
