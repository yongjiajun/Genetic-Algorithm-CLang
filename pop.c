/******************************************************************************
** Student name: 	Jia Jun Yong
** Student number: 	s3688090
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "pop.h"

/* initialise pop list */
Boolean pop_init(Pop_list **pop){
	Pop_list *pList;
	pList = malloc(sizeof(Pop_list));
	pList->head= malloc(sizeof(Pop_node));
	pList->head = NULL;
	pList->count = 0;
	*pop = pList;
	return TRUE;
}

/* set pop list's functions */
void pop_set_fns(Pop_list *p,CreateFn cf,MutateFn mf,CrossOverFn cof,EvalFn ef)
{
	p->create_rand_chrom = cf;
	p->mutate_gene = mf;
	p->crossover_genes = cof;
	p->evaluate_fn = ef;
}

/* print pop list's fittest gene */
void pop_print_fittest(Pop_list *p){
	static int run = 0;
	printf("Gen: %d ", run);
	gene_print(p->head->gene);
	run++;
}

/* insert Gene into pop list and sort list */
void pop_insert(Pop_list *p, Gene *newGene)
{
 	Pop_node *preNode, *currNode, *newNode;

    newNode = malloc(sizeof(*newNode));
    newNode->gene = malloc(sizeof(*newNode->gene));

    *newNode->gene = *newGene;
    newNode->next = NULL;
    preNode = NULL;
    currNode = p->head;

    while(currNode != NULL)
    {
		/* sort fitness from highest to lowest */
        if(newGene->fitness > currNode->gene->fitness)
            break;

        preNode = currNode;
        currNode = currNode->next;
    }

    if(p->head == NULL)
        p->head = newNode;
    else if(preNode == NULL)
    {
        /* Insert at the head */
        newNode->next = p->head;
        p->head = newNode;
    }
    else
    {
        preNode->next = newNode;
        newNode->next = currNode;
    }
    p->count++;
	return;
}

/* free pop list but not its head */
void pop_free(Pop_list *p)
{
	Pop_node *current, *next;
	int i;
	i = HEAD_OFFSET;
	current = p->head->next;
	while (current->next != NULL)
	{
		if (i == p->count)
			break;
		next = current->next;
		gene_free(current->gene);
		free(current);
		current = next;
	}
	p->head = NULL;
	p->count = 0;
	free(p);
}

/* free whole pop list */
void pop_freeAll(Pop_list *p)
{
	Pop_node *current, *next;
	current = p->head;
	while (current != NULL)
	{
		next = current->next;
		gene_free(current->gene);
		free(current);
		current = next;
	}
	p->head = NULL;
	p->count = 0;
	free(p);
}

/* normalise pop list */
void pop_normalise(Pop_list *p)
{
	Pop_node *pointer;
	double totalFitness;
	totalFitness = 0;

	pointer = p->head;

	while (pointer != NULL)
	{
		totalFitness += pointer->gene->fitness;
		pointer = pointer->next;
	}

	pointer = p->head;
	
	while (pointer != NULL)
	{
		gene_normalise_fitness(pointer->gene, totalFitness);
		pointer = pointer->next;
	}
}

/* select gene by doing fitness proportionate selection from pop list */
Gene * selectGene(Pop_list *p)
{
	double random, tempFitness;
	Pop_node *pointer;
	Gene *g;
	tempFitness = 0;
	pointer = p->head;
	/* random a number between 0 and 1 */
	random = ((double)rand()/(double)(RAND_MAX)) * 1; 

	while (pointer != NULL)
	{
		tempFitness += pointer->gene->fitness;
		if (tempFitness >= random)
		{
			g = pointer->gene;
			break;
		}
		g = pointer->gene;
		pointer = pointer->next;
	}
	return g;
}

/* generate initial list */
void pop_generate(Pop_list *p, int aSize, InVTable * invt, int pSize)
{
	Gene *tempGene;
	int i;

	for (i = 0; i < pSize; i++)
	{
		tempGene = gene_create_rand_gene(aSize, p->create_rand_chrom);
		gene_calc_fitness(tempGene, p->evaluate_fn, invt);
		pop_insert(p, tempGene);
	}
	pop_normalise(p);
}

/* evolve genes */
void evolve(Pop_list *p, Pop_list *temp, InVTable *invt, int pSize)
{
	int random, i;
	Pop_list *toBeFreed;
	Gene *g, *g1, *toBeAdded;
	pop_init(&toBeFreed);
	
	toBeAdded = temp->head->gene;
	gene_calc_fitness(toBeAdded, p->evaluate_fn, invt);
	pop_insert(p, toBeAdded);

	for (i = 0; i < pSize - 1; i++)
	{
		random = rand() % RANDOM_MAX + 1;

		if (random < MUTATE_RATE)
		{
			g = selectGene(temp);
			toBeAdded = p->mutate_gene(g);
		}
		else
		{
			g = selectGene(temp);
			g1 = selectGene(temp);	
			toBeAdded = p->crossover_genes(g, g1);
		}
		gene_calc_fitness(toBeAdded, p->evaluate_fn, invt);
		pop_insert(p, toBeAdded);
	}
	toBeFreed = temp;

	pop_normalise(p);
	temp->head = p->head;
	
	p->head = NULL;	
}
