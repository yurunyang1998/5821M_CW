# University of Leeds
# COMP 5821M Triangle Soup Renderer

This is a very simple renderer for triangle soup. It makes no attempt to be efficient, 
which keeps the code clearer.

============================
LINUX (FENG-LINUX) COMPILE:
============================

To compile on the University Linux machines, you will need to do the following:

	[userid@machine triangle_renderer]$ module add qt/5.3.1
	[userid@machine triangle_renderer]$ qmake -project QT+=opengl LIBS+=-lGLU
	[userid@machine triangle_renderer]$ qmake
	[userid@machine triangle_renderer]$ make

You should see a compiler warning about an unused parameter, which can be ignored.

To execute the renderer, pass the file name on the command line:

	[userid@machine triangle_renderer]$ ./Assignment2MeshDSHandout ../models/tetrahedron.tri

On other Linux installs (such as your own machine), the details may vary.

============================
MAC OS 11 (BIG SUR) COMPILE:             
============================

First you will need to install Qt. The simplest way to do this is to use the Homebrew 
package manager:

	https://brew.sh

Once you have installed this (following the instructions), you will want to use:

	brew install qt@5

Note that the current version of Qt is 6, which the code will refuse to compile against, 
so you must explicitly choose qt 5.  If you have already installed Qt, you may need to
use /usr/local/Cellar/qt@5/5.15.2/bin/qmake instead of qmake

	userid@machine triangle_renderer % qmake -project QT+=opengl CONFIG+=c++11 
	userid@machine triangle_renderer % qmake                                  
	userid@machine triangle_renderer % make                                   

On MacOS, the executable is bundled as an application, so you will need to invoke it as 
follows:

	userid@machine triangle_renderer % ./triangle_renderer.app/Contents/MacOS/triangle_renderer ../models/tetrahedron.tri
	
============================
WINDOWS 10 COMPILE:
============================
Install Qt 5.13.0, it will come with QT creator. 

It can be found here: 
	https://download.qt.io/archive/qt/5.13/5.13.0/qt-opensource-windows-x86-5.13.0.exe.mirrorlist

Once QT is installed, restart your computer.
Open Powershell on the folder where you have the source code 
	- can be done by shift+right click in the explorer window, and choosing open powershell
	- or open powershell, cd "directory"

Run qmake -project QT+=opengl LIBS+=-lopengl32

Double click the .pro file that was generated: this will open QTCreator.
Select a compiler version that fits your machine (e.g. MSVC2017 64bit).
Click details to see where the different configurations (debug, release) will be built, and change it if you like.
Click Configure project.
Click Build to confirm the compilation is correct, and produces no errors. 

The executable can be ran from the powershell going to the build folder you defined by doing
./triangle_renderer.exe ../models/tetrahedron.tri

Alternatively, you can click "Projects" on QTCreator, click "run" under your configuration, and write 
../models/tetrahedron.tri 

where it says "Command line arguments". This will allow running with a parameter when you click the green arrow. 