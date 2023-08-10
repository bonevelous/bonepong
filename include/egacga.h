/****************************************************************************
    This file is a part of SDL Pong.
    
    Copyright (C) 2021  Matt Gobbi

    SDL Pong is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SDL Pong is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SDL Pong.  If not, see <https://www.gnu.org/licenses/>.
*****************************************************************************/
#ifndef EGACGA_H
#define EGACGA_H

//Enum for CGA colors.
typedef enum 
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGREY,
	GREY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE,
	ALPHA //A safeguard characer.
} EGACOLORS;

//Enum for nodes.
typedef struct
{
	double r;
	double g;
	double b;
	double a;
} RGBCOLORS;

RGBCOLORS PULLCOLOR(EGACOLORS GETCOLORS)
{
	RGBCOLORS SETCOLORS;

	switch (GETCOLORS)
	{
		case BLACK:
		SETCOLORS.r = 0;
		SETCOLORS.g = 0;
		SETCOLORS.b = 0;
		SETCOLORS.a = 255;
		break;
		case BLUE:
		SETCOLORS.r = 0;
		SETCOLORS.g = 0;
		SETCOLORS.b = 170;
		SETCOLORS.a = 255;
		break;
		case GREEN:
		SETCOLORS.r = 0;
		SETCOLORS.g = 170;
		SETCOLORS.b = 0;
		SETCOLORS.a = 255;
		break;
		case CYAN:
		SETCOLORS.r = 0;
		SETCOLORS.g = 170;
		SETCOLORS.b = 170;
		SETCOLORS.a = 255;
		break;
		case RED:
		SETCOLORS.r = 170;
		SETCOLORS.g = 0;
		SETCOLORS.b = 0;
		SETCOLORS.a = 255;
		break;
		case MAGENTA:
		SETCOLORS.r = 170;
		SETCOLORS.g = 0;
		SETCOLORS.b = 170;
		SETCOLORS.a = 255;
		break;
		case BROWN:
		SETCOLORS.r = 170;
		SETCOLORS.g = 85;
		SETCOLORS.b = 0;
		SETCOLORS.a = 255;
		break;
		case LIGHTGREY:
		SETCOLORS.r = 170;
		SETCOLORS.g = 170;
		SETCOLORS.b = 170;
		SETCOLORS.a = 255;
		break;
		case GREY:
		SETCOLORS.r = 85;
		SETCOLORS.g = 85;
		SETCOLORS.b = 85;
		SETCOLORS.a = 255;
		break;
		case LIGHTBLUE:
		SETCOLORS.r = 85;
		SETCOLORS.g = 85;
		SETCOLORS.b = 255;
		SETCOLORS.a = 255;
		break;
		case LIGHTGREEN:
		SETCOLORS.r = 85;
		SETCOLORS.g = 255;
		SETCOLORS.b = 85;
		SETCOLORS.a = 255;
		break;
		case LIGHTCYAN:
		SETCOLORS.r = 85;
		SETCOLORS.g = 255;
		SETCOLORS.b = 255;
		SETCOLORS.a = 255;
		break;
		case LIGHTRED:
		SETCOLORS.r = 255;
		SETCOLORS.g = 85;
		SETCOLORS.b = 85;
		SETCOLORS.a = 255;
		break;
		case LIGHTMAGENTA:
		SETCOLORS.r = 255;
		SETCOLORS.g = 85;
		SETCOLORS.b = 255;
		SETCOLORS.a = 255;
		break;
		case YELLOW:
		SETCOLORS.r = 255;
		SETCOLORS.g = 255;
		SETCOLORS.b = 85;
		SETCOLORS.a = 255;
		break;
		case WHITE:
		SETCOLORS.r = 255;
		SETCOLORS.g = 255;
		SETCOLORS.b = 255;
		SETCOLORS.a = 255;
		break;
		default:
		SETCOLORS.r = 255;
		SETCOLORS.g = 128;
		SETCOLORS.b = 0;
		SETCOLORS.a = 0;
		break;
	}
	return SETCOLORS;
}

#endif //EGACGA_H
