# onee-chan

This is a very silly project that aims to emulate 8086 on Z80.

![alt text](https://github.com/ninacarrot/bin/scr.png "Screenshot of FUSE running CP/M running 8086 codegolf")


As Z80 is somewhat older than 8086, I decided to call it "Big Sis". Originally, the idea was to run amazing 8086tiny - but the code of 8086tiny uses so many macroses that neither sdcc nor z88dk could handle it. After multiple failed attempts to patch 8086tiny, I decided to switch the core to a different emulator.

The next plausible candidate was fake86's core. And it (kind of) worked!

# what did I do

First things first; fake86 core with default settings doesn't compile for Z80 because the binary is too big. Cutting off some bits here and there, and replacing macroses with functions allowed the emulator to fit into 36kB.

As you can imagine, 8086 normally needs more memory than we have on Z80. Instead of implementing machine-specific paging, I implemented a very simple and slow pagefile RAM implementation. The file called "RAM" is loaded from current floppy and used for both loading the program and storing the data. Note that for convenience IP=0 at start.

The pagefile isn't as slow as I expected: z88dk's default stdio library caches 128 byte blocks when reading/writing. I had no issues with reading the file, but I discovered that "rb+" file mode caused all writes to fail on CP/M, so I had to just use "r+".

The next challenge was to make the 20-bit address space work. Fake86's code reasonably assumed that INT is going to be at least 32 bit long. I mean, WHO IN THE RIGHT MIND is going to compile Fake86 for an 8-bit target computer? A few edits were needed to fix the types of variables and constants. I probably missed some, as I noticed that benchmarks aren't working as expected (see the test line with Fibonacci numbers).

Finally, the screen implementation is a lazy vt52 for CP/M compatible with "emulate 8086" codegolf. It was fun to debug, as the behaviour is different in zxcc emulator running under VT100 and the real CP/M 3. I commented out vt100 line, if you're interested.

The emulator is capable of running "emulate 8086" codegolf with a few mistakes, but it actually supports segment registers and BCD and stuff. Coolio, right?

# what else could be done

Bugs aside, emulator lacks any hardware support. It shouldn't be impossible to emulate a 5.25 floppy and a XT BIOS, but you probably will need two floppy drives for that.

The screen output is limited to 64x25, but you can change the constants if your computer supports bigger console.

Performance-wise, there are at least two things that probably could improve things significantly (but not enough to make it a comfortable experience). First, it is possible to implement some smart caching that would reduce disk operations. Second, the 32-bit arithmetics isn't actually needed there. With clever patching, the getea()/modregrm() functions could just generate bank+offset variables, reducing the amount of maths needed per operation. It would also allow mapping part of the memory to memory banks.

Overall, it took over 7 minutes to run a simple test that would take no time on a real 8086. Very slow. What did you expect? If your z80 is overclocked, you might be able to get something useful out of it, but I personally see no point in spending 2x more time on this project to just be able to boot into an unusable PC-DOS 2 shell.
