#include <stdio.h>
#include <inttypes.h>

const int8_t starpath[] = {
   255, -10,-10,    
   255,  10,-10,    
   255,  10, 10,
//   255, -10, 10,
//   255, -10,-10, 
   1};

int8_t starrot[sizeof(starpath)];

void animate_star(uint8_t frame) {
    frame = 0;
    
    int16_t last_x = 0, last_y = 0;

    for (int i = 0; i < sizeof(starpath)/sizeof(starpath[0]) - 3; i += 3) {
        starrot[i] = starpath[i];
        int16_t x = starpath[i+1];
        int16_t y = starpath[i+2];
        //irotate0(&x, &y, frame);
        starrot[i+1] = y - last_y;
        starrot[i+2] = x - last_x;
        last_y = y;
        last_x = x;

        printf("%d %d %d\n", starrot[i], starrot[i+1], starrot[i+2]);
    }
}

int main() {

    animate_star(0);

    return 0;
}
