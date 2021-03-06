#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <Arduino.h>
#include "Panel.h"

// The total number of animation functions
#define NUMBER_OF_ANIMATIONS 13

void animation_1();
void animation_2();
void animation_3();
void animation_4();
void animation_5();
void animation_6();
void animation_7();
void animation_8();
void animation_9();
void animation_10();
void animation_11();
void animation_12();
void animation_13();

// Run one animation, selected by number
void execute_animation(byte number);

// Run one or more random animations
void do_random_animations(byte count);

#endif
