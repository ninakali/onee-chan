# onee-chan

This is a ridiculous project that aims to emulate 8086 on Z80.

![alt text](https://github.com/NinaCarrot/onee-chan/blob/main/bin/scr.png "Screenshot of FUSE running CP/M running 8086 codegolf")


Z80 is somewhat older than 8086, so I decided to call it "Big Sis". Initially, the idea was to run amazing 8086tiny - but the code of 8086tiny uses so many macros that neither sdcc nor z88dk could handle it. So, after multiple failed attempts to patch 8086tiny, I decided to switch the core to a different emulator.

The next plausible candidate was fake86's core. And it (kind of) worked!

# what did I do

First things first, fake86 core with default settings doesn't compile for Z80 because the binary is too big. However, cutting off some bits here and there and replacing macros with functions allowed the emulator to fit into 36kB.

As you can imagine, 8086 needs typically more memory than we have on Z80. Therefore, instead of implementing machine-specific paging, I implemented a straightforward and slow pagefile RAM implementation. The file called "RAM" is loaded from the current floppy and used to load the program and store the data. Note that for convenience IP=0 at the start.

The pagefile isn't as slow as I expected: z88dk's default stdio library caches 128-byte blocks when reading/writing. I had no issues reading the file, but I discovered that "rb+" file mode caused all writes to fail on CP/M, so I had to just use "r+".

The next challenge was to make the 20-bit address space work. Fake86's code reasonably assumed that INT is going to be at least 32 bit long. I mean, WHO IN THE RIGHT MIND is going to compile Fake86 for an 8-bit target computer? A few edits were needed to fix the types of variables and constants. I probably missed some, as I noticed that benchmarks aren't working as expected (see the test line with Fibonacci numbers).

Finally, the screen implementation is a lazy vt52 for CP/M compatible with "emulate 8086" codegolf. It was fun to debug, as the behaviour is different in zxcc emulator running under VT100 and the real CP/M 3. I commented out vt100 code, if you're interested.

The emulator can run "emulate 8086" codegolf with a few mistakes, but it actually is more powerful than needed, and supports segment registers and BCD and stuff. Coolio, right?

# what else could be done

Bugs aside, the emulator lacks any hardware support. It shouldn't be impossible to emulate a 5.25 floppy and an XT BIOS, but you probably will need two floppy drives.

The screen output is limited to 64x25, but you can change the constants if your computer supports a bigger console.

Performance-wise, at least two things probably could improve things significantly (but not enough to make it a comfortable experience). First, it is possible to implement some smart caching to reduce disk operations. Second, the 32-bit arithmetics aren't actually needed there. With clever patching, the getea()/modregrm() functions could just generate bank+offset variables, reducing the amount of maths required per operation. It would also allow mapping part of the memory to memory banks.

Overall, it took over 7 minutes to run a simple test that would take no time on a real 8086. Very slow. What did you expect? If your z80 is overclocked, you might be able to get something useful out of it, but I personally see no point in spending 2x more time on this project to just be able to boot into an unusable PC-DOS 2 shell.
