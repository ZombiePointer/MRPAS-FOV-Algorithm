# MRPAS-FOV-Algorithm

## What is this?
A straightforward, 2D implementation of [Mingos' Restrictive Precise Angle Shadowcasting (MRPAS)](https://openbase.com/js/mrpas/documentation), a common roguelike Field of View (FOV) algorithm, in C++. A FOV computation algorithm, given a 2D grid with a set of source coordinates and points marked as view-blocking obstacles, will determine all of the points visible from those coordinates. This implementation is lightweight, headers-only, and can be easily dragged-and-dropped into your project. Based on MRPAS code written by [Dominik "Mingos" Marczuk](http://www.roguebasin.com/index.php/User:Dominikmarczuk) in 2008 and posted on the website of the unreleased roguelike game [Umbrarum Regnum](http://www.roguebasin.com/index.php/Umbrarum_Regnum) in April 2009. ([Source Post](https://groups.google.com/g/rec.games.roguelike.development/c/rYm7HDIollM))

MRPAS was originally written with performance in mind, and is very efficient. It processes as few points as possible, quickly discarding the ones obviously out of FOV, and tends to match or outperform all popular FOV algorithms. It is part of the overall family of Restrictive Precise Angle Shadowcasting algorithms, in that instead of calculating one approximated slope for each cell, it uses three extremely exact slopes, or angles, to determine a cell's visibility from the player's coordinates. As such, they have decent speed, don't produce artifacts, and create organic and well-formed shadows.

## How do I use this?
1. Include the header file **FieldOfView.h**.
2. Create a `Map` object with width and height parameters corresponding to your terrain map dimensions, and fill the cells with the `walkable` (can the player walk through this tile?) and `transparent` (can the player see through this tile?) values of your terrain map.
3. Create a `FieldOfView` object and call the `computeFOV` method with your desired parameters.
    - `playerX`: The player's x-coordinate.
    - `playerY`: The player's y-coordinate.
    - `maxRadius`: The maximum FOV radius. Lower values result in lower vision.
    - `lightWalls`: Are obstacles lit? (`false` makes obstacles dark.)
4. The resulting `Map` cells will contain `fov` values corresponding to whether they are visible in the player's FOV cone.

## Read more
- [MRPAS documentation on Openbase](https://openbase.com/js/mrpas/documentation).
- [Restrictive Precise Angle Shadowcasting on Roguebasin](http://www.roguebasin.com/index.php/Restrictive_Precise_Angle_Shadowcasting).

## MRPAS License

> MRPAS
> Copyright (c) 2009, 2010 Dominik Marczuk
> All rights reserved.
> 
> Redistribution and use in source and binary forms, with or without
> modification, are permitted provided that the following conditions are met:
>     * Redistributions of source code must retain the above copyright
>       notice, this list of conditions and the following disclaimer.
>     * Redistributions in binary form must reproduce the above copyright
>       notice, this list of conditions and the following disclaimer in the
>       documentation and/or other materials provided with the distribution.
>     * The name of Dominik Marczuk may not be used to endorse or promote products
>       derived from this software without specific prior written permission.
> 
> THIS SOFTWARE IS PROVIDED BY DOMINIK MARCZUK ``AS IS'' AND ANY
> EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
> WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
> DISCLAIMED. IN NO EVENT SHALL DOMINIK MARCZUK BE LIABLE FOR ANY
> DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
> (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
> LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
> ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
> (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
> SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
