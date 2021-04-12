 /*
   Tasks:
   []: create two structs, Personnel and work
   []: a function to read from an input stream and store in the two structs.
   []: call the input function to take in the user input(company name)
   []: read the personnel record of the given comapany name and store it in personnel struct
   []: sort the information with name in alphabical order
   []: write a function to print it out to another text file.
   */
// include libraries to be able to use functions defined in them.
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  // define macro for the buffer size
  #define LIMIT 100
// create a struct datatype called Work
  typedef struct 
  {
      char company[LIMIT];
      char phone[LIMIT];
  }Work;
// create another struct datatype called personnel  
  typedef struct 
  {
      char name[LIMIT];
      Work work;
  }personnel;
// function prototypes of all the functions defined in my code
  void get_input(FILE *stream, personnel *,  personnel*, int* );
  
  void sort_records(personnel sort_struct[], int );
 
  void output(FILE* ,personnel [], int, personnel* );
  void convert_to_lower(char []);
// Driver code begins   
  int main(void)
  {
      // declare variables to be use in the functions
        personnel test;
        personnel* test1 = &test;
        personnel worker[LIMIT] = {0};
        FILE *fpointer;
        FILE *display;
        int n;
        fpointer = fopen ("info.txt", "r"); 
        display = fopen("output.txt", "w");
        if (fpointer == NULL || display == NULL) 
        { 
            fprintf(stderr, "\nError opening file\n"); 
            exit (1); 
        } 

      get_input(fpointer, worker, test1, &n);

      printf("Companies on the system are: \n");
      for (int i = 1; i < n; i++)
      {
          printf(" %d. %s\n", i, worker[i].work.company);
      }

      get_input(stdin, worker, test1, NULL);
      
      output(display, worker, n, test1);
     
      fclose(display);
      fclose(fpointer);

      return 0;
  }
  void get_input(FILE *stream, personnel *buf, personnel* try, int* count)
  {
      if (stream == stdin)
      {
          printf("Enter the company's name: ");
          scanf("%s", try->work.company);

      }
      else
      {
          int i = 0;
          *count = 0;
          
          while (fscanf(stream,"%s %s %s",buf[i].name,  buf[i].work.company, buf[i].work.phone)==3)
          {  
              i++;
              *count = *count + 1;
          }
          
         
      }
   
  }
  
void sort_records(personnel sort[], int count)
{
      personnel temp[LIMIT];
      for (int i = 1; i < count; i++)
      {
          for (int j = i+1;  j < count; j++)
          {
             if (strcmp(sort[i].name, sort[j].name) > 0)
          {
              temp[i] = sort[i];
             sort[i] = sort[j];
              sort[j] = temp[i];
          }
         
          }
          
      }
    }      
void output(FILE *display, personnel array[], int count, personnel* x)
{

    int y = 0, i;
    char temp[LIMIT];
     convert_to_lower(x->work.company);
     
    fprintf(display, "%s\t  %s\n", array[0].name, array[0].work.phone);
    printf("%s\t  %s\n", array[0].name, array[0].work.phone);
    for ( i = 0; i < count; i++)
        {
            strcpy(temp, array[i].work.company);
            convert_to_lower(temp);
            if (strcmp(temp, x->work.company ) == 0)
            {
                fprintf(display, "%s\t  %s\n", array[i].name, array[i].work.phone);
                printf("%s\t  %s\n", array[i].name, array[i].work.phone);
               y = y+1;
            }
            
        } 
    printf("\n\n");
    if (y == 0)
    {
        printf("No worker of company '%s' found \n", x->work.company);
        printf("Please make sure to correctly type the company's name from list above.");
    }
      
}
void convert_to_lower(char ch[LIMIT])
{
    for (int i=0; ch[i]!='\0'; i++)
    {
        if (ch[i]>='A' && ch[i]<='Z')
        {
             ch[i] = ch[i] + 32;
        }
        
    }

}