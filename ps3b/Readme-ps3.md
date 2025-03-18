# PS4: Sokoban Game

## Contact
Name: Camden Andersson
Section: 202 
Time to Complete: ~20+ hrs


## Description
Explain what the project does.

Creates a the UI for the sokoban game that will be utilized in the next project.


### Features
Describe what your major decisions were and why you did things that way.

I used a Vector of a vector of characters (a 2d vector) to store the level data input from the file using the insertion operator. I did it using this method as it felt it would be better for practice, although a 1d array/vector would also work. I ued a switch statment instead of if-else-ifs for displaying the sprites becuase its faster. Everything else was decided by the conditions needed in the PDF.

### Memory
Describe how you decided to store the level data including whether you used smart pointers.

I stored the level data in a 2d array of vectors, vhere the isnie vector holds characters. I did not use any smart pointers anywhere in my program.

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

I used find_if() and find, and used a lamba expression as the input to the finid_if() function.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I didnt follow the pathway that was described at first, which led to me having to backtrack at some points making this take longer than neccisary.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

The player changes direction while moving, you can undo one step, and a victory sound is played at the end.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Drawable.php

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban

Alarm3.wav from The windows media fodler 

