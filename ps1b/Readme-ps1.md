# PS1: LFSR / PhotoMagic

## Contact
Name: Camden Andersson

Section: 202

Time to Complete: ~1.5hr


## Description
Explain what the project does.

The project takes an std::string seed as a 16-bit binary sequnce and performs bit manipulation on that seed in order to create a fibonacci LFSR. This was then used to encrypt each pixel of an image, and again used to decrypt it

### Features
Describe the representation you used and why you did things that way.

I implemented all the base functions using an int so I could manipulate the bits of the seed easier than using stl containers. This way, it should also help with efficiency as well as I am directly modifying and accessing the LFSR itself. A transform function was then used to modify the RGB values of each pixels, encrypted with the previously mentioned lfsr, by getting the size of said image and iterating pixel by pixel. the image before and after is then displayed to the user.

### Issues
What doesn't work.  Be honest.  You might be penalized if you claim something works and it doesn't.

Everything works correctly as needed by the pdf.

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

sfml:
https://www.sfml-dev.org/tutorials/2.4/start-linux.php

image:
https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.indy100.com%2Fviral%2Fkurt-angle-stare-meme-tiktok&psig=AOvVaw2KAmLRjt1XgK0j5MdmnfB_&ust=1707110203606000&source=images&cd=vfe&opi=89978449&ved=0CBMQjRxqFwoTCLiYx5v3kIQDFQAAAAAdAAAAABAd

Changes: -

i added the screenshots that were missing in the original project submission. thats it.