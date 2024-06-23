![Architecture_diagram](https://github.com/Tictactouc/ADN_PathFinder/assets/63233669/22d70a37-0fb9-458c-9894-1bedcb0c8483)# Description
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

This project is developped in C, so you'll need a compiler. the most used compiller that is compatible with window is MinGw you can downlad it here :
[https://github.com/niXman/mingw-builds-binaries/releases/](https://github.com/niXman/mingw-builds-binaries/releases/)

After the install, check that it is corectly installed using the command
```
gcc --version
```

## Visual studio plugin

After aquiring the basic tools, you need to clone the projet into a folder. Then you can open it on visual studio. To do that you can right click on the project folder or directly using the "open a folder" in the file menu of visual studio. The right root folder is the one that directly contain the folders src, bin..etc

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

This application is divided into multiple part the first one, wich happen to be the entry point of the program is... surprise surprise.... the main ! (okay I know you already know it).

Each component works together to create a robust simulation environment where entities interact within a dynamically updated visual context. This architecture aims to make the system modular and extensible, allowing for easy expansion and modification.

![Uploading Archit<svg aria-roledescription="flowchart-v2" role="graphics-document document" viewBox="-8 -8 598.125 314" height="314" xmlns="http://www.w3.org/2000/svg" width="598.125" id="tmpMermaidElement6596"><style>svg {background: white;}#tmpMermaidElement6596{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:16px;fill:#333;}#tmpMermaidElement6596 .error-icon{fill:#552222;}#tmpMermaidElement6596 .error-text{fill:#552222;stroke:#552222;}#tmpMermaidElement6596 .edge-thickness-normal{stroke-width:2px;}#tmpMermaidElement6596 .edge-thickness-thick{stroke-width:3.5px;}#tmpMermaidElement6596 .edge-pattern-solid{stroke-dasharray:0;}#tmpMermaidElement6596 .edge-pattern-dashed{stroke-dasharray:3;}#tmpMermaidElement6596 .edge-pattern-dotted{stroke-dasharray:2;}#tmpMermaidElement6596 .marker{fill:#333333;stroke:#333333;}#tmpMermaidElement6596 .marker.cross{stroke:#333333;}#tmpMermaidElement6596 svg{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:16px;}#tmpMermaidElement6596 .label{font-family:"trebuchet ms",verdana,arial,sans-serif;color:#333;}#tmpMermaidElement6596 .cluster-label text{fill:#333;}#tmpMermaidElement6596 .cluster-label span,#tmpMermaidElement6596 p{color:#333;}#tmpMermaidElement6596 .label text,#tmpMermaidElement6596 span,#tmpMermaidElement6596 p{fill:#333;color:#333;}#tmpMermaidElement6596 .node rect,#tmpMermaidElement6596 .node circle,#tmpMermaidElement6596 .node ellipse,#tmpMermaidElement6596 .node polygon,#tmpMermaidElement6596 .node path{fill:#ECECFF;stroke:#9370DB;stroke-width:1px;}#tmpMermaidElement6596 .flowchart-label text{text-anchor:middle;}#tmpMermaidElement6596 .node .label{text-align:center;}#tmpMermaidElement6596 .node.clickable{cursor:pointer;}#tmpMermaidElement6596 .arrowheadPath{fill:#333333;}#tmpMermaidElement6596 .edgePath .path{stroke:#333333;stroke-width:2.0px;}#tmpMermaidElement6596 .flowchart-link{stroke:#333333;fill:none;}#tmpMermaidElement6596 .edgeLabel{background-color:#e8e8e8;text-align:center;}#tmpMermaidElement6596 .edgeLabel rect{opacity:0.5;background-color:#e8e8e8;fill:#e8e8e8;}#tmpMermaidElement6596 .labelBkg{background-color:rgba(232, 232, 232, 0.5);}#tmpMermaidElement6596 .cluster rect{fill:#ffffde;stroke:#aaaa33;stroke-width:1px;}#tmpMermaidElement6596 .cluster text{fill:#333;}#tmpMermaidElement6596 .cluster span,#tmpMermaidElement6596 p{color:#333;}#tmpMermaidElement6596 div.mermaidTooltip{position:absolute;text-align:center;max-width:200px;padding:2px;font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:12px;background:hsl(80, 100%, 96.2745098039%);border:1px solid #aaaa33;border-radius:2px;pointer-events:none;z-index:100;}#tmpMermaidElement6596 .flowchartTitleText{text-anchor:middle;font-size:18px;fill:#333;}#tmpMermaidElement6596 :root{--mermaid-font-family:"trebuchet ms",verdana,arial,sans-serif;}</style><g><marker orient="auto" markerHeight="12" markerWidth="12" markerUnits="userSpaceOnUse" refY="5" refX="6" viewBox="0 0 10 10" class="marker flowchart" id="tmpMermaidElement6596_flowchart-pointEnd"><path style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 0 0 L 10 5 L 0 10 z"></path></marker><marker orient="auto" markerHeight="12" markerWidth="12" markerUnits="userSpaceOnUse" refY="5" refX="4.5" viewBox="0 0 10 10" class="marker flowchart" id="tmpMermaidElement6596_flowchart-pointStart"><path style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 0 5 L 10 10 L 10 0 z"></path></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5" refX="11" viewBox="0 0 10 10" class="marker flowchart" id="tmpMermaidElement6596_flowchart-circleEnd"><circle style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" r="5" cy="5" cx="5"></circle></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5" refX="-1" viewBox="0 0 10 10" class="marker flowchart" id="tmpMermaidElement6596_flowchart-circleStart"><circle style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" r="5" cy="5" cx="5"></circle></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5.2" refX="12" viewBox="0 0 11 11" class="marker cross flowchart" id="tmpMermaidElement6596_flowchart-crossEnd"><path style="stroke-width: 2; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 1,1 l 9,9 M 10,1 l -9,9"></path></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5.2" refX="-1" viewBox="0 0 11 11" class="marker cross flowchart" id="tmpMermaidElement6596_flowchart-crossStart"><path style="stroke-width: 2; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 1,1 l 9,9 M 10,1 l -9,9"></path></marker><g class="root"><g class="clusters"></g><g class="edgePaths"><path marker-end="url(#tmpMermaidElement6596_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-A LE-B" id="L-A-B-0" d="M310.867,37L310.867,41.167C310.867,45.333,310.867,53.667,310.867,61.117C310.867,68.567,310.867,75.133,310.867,78.417L310.867,81.7"></path><path marker-end="url(#tmpMermaidElement6596_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-B LE-E" id="L-B-E-0" d="M243.658,124L228.521,128.167C213.384,132.333,183.11,140.667,167.973,148.117C152.836,155.567,152.836,162.133,152.836,165.417L152.836,168.7"></path><path marker-end="url(#tmpMermaidElement6596_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-B LE-C" id="L-B-C-0" d="M378.076,124L393.213,128.167C408.35,132.333,438.624,140.667,453.761,148.117C468.898,155.567,468.898,162.133,468.898,165.417L468.898,168.7"></path><path marker-end="url(#tmpMermaidElement6596_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-E LE-D" id="L-E-D-0" d="M152.836,211L152.836,215.167C152.836,219.333,152.836,227.667,152.836,235.117C152.836,242.567,152.836,249.133,152.836,252.417L152.836,255.7"></path></g><g class="edgeLabels"><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g></g><g class="nodes"><g transform="translate(310.8671875, 18.5)" id="flowchart-A-0" class="node default default flowchart-label"><rect height="37" width="115.15625" y="-18.5" x="-57.578125" ry="0" rx="0" style="" class="basic label-container"></rect><g transform="translate(-50.078125, -11)" style="" class="label"><rect></rect><foreignObject height="22" width="100.15625"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Main (main.c)</span></div></foreignObject></g></g><g transform="translate(310.8671875, 105.5)" id="flowchart-B-1" class="node default default flowchart-label"><rect height="37" width="191.828125" y="-18.5" x="-95.9140625" ry="0" rx="0" style="" class="basic label-container"></rect><g transform="translate(-88.4140625, -11)" style="" class="label"><rect></rect><foreignObject height="22" width="176.828125"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Application Core (app.c)</span></div></foreignObject></g></g><g transform="translate(152.8359375, 192.5)" id="flowchart-E-3" class="node default default flowchart-label"><rect height="37" width="305.671875" y="-18.5" x="-152.8359375" ry="0" rx="0" style="" class="basic label-container"></rect><g transform="translate(-145.3359375, -11)" style="" class="label"><rect></rect><foreignObject height="22" width="290.671875"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Population Management (population.c)</span></div></foreignObject></g></g><g transform="translate(468.8984375, 192.5)" id="flowchart-C-5" class="node default default flowchart-label"><rect height="37" width="226.453125" y="-18.5" x="-113.2265625" ry="0" rx="0" style="" class="basic label-container"></rect><g transform="translate(-105.7265625, -11)" style="" class="label"><rect></rect><foreignObject height="22" width="211.453125"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Event Management (event.c)</span></div></foreignObject></g></g><g transform="translate(152.8359375, 279.5)" id="flowchart-D-7" class="node default default flowchart-label"><rect height="37" width="272.234375" y="-18.5" x="-136.1171875" ry="0" rx="0" style="" class="basic label-container"></rect><g transform="translate(-128.6171875, -11)" style="" class="label"><rect></rect><foreignObject height="22" width="257.234375"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Creature Management (creature.c)</span></div></foreignObject></g></g></g></g></g></svg>ecture_diagram.svg…]()


## Arguments management (main.c)
The main module (we will assume module = simple C file in this project (to be really really clear we're talking about the main.c/main.h files here )) is used to check the arguments, check that they are valid, output a help message if they are not or if the wrong number of argument have been entered.

## Application core functionality (app.c)

The core functionality is handled in app.c, which initializes the SDL framework, sets up the main application window and rendering context, and controls the main simulation loop including drawing and updates based on the simulation state.

## Event management (event.c)

The inputs are managed by the events module in event.c, which captures and processes user inputs, allowing for interaction with the simulation in real-time.

## Population management (population.c)
population.c/populatin.h - Manages a collection of creatures, handling their lifecycle from initialization to updates during the simulation and final cleanup.

## Entities (En-tities lol)

In the heart of our simulation, the entities represent the dynamic components interacting within the virtual environment. Each type of entity, from creatures to obstacles and goals, plays a crucial role in the pathfinding challenges and behaviors demonstrated in the application. Here's how each entity is managed:

### Creature (creature.c)

creatur.c/creature.h - Manages individual creature entities, including their initialization, behavior (movement and rotation based on their DNA), and rendering.

### obstacle (obstacle.c)

obstacle.c/obstacle.h - Defines obstacles in the simulation environment that creatures must navigate around. (Currently not implemented but planned.)

### Goal (goal.c)

goal.c/goal.h - Manages goal points that creatures strive to reach as part of the pathfinding challenges. (Currently not implemented but planned.)
