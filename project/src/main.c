#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include "../include/gc.h"
#include "../include/utils.h"

#define OUTPUT_FILE_NAME_MAX_LEN 100

const char* program_name;

void doit(void (*mark_sweep)(), 
			int num_objects, 
			int num_fields, 
			double pr_adj, 
			double pr_src, 
			bool verbose,
			bool timeit){
				
	if(verbose){
		printf("\n");
		printf("Initializing...\n");
	}
	
	init_gc(num_objects, num_fields * 8);
	
	/*
	 * We construct NUM_OBJECTS objects and set all of them as roots.
	 * Then we randomly build references between them.
	 * Since every object is root, the GC doesn't free any memory.
	 */
	 
	srand(time(NULL));
	
	uintptr_t objects[num_objects];
	int i;
	
	if(verbose){
		printf("Creating objects...\n");
	}
	
	for(i = 0; i < num_objects; i++){
		objects[i] = (uintptr_t) new();
		double u = rand() / (double) RAND_MAX;
		/* With probability pr_src, objects[i] will be an root object */
		if(u < pr_src){
			set_root((void *) objects[i]);
		}
	}
	
	for(i = 0; i < num_objects; i++){
		int j;
		for(j = 0; j < num_fields; j++){
			double u = rand() / (double) RAND_MAX;
			/* With probability pr_adj, objects[i]->o(j + 1) will be an outgoing pointer */
			if(u < pr_adj){
				uintptr_t *ptr = (uintptr_t *)((uintptr_t) objects[i] + 8 * j);
				
				/* Two pointers could reference the same object */
				*ptr = objects[random(0, num_objects - 1)];
			}
		}
	}
	
	if(verbose){
		print_status();
		printf("Running the GC...\n");	
	}
	
	unsigned long long start, end;
	START_CLOCK(start);
	mark_sweep();
	STOP_CLOCK(end);
	
	if(timeit){
		printf("%llu", end - start);
	}
	
	if(verbose){
		print_status();
		printf("Terminating...\n");
	}
	
	terminate_gc();
}

void print_help(){
	printf("Usage of the program:\n");
	printf("\t%s <options> <implementation> [parameters]\n", program_name);
	printf("The available options are:\n");
	printf("\t> -h, -help\n\tPrints help information\n");
	printf("\t> -v, -verbose\n\tPrints additional information alongside the execution of the program\n");
	printf("\t> -f, -file <file_name>\n\tOutput to a specific file\n");
	printf("\t> -t, -timeit\n\tMeasure execution time\n");
	printf("The available Mark-Sweep implementations are:\n");
	printf("\t> std\n");
	printf("\t> fast\n");
	printf("For both implementations, the parameters are the following ones:\n");
	printf("\t> num_objects\n\tThe number of objects we want to create\n");
	printf("\t> num_fields\n\tThe maximum number of pointers an object can have\n");
	printf("\t> pr_adj\n\tThe graph density parameter\n");
	printf("\t> pr_src\n\tThe roots density parameter\n");
	printf("Output's format:\n");
	printf("\tnum_objects num_fields pr_adj pr_src t\n");
	printf("where\n");
	printf("\tt = Mark-Sweep selected implementation tsc\n");
	printf("Example call:\n");
	printf("\t%s -f output.out fast 100 50 0.75 0.1\n", program_name);
}

int main(int argc, char *argv[]){
	void (*mark_sweep)();
	int num_objects;
	int num_fields;
	double pr_adj;
	double pr_src;
	bool redirect_output = FALSE;
	bool verbose = FALSE;
	bool timeit = FALSE;
	char output_file[10 + OUTPUT_FILE_NAME_MAX_LEN];
	
	program_name = argv[0];
	
	/* Options */
	const char* const optstring = "hvf:t";

	const struct option longops[] = {
		{"help", 0, NULL, 'h'},
		{"verbose", 0, NULL, 'v'},
		{"file", 1, NULL, 'f'},
		{"timeit", 0, NULL, 't'},
		{NULL, 0, NULL, 0}
	};
	
	if(argc < 5){
		print_help();
		exit(EXIT_SUCCESS);
	}
	
	while(1){
		int next_opt = getopt_long(argc, argv, optstring, longops, NULL);
		
		if(next_opt == -1){
			break;
		}
		
		switch(next_opt){
			case 'h':
				print_help();
				exit(EXIT_SUCCESS);
			case 'v':
				verbose = TRUE;
				break;
			case 'f':
				if(strlen(optarg) > OUTPUT_FILE_NAME_MAX_LEN){
					abort();
				}
				redirect_output = TRUE;
				strcat(output_file, "./output/");
				strcat(output_file, optarg);
				break;
			case 't':
				timeit = TRUE;
				break;
			default:
				abort();
		}
	}
	
	if(strcmp(argv[optind], "std") == 0){
		mark_sweep = &mark_sweep_std;
	}else if(strcmp(argv[optind], "fast") == 0){
		mark_sweep = &mark_sweep_fast;
	}else{
		abort();
	}
		
	num_objects = atoi(argv[argc - 4]);
	num_fields = atoi(argv[argc - 3]);
	pr_adj = atof(argv[argc - 2]);
	pr_src = atof(argv[argc - 1]);
		
	if(redirect_output){
		fopen(output_file, "a");
		freopen(output_file, "a", stdout);
	}
	
	printf("%i %i %f %f ", num_objects, num_fields, pr_adj, pr_src);
	
	doit(mark_sweep, num_objects, num_fields, pr_adj, pr_src, verbose, timeit);
	
	printf("\n");
	
	return EXIT_SUCCESS;
}
