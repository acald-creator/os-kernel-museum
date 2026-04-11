# How to port ncurses

config.sub file

```bash
		# A lone config we happen to match not fitting any pattern
		case $field1-$field2 in
			decstation-3100)
				basic_machine=mips-dec
				os=
				;;
			*-*)
				# Second component is usually, but not always the OS
				case $field2 in
					# Prevent following clause from handling this valid os
					sun*os*)
						basic_machine=$field1
						os=$field2
						;;
					# Manufacturers
					dec* | mips* | sequent* | encore* | pc533* | sgi* | sony* \
					| astraeaos* \
					| att* | 7300* | 3300* | delta* | motorola* | sun[234]* \
					| unicom* | ibm* | next | hp | isi* | apollo | altos* \
					| convergent* | ncr* | news | 32* | 3600* | 3100* \
					| hitachi* | c[123]* | convex* | sun | crds | omron* | dg \
					| ultra | tti* | harris | dolphin | highlevel | gould \
					| cbm | ns | masscomp | apple | axis | knuth | cray \
					| microblaze* | sim | cisco \
					| oki | wec | wrs | winbond)
						basic_machine=$field1-$field2
						os=
						;;
					*)
						basic_machine=$field1
						os=$field2
						;;
				esac
			;;
		esac
		;;
	*)
		# Convert single-component short-hands not valid as part of
		# multi-component configurations.
		case $field1 in
			astraeaos)
				basic_machine=i[3-7]86-elf
				os=elf
				;;
```

```bash
CC=$SYSROOT/usr/bin/clang \
CXX=$SYSROOT/usr/bin/clang++ \
./configure --prefix=$SYSROOT/usr \
    --host=x86_64-astraeaos-elf \
    --build=x86_64-astraeaos-elf \
    --mandir=/mnt/astraeaos/usr/share/man \
    --with-manpage-format=normal \
    --without-debug \
    --without-ada \
    --without-normal \
    --enable-widec

	make && make install
```