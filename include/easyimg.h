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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#ifndef EASYIMG_H
#define EASYIMG_H

typedef struct{
	int fontW;
	int fontH;
	int offsetX;
	int offsetY;
	int padX;
	int padY;
} asciiChars;

/***********
Code for easy
biymap fonts
***********/

void takeScreenShot(SDL_Window* mainWin, SDL_Renderer* mainRen, char *filename)
{
	const Uint32 format = SDL_PIXELFORMAT_ABGR8888; //You might have to modify the pixel format for the program.
	int screenWidth;
	int screenHeight;
	SDL_GetWindowSize(mainWin, &screenWidth, &screenHeight);

	SDL_Surface *screenshotSurf = SDL_CreateRGBSurfaceWithFormat(0, screenWidth, screenHeight, 32, SDL_PIXELFORMAT_ABGR8888);
	SDL_RenderReadPixels(mainRen, NULL, format, screenshotSurf->pixels, screenshotSurf->pitch);
	if (screenshotSurf != NULL)
	{
		IMG_SavePNG(screenshotSurf, filename);
		SDL_FreeSurface(screenshotSurf);
	}
}

SDL_Texture* createTexture(char* fileName, SDL_Renderer *getRend, SDL_Rect *textRect)
{
	SDL_Texture* mTexture = NULL;
	SDL_Surface* tempSurf = NULL;
	tempSurf = IMG_Load(fileName); //SDL_Image loads an image.
	if (tempSurf == NULL)
	{
		printf("An error occured loading the image to a surface, and it will not be displayed: %s\n", IMG_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(getRend, tempSurf);
		if (mTexture == NULL)
		{
			printf("An error occured loading the image to a texture, and it will not be displayed: %s\n", IMG_GetError());
		}
		else
		{
			textRect->w = tempSurf->w;
			textRect->h = tempSurf->h;
		}
	}
	SDL_FreeSurface(tempSurf);
	tempSurf = NULL;
	return mTexture;
}

//The clip integers in this function allow me to declare the SDL_Rects wherever in my code I'm ready, rather than forcing me to define them before.
//This is useful for allowing me to blit identical clip sizes to multiple rects at once.
SDL_Texture* clipTexture(char* fileName, SDL_Renderer *getRend, SDL_Rect *textRect, SDL_Rect *placRect, int clipW, int clipH)
{
	SDL_Texture* mTexture = NULL;
	SDL_Surface* tempSurf = NULL;
	tempSurf = IMG_Load(fileName); //SDL_Image loads an image.
	if (tempSurf == NULL)
	{
		printf("An error occured loading the image to a surface, and it will not be displayed: %s\n", IMG_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(getRend, tempSurf);
		if (mTexture == NULL)
		{
			printf("An error occured loading the image to a texture, and it will not be displayed: %s\n", IMG_GetError());
		}
		else
		{
			textRect->w = clipW;
			textRect->h = clipH;
			placRect->w = clipW;
			placRect->h = clipH;
		}
	}
	SDL_FreeSurface(tempSurf);
	tempSurf = NULL;
	return mTexture;
}

SDL_Texture* keyTexture(char* fileName, SDL_Renderer *getRend, SDL_Rect *textRect, SDL_Rect *placRect, int clipW, int clipH, int r, int g, int b)
{
	SDL_Texture* mTexture = NULL;
	SDL_Surface* tempSurf = NULL;
	tempSurf = IMG_Load(fileName); //SDL_Image loads an image.
	if (tempSurf == NULL)
	{
		printf("An error occured loading the image to a surface, and it will not be displayed: %s\n", IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(tempSurf, SDL_TRUE, SDL_MapRGB(tempSurf->format, r, g, b));
		mTexture = SDL_CreateTextureFromSurface(getRend, tempSurf);
		if (mTexture == NULL)
		{
			printf("An error occured loading the image to a texture, and it will not be displayed: %s\n", IMG_GetError());
		}
		else
		{
			textRect->w = clipW;
			textRect->h = clipH;
			placRect->w = clipW;
			placRect->h = clipH;
		}
	}
	SDL_FreeSurface(tempSurf);
	tempSurf = NULL;
	return mTexture;
}

#endif
