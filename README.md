lrzip-next - Long Range ZIP
======================

**This is the whats-next branch of `lrzip-next`. Here new features will be tested.**

## NEW: LZMA SDK 21.06 (Feb 2022)

Tag v0.8.10
This branch **lzma-21.06** is now the default branch.
**Encrypted archives from any earlier version will not be compatible or readable.**

Many new changes, not in the main branch, including:
* latest LZMA and ZPAQ libraries (**ABI Compatible** with earlier versions. No need to re-compress files).
* more helpful usage messages.
* filters for x86 and other processors, and delta.
* ASM LZMA DeCompressor (up to 40% faster. x86_64 only).
* ASM LZMA Match Finder (x86_64 only).
* ability to set rzip pre-compression level independently of compression level.
* variable compressibility threshold testing.
* ability to set specific LZMA Dictionary Size.
* improved info reporting, column alignment, improved formatting, thousands separator.
* improved memory management favoring large chunk and dictionary sizes over maxmizing number of threads.
* improved ZPAQ processing by analyzing data prior to sending to compressor.
* many bug fixes including validating a file prior to decompression (prevents corrupt file decompression before it starts!).
* use of git describe to present current version without changing configure.ac.
* lz4 Threshold testing (replaces lzo).
* File info `lrzip-next -i` will now fetch info from encrypted files.
* `lrzip-next -i` will not print percent info when file size is not known.
* `lrzip-next -i` will format data with thousands separators.
* Substitute libgcrypt functions for separate sources for **md5** and **sha512** hash functions, and **aes 128 bit** encryption.\
(This will allow for future bug fixes and possibly using different encryption methods through a standard library.)
* SCRYPT (Bitcoin style) Key Derivation.
* lzma match finder x86_64 Assembler module.
* ZPAQ 7.15 library (Levels 3-5, random and text modes only. Binary mode (e8e9) covered by lzma-next filters).
* ZPAQ compression settings stored in magic header. Will show in INFO output.
* ZPAQ Compression Block Size can be independently set from 2MB to 2GB.
* 13 Hash options (see CURRENT_HASHES)
* 2 Encryption options (see CURRENT_ENCMETHODS)
* Configurable with `lrzip.conf` file
* Configurable LOCALE settings via lrzip.conf
* Update autofoo to remove obsolete macros
* REMOVE 32-BIT Architecture support

(See original README for more historical info)

### Download and Build
`$ git clone https://github.com/pete4abw/lrzip-next`\
or if you desire to also download the **lrzip-fe** front end\
`$ git clone --recurse-submodules https://github.com/pete4abw/lrzip-next`

If you forget use --recurse-submodules and want to download lrzip-fe separately, use these commands:
```
$ git clone https://github.com/pete4abw/lrzip-next
$ cd lrzip-next
$ git submodule update --init (to download lrzip-fe)
```
**NEW**! Tarballs will now compile from version 0.7.44 onward. gitdesc.sh has been made
more intelligent! Recommend downloading from master, not from past tags/releases.

**NEW**! If you just want to try `lrzip-next`, download the static binaries. No compilation
necessary. [Visit this link to download](https://peterhyman.com/download/lrzip-next/).

Verify file with gnupg key 0x467FBF7D.

### Build
```
cd lrzip-next
$ ./autogen.sh
$ ./configure [options] (see configure --help for all options)
```
If any required libraries or compilers are missing, **configure** will report and stop.
```
$ make [-j#] (for parallel make where # is typically number of processors)
$ make install (as root)
```

### How it Works
**lrzip-next** applies a two-step process (optionally three-step process if filters are used)
and reads file or STDIN input, passes it to the **rzip** pre-processor (and optional filter).
The rzip pre-processor applies long-range redundancy reduction and then passes the streams of
data to a back-end compressor. **lrzip--next** will, by default, test each stream with a *compressibility*
test using **lz4** prior to compression. The selected back-end compressor works on smaller data
sets and ignore streams of data that may not compress well. The end result is significantly
faster compression than standalone compressors and much faster decompression.

**lrzip-next**'s compressors are:
* lzma (default)
* gzip
* bzip2
* lzo
* zpaq
* rzip (pre-processed only)

**lrzip-next**'s memory management scheme permits maximum use of system ram to pre-process files and then compress them.

### Usage and Integration
See Discussions and Wiki for info.

### Thanks
Con Kolivas - the creator of `lrzip`\
Others listed in original README file.

#### README Authors

For **lrzip-next**\
Peter Hyman (pete4abw on Guthub) <pete@peterhyman.com>\
Sun, 04 Jan 2009, README\
Mon, 28 Apr 2021: README.md

For **lrzip**\
Con Kolivas (ckolivas` on GitHub) <kernel@kolivas.org>\
Fri, 10 June 2016: README
