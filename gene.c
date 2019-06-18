/******************************************************************************
** Student name: 	Jia Jun Yong
** Student number: 	s3688090
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "gene.h"

/* create pcbmill chromosomes */
int * create_pcbmill_chrom(int numAlleles){
	int *chrom, i, j, temp;

	chrom = calloc(numAlleles, sizeof(int));

	for (i = 0; i < numAlleles; i++)
	{
		chrom[i] = i;
	}

	/* randomly swap chromosome */
	for (i = 0; i < numAlleles; i++)
	{
		j = (rand() % (i+1));
		temp = chrom[i];
		chrom[i] = chrom[j];
		chrom[j] = temp;
	}
	
	return chrom;
}

/* create minfn chromosomes */
int * create_minfn_chrom(int numAlleles){
	int *chrom, i;

	chrom = calloc(numAlleles, sizeof(int));

	for (i = 0; i < numAlleles; i++)
	{
		chrom[i] = rand() % MINFN_MAX;
	}

	return chrom;
}

/* mutate pcbmill gene */
Gene * mutate_pcbmill(Gene *g){
	int randPosA, randPosB, chrom, i;
	Gene *newGene;

	newGene = malloc(sizeof(Gene));

	newGene->chromosome = calloc(g->num_alleles, sizeof(int));
	newGene->num_alleles = g->num_alleles;
	newGene->raw_score = 0;
	newGene->fitness = 0;

	for (i = 0; i < newGene->num_alleles; i++)
	{
		newGene->chromosome[i] = g->chromosome[i];
	}

	/* random positions of chromosomes to be swapped */
	randPosA = rand() % newGene->num_alleles;
	do
	{
		randPosB = rand() % newGene->num_alleles;
	} while (randPosB == randPosA);

	#ifdef DEBUG
		randPosA = 2;
		randPosB = 4;
	#endif
	
	/* swap chromosomes */
	chrom = newGene->chromosome[randPosA];
	newGene->chromosome[randPosA] = newGene->chromosome[randPosB];
	newGene->chromosome[randPosB] = chrom;

	return newGene;
}

/* mutate minfn gene */
Gene * mutate_minfn(Gene *g){
	int randVal, randPos, i;
	Gene *newGene;

	newGene = malloc(sizeof(Gene));

	newGene->chromosome = calloc(g->num_alleles, sizeof(int));
	newGene->num_alleles = g->num_alleles;
	newGene->raw_score = 0;
	newGene->fitness = 0;

	for (i = 0; i < newGene->num_alleles; i++)
	{
		newGene->chromosome[i] = g->chromosome[i];
	}
	/* random new chromosome value at random position */
	randVal = (rand() % MINFN_MAX) + 1;
	randPos = (rand() % newGene->num_alleles);

	#ifdef DEBUG
		randPos = 2;
	#endif

	newGene->chromosome[randPos] = randVal;
	return newGene;
}

/* crossover pcbmill gene */
Gene * crossover_pcbmill(Gene *g1, Gene *g2){
	Gene *g;
	int randPosA, randPosB, alleleSize, pointer, i, j;
	Boolean exist;
	pointer = 0;
	alleleSize = g1->num_alleles;
	g = malloc(sizeof(Gene));
	g->chromosome = calloc(alleleSize, sizeof(int));
	g->num_alleles = alleleSize;
	g->raw_score = 0;
	g->fitness = 0;
	randPosA = rand() % alleleSize;
	do {
		randPosB = rand() % alleleSize;
	} while (!(randPosA <= randPosB));

	#ifdef DEBUG
		randPosA = 2;
		randPosB = 4;
	#endif
	/* copy some of Gene g1's chromsomes to g's randomly */
	do{
		g->chromosome[pointer] = g1->chromosome[randPosA];
		if (randPosA == randPosB)
			break;
		else {
			randPosA++;
			pointer++;
		}
	} while (randPosA != randPosB + 1);
	/* copy some of Gene g2's chromsomes to g's sequentially */
	for (i = 0; i < alleleSize; i++) {
		exist = FALSE;
		for (j = 0; j <= pointer; j++) {
			if (g->chromosome[j] == g2->chromosome[i]) {
				exist = TRUE;
				break;
			}
		}
		if (exist == FALSE) {
			g->chromosome[j] = g2->chromosome[i];
			pointer++;
		}
	}
	return g;
}

/* crossover minfn gene */
Gene * crossover_minfn(Gene *g1, Gene *g2){
	Gene *g;
	int randPos, alleleSize, alleleHalf, i;

	alleleSize = g1->num_alleles;

	alleleHalf = (alleleSize + (2+1)/2) / 2;

	g = malloc(sizeof(Gene));

	g->chromosome = calloc(alleleSize, sizeof(int));
	g->num_alleles = alleleSize;
	g->raw_score = 0;
	g->fitness = 0;

	randPos = rand() % alleleSize;

	#ifdef DEBUG
		randPos = 2;
	#endif
	/* copy some of Gene g1's chromsomes to g's */
	if (randPos < alleleHalf)
	{
		for (i = 0; i < alleleHalf; i++)
			g->chromosome[i] = g1->chromosome[i];
		for (i = alleleHalf; i < alleleSize; i++)
			g->chromosome[i] = g2->chromosome[i];
	}
	else
	{
		for (i = alleleHalf; i < alleleSize; i++)
			g->chromosome[i] = g2->chromosome[i];
		for (i = 0; i < alleleHalf; i++)
			g->chromosome[i] = g1->chromosome[i];
	}

	return g;
}

/* evaluate pcbmill gene */
double eval_pcbmill(InVTable *invt, Gene *gene){
	int i, indexA, indexB;
	double result, tempX, tempY, temp;
	result = 0;
	for (i = 0; i < gene->num_alleles - 1; i++)
	{
		indexA = gene->chromosome[i];
		indexB = gene->chromosome[i+1];
		tempX = invt->table[indexB][0] - invt->table[indexA][0];
		tempX = pow(tempX, SQUARE);
		tempY = invt->table[indexB][1] - invt->table[indexA][1];
		tempY = pow(tempY, SQUARE);
		temp = tempX + tempY;
		temp = sqrt(temp);
		result += temp;
	}
	return result;
}

/* evaluate minfn gene */
double eval_minfn(InVTable *invt, Gene *gene){
	int i;
	double result;
	result = 0;
	
	for (i = 0; i < invt->width - 1; i++)
	{
		result += invt->table[MINFN_TABLE_NUM][i]*gene->chromosome[i];
	}
	
	result -= invt->table[MINFN_TABLE_NUM][invt->width - 1];
	result = fabs(result);
	return result;
}

/* create random gene */
Gene * gene_create_rand_gene(int numAlleles, CreateFn create_chrom){
	int *chromosome;
	Gene *gene;
	chromosome = 0;
	
	chromosome = create_chrom(numAlleles);

	gene = malloc(sizeof(Gene));
	gene->chromosome = chromosome;
	gene->num_alleles = numAlleles;
	gene->raw_score = 0;
	gene->fitness = 0;

	return gene;
}

/* calculate gene's fitness */
void gene_calc_fitness(Gene *gene, EvalFn evaluate_fn, InVTable *invTab){
	double fitness, rawScore;
	rawScore = evaluate_fn(invTab, gene);
	gene->raw_score = rawScore;
	fitness = 1/(rawScore + 1);
	gene->fitness = fitness;
}

/* normalise gene fitness */
void gene_normalise_fitness(Gene *gene, double total_fitness){
	gene->fitness = gene->fitness/total_fitness;
}

/* free gene's allocated memory */
void gene_free(Gene *gene){
	free(gene->chromosome);
	free(gene);
}

/* get gene's fitness */
double gene_get_fitness(Gene *gene){
	return gene->fitness; 
}

/* print gene's details */
void gene_print(Gene *gene) {
	int i;
	printf("chrom: ");
	for (i = 0; i < gene->num_alleles; i++)
	{
		if (i == gene->num_alleles - 1)
			printf("%d ", gene->chromosome[i]);
		else
			printf("%d, ", gene->chromosome[i]);
	}
	printf("fit: %.3f ", gene->fitness);
	printf("raw: %.3f\n", gene->raw_score);
}
