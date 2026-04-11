# How to port pkgconf


-- Content of config.sub file
```bash
### Let's recognize common machines as not being operating systems so
### that things like config.sub decstation-3100 work.  We also
### recognize some manufacturers as not being operating systems, so we
### can provide default operating systems below.
case $os in
	-sun*os*)
		# Prevent following clause from handling this invalid input.
		;;
	-dec* | -mips* | -sequent* | -encore* | -pc532* | -sgi* | -sony* | \
	-astraeaos* | \
	-att* | -7300* | -3300* | -delta* | -motorola* | -sun[234]* | \
	-unicom* | -ibm* | -next | -hp | -isi* | -apollo | -altos* | \
	-convergent* | -ncr* | -news | -32* | -3600* | -3100* | -hitachi* |\
	-c[123]* | -convex* | -sun | -crds | -omron* | -dg | -ultra | -tti* | \
	-harris | -dolphin | -highlevel | -gould | -cbm | -ns | -masscomp | \
	-apple | -axis | -knuth | -cray | -microblaze*)
---------------------------------------------------
	# Recognize the basic CPU types without company name, with glob match.
	xtensa*)
		basic_machine=$basic_machine-unknown
		;;
	# Recognize the various machine names and aliases which stand
	# for a CPU type and a company and sometimes even an OS.
	astraeaos)
		basic_machine=i[3-7]86-elf
		os=-elf
		;;
	386bsd)
		basic_machine=i386-pc
		os=-bsd
		;;
```

```bash
./autogen.sh # add the missing m4 if needed to Makefile.am

ACLOCAL_AMFLAGS = -I m4

CC=/mnt/astraeaos/usr/bin/clang \
    ./configure \
        --build=x86_64-astraeaos-elf \
        --host=x86_64-astraeaos-elf \
        --prefix=/mnt/astraeaos/usr \
        --with-system-libdir=/mnt/astraeaos/lib:/mnt/astraeaos/usr/lib \
        --with-system-includedir=/mnt/astraeaos/usr/include

make && make install
```