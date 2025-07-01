// implentation file for ASCII.h
#include "ASCII.h"
#include <iostream>

using namespace std;


// background_color;Text_colorm output
// font: 30-37
// back: 40-37
void Example1()
{
    cout << ESC << LIGHT_BLUE_BKG << ";" << PURPLE_TXT << "m" << "Hello, world!" << RESET;
}

void DisplayCharacter()
{
    cout << "\033[37;41m o \033[m" << endl;
    cout << "\033[37;41m/D\\\033[m" << endl;
}

void DisplayForest()
{
    cout << "\033[31;42m(o)\033[m" << endl;
    cout << "\033[31;42m_#_\033[m" << endl;
}

void DisplayMountain()
{
    cout << "\033[" << RED_TXT << ";" << LIGHT_BROWN_BKG << "m^^^\033[m" << endl;
    cout << "\033[" << RED_TXT << ";" << LIGHT_BROWN_BKG << "m^^^\033[m" << endl;
}

void DisplayPrairie()
{
    cout << "\033[" << DARK_GREEN_TXT << ";" << LIGHT_GREEN_BKG << "m\"\"\033[m" << endl;
    cout << "\033[" << DARK_GREEN_TXT << ";" << LIGHT_GREEN_BKG << "m\"\"\033[m" << endl;
}

void DisplayRoad()
{
    cout << "\033[" << WHITE_TXT << ";" << BROWN_TXT << "m===\033[m" << endl;
    cout << "\033[" << WHITE_TXT << ";" << BROWN_TXT << "m===\033[m" << endl;
}


void DisplayWater()
{
    cout << "\033[37;46m~~~\033[m" << endl;
    cout << "\033[37;46m~~~\033[m" << endl;
}

void DisplayWall()
{
    cout << "\033[33;45m###\033[m" << endl;
    cout << "\033[33;45m###\033[m" << endl;
}

void print_8_colors()
{
    for (int i = 0; i < 108; i++)
    {
        if (i % 9 == 0 && i != 0)
            cout << endl;
        printf("\033[%dm %3d\033[m", i, i);
    }
    cout << endl;
}

void print_256_colors_txt()
{
    cout << "Display 256 colors text" << endl;
    for (int i = 0; i < 256; i++)
    {
        if (i % 16 == 0 && i != 0)
            cout << endl;
        printf("\033[38;5;%dm %3d\033[m", i, i);
    }
    cout << endl;
}

void print_256_colors_background()
{
    cout << "Display 256 colors background" << endl;
    for (int i = 0; i < 256; i++)
    {
        if (i % 16 == 0 && i != 0)
            cout << endl;
        printf("\033[48;5;%dm %3d\033[m", i, i);
    }
    cout << endl;
}