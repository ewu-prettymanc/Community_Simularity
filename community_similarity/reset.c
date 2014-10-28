#include<stdio.h>
#include"reset.h"

/*
  Step 2 of main....see previouse docs */


int play_again()
{
  char resp;

  flush();
  
  printf( "Play again? y or n? ");/* we need to protype them*/
  scanf( "%c", &resp );
  flush();

  printf("\n\n\n"); 
  return resp == 'y';
}



void flush()
{
  char c;
  
  for( scanf ("%c", &c); c!= '\n'; scanf( "%c" , &c ) )
    ;
}
