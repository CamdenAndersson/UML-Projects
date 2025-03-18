# PS1: LFSR / PhotoMagic

## Contact
Name: Camden Andersson

Section: 202

Time to Complete: ~5.5hr


## Description
Explain what the project does.

The project takes an std::string seed as a 16-bit binary sequnce and performs bit manipulation on that seed in order to create a fibonacci LFSR.

### Features
Describe the representation you used and why you did things that way.

I implemented all the base functions using an int so I could manipulate the bits of the seed easier than using stl containers. This way, it should also help with efficiency as well as I am dirctly modifying and accessing the LFSR itself.

### Issues
What doesn't work.  Be honest.  You might be penalized if you claim something works and it doesn't.

Everything implemented works correctly.

### Tests
Describe what is being tested in your Boost unit tests.

The first new test case tests the overloaded output operator.

The second test evaluates the result of using generate then step

The third test uses an ss stream to test the orginal state of the bits.

The fourth test uses a different seed for l with the taps at the correct positions and checks the result

The fifth test uses the step() function to pass list steps.

### Extra Credit
Anything special you did. This is required to earn bonus points.

No extra credit for this assignment.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

Michael Doan
https://cplusplus.com/reference/sstream/