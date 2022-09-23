# MRPAS-FOV-Algorithm-C-
A straightforward implementation of Mingos' Restrictive Precise Angle Shadowcasting (MRPAS), a common roguelike Field of View (FOV) algorithm, in C++. Lightweight, headers-only, drag-and-drop into your project. Based on MRPAS code written by Dominik Marczuk and posted on Umbrarum Regnum.

## How to use
1. Include the header file **FieldOfView.h**.
2. Create a **Map** object with width and height parameters corresponding to your terrain map dimensions, and fill the cells with the `walkable` (can the player walk through this tile?) and `transparent` (can the player see through this tile?) values of your terrain map.
3. Create a **FieldOfView** object and call the **computeFOV** method with your desired parameters. The resulting Map cells will contain `fov` values corresponding to whether they are visible in the player's FOV cone.
