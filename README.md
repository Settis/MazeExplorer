MazeExplorer
============

Idea
----

Idea comes from [Collective map making](https://www.ftj.agh.edu.pl/~kulakowski/ssol.pdf) 
presentation by [Prof. dr hab. Krzysztof Kułakowski](https://www.ftj.agh.edu.pl/~kulakowski/).

This program simulates how robots explore a maze. You have a maze with some gates. 
Robots come to maze through these gates and walk through the maze. Also if they meets, they merge knowledge.

How to
------

For build programm on Linux you can run:

    $ qmake && make

Then you get binary file *console/mazeExplorer*

Let's generate a maze (run *'mazeExplorer gen help'* for help):

    $ ./mazeExplorer gen maze 10 10 2 100
    Make borders ... Done
    Make gates ... Done
    Make walls ... Done
    generation complete with 54% of walls.
    $ cat maze
    ***** ****
    ***   ****
    *****    *
    * ****** *
    * ***    *
    * ***** **
    * **    **
    * ** **   
    *    *****
    **********

Then you can run robots (run *'mazeExplorer gen help'* for help):

    $ ./mazeExplorer run randomWalker 2 maze aaLog

Log will be printed to *aaVideo.txt*

Generate new maze
-----------------

Using: mazeExplorer gen fileName x\_size y\_size num\_gates persent\_of\_walls

Where persent\_of\_walls is desired percentage of maze area. 

Generator works by the follow way:

- filling border walls
- make gates randomly
- take all internal points and shuffle
- repeat if we have unused nested points and current percentage of walls less then we desired
 - take internal point
 - put a wall on it
 - check available gate to another
 - if false delete the wall

Run simulate
------------

Usage: mazeExplorer run robotName robotCount mazeFile [aaLog]

Available robots are:

- pureRandom
- randomWalker
- determin
- deepLook

On running program write *progress.csv* file. File contain information about how many rooms robot visited. 
Colums for each robots and one row per simulation step.

'aaLog' flag enable ascii-art logging. It print movie by frames and can be scrolled by 'PageDown'.

Implemented robots
------------------

### Pure random robot

On each step it choose random direction. No matter that it try to go in wall. Program engine check it and hold 
the robot in previous place.

### Random walker robot

This robot looks on possible ways and choose direction randomly except the room from it came

### Determin robot

This robot remembers how much times it been in each room. On each step it choose room that less times visited.

### Deep look robot

This robot remembers rooms that it was already been. On each step it choose a room that never visited. 
If it surrounded by already visited rooms then it find nearest non visited room and go to it.