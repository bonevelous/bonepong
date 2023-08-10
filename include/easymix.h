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
#include <SDL2/SDL_mixer.h>

#ifndef EASYMIX_H
#define EASYMIX_H

Mix_Music* playMusic(char* fileName)
{
    Mix_Music* curSong = NULL;
    curSong = Mix_LoadMUS(fileName);
    if (curSong == NULL)
    {
        printf("Could not load song. Read: %s\n", Mix_GetError());
    }
    else
    {
        if (Mix_PlayMusic(curSong, -1) != 0)
        {
             printf("Could not play song. Read: %s\n", Mix_GetError());
        }
    }
    return curSong;
}

#endif
