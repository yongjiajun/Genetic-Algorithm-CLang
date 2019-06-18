/******************************************************************************
** Student name: 	Jia Jun Yong
** Student number: 	s3688090
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#ifndef DRIVE_H
#define DRIVE_H

#include "utility.h"

/* The seed value for srand */
#define SRAND_SEED 1

/* Possible valid values of argv[geneType] (see the enum below)*/
#define CMD_ARG_MINFN "minfn"
#define CMD_ARG_PCBMILL "pcbmill"

#define TYPE_MINFN 'm'
#define TYPE_PCBMILL 'p'

/* The maximum number of command line arguments expected */
#define CMD_ARG_MAX 7
#define CMD_ARG_MIN 6

/* The number of alleles for use in the two test functions 
 * test_pcbmill() and test_minfn() */
#define TEST_ALLELE_LEN 6

#define SAME_STR 0
#define INT_LIMIT 0
#define MAX_LIMIT 60
#define PSIZE_LIMIT 1

/* Avoid having 'magic numbers' when using argv ... */
enum argtype {geneType = 1, alleleSize, popSize, numGen, inputFile, outputFile};

/* Functions for testing creation of random genes, crossover and mutation.
 * These functions are only called if a DEBUG macro has been defined during 
 * compilation */
void test_pcbmill(void);
void test_minfn(void);


#endif
