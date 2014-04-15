/*** System Interfaces ***/
#include <stdio.h>

/*** NETGEN Interfaces ***/
#include "netgen.h"

/*** Local Constants ***/
#define INPUT_FILE	1
#define INPUT_STDIN	2

/*** Local Macros ***/
#define READ(v) 		     		\
	switch( scanf("%ld", &v) ) {	\
		case 1:						\
			break;					\
		default:					\
			exit(0);				\
		}

int
main(int argc, char **argv)
{
	/* Main Variables */
	long seed, problem;
	long parms[PROBLEM_PARMS];
	long arcs;
	int i;
	
	/* I/O Variables */
	FILE * fin = NULL;
	FILE * fout = NULL;
	char filename[256];
	unsigned char flag;
	
	/* The generator accepts two forms of input: a file from where the problem
	 * params are read or an input stream from stdin. If no file is provided in
	 * command line, it is assumed that the params are to be inputed from stdin.
	 */
	if(argc == 2) {
		flag = INPUT_FILE;
	} else if(argc == 1) {
		flag = INPUT_STDIN;
	} else {
		fprintf(stderr, "Usage: ./netgen [FILE]\n");
		goto TERMINATE;
	}
	
	if(flag == INPUT_FILE) {
		fprintf(stderr, "ERROR: reading from input file still not possible.\n");
		goto TERMINATE;
	} else if(flag == INPUT_STDIN) {
		/* First read the seed and the problem: if valid, read the rest of input */
		fprintf(stdout, "Seed: ");
		READ(seed);
		fprintf(stdout, "Problem: ");
		READ(problem);

		if(seed <= 0 || problem <= 0) {
			fprintf(stderr, "Incorrect seed value or problem value.\n");
			goto TERMINATE;
		}

		for(i = 0; i < PROBLEM_PARMS; i++) {
			switch(i) {
				case 0:
					fprintf(stdout, "Number of Nodes: ");
					break;
				case 1:
					fprintf(stdout, "Number of Sources: ");
					break;
				case 2:
					fprintf(stdout, "Number of Sinks: ");
					break;
				case 3:
					fprintf(stdout, "Number of Arcs: ");
					break;
				case 4:
					fprintf(stdout, "Arc Minimum Cost: ");
					break;
				case 5:
					fprintf(stdout, "Arc Maximum Cost: ");
					break;
				case 6:
					fprintf(stdout, "Total Supply: ");
					break;
				case 7:
					fprintf(stdout, "Transshipment Sources: ");
					break;
				case 8:
					fprintf(stdout, "Transshipment Sinks: ");
					break;
				case 9:
					fprintf(stdout, "Percent of skeleton arcs given maximum cost: ");
					break;
				case 10:
					fprintf(stdout, "Percent of arcs to be capacitated: ");
					break;
				case 11:
					fprintf(stdout, "Minimum capacity for capacitated arcs: ");
					break;
				case 12:
					fprintf(stdout, "Maximum capacity for capacitated arcs: ");
					break;
				default:
					break;
			}
			READ(parms[i]);
		}
	}
	
	/* Open output file */
	sprintf(filename, "%ld", problem);
	fout = fopen(filename, "w");
	if(!fout) {
		fprintf(stderr, "Unable to open output file.\n");
		exit(0);
	}
	
	/* Output to file */
	fprintf(fout, "c NETGEN flow network generator (C version)\n");
	fprintf(fout, "c  Problem %2ld input parameters\n", problem);
	fprintf(fout, "c  ---------------------------\n");
	fprintf(fout, "c   Random seed:          %10ld\n",   seed);
	fprintf(fout, "c   Number of nodes:      %10ld\n",   NODES);
	fprintf(fout, "c   Source nodes:         %10ld\n",   SOURCES);
	fprintf(fout, "c   Sink nodes:           %10ld\n",   SINKS);
	fprintf(fout, "c   Number of arcs:       %10ld\n",   DENSITY);
	fprintf(fout, "c   Minimum arc cost:     %10ld\n",   MINCOST);
	fprintf(fout, "c   Maximum arc cost:     %10ld\n",   MAXCOST);
	fprintf(fout, "c   Total supply:         %10ld\n",   SUPPLY);
	fprintf(fout, "c   Transshipment -\n");
	fprintf(fout, "c     Sources:            %10ld\n",   TSOURCES);
	fprintf(fout, "c     Sinks:              %10ld\n",   TSINKS);
	fprintf(fout, "c   Skeleton arcs -\n");
	fprintf(fout, "c     With max cost:      %10ld%%\n", HICOST);
	fprintf(fout, "c     Capacitated:        %10ld%%\n", CAPACITATED);
	fprintf(fout, "c   Minimum arc capacity: %10ld\n",   MINCAP);
	fprintf(fout, "c   Maximum arc capacity: %10ld\n",   MAXCAP);

	/* Generate Network */
	if((arcs = netgen(seed, parms)) < 0) {
		error_exit(arcs);
	}

	/* Print Network */
	if((SOURCES - TSOURCES) + (SINKS - TSINKS) == NODES && (SOURCES - TSOURCES) == (SINKS - TSINKS) && SOURCES == SUPPLY) {
		fprintf(fout, "c\n");
		fprintf(fout, "c  *** Assignment ***\n");
		fprintf(fout, "c\n");
		fprintf(fout, "p asn %ld %ld\n", NODES, arcs);
		for(i = 0; i < NODES; i++) {
			if(B[i] > 0) {
				fprintf(fout, "n %ld\n", (long) (i + 1));
			}
		}
		for(i = 0; i < arcs; i++) {
			fprintf(fout, "a %ld %ld %ld\n", FROM[i], TO[i], C[i]);
		}	
	} else if (MINCOST == 1 && MAXCOST == 1) {
		fprintf(fout, "c\n");
		fprintf(fout, "c  *** Maximum flow ***\n");
		fprintf(fout, "c\n");
		fprintf(fout, "p max %ld %ld\n", NODES, arcs);
		for(i = 0; i < NODES; i++) {
			if(B[i] > 0) {
				fprintf(fout, "n %ld s\n", (long) (i + 1));
			} else if(B[i] < 0) {
				fprintf(fout, "n %ld t\n", (long) (i + 1));
			}
		}
		for(i = 0; i < arcs; i++) {
			fprintf(fout, "a %ld %ld %ld\n", FROM[i], TO[i], U[i]);
		}
	} else {
		fprintf(fout, "c\n");
		fprintf(fout, "c  *** Minimum cost flow ***\n");
		fprintf(fout, "c\n");
		fprintf(fout, "p min %ld %ld\n", NODES, arcs);
		for(i = 0; i < NODES; i++) {
			if(B[i] != 0) {
				fprintf(fout, "n %ld %ld\n", (long) (i + 1), B[i]);
			}
		}
		for(i = 0; i < arcs; i++) {
			fprintf(fout, "a %ld %ld %ld %ld %ld\n", FROM[i], TO[i], (long) 0, U[i], C[i]);
		}
	}
	
TERMINATE:

	fclose(fout);
	exit(EXIT_SUCCESS);
} /* END OF MAIN */
