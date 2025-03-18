# PS6: RandWriter

## Contact
Name: Camden Andersson
Section: 202
Time to Complete: ~7 Hr


## Description
Explain what the project does.

The project takes an input of characters, such as from a novel, and uses them to create a new passage in the style of that writing (pseudo-random text), using a markov model (specifcically an order-k markov model). You are able to adjust the size of the k-gram and the amount of characters generated to make a different output.

### Features
Describe what your major decisions were and why you did things that way.

I used a map, that contains a string and another map of chars and ints, as my symbol table. This appraoch seemed the most simple in my mind and thats why I did it this way. I also used another class TextWriter to actually do the part of displaying, although this isnt necessary, and was more done for debugging. All of the other functions are implemented in a way that makes the most sense following my implementation of the symbol table, and in a way that follows what is needed from the PDF.

### Testing
What tests did you write?  What exceptions did you use?  Does your code pass the tests?

I used no_throw, require equal, and close to test an invalid argument, wrong distribution, and generate. My code does pass the tests, although 3 of them passed everything so i had to write another to get the required amount for "your tests:.

### Lambda
What does your lambda expression do?  What function did you pass it to?

my lambda function is used inside of the freq(string, char) function, being passed into a find_if function as a paramter in order to find a character in a pair.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

Everything works as intended.

I didnt have any issues
### Extra Credit
Anything special you did.  This is required to earn bonus points.

N/A

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

Michael Doan