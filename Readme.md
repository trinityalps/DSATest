## DSA Test Erik Stansbury:
### General Discussion:
This code takes a file and converts it into a string. Then it takes that string and breaks it into a vector of floats. It then takes those floats and uses an assumed deviation checks if the points are close enough together to count as part of a cluster. It then averages the points to get a centre. The most interesting part, also the part that took the longest, was determining how to deal with the edge case of a cluster that wraps around 360 back to 0.
### Why this way:
The reason I chose to do it this way was quite simply it was the most straightforward solution I thought of. It isn't the most robust way to deal with this but tried to leverage as many simplifying assumptions as possible. I.E. just using the given files, assuming a standard deviation, assuming a minimum amount of points in a cluster. 
### Bugs:
One of the largest pitfalls is the assumptions made about good well formatted data. If the data is ill-formatted this code would instantly stop working, however for the given test, it works. 
An error I assume that exists in visual studios is the conversion between a string value of "70.4" to a float creates a float that is much longer but less precise, I.E 70.4 becomes 73.9999998. I couldn't figure out where this was coming from but for now I am assuming there is something with visual studios implementation that makes it slightly off. This problem creates outputs which are slightly off from the expected results. 

### Simplifying assumptions made:
1. Using the provided inputs and outputs, it's clear that the largest deviation between points in a cluster is somewhere around 6.5, so a constant was made to represent a safe assumed deviation from test data. In this case it's set to 7 to provide some buffer
2. Assume a cluster requires a specific number of points, again this was determined from code, and seems to be at a minimum to be 7 points in a cluster
3. Assume the points come in order. If they didn't a sorting algorithm would have to be added.

### Critiques of the problem
One of my many issues with this is there is a lot of fluff to this problem that could easily be avoided for a simple problem. Having a complex explanation with nuances is great for large problems, however for a simpler problem like this, it creates a game of "find the important info" which I guess is probably intentional. 
From a robotics perspective this problem is what is the robot counting as a corner. Looking at the images provided, it isn't clear what counts as a corner and not a corner. There is also the issue that a very smooth surface may not be seen as an obstacle but without more test data it isn't easy to tell if it's working correctly. The other issue is you would need filters to filter out corners and obstacles that are just part of the robot. Otherwise it'll try to avoid itself. 
### How this was made.
This code was developped in microsoft visual studios and runs as a simple console exe, The console program only needs the input text documents in it's folder to run (It looks for Input0.txt to Input4.txt)
