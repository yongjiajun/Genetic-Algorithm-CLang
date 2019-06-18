/******************************************************************************
** Student name: 	Jia Jun Yong
** Student number: 	s3688090
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "drive.h"
#include "invector.h"
#include "pop.h"
#include "gene.h"

#ifdef DEBUG

/* debug pcbmill function */
void test_pcbmill(void){
	Gene *g, *p1, *p2, *c, *m;
	CreateFn createRanChrom;
	MutateFn mutGene;
	CrossOverFn crossGene;

	createRanChrom = &create_pcbmill_chrom;
	mutGene = &mutate_pcbmill;
	crossGene = &crossover_pcbmill;
	
	printf("PCBMILL gene:\n");
	g = gene_create_rand_gene(TEST_ALLELE_LEN, createRanChrom);
	gene_print(g);
	printf("Mutate: \n");
	m = mutGene(g);
	gene_print(m);
	gene_free(g);
	gene_free(m);
	printf("PCBMILL genes:\n");
	p1 = gene_create_rand_gene(TEST_ALLELE_LEN, createRanChrom);
	p2 = gene_create_rand_gene(TEST_ALLELE_LEN, createRanChrom);
	gene_print(p1);
	gene_print(p2);
	printf("Crossover: \n");
	c = crossGene(p1, p2);
	gene_print(c);
	gene_free(p1);
	gene_free(p2);
	gene_free(c);
}

/* debug minfn function */
void test_minfn(void){
	Gene *g, *p1, *p2, *c, *m;
	CreateFn createRanChrom;
	MutateFn mutGene;
	CrossOverFn crossGene;
	
	createRanChrom = &create_minfn_chrom;
	mutGene = &mutate_minfn;
	crossGene = &crossover_minfn;

	printf("MINFN gene:\n");
	g = gene_create_rand_gene(TEST_ALLELE_LEN, createRanChrom);
	gene_print(g);
	printf("Mutate: \n");
	m = mutGene(g);
	gene_print(m);
	gene_free(g);
	gene_free(m);
	printf("MINFN genes:\n");
	p1 = gene_create_rand_gene(TEST_ALLELE_LEN, createRanChrom);
	p2 = gene_create_rand_gene(TEST_ALLELE_LEN, createRanChrom);
	gene_print(p1);
	gene_print(p2);
	printf("Crossover: \n");
	c = crossGene(p1, p2);
	gene_print(c);
	gene_free(p1);
	gene_free(p2);
	gene_free(c);
}

/* test debug functions */
int main(int argc, char *argv[]){
	test_minfn();
	printf("\n");
	test_pcbmill();
	return EXIT_SUCCESS; 
}

#else

/* set up pop lists */
Boolean setupPop(Pop_list *pList, Pop_list *pTemp, char *type, char *argv[])
{
	CreateFn createRanChrom;
	MutateFn mutGene;
	CrossOverFn crossGene;
	EvalFn evalGene;

	if (strcmp(argv[geneType], CMD_ARG_MINFN) == SAME_STR)
	{
		createRanChrom = &create_minfn_chrom;
		mutGene = &mutate_minfn;
		crossGene = &crossover_minfn;
		evalGene = &eval_minfn;
		*type = TYPE_MINFN;

	}
	else if (strcmp(argv[geneType], CMD_ARG_PCBMILL) == SAME_STR)
	{
		createRanChrom = &create_pcbmill_chrom;
		mutGene = &mutate_pcbmill;
		crossGene = &crossover_pcbmill;
		evalGene = &eval_pcbmill;
		*type = TYPE_PCBMILL;
	}
	else{
		printf("incorrect 2nd argument\n");
		return FALSE;
	}
	pop_set_fns(pList, createRanChrom, mutGene, crossGene, evalGene);
	pop_set_fns(pTemp, createRanChrom, mutGene, crossGene, evalGene);
	return TRUE;
}

/* read integers from arguments */
Boolean getInteger(int argc, char *argv[], int *aSize, int *pSize, int *nGen)
{
	if (isdigit(*argv[alleleSize]) && isdigit(*argv[popSize]) 
		&& isdigit(*argv[numGen]))
	{
		*aSize = atoi(argv[alleleSize]);
		*pSize = atoi(argv[popSize]);
		*nGen = atoi(argv[numGen]);

		if (!(*aSize > INT_LIMIT) || !(*pSize > PSIZE_LIMIT)
			 || !(*nGen >= INT_LIMIT))
		{
			printf("invalid integer argument\n");
			return FALSE;
		}
	}
	else{
		printf("invalid integer argument\n");
			return FALSE;
	}
	return TRUE;
}

/* check number of arguments */
Boolean argNumCheck(int argc, char *argv[])
{
	if (argc > CMD_ARG_MAX || argc < CMD_ARG_MIN)
	{
		printf("main: incorrect number of arguments\n");
		return FALSE;
	}
	return TRUE;
}

/* main program function */
int main(int argc, char *argv[]){
	int aSize, pSize, nGen, i;
	char type;
	Boolean getIntegerOK, argNumChecked, fileReadSuccess;
	FILE *input, *output;
	InVTable *invt;
	Pop_list *pList, *pTemp;
	pop_init(&pList);
	pop_init(&pTemp);
	srand(SRAND_SEED);
	/* verify number of arguments */
	argNumChecked = argNumCheck(argc, argv);
	if (argNumChecked == FALSE)
		return EXIT_FAILURE;
	/* verify existance of input file */
	input = fopen(argv[inputFile], "r");
	if (input == NULL) {
		printf("Failed to open invector file\n");
		return EXIT_FAILURE;
	}
	/* read integers from arguments */
	getIntegerOK = getInteger(argc, argv, &aSize, &pSize, &nGen);
	if (getIntegerOK == FALSE)
		return EXIT_FAILURE;
	/* initialise invt */
	invt = malloc(sizeof(InVTable));
	invector_init(invt);
	/* read input file */
	fileReadSuccess = invector_read(aSize, input, invt, type);
	if (fileReadSuccess == FALSE)
		return EXIT_FAILURE;
	setupPop(pList, pTemp, &type, argv);
	/* redirect output to file */
	if (argc == CMD_ARG_MAX)
		output = freopen(argv[outputFile], "w", stdout);
	/* generate initial list, then evolve list */
	pop_generate(pList, aSize, invt, pSize);
	for (i = 0; i < nGen; i++) {
		evolve(pTemp ,pList, invt, pSize);
		pop_print_fittest(pList);
	}
	pop_freeAll(pList);
	/* close input and output files */
	fclose(input);
	if (argc == CMD_ARG_MAX)
		fclose(output); 
	free(invt);
	return EXIT_SUCCESS;
}

#endif
