# cartuchnik
Flash Cartridge for Vectrex on LPC1769

Here's a youtube of an early test of Cartuchnik:
http://www.youtube.com/watch?v=1frCw8D-Ybc

And here's the loader menu:
http://www.youtube.com/watch?v=H1Qx4sDnVfg

This is a flash cartridge for Vectrex console. It uses internal flash memory LPC1769 for ROM storage. LPC1769 shows itself
to the host as a mass storage device where ROM files can be copied. There is a loader program that allows selection of
ROM file when Vectrex is first powered up. 64K roms are supported.

The hardware is LPC1769 Expresso board with an add-on board that plugs into the cartridge slot.

The project is very quirky, especially the mass storage part that's based on LPC port of LUFA, which was
extremely disappointingly buggy at the time of Cartuchnik development. However it works and can be used as a development
cartridge if you don't mind some messing around.

 * [kicad](kicad/) contains design files for LPC1769 Expresso board "shield" that plugs directly into the Vectrex.
 * [loader](loader/) is the loader code that's executed on the Vectrex and provides interface for ROM selection
 * [firmware](firmware/) LPC1769 code 

The loader should be compiled using [https://github.com/bcd/gcc]. I had trouble compiling the compiler on my system and here's a fork that builds on my machine: [https://github.com/svofski/gcc]
 
