
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct _person{
	char name[20];
	char surname[20];
	char gender;
	int year,month,day;
	int left, right;
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
	memset(ppl, 0, sizeof(person) * MAXX);
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
	init_time();
	
	//-----------	
	nf = 1;	
	int idx;
	for(int i = 0; i < n; i++){
		idx = 0;
		int k;
		do{
			k = strcmp(ppl[idx].surname, ppl[i].surname);
			if(k < 0){
				if(ppl[idx].left == 0){
					ppl[idx].left = i;
					nf++;
					k = 0;
				}else
					idx = ppl[idx].left;				
			}
			if(k > 0){
				if(ppl[idx].right == 0){
					ppl[idx].right = i;
					nf++;
					k = 0;
				}else
					idx = ppl[idx].right;
			}
		}while(k != 0);
	}
	
	//-----------
	update_time();	
	printf("Unique surnames: %d\n", nf);	
	
	free(ppl);
	return 0;
}
