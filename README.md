# lab2_morse
Notes: 
- I prescaled by a factor of 1024
- the dds array stores 5 dots(1)/dashes(2) and i tracks the next index to be filled in this array
- I changed the timing on the dots/dashes/spaces to make it easier to demonstrate:
    -a dot is between 30 and 200ms
    -a dash is any press longer than 200ms (you can see the commented-out 400ms upper bound)
    -a space is longer than 800ms unpressed
- I also added polling in the main loop to make the letters print before the next letter starts (i.e. a space is assumed after 800ms unpressed)
