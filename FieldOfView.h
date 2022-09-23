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

#include "Map.h"
#include <stdlib.h>

// Maximum and minimum functions
#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)

class FieldOfView
{
public:

	FieldOfView() { }

	// Compute a single quadrant.
	void computeQuadrant(Map* m, int playerX, int playerY, int maxRadius, bool lightWalls, int maxObstacles, int dx, int dy)
	{
		double* startAngle, * endAngle;
		startAngle = (double*)calloc(maxObstacles * 2, sizeof(double));
		endAngle = (double*)calloc(maxObstacles, sizeof(double));

		// Octant: Vertical edge.
		{
			int iteration = 1;
			bool done = false;
			int totalObstacles = 0;
			int obstaclesInLastLine = 0;
			double minAngle = 0.0;
			int x, y;

			// Do while there are unblocked slopes left and the algorithm is within the map's boundaries.
			// Scan progressive lines/columns from the player outwards.
			y = playerY + dy;
			if (y < 0 || y >= m->height)
				done = true;
			while (!done)
			{
				// Process cells in the line
				double slopesPerCell = 1.0 / (double)(iteration + 1);
				double halfSlopes = slopesPerCell * 0.5;
				int processedCell = (int)(minAngle / slopesPerCell);
				int minx = MAX(0, playerX - iteration), maxx = MIN(m->width - 1, playerX + iteration);
				done = true;
				for (x = playerX + (processedCell * dx); x >= minx && x <= maxx; x += dx)
				{
					int c = x + (y * m->width);
					// Calculate slopes per cell
					bool visible = true;
					double startSlope = (double)processedCell * slopesPerCell;
					double centreSlope = startSlope + halfSlopes;
					double endSlope = startSlope + slopesPerCell;
					if (obstaclesInLastLine > 0 && !m->cells[c].fov)
					{
						int idx = 0;
						while (visible && idx < obstaclesInLastLine)
						{
							if (m->cells[c].transparent == true)
							{
								if (centreSlope > startAngle[idx] && centreSlope < endAngle[idx])
									visible = false;
							}
							else
							{
								if (startSlope >= startAngle[idx] && endSlope <= endAngle[idx])
									visible = false;
							}
							if (visible && (m->cells[c - (m->width * dy)].fov == false || !m->cells[c - (m->width * dy)].transparent) && (x - dx >= 0 && x - dx < m->width && (m->cells[c - (m->width * dy) - dx].fov == false || !m->cells[c - (m->width * dy) - dx].transparent)))
								visible = false;
							idx++;
						}
					}
					if (visible)
					{
						m->cells[c].fov = true;
						done = false;
						// If the cell is opaque, block the adjacent slopes
						if (!m->cells[c].transparent) {
							if (minAngle >= startSlope)
								minAngle = endSlope;
							else {
								startAngle[totalObstacles] = startSlope;
								endAngle[totalObstacles++] = endSlope;
							}
							if (!lightWalls)
								m->cells[c].fov = false;
						}
					}
					processedCell++;
				}
				if (iteration == maxRadius)
					done = true;
				iteration++;
				obstaclesInLastLine = totalObstacles;
				y += dy;
				if (y < 0 || y >= m->height)
					done = true;
				if (minAngle == 1.0)
					done = true;
			}
		}

		// Octant: Horizontal edge.
		{
			int iteration = 1;
			bool done = false;
			int totalObstacles = 0;
			int obstaclesInLastLine = 0;
			double minAngle = 0.0;
			int x, y;

			// Do while there are unblocked slopes left and the algorithm is within the map's boundaries.
			// Scan progressive lines/columns from the player outwards.
			x = playerX + dx;
			if (x < 0 || x >= m->width)
				done = true;
			while (!done)
			{
				// Process cells in the line
				double slopesPerCell = 1.0 / (double)(iteration + 1);
				double halfSlopes = slopesPerCell * 0.5;
				int processedCell = (int)(minAngle / slopesPerCell);
				int miny = MAX(0, playerY - iteration), maxy = MIN(m->height - 1, playerY + iteration);
				done = true;
				for (y = playerY + (processedCell * dy); y >= miny && y <= maxy; y += dy)
				{
					int c = x + (y * m->width);
					// Calculate slopes per cell
					bool visible = true;
					double startSlope = (double)(processedCell * slopesPerCell);
					double centreSlope = startSlope + halfSlopes;
					double endSlope = startSlope + slopesPerCell;
					if (obstaclesInLastLine > 0 && !m->cells[c].fov)
					{
						int idx = 0;
						while (visible && idx < obstaclesInLastLine)
						{
							if (m->cells[c].transparent)
							{
								if (centreSlope > startAngle[idx] && centreSlope < endAngle[idx])
									visible = false;
							}
							else {
								if (startSlope >= startAngle[idx] && endSlope <= endAngle[idx])
									visible = false;
							}
							if (visible && (m->cells[c - dx].fov == false || !m->cells[c - dx].transparent) && (y - dy >= 0 && y - dy < m->height && (m->cells[c - (m->width * dy) - dx].fov == false || !m->cells[c - (m->width * dy) - dx].transparent)))
								visible = false;
							idx++;
						}
					}
					if (visible)
					{
						m->cells[c].fov = true;
						done = false;
						// If the cell is opaque, block the adjacent slopes
						if (!m->cells[c].transparent)
						{
							if (minAngle >= startSlope)
							{
								minAngle = endSlope;
							}
							else
							{
								startAngle[totalObstacles] = startSlope;
								endAngle[totalObstacles++] = endSlope;
							}
							if (!lightWalls)
							{
								m->cells[c].fov = false;
							}
						}
					}
					processedCell++;
				}
				if (iteration == maxRadius)
					done = true;
				iteration++;
				obstaclesInLastLine = totalObstacles;
				x += dx;
				if (x < 0 || x >= m->width)
					done = true;
				if (minAngle == 1.0)
					done = true;
			}
		}
		free(startAngle);
		free(endAngle);
	}

	// Compute the current field of view given the player's coordinates, the view radius, and whether the walls should be highlighted.
	void computeFov(Map* m, int playerX, int playerY, int maxRadius, bool lightWalls)
	{
		// Zero the FOV map.
		for (int c = 0; c < m->nbcells; c++)
		{
			m->cells[c].fov = false;
		}

		// Calculate an approximated maximum number of obstacles per octant.
		int maxObstacles = m->nbcells / 7;

		// Set the player's position as visible, since the player should always be able to see themselves.
		m->cells[playerX + (playerY * m->width)].fov = true;

		// Compute the 4 quadrants of the map.
		computeQuadrant(m, playerX, playerY, maxRadius, lightWalls, maxObstacles, 1, 1);
		computeQuadrant(m, playerX, playerY, maxRadius, lightWalls, maxObstacles, 1, -1);
		computeQuadrant(m, playerX, playerY, maxRadius, lightWalls, maxObstacles, -1, 1);
		computeQuadrant(m, playerX, playerY, maxRadius, lightWalls, maxObstacles, -1, -1);
	}
};