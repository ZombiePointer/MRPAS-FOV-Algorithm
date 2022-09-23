/*
* MRPAS
* Copyright (c) 2009, 2010 Dominik Marczuk
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The name of Dominik Marczuk may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY DOMINIK MARCZUK ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL DOMINIK MARCZUK BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Cell.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class Map
{
private:

public:

	int width;
	int height;
	int nbcells;
	Cell* cells;

	// Constructor
	Map(int w, int h)
	{
		width = w;
		height = h;
		nbcells = w * h;
		cells = (Cell*)calloc(nbcells, sizeof(Cell));
	}

	// Destructor
	~Map()
	{
		free(cells);
	}

	// Generate a random map.
	void generate()
	{
		for (int i = 0; i < nbcells; i++)
		{
			int r = rand() % 100;
			if (r > 10)
			{
				cells[i].transparent = true;
				cells[i].walkable = true;
			}
			else
			{
				cells[i].transparent = false;
				cells[i].walkable = false;
			}
			cells[i].fov = false;
		}
	}

	// Getter.
	bool isFOV(int i)
	{
		return cells[i].fov;
	}

	void setCellAsNotWalkableOrTransparent(int i)
	{
		cells[i].transparent = false;
		cells[i].walkable = false;
	}

	void setCellAsWalkableAndTransparent(int i)
	{
		cells[i].transparent = true;
		cells[i].walkable = true;
	}
};
