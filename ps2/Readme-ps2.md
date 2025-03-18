# PS2: Pythagorean Tree

## Contact
Name: Camden Andersson
Section: 202 
Time to Complete: 10+ hrs


## Description
Explain what the project does.

Creates a pythagorean tree using sfml and displays it to the user, using inputs from the command line.


### Features
Describe what your major decisions were and why you did things that way.

I used rect.getTransform().transformPoint(rect.getPoint()); to get the points of the child sqaures during rotation, this made it much easier as I could work with the coordinates directly, even though I am using rectangleShape.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I has the most trouble with just getting the tree display properly after the first recursive iteration. After that, I learned that devloping a better plan of action for such assignments might be a good idea. Everything works correctly now, even the changing colors.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

I made it so the tree changes colors over time as it is recursively called.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

Dr. Daly
Michael Doan
https://en.sfml-dev.org/forums/index.php?topic=15973.0