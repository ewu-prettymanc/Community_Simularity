#define SIZE_NAME  200
#define SIZE_INFO  1024


/* the data structure holds the name of the community and the array of the
data numbers. And ther percapita_crime; */ 
struct data
{
  char  * communityname; 
  double * info; 
  double percapita_crime;
  	    
};

/* this stores the name */ 
struct names
{	
  char  *names;
};







struct data * construct_data(int *d_length);
void read_in_data(FILE * in, struct data *d );
void get_info( FILE * in, struct data *d, int end, int start, char * buffer  );
double get_double(char *from, int start, int end);
void copy_string(char *from, int start, int end, char*to);
FILE * open_file(char * name);
int calc_file_length( FILE * in );
struct names * construct_names(int * n_length);
void read_names( FILE * innames, struct names * n );
void free_data(struct data * d, int d_length );
void free_names(struct names * n, int n_length);

