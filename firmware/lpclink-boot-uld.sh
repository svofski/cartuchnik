export LPCXPRESSO=/Applications/lpcxpresso_5.0.12_1041/lpcxpresso/bin
PATH=$PATH:$LPCXPRESSO
dfu-util -d 0x471:0xdf55 -c 0 -t 2048 -R -D $LPCXPRESSO/LPCXpressoWIN.enc
