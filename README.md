MazeExplorer
============

Idea
----

Idea comes from [Collective map making](https://www.ftj.agh.edu.pl/~kulakowski/ssol.pdf) 
presentation by [Prof. dr hab. Krzysztof Kułakowski](https://www.ftj.agh.edu.pl/~kulakowski/).

This program [simulates](#run-simulate) how robots explore a maze. You have a maze with some gates. 
Robots come to maze through these gates and walk through the maze. Also if they meet, they merge knowledge.

How to
------

For build program on Linux you could run:

    $ qmake && make

Then you get binary file *console/mazeExplorer*

Let's generate a maze (run [*'mazeExplorer gen help'*](#generate-new-maze) for help):

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

Then you can run robots (run [*'mazeExplorer gen help'*](#run-simulate) for help):

    $ ./mazeExplorer run randomWalker 2 maze aaLog

Log will be printed to *aaVideo.txt*

Generate new maze
-----------------

Using: mazeExplorer gen fileName x\_size y\_size num\_gates persent\_of\_walls

Where persent\_of\_walls is desired percentage of maze area. 

Generator works in the following way:

- filling border walls
- make gates randomly
- take all internal points and shuffle
- repeat if we have unused nested points and current percentage of walls less than we desired
 - take internal point
 - put a wall on it
 - check all gates accessibility from all other gates
 - if false delete the wall

Run simulate
------------

Usage: mazeExplorer run robotName robotCount mazeFile [aaLog]

Available robots are:

- [pureRandom](#pure-random-robot)
- [randomWalker](#random-walker-robot)
- [determine](#determine-robot)
- [deepLook](#deep-look-robot)

On running program write *progress.csv* file. File contain information about how many rooms robot visited. 
Colums for each robots and one row per simulation step.

'aaLog' flag enable ascii-art logging. It print movie by frames and can be scrolled by 'PageDown'.

Implemented robots
------------------

### Pure random robot

On each step it choose random direction. No matter that it try to go in wall. Program engine checks it and holds 
the robot in the previous place.

### Random walker robot

This robot looks for possible ways and chooses direction randomly except the room from it came

### Determine robot

This robot remembers how much times it has been in each room. On each step it chooses a room which was visited 
by fewer times.

### Deep look robot

This robot remembers rooms where it has already been. On each step it choose a room that was never visited. 
If it is surrounded by already visited rooms then it find nearest non visited room and go to it.
