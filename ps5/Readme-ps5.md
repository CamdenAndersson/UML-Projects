# PS5: DNA Alignment

## Contact
Name: Camden Andersson
Section: 202
Time to Complete: hr

Partner: none

## Description
Explain what the project does

The project is designed to use dynamic programming to find the solution to a problem of DNA sequence alignment. It takes two strings of DNA and runs an algorithm of your choice (in my case the Neddleman-Wunsch method) in order to find the best way to pair them properly. 


### Features
Explain how you did the actual alignment including the data structures used.

I used a vector to hold the two strings into a matrix and then performed the alignment accordingly. The use of a vector for my matrix was optimal as it provided the most optimal way to calculate optDistance().

### Testing
Describe what the unit tests you wrote check for and why you picked them.

The first unit tests check the output is correct, and the second unit tests sees if the distance is correct I picked them to cover as many cases as possible.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

everything works as intended

## Analysis

### Example
Do one additional test case by hand. It should be constructed in such a way that you know the correct  output before running your program on it, and it should be a "corner case" that helps check if your program handles all special situations correctly. 

Please list:
 - a copy of the test case input
 - the expected test case output
 - whether your program ran correctly on it or not
 - optionally, any other remarks

 test: see if the distance is correct
 - Input : AACCA
           TAA
 - Output: Edit distance = 5
        A T 1
        A A 0
        C - 2
        C - 2
        A A 0
    Execution time is - seconds
- The the program ran correctly on it



### Specs
Your Computer
Memory: LPDDR4-4266MHZ (ex: 8gb, DDR4)
Processors: R7 5800U (ex: i5-8500 @ 3.00 GHz x6)

Partner's Computer
Memory: (ex: 8gb, DDR4)
Processors: (ex: i5-8500 @ 3.00 GHz x6)

### Runs
Fill in the table with the results of running your code on both your and your partner's computers.

| data file     | distance | memory (mb) | time (seconds) | partner time (N/A) |
|---------------|----------|-------------|----------------|--------------|
|ecoli2500.txt  |    118   |  24.07 MB   | 0.116228       |              |
|ecoli5000.txt  |    160   |  95.76 MB   | 0.475475       |              |
|ecoli10000.txt |    223   |  382.1 MB   | 1.82397        |              |
|ecoli20000.txt |    3135  |  1.491 GB   | 8.03783        |              |
|ecoli50000.txt |    N/A   |             |                |              |
|ecoli100000.txt|    N/A   |             |                |              |

Here is an example from another computer for some of the files.

| data file    | distance | time (s) |
|--------------|----------|----------|
|ecoli2500.txt |      118 |    0.171 |
|ecoli5000.txt |      160 |    0.529 |
|ecoli7000.txt |      194 |    0.990 |
|ecoli10000.txt|      223 |    1.972 |
|ecoli20000.txt|     3135 |    7.730 |

### Time
Assume the two strings are the same length (M = N).  By applying the doubling method to the data points that you obtained, estimate the running time of youu program in seconds as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input your program can handle if it is limited to one day of computation.

Provide a brief justification/explanation of how you applied the doubling method, and if you data seems not to work, describe what went wrong and use the sample data instead.
 - a = 1.898144125e−8
 - b = 2
 - largest N = 21436.1

### Memory
Assume the two strings are the same length (M = N).  Look at your code and determine how much memory it requires as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input size your computer can handle if limited to 8GiB of RAM.
 - a = 4
 - b = 2
 - largest N = 46340, assuming that 8GB is 8,589,934,592 bytes

### Valgrind
Run valgrind and list any errors you see.  Identify whether the memory usage reported by valgrind almost matches the calculations in the previous section.

No error with valgrind. The calculation matches the predictions in the previous section.

## Pair Programming
If you worked with a partner, do you have any remarks on the pair programming method? E.g., how many times did you switch, what are the tradeoffs of driving vs. navigating, etc.?

No partner, so N/A

## Extra Credit
Anything special you did.  This is required to earn bonus points.

ecoli10000.txt as example file.
            | time (seconds) |
std::min3:      2.27108

custom min3:    1.82397

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

Michael Doan