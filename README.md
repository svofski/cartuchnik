# cartuchnik
Flash Cartridge for Vectrex on LPC1769

This is a flash cartridge for Vectrex console. It uses internal flash memory LPC1769 for ROM storage. LPC1769 shows itself
to the host as a mass storage device where ROM files can be copied. There is a loader program that allows selection of
ROM file when Vectrex is first powered up. 64K roms are supported.

The project is very quirky, especially the mass storage part that's based on LPC port of LUFA, which was
extremely disappointingly buggy at the time of Cartuchnik development. However it works and can be used as a development
cartridge if you don't mind some messing around.
