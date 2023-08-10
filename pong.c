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

//Includes.
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_mixer.h>
#include "include/bonemath.h"
//#include "include/easymix.h"
#include "include/egacga.h"
#include "include/easyimg.h"

//Engine variables and data.
int winX = 960;
int winY = 640;
int running = 1;
SDL_Window *mwin;
SDL_Renderer *mren;
//time_t getTime;
int pScore = 0;
int cScore = 0;
int maxScore = 10;
double minY;// = 16;
double maxY;// = (double) winY - minY;

//Defines and constants.
const Uint32 WFLAGS = SDL_INIT_VIDEO;
const char WNAME[] = "SDL Pong!";
const int padlX = 32; //Paddle location in relation to the X axis. This doesn't change in game, so it is a constant.
const double padlS  = 0.75;
const double padlW = 8; //Paddle width.
const double padlH = 64; //Paddle height.
const double goalPost = 16.0;
const Uint32 WMODE = SDL_WINDOW_BORDERLESS;
const double MAXBV = 8;
const double maxBV = 16.0;

//Ball initialization.
double ballS = 8; //While it's unlikely I will need to change the ball size during the game, having the option of doing so is nice, so it's not a constant.
double ballX;// = (double) winX / 2; //The ball always starts in the center of the screen.
double ballY;// = (double) winY / 2;
double ballAccl = 0.75;//0.25;
double ballVX = 0;
double ballVY = 0;
double ballAng = 135; //The ball begins moving towards the player by default.
double compS = 4;

//Font implementation.
int fontW = 16;
int fontH = 24;
int fontPXP = 80;
int fontPYP = 40;
int fontPXC;// = winX - fontPXP;
int fontPYC;// = winY - fontPXY;

//Paddle information.
double playY;// = (double) winY / 2; //Player's initial position.
double compY;// = (double) winY / 2; //Computer's initial position.

SDL_Rect winRect;
SDL_Rect playRect;
SDL_Rect compRect;
SDL_Rect pongB;
SDL_Rect textRectP;
SDL_Texture *fontTextP;
SDL_Rect textLocP;
SDL_Rect textRectC;
SDL_Texture *fontTextC;
SDL_Rect textLocC;

int checkCol(SDL_Rect boxOne, SDL_Rect boxTwo)
{
	int truth = 0;
	if (boxOne.x < boxTwo.x + boxTwo.w && boxOne.x + boxOne.w > boxTwo.x && boxOne.y < boxTwo.y + boxTwo.h && boxOne.y + boxOne.h > boxTwo.y)
	{
		truth = 1;
	}
	return truth;
}

void loadSDLMedia()
{
	fontTextP = keyTexture("media/PONG.PNG", mren, &textRectP, &textLocP, fontW, fontH, 0xAA, 0x00, 0xAA);
	textLocP.x = fontPXP;
	textLocP.y = fontPYP;
	textRectP.x = fontW * pScore;
	fontTextC = keyTexture("media/PONG.PNG", mren, &textRectC, &textLocC, fontW, fontH, 0xAA, 0x00, 0xAA);
	textLocC.x = fontPXC;
	textLocC.y = fontPYC;
	textRectC.x = fontW * cScore;
}

int startup()
{
	int success = 0;
	printf("SDL Pong  Copyright (C) 2021  Matt Gobbi\nThis program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions; type `show c' for details.\n");
	minY = 16;
	maxY = (double) winY - minY;
	ballX = (double) winX / 2; //The ball always starts in the center of the screen.
	ballY = (double) winY / 2;
	fontPXC = winX - fontPXP;
	fontPYC = fontPYP;
	playY = (double) winY / 2; //Player's initial position.
	compY = (double) winY / 2; //Computer's initial position.
	if(SDL_Init(WFLAGS) != 0)
	{
		printf("SDL error: %s\n", SDL_GetError());
		success = -1;
	}
	else
	{
		mwin = SDL_CreateWindow(WNAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winX, winY, WMODE);
		if (mwin == NULL)
		{
			printf("SDL error: %s\n", SDL_GetError());
			success = -1;
		}
		else
		{
			mren = SDL_CreateRenderer(mwin, -1, SDL_RENDERER_ACCELERATED);
			if (mren == NULL)
			{
				printf("SDL error: %s\n", SDL_GetError());
				success = -1;
			}
			else
			{
				int imgFlags = IMG_INIT_PNG;
				int imgInit = IMG_Init(imgFlags);
				if (imgInit != imgFlags)
				{
					printf("SDL_image error: %s\n", IMG_GetError());
					success = -1;
				}
				else
				{
					//Mixer initialization, added last.
					printf("SDL Success!\n");
				}
			}
		}
	}
	playRect.w = padlW;
	compRect.w = padlW;
	playRect.h = padlH;
	compRect.h = padlH;
	compRect.x = (winX - padlX) - (padlW / 2);
	playRect.x = padlX - (padlW / 2);
	pongB.w = ballS;
	pongB.h = ballS;
	winRect.x = winX;
	winRect.y = winY;
	loadSDLMedia();
	return success;
}

void cleanup()
{
	//Mix_Quit();
	SDL_DestroyTexture(fontTextP);
	SDL_DestroyTexture(fontTextC);
	fontTextP = NULL;
	fontTextC = NULL;
	IMG_Quit();
	SDL_DestroyRenderer(mren);
	mren = NULL;
	SDL_DestroyWindow(mwin);
	mwin = NULL;
	SDL_Quit();
}

void pollEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		switch(e.type)
			{
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							running = 0;
							break;
						case SDLK_p:
							printf("%i\t", pScore);
							fflush(stdout);
							break;
						case SDLK_o:
							printf("%i\t", cScore);
							fflush(stdout);
							break;
						case SDLK_i:
							printf("%i\t%i\t%i\t%i\n", textLocP.x, textLocP.y, textLocC.x, textLocC.y);
							break;
						case SDLK_u:
							printf("%i\t%i\t%i\t%i\n", textLocP.w, textLocP.h, textLocC.w, textLocC.h);
							break;
						case SDLK_y:
							printf("%i\t%i\t%i\t%i\n", textRectP.x, textRectP.y, textRectP.x, textRectP.y);
							break;
						case SDLK_t:
							printf("%i\t%i\t%i\t%i\n", textRectP.w, textRectP.h, textRectP.w, textRectP.h);
							break;
						case SDLK_F12:
							takeScreenShot(mwin, mren, "pongimg.png");
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
	}
}

void COLOR(EGACOLORS GETCOL)
{
	RGBCOLORS SETCOL = PULLCOLOR(GETCOL);
	SDL_SetRenderDrawColor(mren, SETCOL.r, SETCOL.g, SETCOL.b, SETCOL.a);
}

void renDivider(int lineSize, int offset)
{
	int lineI;
	for (lineI = offset; lineI < winY; lineI += (lineSize * 2))
	{
		COLOR(GREY);
		SDL_RenderDrawLine(mren, (winX / 2), lineI, (winX / 2), lineI + lineSize);
	}
}

void renPaddles()
{
	playRect.y = playY - (padlH / 2);
	compRect.y = compY - (padlH / 2);
	COLOR(WHITE);
	SDL_RenderFillRect(mren, &playRect);
	COLOR(LIGHTGREY);
	SDL_RenderDrawRect(mren, &playRect);
	SDL_RenderFillRect(mren, &compRect);
	COLOR(WHITE);
	SDL_RenderDrawRect(mren, &compRect);
}

void renBall()
{
	pongB.x = ballX - (ballS / 2);
	pongB.y = ballY - (ballS / 2);
	COLOR(LIGHTGREEN);
	SDL_RenderFillRect(mren, &pongB);
	COLOR(GREEN);
	SDL_RenderDrawRect(mren, &pongB);
}

void rendUp()
{
	COLOR(BLACK);
	SDL_RenderClear(mren);
	renDivider(16, 8);
	renPaddles();
	renBall();
	SDL_RenderCopy(mren, fontTextP, &textRectP, &textLocP);
	SDL_RenderCopy(mren, fontTextC, &textRectC, &textLocC);
	SDL_RenderPresent(mren);
}

int waitTime = 1000;

void ballMotions()
{
	ballX += ballVX;
	ballY += ballVY;
	if (waitTime > 0)
	{
		waitTime -= 1;
	}
	else
	{
		if (ballVX == 0 && ballVY == 0)
		{
			ballVX += polarXCoord(0, ballAccl, ballAng);
			ballVY += polarYCoord(0, ballAccl, ballAng);
		}
	}
	if (ballY > winY - (ballS / 2) && ballVY > 0)
	{
		ballVY = -ballVY;
	}
	if (ballY < (ballS / 2) && ballVY < 0)
	{
		ballVY = -ballVY;
	}
	if (checkCol(pongB, playRect) == 1 && ballVX < 0)
	{
		ballVX = -ballVX;
	}
	if (checkCol(pongB, compRect) == 1 && ballVX > 0)
	{
		ballVX = -ballVX;
	}
	if (ballX > winX + goalPost)
	{
		++pScore;
		loadSDLMedia();
		ballVX = 0;
		ballVY = 0;
		ballX = (winX / 2);
		ballY = (winY / 2);
		ballAng += 180;
		waitTime = 1000;
	}
	if (ballX < -goalPost)
	{
		++cScore;
		loadSDLMedia();
		ballVX = 0;
		ballVY = 0;
		ballX = (winX / 2);
		ballX = (winX / 2);
		ballY = (winY / 2);
		ballAng += 180;
		waitTime = 1000;
	}
}

void getKeyboard()
{
	const Uint8 *flowKeys = SDL_GetKeyboardState(NULL);
	if (!flowKeys[SDL_SCANCODE_UP] && !flowKeys[SDL_SCANCODE_DOWN])
	{
		playY += 0;
	}
	else
	{
		if (flowKeys[SDL_SCANCODE_UP])
		{
			if (playY > minY)
			{
				playY -= padlS; 
			}
			else
			{
				playY = minY;
			}
		}
		else if (flowKeys[SDL_SCANCODE_DOWN])
		{
			if (playY < maxY)
			{
				playY += padlS; 
			}
			else
			{
				playY = maxY;
			}
		}
	}
}

void compAI()
{
	compS = log(compY / ballY);
	if (ballY > compY) 
	{
		compY -= compS;
	}
	else if (ballY < compY)
	{
		compY -= compS;
	}
}

void keepScore()
{
	if (pScore >= maxScore)
	{
		printf("You won the game!\n");
		running = 0;
	}
	else if (cScore >= maxScore)
	{
		printf("You lost.\n");
		running = 0;
	}
}

int main(int argc, char **argv)
{
	if (startup() != 0)
	{
		printf("SDL Failed to initialize.\n");
		return 0;
	}
	while (running == 1)
	{
		pollEvent();
		rendUp();
		getKeyboard();
		ballMotions();
		keepScore();
		compAI();
	}
	cleanup();
	return 0;
}
