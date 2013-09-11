MazeExplorer
============

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