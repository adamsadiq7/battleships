#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>


struct board{
  char cells[5][6];
  char player;
  int previousHcol;
  int previousHrow;
  int previousCcol;
  int previousCrow;
  int moves;
};

struct position {
   int Hrow;
   int Hcol;

   int Crow;
   int Ccol;
};

typedef struct board Board;
typedef struct position Position;

enum {L = 'L', S ='S', H = 'H', C = 'C', B = 'B'};

bool testing;

void findHposition(Board *b, Position *p);
void findCposition(Board *b, Position *p);
void move(Board *b, Position *p);

void newGame(Board *b, Position *p) {
  for (int x=0; x<6;x++){
    for (int y=0; y<5; y++){
      b->cells[x][y] = B;
    }
  }
  b->cells[0][2] = L; //Goes to [1][2]
  b->cells[0][5] = L; //Goes to [1][4]
  b->cells[1][2] = L; //Goes to [2][1]
  b->cells[3][4] = L; //Goes to [4][3]
  b->cells[2][5] = S; //Goes to [1][4]
  b->cells[3][5] = S; //Goes to [2][4]
  b->cells[3][3] = S; //Goes to [2][2]
  b->cells[4][2] = S; //Goes to [3][1]

  b->player = H;
  b->moves = 0;
  p->Hrow = 0;
  p->Hcol = 0;
  p->Crow = 0;
  p->Ccol = 0;
  findHposition(b, p);

  srand(time(NULL));
}


void display(Board *b) {
  printf("   %c | %c | %c | %c | %c | %c\n", b->cells[4][0], b->cells[4][1], b->cells[4][2], b->cells[4][3], b->cells[4][4], b->cells[4][5]);
  printf(" -------------------------\n");
  printf("   %c | %c | %c | %c | %c | %c\n", b->cells[3][0], b->cells[3][1], b->cells[3][2], b->cells[3][3], b->cells[3][4], b->cells[3][5]);
  printf(" -------------------------\n");
  printf("   %c | %c | %c | %c | %c | %c\n", b->cells[2][0], b->cells[2][1], b->cells[2][2], b->cells[2][3], b->cells[2][4], b->cells[2][5]);
  printf(" -------------------------\n");
  printf("   %c | %c | %c | %c | %c | %c\n", b->cells[1][0], b->cells[1][1], b->cells[1][2], b->cells[1][3], b->cells[1][4], b->cells[1][5]);
  printf(" -------------------------\n");
  printf("   %c | %c | %c | %c | %c | %c\n", b->cells[0][0], b->cells[0][1], b->cells[0][2], b->cells[0][3], b->cells[0][4], b->cells[0][5]);

}


void findCposition(Board *b, Position *p){
  printf("C is Being called\n");
  int diceNumber;
  //bool nomove;
    diceNumber = ((rand() % 6)+1);
    printf("Computer rolled %d\n",diceNumber);
    if (p->Crow == 4){
      if (p->Ccol + diceNumber > 5) {
        printf("Too large a roll for Computer to win\n");
        b->player = H;
        findHposition(b, p);
      }
      else if (p->Ccol + diceNumber == 5){
        printf("Computer Wins!");
        exit(1);
      }
      b->previousCrow = p->Crow;
      b->previousCcol = p->Ccol;

    }
      for (int i=0;i<diceNumber;i++){
        if (p->Ccol == 5){
          p->Ccol = 0;
          p->Crow++;
          i = i + 1;
          if (i == diceNumber - 1){
            break;
          }
        }
        p->Ccol++;
      }
    move(b, p);

}

//bool valid(char rolled){

  //if (strcmp(rolled,"r") != 0){
    //printf("0.5\n");
    //return false;
  //}
//return true;
//}

void findHposition(Board *b, Position *p){

  printf("H is Being called\n");
  char rolled[5];
  int diceNumber;
  //bool validroll;
  //bool nomove;

//while (validroll == false){
  printf("Press 'r' and Enter to Roll!\n");
  fgets(rolled, 4, stdin);

  //if (!valid(rolled)){
    //printf("Invalid Roll");
  //}
  //else{
    //validroll = true;
  //};
//}

  diceNumber = ((rand() % 6)+1);
  printf("You rolled %d\n",diceNumber);
  if (p->Hrow == 4){
    if (p->Hcol + diceNumber > 5) {
      printf("Too large a roll to win\n\n");
      b->player = C;
      findCposition(b, p);
    }
    else if (p->Hcol + diceNumber == 5){
      printf("You Win!");
      exit(1);
    }
  }

    b->previousHrow = p->Hrow;
    b->previousHcol = p->Hcol;

    for (int i=0;i<diceNumber;i++){
      p->Hcol++;
      if (p->Hcol == 6){
        p->Hcol = 0;
        p->Hrow++;
      }

    }
    move(b, p);

}

bool blank(Board *b, Position *p, bool blankcell){
  //int checker = -1;
  //printf("%d\n",checker++);
  if (b->player == H)
    if (b->cells[p->Hrow][p->Hcol] == B){
      //printf("Row %d Column %d is available\n",p->Hrow, p->Hcol);
      blankcell = true;
    }
    else{
      printf("Cell is full with %c\n",b->cells[p->Hrow][p->Hcol]);
      if (p->Hcol == 0){
        //printf("End of column\n");
        p->Hrow --;
        p->Hcol = 5;
      }
      else{
        p->Hcol--;
        blank(b, p, false);
      }
    }
  else{
    if (b->cells[p->Crow][p->Ccol] == B){
      //printf("Row %d Column %d is available\n",p->Crow, p->Ccol);
      blankcell = true;
    }
    else{
      //printf("Cell is full with %c\n",b->cells[p->Crow][p->Ccol]);
      if (p->Ccol == 0){
        //printf("End of column\n");
        p->Crow --;
        p->Ccol = 5;
      }
      else{
        p->Ccol--;
        blank(b, p, false);
      }
    }
  }
  return blankcell;
}

void callBlankCell(Board *b, Position *p){
  bool blankcell;
  blankcell = false;
  while (blankcell == false){
    //printf("Calling blank Function...\n");
    blankcell = blank(b,p, blankcell);
    if (b->player == H){
      //printf("Position is now on %d %d\n", p->Hrow, p->Hcol);
    }
    else{
      //printf("Position is now on %d %d\n", p->Crow, p->Ccol);
    }
    //blankcell == true ? printf("True\n") : printf("False\n");
  }
}

void ladder(Board *b, Position *p){
  if (b->player == H){
    p->Hrow ++;
    p->Hcol --;
  }
  else{
    p->Crow ++;
    p->Ccol --;
  }
}

void snake(Board *b, Position *p){
  if (b->player == H){
    p->Hrow--;
    p->Hcol--;
  }
  else{
    p->Crow ++;
    p->Ccol --;
  }
}
void move(Board *b, Position *p) {
  //printf("Opening Move Function...\n");
  if (b->player == H){
    //printf("Human is about to be checked\n\n");
    if (b->cells[p->Hrow][p->Hcol] == L){
      printf("You landed on a ladder!\n");

      //printf("Calling ladder Function...\n");
      ladder(b,p);
      //printf("You are now on %d %d\n", p->Hrow, p->Hcol);
      //printf("Calling callBlankCell Function...\n");

      callBlankCell(b,p);
      b->cells[p->Hrow][p->Hcol] = H;
      b->cells[b->previousHrow][b->previousHcol] = B;

    }
    else if (b->cells[p->Hrow][p->Hcol] == S){
      printf("You landed on a Snake\n");
      //printf("Calling snake Function...\n");
      snake(b,p);
      //printf("You are now on %d %d", p->Hrow, p->Hcol);
      //printf("Calling callBlankCell Function...\n");
      callBlankCell(b,p);
      b->cells[p->Hrow][p->Hcol] = H;
      b->cells[b->previousHrow][b->previousHcol] = B;
    }
    else{
      //printf("You are now on %d %d\n", p->Hrow, p->Hcol);
      callBlankCell(b,p);
      //printf("You are now on %d %d\n", p->Hrow, p->Hcol);
      b->cells[p->Hrow][p->Hcol] = H;
      b->cells[b->previousHrow][b->previousHcol] = B;

    }
    b->moves++;
  }
  else{
    printf("Computer is about to be checked\n\n");
    if (b->cells[p->Crow][p->Ccol] == L){
      printf("Computer Landed on a ladder");
      ladder(b,p);
      //printf("Computer is now on %d %d\n", p->Crow, p->Ccol);
      callBlankCell(b,p);
      //printf("Computer is now on %d %d\n", p->Crow, p->Ccol);
      b->cells[p->Crow][p->Ccol] = C;
      b->cells[b->previousCrow][b->previousCcol] = B;

      b->moves++;
    }
    else if (b->cells[p->Crow][p->Ccol] == S){
      printf("Computer landed on a snake");
      snake(b,p);
      //printf("Computer is now on %d %d\n", p->Crow, p->Ccol);
      callBlankCell(b,p);
      b->cells[p->Crow][p->Ccol] = C;
      //printf("Computer is now on %d %d\n", p->Crow, p->Ccol);
      b->cells[b->previousCrow][b->previousCcol] = B;

      b->moves++;
    }
    else{
      //printf("Computer is now on %d %d\n", p->Crow, p->Ccol);
      callBlankCell(b,p);
      //printf("Computer is now on %d %d\n", p->Crow, p->Ccol);
      b->cells[p->Crow][p->Ccol] = C;
      b->cells[b->previousCrow][b->previousCcol] = B;

      b->moves++;
    }
  }
  //printf("%d Moves have been played\n\n", b->moves);

  display(b);
  if (b->player == H) {
     b->player = C;
     findCposition(b, p);
  }
  else{
    b->player = H;
    findHposition(b, p);
  }

}

/*int booleq(int n, bool actual, bool expected){
    n++;
    if (actual != expected){
        fprintf(stderr, "Test %d fails\n", n);
        exit(1);
    }
    return n;
}*/
//int eqb(int n, bool x, bool y) { return booleq(n, x, y); }

//void test() {
  //  int n = 0;

      /*  n = eqb(n, valid(';'), true);
        n = eqb(n, valid("3453"), false);
        n = eqb(n, valid('R'), false);
        n = eqb(n, valid('7'), false);
        n = eqb(n, valid(""), false);
        n = eqb(n, valid('r'), true);
        //n = eqb(n, logic(3,2), true);
        //n = eqb(n, logic(3,3), false);

        printf("Tests passed: %d\n\n", n);
        testing = false;
*/



//}


int main(){
  setbuf(stdout, NULL);

  Board bdata;
  Board *b = &bdata;

  Position pdata;
  Position *p = &pdata;
  newGame(b, p);


return 0;
}
