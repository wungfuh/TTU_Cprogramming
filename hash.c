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
#define MAX3 27000

typedef struct _hNode{
	char *data;
	struct _hNode *next;
} hNode;

#define MULT 43

unsigned int hash(char *s)
{
    unsigned int i, h = 0;
    for(i = 0; i < strlen(s); i++) {
        h = h * MULT + (s[i] - 32);
    }
    return h;
}

void addHash(int n, hNode **tab, char *data){
	int loc = hash(data) % n;
	hNode *x;
	if(tab[loc] != NULL){ //location is used, either data already in table or another data has same hash 
		x = tab[loc];
		while(x != NULL){
			if(strcmp(x->data,data) == 0)
				return; //already in table
			x = x->next;
		}
	}
	//if we reach here, we have new data
	nf++;
	x = malloc(sizeof(hNode));
	x->data = data;
	x->next = tab[loc];
	tab[loc] = x;
}

void freeTab(int n, hNode **tab){
	hNode *x, *p;
	for(int i = 0; i < n; i++){
		x = tab[i];
		while(x){
			p = x->next;
			free(x);
			x = p;
		}
	}
	free(tab);
}

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
	hNode **hashTable = malloc(sizeof(hNode*) * MAX3);
	memset(hashTable, 0, sizeof(hNode*) * MAX3); //clear all memory in the table
	init_time();
	//-----------
	nf = 0;
	for(int i = 0; i < n; i++){
		addHash(MAX3, hashTable, ppl[i].surname);
	}
	//-----------
	update_time();	
	printf("Unique surnames: %d\n", nf);
	freeTab(MAX3, hashTable);
	free(ppl);
	return 0;
}
