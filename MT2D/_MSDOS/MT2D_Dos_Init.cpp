// MT2D Created By Lucas Zimerman Fraulob
// This is the core of MT2D engine, with only this .cpp you can do everything
// This file is related to almost all MT2D video interface, like draw, clear and update.
#if defined(__MSDOS__)
#include "MT2D/MT2D_Terminal_Define.h"

#include <dos.h>
#include "../MT2D.h"
#include <string.h>
#include <stdio.h>

unsigned char WINDOW1[MAX_VER + 1][MAX_HOR];
unsigned char WINDOW2[MAX_VER + 1][MAX_HOR];


bool MT2D_Dos_Init() {// Return: true - it started without any kind of problem, false : there were a problem when MT2D was started
	bool output = true;
	return output;
}
#endif