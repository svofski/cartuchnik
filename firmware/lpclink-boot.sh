. ./lpclink-path.sh
dfu-util -d 0x471:0xdf55 -c 0 -t 2048 -R -D $LPCXPRESSO/LPCXpressoWIN.enc
