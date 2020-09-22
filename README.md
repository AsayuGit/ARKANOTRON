# ARKANOTRON

A clone of Arkanoid for Linux and the Original XBOX.

The game supports both SDL1.2 and SDL2 and can be played using a keyboard or a controller.

## How to build ?

### Linux :

In the project root folder execute "make" followed by either "SDL" or "SDL2" depending on which API you want to use.

### XBOX :

Compiling for the Original XBOX require the use of a compatible devkit.

Open the .vcproj project file using Visual Studio .net 2003, from there chose the Release target and build the project.
