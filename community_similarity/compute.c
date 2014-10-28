/* Colton Pretttyman...CS211. 12-9-2011....Prof. John Mill */ 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"data.h"
#include"compute.h"


/* Step 1 of Main
name: compute
desc: Declares a structure for the data, the user,and for the names. It calls a 
function to construct the structures. It than gets data from the user. And matches 
that data with a town which has the most similar data. It than prints out the name
of that town and its capita crime rate. 
params: none
returns: void
1) struct data *d, struct data * user, struct names *n;
2) constructs the data array d				(F)
3) conscturcts the names array n			(F)
4) gets user action/data       				(F)
5) matches the user data with a town			(F)
6) tell the user about a town which matches 		(F)
7) free d, user, and n					(F)
*/ 
void compute()
{ 
  struct data * d;
  struct names * n; 
  struct data * user;
  int d_length, n_length; 
  int match; /* which element in the d array that matches */  

  d = construct_data(& d_length);  
  n = construct_names(& n_length); 
 
  user = get_user(n, n_length);
  
  match =  find_town_match(d, user, n_length,  d_length );

  tell_user(d, user, n_length , match); 
  
  free_data(d, d_length);
  free_names(n, n_length);
  free_data(user, 1); 
}

/*Step 4 of compute
name: get_user
desc: Given a pointer to a structure and an array of name structures, and the 
structure length. It allocates a data structure user. Than prints out which piece of
 data we want to read from the userand reads that piece storing it into the correct
 place in the user structure
params: struct names *n, int n_length
returns: struct data 8
1) declare struct data * user
2) ask the user to enter names[0].names data
3) read the data from the user stroing it into the correct element of user->info
4) return user; 
*/ 
struct  data * get_user(struct names *n, int n_length )
{
  FILE * fake_data;
  struct data * user; 
  int i=0; 
  double num;
  
  fake_data = open_file("fake.data" ); 
  user = malloc(sizeof(struct data  ) ); 
  if( !user )
  {
    fprintf(stderr, "Could not allocate the user data structure!!\n"); 
    exit(1); 
  }

  user-> communityname = malloc(SIZE_NAME*sizeof(char ) ); 
  if( !user->communityname )
  {
    fprintf(stderr, "Could not allocate the user info array!!\n"); 
    exit(1); 
  }
  
  user->info = malloc(SIZE_NAME*sizeof(double ) );
  if( !user->info )
  {
    fprintf(stderr, "Could not allocate the user info array!!\n"); 
    exit(1); 
  }
    
  printf("Enter the %s >> ", n[0].names);
  scanf("%s", user->communityname ); /* get the name of the user town */ 
  
  for(i=1; i<n_length-1; i++)/* last element is the crimes percapita */ 
  {
    printf("Enter the %s >> ", n[i].names);
    fscanf(stdin, "%lf", &(user->info[i] ) ); 
    /*enter that piece of data into the info array*/
  }      
  
  printf("\n"); 
  fclose(fake_data); 
  return user; 
}

/* step 5 of compute
name: find_town_match
desc: for each element of the data d array given find the distance between the 
coorisponding user element. The whole time keeping track of the town with the 
closest distance. When we've checked all the elements in the data d array return
which element has the closest distance
params: struct data *d, struct data * user, int n_length, int d_length
returns: int 
1) give best_dist the value between the the user and the first d element	(F)
2) for( i=1; i < d_length; i++ ) do step 3 
3) calculate the distance from the d[i]->info element and the user->info
4) if that distance is smaller then best_best that value and change which to i
5) return which
*/ 
int  find_town_match(struct data * d, struct data * user, int n_length,int d_length)
{
  int i=0; 
  double best_dist, temp; 
  int which; 

  best_dist = get_dist(&d[i], user, n_length-1 ); 
  which = i;

  for(i=1; i<d_length; i++)/* calculate with all the elements of the data array */ 
  {
    temp = get_dist(&d[i], user, n_length-1 ); 
    
    if( temp < best_dist )
    {
      best_dist = temp;
      which = i; /* give which the element of the closest distance data structure */ 
    }
  }

  return which; 
}

/* Step 1 of find_town_match
name: get_distance
desc: loop sum up the value of the (distance between user and d ) squared. The
distance is the square root of distance sum. 
params: struct data *d, struct data * user, int n_length
return: double
1) for(i=0; i<n_length; i ++ ) do step 2 
2) temp += the distance between user[i] and d[i] squared
3) return the square root of the temp 
*/ 
double get_dist( struct data * d, struct data * user, int n_length )
{
  int i;
  double temp=0;
  double distance; 

  for(i=0; i<n_length; i ++)/* last element is the crimes per capita */ 
  {
    temp += pow( (d->info[i] - user->info[i]), 2); /* square it */ 
  }

  distance = sqrt(temp); 

  return distance; 
}

/* Step 7  of compute
name: tell_user
desc: tells the user which town theirs was like. It also prints out the crime per
captita value of that town 
params: struct data *d, struct data *user, int n_length, int match 
returns: void
1) printf("The data fro the town %s that you entered matches \n", 
   user->communityname);
2)  printf(" town %s which has a crime rate percap of %lf:\n"
	 , d[match].communityname, d[match].percapita_crime ); 
*/ 
void tell_user(struct data *d, struct data *user, int n_length , int match)
{
  double percap;
  
  printf("\n\n"); 
  printf("\t Your town '%s'\n", user->communityname);
  printf("\t Is most like--\n");
  printf("\t The town '%s':\n", d[match].communityname);
  printf("\t which has a crime rate percap of %lf:\n\n\n", 
	 d[match].percapita_crime ); 
  /* we know that the percap is stored at the end of the info array */ 
}
