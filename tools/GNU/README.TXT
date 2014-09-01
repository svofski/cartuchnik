This directory contains the sources for the Vectrex C compiler.
(actually a gcc version)

And the tools used to generate binaries from the assembler source.
As there are a Assembler, Linker, Archiver, S19-to-Binary-Converter.

These tools are pretty Unix'ish.
I compiled them under Windows98 in a DOS shell using DJGPP Version 2.81
(well that's actually the gcc version).

You need most of the available GNU tools in order to compile the compiler,
like autoconf, file utils, make, yacc, bison flex...
Once you get to a pretty unix'ish environment under windows... compiling
should not be a problem anymore.
Oh... and you'll need the compiler sources, I worked with (have a guess)
version 2.81 of the gcc compiler.
Copy the sources from here to where the compiler is, and overwrite the
configure and config.sub files.

To Configure the compiler (under DOS) for a m6809 vectrex crosscompiler,
type (after installing a bash and 1000 other tools):

sh configure --target=m6809-gcs-vectrex --host=i586-pc-msdosdjgpp --build=i586-pc-msdosdjgpp

This will generate a Makefile.
Type make and wait till the compiler prints some errors (in the F77 section,
unless you specified some language restrictions, section).
The CC1.EXE is the compiler for C you'll probably want.
(I never tried the CPLUS, wonder if it works -> probably though...)

For the other tools... just MAKE them...

The compiler seems to work allright, there might sometimes be an
asm vialoation... I explained it somewhere in the demos...


Chris
