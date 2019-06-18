/******************************************************************************
** Student name: 	Jia Jun Yong
** Student number: 	s3688090
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "invector.h"

/* verify input file, then store in InVTable */
Boolean invector_read(int alleleSize, FILE *inputFile, InVTable *invt, 
	char type) 
{
	char readStr[INV_LEN], *label, *value, *checkNewLine;
	int tableIndex, arrayIndex, alleleCounter, i, numInv;
	InVector invTable;
	numInv = 0;

	/* read input file line by line */
	while(!feof(inputFile)) {
		alleleCounter = 0;
		arrayIndex = 0;
		checkNewLine = fgets(readStr, INV_LEN, inputFile);
		/* check if new line is empty or new line */
		if (checkNewLine == NULL || strcmp(checkNewLine, "\n") == SAME_STR) {
			if (numInv == EMPTY) {
				printf("Error: must have at least 1 invector\n");
				return FALSE;
			}
			else if (checkNewLine == NULL)
				break;
			else if (strcmp(checkNewLine, "\n") == SAME_STR) {
				printf("Error: invector string invalid\n");
				return FALSE;
			}
		}
		label = strtok(readStr, INV_DELIM1);
		tableIndex = atoi(strtok(NULL, INV_DELIM2));
		/* check minfn table limit */
		if (numInv > MINFN_TABLE_LIMIT && type == MINFN_TYPE) {
			printf("too many input vectors for minfn data file\n");
			return FALSE;
		}
		/* check if the label "InputVector" is present */
		if (strcmp(label, INV_LABEL) != SAME_STR || numInv != tableIndex) {
			printf("invalid invector file\n");
			return FALSE;
		}
		/* read allele values in a line */
		while (TRUE) {
			value = strtok(NULL, INV_DELIM3);
			if (value == '\0' || (strcmp(value, "\n") == SAME_STR)) {
				alleleCounter = arrayIndex - 1;
				break;
			}
			invTable[arrayIndex] = atoi(value);
			arrayIndex++;
		} 
		if (arrayIndex > INVT_WIDTH) {
			printf("Error: invector string invalid\n");
			return FALSE;
		}
		else if (alleleCounter != alleleSize && type == MINFN_TYPE) {
			printf("allelesize mismatch with vector size\n");
			return FALSE;
		} 
		for (i = 0; i < arrayIndex; i++) {
			invt->table[numInv][i] = invTable[i];
		}
		numInv++;
		invt->width = arrayIndex;
	}
	if (numInv != alleleSize && type == PCBMILL_TYPE) {
		printf("allelesize mismatch with num vectors\n");
		return FALSE;
	}
	numInv++;
	invt->tot = numInv;
	return TRUE;
}

/* initialise InVTable */
void invector_init(InVTable *invt) {
	invt->tot = 0;
	invt->width = 0;
}
