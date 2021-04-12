#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct screen screen, *pno;
typedef struct part part, *pno2;
struct screen
{
  int x;
  int y;
  char *str;
  pno ptr;

  
};

struct part
{
  int y;
  int x;
  char type;
  pno2 ptr;
};


pno make_board(pno p_struct, int a_x, int a_y, char character)
{
  p_struct -> x = a_x;
  p_struct -> y = a_y;
  char * str2 = (char *) malloc(sizeof(char) * (a_x*a_y));

  for (int i =0; i < (a_x*a_y); i++)
  {
    str2[i] = character;
  }
  str2[a_x*a_y] = '\0';
  p_struct -> str = str2;
  return p_struct;
}


part *init_board(pno p_struct, part *particles, int num_particles)
{
 for(int i = 0; i < num_particles; i++)
 {
    part p_part = particles[i];
    if (p_struct -> str[((p_struct -> x) * (p_part.y)) + p_part.x] == '.')
    {
    p_struct -> str[((p_struct -> x) * (p_part.y)) + p_part.x] = p_part.type;
    }
    else
    {
      particles[i].type = '.';
    }
 } 
 return particles;
}
pno display_board(pno p_struct)
{
  int a_x = p_struct -> x;
  int a_y = p_struct -> y;
  char *str = p_struct -> str;
  for (int i =a_y; i >= 0; i--)
  {
    printf("%.*s\n", a_x, str + (a_y * i));
  }
  return p_struct;
}

int can_fall(pno p_struct, pno2 p_part)
{

  int y = p_part -> y;
  int x = p_part -> x;
  printf("X %i Y %i Type %c",x,y,p_part -> type );
  if(y == 0) return 0;
  //....
  //..#.
  //..G.
  //....
  //need to check char underneath, probably shouldent pass the entire struct but, yes?
  if(p_struct -> str[((p_struct->x) * (y-1) + x)] != '.') 
  {
    char n = p_struct -> str[((p_struct->x) * (y-1) + x)];
  
    printf("DLKSFJLSKJDFLSKDJFLSKDJFLSKJDFLKSJDFLKSJDFSL\n\n\n\n%c\n\n\n\n\n\n\n sdfsdfsdfdsfsdfsfs",n);
    return 0;
  }
  else
  {
    return 1; //true
  }
}

int can_slide_down(pno p_struct, pno2 p_part) // checks if the particle can go down diagonally
{                                             // .A. 
  int b_y = p_struct -> y; //board y          // x#x
  int b_x = p_struct -> x; //board x          //if A can go to either X tile
  int p_y = p_part -> y;//   particle y
  int p_x = p_part -> x;//   particle x
  char *str = p_struct ->str;

  int result = 0;

  if(p_x == 0 || (str[(b_x*(p_y - 1))+ (p_x - 1)]!= '.')) // checks down to the left
  {
    result += 0; // no
  }
  else
  {
    result +=1; // left true
  }
  if(p_x == b_x || (str[(b_x * (p_y - 1)) + (p_x + 1)] != '.')) // checks down to the right
  {
    result +=0; // no
  }
  else
  {
    result +=2; // right true
  }

  return result; // 4 cases, 0 none, 1 = left, 2 = right, 3 = both
}

int move(pno p_struct, pno2 p_part) // checks if the particle can fall and then moves it if it can
{
  if(p_part -> type == '.')
  {
    return 0;
  }
  if(can_fall(p_struct, p_part) == 1)
  {
    p_struct -> str[((p_struct -> x) * (p_part -> y)) + p_part -> x] = '.';
    p_struct -> str[((p_struct -> x) * ((p_part -> y) - 1)) + p_part -> x ] = p_part -> type;
    p_part -> y--;
    return 1;
  }
  else
  {
   int slide = can_slide_down(p_struct, p_part);
   if(slide != 0)
   {
     if(slide == 1 || slide == 3)
     {
       p_struct -> str[((p_struct -> x) * (p_part -> y)) + p_part -> x] = '.';
       p_struct -> str[((p_struct -> x) * ((p_part -> y) - 1)) + p_part -> x - 1] = p_part -> type;
       p_part -> y--;
       p_part -> x++;
       return 1;
     }
     else
     {
       p_struct -> str[((p_struct -> x) * (p_part -> y)) + p_part -> x] = '.';
       p_struct -> str[((p_struct -> x) * ((p_part -> y) - 1)) + p_part -> x + 1] = p_part -> type;
       p_part -> y--;
       p_part -> x++;
       return 1;
     }
   }
   else
   {
     return 0;
   }
  }
}

int move_all(pno p_struct, part * particles, int num_particles)
{
  int sum = 0;
  for(int i = 0; i < num_particles; i++)
  {
    sum += move(p_struct, &particles[i]);
  }
  if( sum != 0)
  {
   return 1;
  }
  else
  {
    return 0;
  }
}

int main()
{
  //setting up rand
  time_t t;
  srand( (unsigned) time(&t));

  //initilizing stuff
  screen board;
  make_board(&board,20,20,'.');
  part * particles = (part *) malloc((board.x*board.y) * sizeof(part));
  int num_manual_part = 8;
  part p1 = {19,2,'#'};
  part p2 = {18,1,'a'};
  part p3 = {18,2,'b'};
  part p4 = {17,0,'c'};
  part p5 = {16,0,'d'};
  part p6 = {16,2,'e'};
  part p7 = {16,3,'f'};
  part p8 = {18,4,'g'};
  particles[0] = p1;
  particles[1] = p2;
  particles[2] = p3;
  particles[3] = p4;
  particles[4] = p5;
  particles[5] = p6;
  particles[6] = p7;
  particles[7] = p8;
  //random particles now?
  int num_it_part=0;
  for( int i =0; i < num_it_part; i++)
  {
    part p_it = {rand () % board.y, rand() % board.x, 'x'};
    particles[num_manual_part+i] = p_it;
  } 
  particles = init_board(&board, particles, num_manual_part + num_it_part);
  printf("dd %c\n",particles[3].type);

  // we are getting an error with
  // ...#...
  // ...#...
  // ..#.#


  //the loop begins
  do 
  {
  printf("\n          %i,%i", can_slide_down(&board,&particles[3]),can_fall(&board,&particles[3]));
  display_board(&board);
  }while(move_all(&board,particles,num_manual_part + num_it_part) != 0);

  return 0;
}


