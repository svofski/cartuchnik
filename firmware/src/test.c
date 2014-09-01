unsigned int test(unsigned int x) {
    return x & 0x38000;
    //return (x & 0xfff) | ((x & 0x3800)>>3);
}
