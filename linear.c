
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct _person{
	char name[20];
	char surname[20];
	char gender;
	int year,month,day;
} person;

struct timeval start, stop;
int nf;

void init_time(void){
	gettimeofday(&start, NULL);
}

void update_time(void){
	gettimeofday(&stop, NULL);
	double sec = stop.tv_sec + (stop.tv_usec / 1000000.0) - 
		( start.tv_sec + start.tv_usec / 1000000.0);
	printf("Time\t%12.6f\n", sec);
	
}

#define MAXX 400000
#define MAX2 20000

int main(int argc, char **argv){
	if(argc<2){
		printf("no filename specified!\n");
		return 0;
	}
	FILE *f = fopen(argv[1], "r");
	if(f == NULL){
		printf("can't open file %s!\n", argv[1]);
		return 0;
	}
	int n = 0;
	person *ppl = malloc(sizeof(person) * MAXX);
	while(!feof(f)){
		if(fscanf(f, "%s %s %c %d-%d-%d", ppl[n].name, ppl[n].surname, &ppl[n].gender, &ppl[n].year, &ppl[n].month, &ppl[n].day) == 6)
			n++;
		else
			break;
		if(n >= MAXX)
			break;
	}
	fclose(f);
	printf("Read %d records\n", n);
	if(n == 0){
		printf("No records!");
		return 0;
	}
	char **surnames = malloc(sizeof(char*) * MAX2);
	init_time();
	//-----------
	nf = 0;
	for(int i = 0; i < n; i++){
		int found = 0;
		for(int j = 0; j < nf; j++)
			if(strcmp(ppl[i].surname, surnames[j]) == 0){
				found = 1;
				break;
			}
		if(!found){
			surnames[nf] = ppl[i].surname;
			nf++;
		}
	}
	//-----------
	update_time();	
	printf("Unique surnames: %d\n", nf);
	free(surnames);
	free(ppl);
	return 0;
}
