# Description
Ahah, pixel go brrrrr


bin/pathfinder.exe [RECTSIZE] [ADNSIZE] [SPEED] [ROTATIONSPEED] [NPOP] [PLAYMODE]

[PLAYMODE] = 0 : Step by step, (type space-bar to show next frame)
[PLAYMODE] = 1 : Continuous, (type space-bar to pause/play)


# Build
To build the project :
```
make
```

To clean the binary :
```
make clean
```


# Setting up the environnement

## The basics

Firstly install, if you don't already have it, chocolatey. It is a package manager that allow you to install command line tool (like git) without trouble. 
you can install it with this command (intalation is described [here](https://chocolatey.org/install)) :
```
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```

Then you will need your favorite editor, I strongly recommand visual studio [here](https://code.visualstudio.com/).

Then you will need to install git with this command using the *powershell*
```
choco install git
```

This project is developped in C, so you'll need a compiler. the most used compiller that is compatible with window is MinGw you can downlad it here :
[https://sourceforge.net/projects/mingw/](https://sourceforge.net/projects/mingw/)

After the install, check that it is corectly installed using the command
```
gcc --version
```

## Visual studio plugin

After aquiring the basic tools, you need to clone the projet into a folder with the command
```
git clone https://github.com/Tictactouc/ADN_PathFinder.git
```
(if you'r new to git, the url in this command is found by clicking the green button on the top of the project)
You can clone the project using ssh too, but you'll need to set up a ssh key.

After clonning the project you can open it on visual studio. To do that you can right click on the project folder or directly using the "open a folder" in the file menu of visual studio. The right root folder is the one that directly contain the folders src, bin..etc

Once you have the the project opened in visual studio you will need to install some plugins (remember, visual studio is a text editor, to develop on this software you'll often need to enhance it with multiple plugin to enable syntax coloring, syntax error recognition, code autocopletion and suggestion etc...).

Fortunately, visual studio will detect the technology used in the folder and suggest in popup (in the bottom-right of the screen) some plugin to install.
The plugin needed are :
- C/C++
- C/C++ Extention Pack
- C/C++ Themes
- Makefile tools
- Whatever other plugins VScode suggest to install

## does the project is even correctly setup ??

to test if the setup has been corectly setup check if you DON'T have some word that are underlined in red, if the code is colored, if you do *CTRL+space* you have a menu suggesting some code.

Also, execute the *make* command. does it work ? does a .exe file have been created in the bin folder ?

if the answer to all those question is YES then .. congrats, the project is now fully setup, it's the very very very first step BUT dont get discouraged, it's often troublesome and the developement process is likely to be less complex in some way.

# Architecture

*ATTENTION : WORK IN PROGRESS, THE ARCHITECTURE DESCRIBED HERE HAS NOT BEEN IMPLEMENTED*

This application is divided into multiple part the first one, wich happen to be the entry point of the program is... surprise surprise.... the main ! (okay I know you already know it).

## Arguments mnagement

The main module (we will assume module = simple C file in this project (to be really really clear we're talking about the main.c/main.h files here )) is used to check the arguments, check that they are valid, output a help message if they are not or if the wrong number of argument have been entered.

*WHAT IS DESCRIBED BELOW IS NOT IMPLEMENTED*

Then it will create a context variable using the App stucture (The App stucture is just a variable that have multiple attribut, simply said, it is a variable that contain other multiple variable. like a folder that contain multiple file). The App variable contain all the context info needed for the rest of the program : all the argument, aaaand others things that I didn't think of just now but that certainly will be usefull in the future.......

## Event mnagement

The inputs are managed by the events module

##Application

##Entity

### creature

creatur.c/creatur.h

### obstacle

obstacle.c/obstacle.h

### goal

goal.c/goal.h
