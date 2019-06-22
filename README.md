# Genetic Algorithm

###### Project for Advanced Programming Techniques Assignment 2 [94/100%], RMIT University 2018

Implemented various advanced core functions in **C language [ANSI / ISO C]** such as gene mutation/crossover. 

More info about the project can be found in the [assignment spec](https://github.com/yongjiajun/Genetic-Algorithm-CLang/blob/master/specs/AssignmentSpecs.pdf), while other supporting documents can be found [here](https://github.com/yongjiajun/Genetic-Algorithm-CLang/tree/master/specs).

*It's best to be compiled and ran on Linux.

#### To compile:

```bash
make
```

#### To run:

```bash
./ga geneType alleleSize popSize numGen inputFile [outputFile]
```

where: 

- **./ga** is the name of the executable 

- **geneType** is a string, of either *minfn* or *pcbmill* – indicating which problem the GA is being applied to 

- **alleleSize** is a positive non-zero integer specifying the length of a candidate solution (chromosome) 

- **popSize** is a positive non-zero integer specifying the number of candidate solutions in the population 

- **numGen** is a positive integer specifying the number of generations to run the GA for 

- **inputFile** is a string specifying the name of a data file to read [either *minfnin*.*dat* or *pcbin.dat*]

- **outputFile** is an optional string specifying the name of an output file to write. If specified, there will be no console output but output will be stored into the output file.

##### For example:

```bash
./ga minfn 10 20 100 minfnin.dat
```

where:

- **geneType** = *minfn*
- **alleleSize** = *20*
- **popSize** = *20*
- **numGen** = *100*
- **inputFile** = *minfnin.dat*
- **outputFile** = *none*

or

```bash
./ga pcbmill 10 20 100 pcbin.dat output.txt
```

where:

- **geneType** = *pcbmill*
- **alleleSize** = *10*
- **popSize** = *20*
- **numGen** = *100*
- **inputFile** = *pcbin.dat*
- **outputFile** = *output.txt*

##### To cleanup:

```bash
make clean
```

