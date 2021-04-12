#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 3

typedef struct {
  char equivalent[15];
  long int value;
}Data;

// array of structs
typedef struct
{
    Data *array;
    size_t used;
    size_t size;
} Array;

void initArray(Array *a, size_t initialSize);
void freeArray(Array *a);
int get_base(char []);
void input_data(FILE* stream, Array*);
char reVal(int num);
void strev(char *str);
void fromDeci(char res[], int base, long int inputNum);
void conversion(Array* a, int base);
void output(FILE* stream, Array *arr, int base);


int main()
{
    int base;
    Array a;
    FILE* fp;
    FILE* fo;

    fp = fopen("data.txt", "r"); // open the file for writing
    fo = fopen("results.txt", "w"); // open the file for writing
    if (fp == NULL || fo == NULL) 
    { 
        printf("\nError opening file\n"); // check for error opening the file
        exit (1); 
    } 
    base = get_base("Enter the base:  ");
    initArray(&a, MAX);

    input_data(fp, &a);
    // for (size_t i = 0; i < n; i++)
    // {
    //     printf("%ld\n", a.array[i].value);
    // }

    conversion(&a, base);

    //  for (size_t i = 0; i < n; i++)
    // {
    //     printf("%s\n", a.array[i].equivalent);
    // }

    output(fo, &a, base);
    

    fclose(fp);
    fclose(fo);
    freeArray(&a);
    return 0;
}

int get_base(char text[])
{
    int base;
    do
    {
        printf("%s", text);
        scanf("%d", &base);
    } while (base <=1 || base >= 17);
    
    return base;
}

void initArray(Array *a, size_t initialSize)
{
    // Allocate initial space
    a->array = (Data *)malloc(initialSize * sizeof(Data));

    a->used = 0;           // no elements used
    a->size = initialSize; // available nr of elements

    // Initialize all values of the array to 0
    for(unsigned int i = 0; i<initialSize; i++)
    {
        memset(&a->array[i],0,sizeof(Data));
    }
}

void input_data(FILE* stream, Array* a)
{   
    Data X;
       while ((fscanf(stream,"%ld", &X.value)) == 1)
    {
        if (a->used == a->size)
    {
        a->size *= 2;
        a->array = (Data *)realloc(a->array, a->size * sizeof(Data));
    }
    a->array[a->used].value = X.value;
    a->used++;

    }
 } 

 // To return char for a value. For example '2' 
// is returned for 2. 'A' is returned for 10. 'B' 
// for 11 
char reVal(int num) 
{ 
    if (num >= 0 && num <= 9) 
        return (char)(num + '0'); 
    else
        return (char)(num - 10 + 'A'); 
}  

// Utility function to reverse a string 
void strev(char *str) 
{ 
    int len = strlen(str); 
    int i; 
    for (i = 0; i < len/2; i++) 
    { 
        char temp = str[i]; 
        str[i] = str[len-i-1]; 
        str[len-i-1] = temp; 
    } 
}


// Function to convert a given decimal number 
// to a base 'base' and 
void fromDeci(char res[], int base, long int inputNum) 
{ 
    int index = 0;  // Initialize index of result 
  
    // Convert input number is given base by repeatedly 
    // dividing it by base and taking remainder 
    while (inputNum > 0) 
    { 
        res[index++] = reVal(inputNum % base); 
        inputNum /= base; 
    } 
    res[index] = '\0'; 
  
    // Reverse the result 
    strev(res); 
  
}

void conversion(Array* a, int base)
{
    for (size_t i = 0; i < a->used; i++)
    {
        fromDeci(a->array[i].equivalent, base, a->array[i].value);
    }
    
}

void output(FILE* stream, Array *arr, int base)
{   //print to the file
    fprintf(stream, "Conversion from Decimal to base %d\n", base);
     for (int i = 0; i < arr->used; i++)
    { 
        fprintf(stream, "%ld\t %s\n",arr->array[i].value, arr->array[i].equivalent);
    } 
} 
  // free the array memory
void freeArray(Array *a) {
  free(a->array);
  // set the pointer to null
  a->array = NULL;
  // reinitialize the values of Array structure
  a->used = a->size = 0;
}