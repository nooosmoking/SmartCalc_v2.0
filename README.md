# SmartCalc v2.0

Implementation of SmartCalc v2.0.

The SmartCalc v1.0 program must be implemented:

- The program must be built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, test, gcov_report. 
- Installation directory could be arbitrary, except the building one GUI implementation, based on Qt
- Calculating arbitrary bracketed arithmetic expressions in infix notation
- Calculate arbitrary bracketed arithmetic expressions in infix notation with substitution of the value of the variable x as a number
- Plotting a graph of a function given by an expression in infix notation with the variable x (with coordinate axes, mark of the used scale and an adaptive grid)
- It is not necessary to provide the user with the ability to change the scale Domain and codomain of a function are limited to at least numbers from -1000000 to 1000000
- To plot a graph of a function it is necessary to additionally specify the displayed domain and codomain
- Verifiable accuracy of the fractional part is at least to 7 decimal places
- Users must be able to enter up to 255 characters Bracketed arithmetic expressions in infix notation must support arithmetic operations and mathematical functions
