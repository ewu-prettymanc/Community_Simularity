#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"data.h"
#define SIZE 4096

/* Step 2 of compute
name: construct_data
desc: reads in all the towns' data from a file and stores it in an array of 
structures. It needs to get the length of the file and than allocate an array
of structues that long. It will return this array and will close the input file.
params: int *d_length
returns struct data *
1) declare the FILE *in, and Struct data *
2) open the input file named 'communities.data'
3) get the length of the file and store it in *d_length		(F)
4) rewind the file so we can reread it
5)  allocate the array of structures *d_length
6) for (i=0 i<*d_length i++) do step 7				(L)
7) read in the data                                             (F)
8) close the in file 
*/ 
struct data * construct_data(int *d_length)
{
  FILE * in;
  struct  data* d;
  int i;
 
  in = open_file("communities.data"); /* open data file */ 
  
  *d_length = calc_file_length(in); /* get the length of the input file */ 
  rewind(in); 
  
  d = malloc(*d_length*sizeof(struct data ) );
  if( !d)
  {
    fprintf(stderr, "Could not allocate array of data structures!!\n " );
    exit(1); 
  }
  
  for( i=0; i< *d_length; i++)
    read_in_data(in, &d[i]);
  
  fclose(in); 
  return d; 
}

/* Step 7 of compute
name: read_in_data
desc: declares a structure d. It reads in the data from the file storing it in that 
structure. It reads a line of data into the buffer. It than parses that file reading
out the name and storing it in the structure. It than reads out all of the number
data storing it in the structure. 
params: FILE * in
1) declare a struct data * d, and a char buffer[SIZE]
2) allocate the stucture
3) get the next line of the file storing it into the buffer
4) read throught the buffer until we get to comma #3 storing that value
in start. Than read until comman #4 storing that into end.   	  (L)
5) copy the data between start and end and store that into d->communityname (F)
6) starting at end read through the buffer do step 7  	   		    (L)
7) get the info from the file
8) return d
*/ 

void read_in_data(FILE * in, struct data *d )
{
  int i,j,k,x, c_count=0, start, end;
  char  buffer [SIZE];
  
  d->communityname = malloc( SIZE_NAME*sizeof( char ) );
  if ( ! d )
  {
    fprintf(stderr, "Could not allocate the data communityname. \n ");
    exit(1); 
  }
  
  fgets(buffer, SIZE, in ); 
 
  for(i=0; i<SIZE; i++)
    if( buffer[i] == ',')
    {
      c_count ++;
      if(c_count == 3)/* town name starts at 3 commas and ends at 4 */  
	start = i;
      if(c_count == 4)
      {
	end = i;
	break;
      }    
    }

  copy_string(buffer, start+1, end-1, d->communityname ); /* copy the name */
  get_info( in, d, end, start, buffer); /* fill the info array */ 	   
}

/* Step 7 of read_in_data
name: get_info
desc: Allocate the d-> array .reads in the doubles from the buffer storing them into 
d->info[i]. Do this by reading through the buffer until it comes to a comman. Copy 
the data between each comma and convert it into a double than store it into info[i]. 
params: FILE * in, struct data *d, int end, int start, char *buffer 
returns: void
1) allocate the d-> info array of SIZE_INFO
2) go through the buffer until we get to another comma  storing that in end (L)
3) if buffer[end] == '\n' than copy start-end into the d->capitacrime and break
4) if the buffer[start+1] == '?' than give the next d->info[] element -10
5) else convert the data between start and end by step 11
6) call get_double and store that data in the next d->info[] element	     (F)
*/
void get_info( FILE * in, struct data *d, int end, int start, char * buffer  )
{
  int j, k,i;
  int c_count=0;
  
  d->info = malloc( SIZE_INFO*sizeof( double ) ); 
  if ( ! d )
  {
    fprintf(stderr, "Could not allocate the data communityname. \n ");
    exit(1); 
  }
  
  /* the last place we were at with i was we read out a comman...so
     we need to start j at that. Check for the next element to be a question mark.
     if not than read till we hit another comma than copy from the last comma to
     the jth one. copy into the structure array */ 
  
  for(j=end, k=0; j < SIZE; j++)/* the last place we were at was a comma */ 
  {
    start = end+1;/* put our start of good data  the end plus + since
		     that is where we will copy from */     
    for( i=start; buffer[i] != ',' && i<SIZE && buffer[i] != '\n'; i ++ )
      ;
    end = i;
    
    if( buffer[end] == '\n' )
    {
      d->percapita_crime = get_double(buffer, start, end -1); 
      break; /* last data between ',' and '\n' is percapita crime */ 
    }

    if( buffer[start+1 ] == '?' )
    {
      d->info[k]= -10;
      k++;
    }
    else/* the data inbetween must be a double */ 
    {
      d->info[k] =  get_double(buffer, start, end-1 );
      /* the last place i was was at a comma so subtract 1 from end*/ 
      k++;
    }   
  }
}


/* Step 11 of read_in_data
name: get_double
desc: given a buffer and the start and end points. It reads the data from start to
end and converts that data into a double 
params: char * from, int start, int end
returns: double 
1) copy from[start] from[end] into a char[] to 
2) null terminate the string in 'to'
3) call atof(to) storing its return into num
4) return num 
*/ 
double get_double(char *from, int start, int end)
{
  int f, t;
  char to[100];
  double num;
  
  /* from and to */ 
  for( f=start, t=0; f <=end; f++, t++)
    to[t] = from[f];
  
  to[t] = '\0';
   
  num = atof(to ); /* convert the string of numbers to a double */ 
  /* singlue quotes are for characgters double quotes are for strings*/
  return num;
}


/* Step 5 of read_in_data
name: copy_string
desc: copies the data from the start to the end  of the buffer given storing it into
the char *  given;
params: char * from, int start, int end, char * to
returns: void
1) read through the buffer from start to end copying that data into to;
2) null terminate the end of the string in to
*/ 
void copy_string(char *from, int start, int end, char*to)
{
  int f, t;
  
  /* from and to */ 
  for( f=start, t=0; f <=end; f++, t++)
    to[t] = from[f];
  
  to[t] = '\0';
  /* singlue quotes are for characters double quotes are for strings*/
}

/* SEE previouse design */  
FILE * open_file(char * name)
{
  FILE * f;
  
  f = fopen(name, "r");
  if ( ! f )
  {
    fprintf(stderr,"could not open %s. exiting.\n", name);
    exit(1);
  }
  
  return f;
}

/* Step 3 of compute
name: calc_file_length
desc: calculates how many lines are in a file and returns that number
params: FILE * in
returns int
1) declare a char c[SIZE];
2) while (fgets(c, SIZE, in  do step 3				(L)
3) lines ++
4) return lines
*/ 
int calc_file_length( FILE * in )
{
  char  c[SIZE];
  int lines=0;
  
  while( fgets(c, SIZE, in) ) 
     lines ++;
  
  return lines;  
}

/* Step 3 of compute
name: construct_names
desc: Reads the names of the variables into an array of structures.Each structure 
containging a char array; 
params: int *n_length 
returns: struct names *
1) declare a struct names *n, a buffer[] and a in_file_name[]
2) open the innames file with a file name of names.data			
3) find the length of the file and store that in *n_length 
4) allocate the names structure n
5) rewind the file
6) for(i=0; i<*n_lenght; i++) do step 7
7) read the names from the structure                                      (F)
8) fclose(innames)
9) return n
*/
struct names * construct_names(int * n_length)
{
   struct names * n; 
   FILE * innames;
   char  in_file_name[100] = "names.data";
   int i, j; 
   char buffer [SIZE_NAME]; 
   char temp [SIZE_NAME];

   innames = open_file(in_file_name); 
   *n_length = calc_file_length(innames); 
   
   rewind(innames); 
  
   /* allocate an array of structures  with the a name in each structure */ 
   n = malloc(*n_length*sizeof(struct names) );
   if( ! n )
   {
     fprintf(stderr, "Could not allocate the names structure!!\n"); 
     exit(1); 
   }

   /* read the names from the name file and store them into the names structure*/ 
   for( i=0; i<*n_length; i++)
     read_names(innames, &n[i] ); 
          
   fclose(innames); 
   return n;
}

/* Step 8 of construct_names
names: read_names:
desc: Allocate an array of char of SIZE_NAME and reads in the names from the file 
given storing it into the n->names
params: FILE * innames, struct names *n
returns: void 
*/ 
void read_names( FILE * innames, struct names * n )
{
  
  n->names = malloc(SIZE_NAME*sizeof(char ) ); 
  if( ! n )
  {
    printf("Could not allocate the name char array !! \n "); 
    exit(1);
  }

  fscanf(innames, "%s", n->names ); 
}


/*Step 7 of compute
name: free_data
desc: for each element  of the struct data * d give, free communityname and info
params: struct data * d, int d_length
returns: void
1) for(i=0; i<d_length; i++) do step 2
2) free d[i].communityname, free d[i].info
3) free d
*/
void free_data(struct data * d, int d_length )
{
  int i;
  
  for( i=0; i<d_length; i++)
  {
    free(d[i].communityname ); 
    free(d[i].info); 
  }
  
  free(d);
}

/* Step 8 of compute
name: free_names
desc: for each element of the struct names * n free names.
params: struct names *n, int n_length
returns: void
1) for( i=0; i<n_length; i++)
2) free n[i].names
3) free n
*/
void free_names(struct names * n, int n_length)
{
  int i;
  
  for( i=0; i<n_length; i++ )
    free( n[i].names ); 
  
  free(n); 
}
