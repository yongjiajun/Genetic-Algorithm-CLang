     /******************************************************************************
** Student name: 	Jia Jun Yong
** Student number: 	s3688090
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#ifndef POP_H
#define POP_H

#include "gene.h"
#include "invector.h"

#define MUTATE_RATE 5
#define HEAD_OFFSET 1
#define RANDOM_MAX 100

typedef struct pop_node {
	Gene *gene;
	struct pop_node *next;
} Pop_node;

typedef struct pop_list {
	/* the head of the population list */
	Pop_node *head;
	/* the size of the population */
	int count;
	/* pointers to functions to perform
 	 * gene chromosome creation, mutation,
 	 * crossover and evaluation */
	CreateFn create_rand_chrom;
	MutateFn mutate_gene;
	CrossOverFn crossover_genes;
	EvalFn evaluate_fn;
} Pop_list;

/* Create and initialise the population list to a safe state.
 * Returns TRUE on success */
Boolean pop_init(Pop_list **);

/* Set the function pointers of a population list */
void pop_set_fns(Pop_list *p,CreateFn cf,MutateFn mf,CrossOverFn cof,EvalFn ef);

/* This function causes details of the fittest gene of the generation to 
 * be printed out.
 * The function also prints out the number of the current generation.
 * This function must not be able to access any generation value outside
 * of the function. */
void pop_print_fittest(Pop_list *p);

/* TO DO - other functions as appropriate */

void pop_insert(Pop_list *, Gene *);
void pop_free(Pop_list *);
void pop_normalise(Pop_list *);
Gene * selectGene (Pop_list *);
void pop_generate(Pop_list *, int , InVTable *, int);
void  evolve(Pop_list *, Pop_list *,  InVTable *, int);
void cloneList(Pop_list *, Pop_list*);
void pop_freeAll(Pop_list *);
#endif
