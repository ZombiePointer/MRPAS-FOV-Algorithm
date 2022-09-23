# MRPAS-FOV-Algorithm

## What is this?
A straightforward, 2D implementation of [Mingos' Restrictive Precise Angle Shadowcasting (MRPAS)](https://openbase.com/js/mrpas/documentation), a common roguelike Field of View (FOV) algorithm, in C++. An FOV computation algorithm, given a 2D grid with a set of source coordinates and points marked as obstacles, will determine all of the points visible from those coordinates. This implementation is lightweight, headers-only, and can be easily dragged-and-dropped into your project. Based on MRPAS code written by Dominik Marczuk and posted on Umbrarum Regnum. ([Source](https://groups.google.com/g/rec.games.roguelike.development/c/rYm7HDIollM))

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
