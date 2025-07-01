// ASCII.h file he provides, I added some #define
#pragma once
#define ESC "\033[" // starts
#define LIGHT_BLUE_BKG "106" // controls the background color needs ";" after it
#define PURPLE_TXT "35" // MOUNTAINS
#define RESET "\033[m" // ends
#define BROWN_TXT "33" // PATH
#define LIGHT_BROWN_BKG "48;5;94" // ANSI code for light brown background(Mountains)
#define RED_TXT "31" // MOUNTAIN
#define LIGHT_GREEN_BKG "48;5;82" // ANSI code for light green background(PRAIRIES)
#define DARK_GREEN_TXT "32" // ANSI code for dark green text(PRAIRIES)
#define GREEN_TXT "42" // FORESTS
#define WHITE_TXT "29" // ROADS
#define BLUE_TXT "44" // WATER
#define LIGHT_SCARLET_RED_BKG "101" // background

#include <iostream>
using namespace std;

// tile template
// font: 30-37
// back: 40-37
// m goes after the back which background color, so it's not backm but back and m is needed to end it
// extern void DisplayName()
// {
// cout << "\033[font; backm(characterToBeDisplayed)\033[m" << endl;
// cout << "\033[font; backm(characterToBeDisplayed)\033[m" << endl;
// }

// background_color;Text_colorm output
// font: 30-37
// back: 40-37

extern void Example1();

extern void DisplayCharacter();

extern void DisplayForest();

extern void DisplayMountain();

extern void DisplayPrairie();

extern void DisplayRoad();

extern void DisplayWater();

extern void DisplayWall();

extern void print_8_colors();

extern void print_256_colors_txt();

extern void print_256_colors_background();