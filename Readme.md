##DSA Test Erik Stansbury:
#General Discussion:
This code takes a file and converts it into a string. Then it takes that string and breaks it into a vector of floats. It then takes those floats and uses an assumed deviation checks if the points are close enough together to count as part of a cluster. It then averages the points to get a centre. 
#Bugs:
One of the largest pitfalls is the assumptiuons made about good well formated data. If the data is ill-formated this code would instantly stop working, however for the given test, it works. 
An error I assume that exists in visual studios is the conversion between a string value of "70.4" to a float creates a float that is much longer but less precise, I.E 70.4 becomes 73.9999998. I couldn't figure out where this was coming from but for now I am assuming there is something with visual studios implemntation that makes it slightly off. This problem creates outputs which are slightly off from the expected results. 

#Simplifying assumptions made:
1. Using the provided inputs and outputs, it's clear that the largest deviation between points in a cluster is somewhere around 6.5, so a constant was made to represent a safe assumed deviation from test data. In this case it's set to 7 to provide some buffer
2. Assume a cluster requires a specific number of points, again this was determined from code, and seems to be at a minimum to be 7 points in a cluster
3. Assume the points come in order. If they didn't a sorting algorithm would have to be added.
