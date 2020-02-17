# README

### Set up the system for xv6 use

- Install Ubuntu on windows
    - Enable the windows subsystem for linux (This removes the need for us to use VirtualBox to run a new linux subsystem)
- Check for updates on Ubuntu and download them using:

     `sudo apt update`

- Install gcc (C compiler), g++ and make on the Ubuntu terminal by using :

    `sudo apt install build-essential`

- Install qemu using:

    `sudo apt install qemu`

- Git clone the xv6 file from mit-pdos file by running:

    `git clone git://github.com/mit-pdos/xv6-public.git`

- Navigate into the xv6 folder where all the c files exist.

### Start xv6

- Compile xv6 by running: `make`
- Run the qemu emulator by running: `make qemu-nox`

### Restarting xv6 after making changes to code

- After saving the files you made changes to, run `make clean` on the main xv6 directory to delete all the .o and .h files created
- Re-compile using `make` or simply run `make qemu-nox`

---

### Adding a whatIf system call to xv6

- Create a new whatIf.c file with all its functionality to the xv6 directory
- Make the following changes to Makefile
    - Add _whatIf\ to the UPROGS as follows

            UPROGS=\
            	_cat\
            	_echo\
            	_forktest\
            	_grep\
            	_init\
            	_kill\
            	_ln\
            	_ls\
            	_mkdir\
            	_rm\
            	_sh\
            	_stressfs\
            	_usertests\
            	_wc\
            	_zombie\
            	_whatIf\

    - Add whatIf.c to the EXTRA as follows

            EXTRA=\
            	mkfs.c ulib.c user.h cat.c echo.c forktest.c grep.c kill.c\
            	ln.c ls.c mkdir.c rm.c stressfs.c usertests.c wc.c zombie.c\
            	printf.c umalloc.c whatIf.c\
            	README sample.txt dot-bochsrc *.pl toc.* runoff runoff1 runoff.list\
            	.gdbinit.tmpl gdbutil\

- Restart xv6 with following changes as specified above

### Adding a text file to xv6 (Use in whatIf)

- Simple way: Look for instances of README and add a sample text file next to those places in the following way
    - fs.img section

            fs.img: mkfs README sample.txt $(UPROGS)
            ./mkfs fs.img README sample.txt $(UPROGS)

    - PRINT section

            PRINT = runoff.list runoff.spec README sample.txt toc.hdr toc.ftr $(FILES)

    - EXTRA section

            EXTRA=\
            mkfs.c ulib.c user.h cat.c echo.c forktest.c grep.c kill.c\
            ln.c ls.c mkdir.c rm.c stressfs.c usertests.c wc.c zombie.c\
            printf.c umalloc.c\
            README sample.txt dot-bochsrc *.pl toc.* runoff runoff1 runoff.list\
            .gdbinit.tmpl gdbutil\

---

### Running xv6 commands

- nonohup: Simple run `nonohup cmd1`
    - Example: `nonohup echo a`, `echo a; nonohup echo b; echo c`
- whatIf
    - Run `whatIf` and press enter to write in your own value that you can see in parent.txt and child.txt
    - Run `whatIf fileName.txt` to specify the file from where parent.txt and child.txt will read from.

### Updated files
- whatIf.c has been added to accomodate for whatIf system call
    - Makefile updated to reflect the whatIf command
    - Makefile updated to add a sample.txt file to test whatIf.c
- `runcmd()` has been updated in sh.c to make it work with nonohup. View the comments in there to understand the implementation
    - Implemented in there to make it easy to look for "nonohup" command.
