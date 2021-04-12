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

typedef struct _node{
	char *data;
	struct _node *left, *right;
} node;

node *root;

node *add(node *nd, char *data){
	if(nd == NULL){//new
		nd = malloc(sizeof(node));
		nd->data = data;
		nd->left = NULL;
		nd->right = NULL;
		nf++;
		return nd;
	}
	int k = strcmp(data, nd->data);
	if(k == 0)//match
		return NULL;
	if(k < 0){//is in left branch or should be added there
		if(nd->left == NULL)
			nd->left = add(NULL, data);
		else
			add(nd->left, data);
	}
	else{//is in right branch or should be added there
		if(nd->right == NULL)
			nd->right = add(NULL, data);
		else
			add(nd->right, data);
	}
	return NULL;
}

void freeTree(node *nd){
	if(nd == NULL)
		return;
	if(nd->left)
		freeTree(nd->left);
	if(nd->right)
		freeTree(nd->right);
	free(nd);
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
	init_time();
	
	//-----------	
	nf = 0;
	root = add(NULL, ppl[0].surname);
	for(int i = 0; i < n; i++){
		add(root, ppl[i].surname);
	}
	
	//-----------
	update_time();	
	printf("Unique surnames: %d\n", nf);	
	freeTree(root);
	free(ppl);
	return 0;
}
