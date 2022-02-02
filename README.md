# NETGEN 

This is a benchmark instance generator for usual graph problems written in C. The graph generation metholody used follows 
Klingman, Napier and Stutz's methodology as proposed in their paper - [Linked](https://pubsonline.informs.org/doi/10.1287/mnsc.20.5.814)

```
NETGEN: A Program for Generating Large Scale Capacitated Assignment, Transportation, and Minimum Cost Flow Network Problems
D. Klingman, A. Napier, J. Stutz
Published Online:1 
Jan 1974
https://doi.org/10.1287/mnsc.20.5.814
```


The following changes have been made:
* Declarations and definitions have been separated between severel header files,
  each one is an individual interface that can be used alone. The new files are
  random.h, where declarations for the portable random generator are made, 
  index.h, the interface for the index lists. The header netgen.h has also been
  repurposed to conform to a more modern style.
* The files random.c, index.c and netgen.c have been refactored using better
  identation (there were identation issues previously), brackets have been used
  to clarify some parts of the source code.
* The file netgen.h no longer holds the main function of the NETGEN C generator.
  The rationale behind this decision is to allow the usage of netgen as an
  interface that can be adapted. The main function is located in the file named
  main.c, that holds only the main function and several macros to make it easy
  to perform some actions.
* Added two directories bin/ and src/. The bin/ is where the generator is put
  by the makefile. The src/ is where all source code is stored. At the root
  directory we now have just the bin/ and src/ directories, the makefile and
  this README.

NO CHANGES HAVE BEEN MADE TO THE SOURCE CODE STRUCTURE: THE NETGEN GENERATOR
WORKS AND GENERATES THE NETWORKS IN EXACTLY THE SAME MANNER AS IN THE ORIGINAL
SOURCE CODE. THE PURPOSE OF THE CHANGES MADE IS JUST TO ELIMINATE SOME
UNNECESSARY OBSCURITY IN THE ORIGINAL SOURCE CODE.

NOTE: The compilation of the file netgen.c produces a lot of warnings with the
current flags set for gcc (-Wall -Wextra). All these warnings are about the
several comparisons between signed and unsigned integer variables. As of now, 
no problem has been found that can damage the overall functionality of the
generator. If needed, remove the flags from the makefile. In the future I may
(given I have the time) correct some of these warnings, always without messing
with the overall code structure.


# INSTRUCTION for Installation >>

mkdir bin
make
