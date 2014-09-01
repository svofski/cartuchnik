#ifndef PACMAN_H
#define PACMAN_H

/*
 * A pacman Sprite is defined here. It has five different pictures.
 *
 * It uses these five pictures to built an animation of the length 8.
 *
 * It was drawn using the 'veccy' tool!
 * (Which still generates only assembly 'DB' statements, but that
 * is not a real problem... use copy and paste :-).
 */

#define PACMAN_SCALE 10
#define SPRITE_SIZE 25
#define MAX_ANIM 8

const signed char pac1[] = {
                            15,
                            -2 * SPRITE_SIZE,  0 * SPRITE_SIZE,
                            -2 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             0 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                             2 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                             2 * SPRITE_SIZE,  0 * SPRITE_SIZE,
                             2 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                             1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                             1 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                             0 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                            -2 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                           };
const signed char pac2[] = {
                            16,
                            -2 * SPRITE_SIZE,  0 * SPRITE_SIZE,
                            -2 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             0 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                             2 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                             1 * SPRITE_SIZE, -5 * SPRITE_SIZE,
                             1 * SPRITE_SIZE,  5 * SPRITE_SIZE,
                             2 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                             1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                             1 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                             0 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                            -2 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                           };
const signed char pac3[] = {
                            16,
                            -2 * SPRITE_SIZE,  0 * SPRITE_SIZE,
                            -2 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             0 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                             1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                             2 * SPRITE_SIZE, -5 * SPRITE_SIZE,
                             2 * SPRITE_SIZE,  5 * SPRITE_SIZE,
                             1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                             1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                             1 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                             0 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                            -2 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                           };
const signed char pac4[] = {
                            14,
                            -2 * SPRITE_SIZE,  0 * SPRITE_SIZE,
                            -2 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             0 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                             3 * SPRITE_SIZE, -4 * SPRITE_SIZE,
                             3 * SPRITE_SIZE,  4 * SPRITE_SIZE,
                             1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                             1 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                             0 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                            -2 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                           };
const signed char pac5[] = {
                            12,
                            -2 * SPRITE_SIZE,  0 * SPRITE_SIZE,
                            -2 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             0 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
                             4 * SPRITE_SIZE, -3 * SPRITE_SIZE,
                             4 * SPRITE_SIZE,  3 * SPRITE_SIZE,
                             1 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                             0 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE, -2 * SPRITE_SIZE,
                            -1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                            -2 * SPRITE_SIZE, -1 * SPRITE_SIZE,
                           };

const signed char *pacman[MAX_ANIM] = {
                                 pac1,
                                 pac2,
                                 pac3,
                                 pac4,
                                 pac5,
                                 pac4,
                                 pac3,
                                 pac2
                               };

#endif