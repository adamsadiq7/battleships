#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#define KBLU  "\x1B[34m"
#define KRED  "\x1B[31m"
#define RESET   "\x1b[0m"

struct playerBoard{
  char cells[10][10];
  int ships;
};

struct computerBoard{
  char cells[10][10];
  int ships;
};

struct hitBoard{
  char cells[10][10];
};

struct position {
   int row;
   int col;
   char vector;
};

typedef struct playerBoard playerBoard;
typedef struct computerBoard computerBoard;
typedef struct position position;
typedef struct hitBoard hitBoard;
typedef struct gameBoard gameBoard;

enum {Ship = 'S', Hit = 'H', Miss ='M', Water = 'W'};

bool testing;
void delay(unsigned int);
void displayPlayerBoard(playerBoard *pb);
void displayComputerBoard(computerBoard *cb);
void newGame(playerBoard *pb, computerBoard *cb, hitBoard *hb, position *p);
bool valid(int choice);
void retrieve(playerBoard *pb, position *p);
void displayHitBoard(hitBoard *hb);
void cpuSet(computerBoard *cb, position *p);
bool playerGuess(computerBoard *cb, hitBoard *hb, position *p);
bool cpuGuess(playerBoard *pb, position *p);
bool playerWin(computerBoard *cb);
bool cpuWin(playerBoard *pb);
bool checkpos(int length, position *p, playerBoard *pb);

void delay(unsigned int secs){
  unsigned int retTime = time(0) + secs;
  while (time(0) < retTime);
}

void newGame(playerBoard *pb, computerBoard *cb, hitBoard *hb, position *p){

  for (int x=0; x<10;x++){
    for (int y=0; y<10; y++){
      pb->cells[x][y] = Water;
      cb->cells[x][y] = Water;
      hb->cells[x][y] = Water;
    }
  }

  pb->ships = 14;
  cb->ships= 14;

}

void displayComputerBoard(computerBoard *cb){

  for (int i=9;i>=0;i--){

      printf("   %c | %c | %c | %c | %c | %c | %c | %c | %c | %c\n", cb->cells[i][0], cb->cells[i][1], cb->cells[i][2], cb->cells[i][3], cb->cells[i][4], cb->cells[i][5], cb->cells[i][6], cb->cells[i][7], cb->cells[i][8], cb->cells[i][9]);
      printf(" ------------------------------------------\n");
  }



}

void displayPlayerBoard(playerBoard *pb){

  for (int i=9;i>=0;i--){
      printf("   %c | %c | %c | %c | %c | %c | %c | %c | %c | %c\n", pb->cells[i][0], pb->cells[i][1], pb->cells[i][2], pb->cells[i][3], pb->cells[i][4], pb->cells[i][5], pb->cells[i][6], pb->cells[i][7], pb->cells[i][8], pb->cells[i][9]);
      printf(" ------------------------------------------\n");
  }

}


void displayHitBoard(hitBoard *hb){

  for (int i=9;i>=0;i--){
      printf("   %c | %c | %c | %c | %c | %c | %c | %c | %c | %c\n", hb->cells[i][0], hb->cells[i][1], hb->cells[i][2], hb->cells[i][3], hb->cells[i][4], hb->cells[i][5], hb->cells[i][6], hb->cells[i][7], hb->cells[i][8], hb->cells[i][9]);
      printf(" -------------------------------------------------\n");
  }
}

bool valid(int choice){

  bool valid = true;
  if (choice > 10){
    if (!testing){
      printf("Your choice %d is invalid\n", choice);
      printf("Because it is greater than 10\n");
    }
    valid = false;
  }
  if (choice < 0){
    if (!testing){
      printf("Your choice %d is invalid\n", choice);
      printf("Because it is less than 0\n");
    }
    valid = false;
  }
  if (isdigit(choice)){
    if (!testing){
      printf("Your choice %d is invalid\n", choice);
      printf("Because it is not a number\n");
    }
    valid = false;
  }

if (!testing){
  printf("Valid\n");
}
  return valid;
}

bool checkvector(position *p){
  if (p->vector == 'l' || p->vector == 'r'  || p->vector == 'u' || p->vector == 'd' ){ return true;}
  else{
    if (!testing){
      printf("Invalid Vector\n");
    }
    return false;
  }
}


bool checkpos(int length, position *p, playerBoard *pb){

  if (p->col > 9){return false;}
  if (p->col > 9){return false;}
  if (p->row < 0){return false;}
  if (p->row < 0){return false;}

  if (p->vector == 'l'){
    if (p->col-(length-1) < 0) {return false;}
    else{ for(int a=0;a<length;a++){
      pb->cells[p->row][p->col-a] = Ship;
    }
    }
  }
  else if (p->vector == 'r'){
    if (p->col >9){return false;}
    if (p->col + (length-1) > 10) {return false;}
    else{ for(int b=0;b<length;b++){
      pb->cells[p->row][p->col + b] = Ship;
    }
    }
  }
  else if (p->vector == 'u'){
    if (p->col >9){return false;}
    if (p->row + (length-1) > 10) {return false;}
    else{ for(int c=0;c<length;c++){
      pb->cells[p->row+c][p->col] = Ship;
    }
    }
  }
  else if (p->vector == 'd'){
    if (p->col >9){return false;}
    if (p->row - (length-1) < 0) {return false;}
    else{ for(int d=0;d<length;d++){
      pb->cells[p->row-d][p->col] = Ship;
    }
    }
  }

return true;
}

void retrieve(playerBoard *pb, position *p){

  bool picked = false;
  int length = 5;
  printf("Your current Board\n");
  displayPlayerBoard(pb);
  printf("\n\n");
  char row1[10];
  char col1[10];
  char vector[10];
  bool validposition = false;

  while (picked == false){

    while(validposition == false){
      printf("Pick a row for your %d length ship\n", length);
      //scanf("%d\n", row1);
      fgets(row1, 4, stdin);
      printf("Row picked: ");puts(row1);

      printf("Pick a column for your %d length ship\n", length);
      fgets(col1, 4, stdin);
      printf("Column picked: ");puts(col1);

      printf("Pick a vector for your %d length ship\n", length);
      fgets(vector, 4, stdin);
      printf("Vector picked: ");puts(vector);

      if (!isdigit(row1[0])){
        printf("Invalid row\n");
        continue;
      }

      if (!isdigit(col1[0])){
        printf("Invalid Column\n");
        continue;
      }

      int Row = atoi(row1);
      int Col = atoi(col1);

      /*printf("Row is now converted to: %d\n", Row);
      printf("Column is now converted to: %d\n", Col);
      printf("Vector is still %s\n", vector);
      */
      if (valid(Row) == false || valid(Col) == false){
        validposition = false;
        printf("Invalid\n");
        continue;
      }

      p->row = Row;
      p->col = Col;
      p->vector = vector[0];

      if ( checkvector(p) ){}
      else{
        validposition = false;
        continue;
      }

      printf("Vector is fine\n");
      if ( checkpos(length, p, pb) ){printf("Valid Position for ship\n");}
      else{validposition = false;printf("Invalid Position\n"); continue;}



      length--;
      if (length == 1){validposition = true; picked = true;}
      else{
        printf("Now checking for ship %d\n", length);
        continue;
      }

    }


  }

}

void cpuSet(computerBoard *cb, position *p){
  bool fine;
  int row1, row2;
  int vector;


  for (int i=5;i>1;i--){
    puts("Hi");
    row1  = ((rand() % 10) +1);
    puts("Row has been chosen");
    row2  = ((rand() % 10) +1);
    puts("Column has been chosen");
    fine = false;

    while (fine == false){

      vector  = ((rand() % 4) +1);
      puts("Vector has been chosen");
      if (vector == 1){p->vector = 'l';puts("Left");}
      if (vector == 2){p->vector = 'r';puts("Right");}
      if (vector == 3){p->vector = 'u';puts("Up");}
      if (vector == 4){p->vector = 'd';puts("Down");}

      p->row = row1;
      p->col = row2;

      if (p->vector == 'l'){
        if (p->col-(i-1) < 0) {fine = false; continue;}
        else{ for(int a=0;a<i;a++){
          cb->cells[p->row][p->col-a] = Ship;
        }
        }
      }
      else if (p->vector == 'r'){
        if (p->col + (i-1) > 10) {fine = false; continue;}
        else{ for(int b=0;b<i;b++){
          cb->cells[p->row][p->col + b] = Ship;
        }
        }
      }
      else if (p->vector == 'u'){
        if (p->row + (i-1) > 10) {fine = false; continue;}
        else{ for(int c=0;c<i;c++){
          cb->cells[p->row+c][p->col] = Ship;
        }
        }
      }
      else if (p->vector == 'd'){
        if (p->row - (i-1) < 0) {fine = false; continue;}
        else{ for(int d=0;d<i;d++){
          cb->cells[p->row-d][p->col] = Ship;
        }
        }
      }
      else{fprintf(stderr, "CPU Error\n");}
      fine = true;
    }

    p->row = 0;
    p->col = 0;
}



}

bool playerGuess(computerBoard *cb, hitBoard *hb, position *p){

  char crowguess[5];
  char ccolguess[5];
  int rowguess;
  int colguess;

  printf("Insert Row\n");
  fgets(crowguess, 5, stdin);

  rowguess = atoi(crowguess);

  if (!valid(rowguess)){
    printf("Row Invalid\n\n");
    playerGuess(cb,hb,p);
  }

  printf("Insert Column\n");
  fgets(ccolguess, 5, stdin);

  colguess = atoi(ccolguess);

  if (!valid(colguess)){
    printf("Column Invalid\n\n");
    playerGuess(cb,hb,p);
  }

  else{
    p->row = rowguess;
    p->col = colguess;

    if (cb->cells[p->row][p->col] == Ship){
      hb->cells[p->row][p->col] = Hit;
      printf("You hit a ship\n");
      cb->ships--;
      return true;
    }
    else{
      hb->cells[p->row][p->col] = Miss;
      printf("You Missed\n");
      return false;
    }

  }
return false;
}

bool cpuGuess(playerBoard *pb, position *p){

  char guess[5];
  guess[0] = ((rand() % 10) +1);
  guess[1] = ((rand() % 10) +1);

  p->row = guess[0];
  p->col = guess[1];

  if (pb->cells[p->row][p->col] == Ship){
    pb->cells[p->row][p->col] = Hit;
    pb->ships--;
    if (!testing){
      printf("Computer hit your ship...\n");
    }
    return true;
  }
  else{
    pb->cells[p->row][p->col] = Miss;
    if (!testing){
      printf("Computer Missed\n");
    }
    return false;
  }


  return false;
}


bool playerWin(computerBoard *cb){

  if (cb->ships == 0) {
    return true;
  }
  else{
    return false;
  }

  return true;
}

bool cpuWin(playerBoard *pb){

  if (pb->ships == 0){
    return true;
  }
  else{
    return false;
  }

}

void control(playerBoard *pb, computerBoard *cb, hitBoard *hb, position *p){


    newGame(pb, cb, hb, p);
    //puts("1");
    cpuSet(cb, p);
    //puts("2");
    displayComputerBoard(cb);
    puts("");
    retrieve(pb, p);
    puts("Your Board");
    displayPlayerBoard(pb);

    bool game = false;
    bool playerwon = false;
    bool cpuwon = false;
    bool playerright;
    bool cpuright;

    while (game == false){
      do {
        printf("Your HitBoard\n\n");
        displayHitBoard(hb);
        puts("Human's Go");
        delay(2);

        if ( playerGuess(cb,hb,p) ){
          playerright = true;//puts("8");
          displayHitBoard(hb);
          if ( playerWin(cb) ){
            puts("9");
            game = true;
            playerwon = true;
            cpuwon = false;
            break;
          }
        }
        else{
          playerright = false;
          delay(1);
          printf("Your current HitBoard:\n\n");
          displayHitBoard(hb);
          printf("\n\n\n");

          printf("Computer's Go...\n\n");
          delay(2);
        }
    } while (playerright == true);

      if (playerwon == false){
        do{

        if ( cpuGuess(pb,p) ){
          cpuright = true;
          puts("");
          displayPlayerBoard(pb);
          if ( cpuWin(pb) ){
            game = true;
            cpuwon = true;
            playerwon = false;
          }
        }
        else{
          cpuright = false;
          delay(1);
          printf("\n\n\n");

        }
      } while (cpuright == true);
    }
  }

    if (playerwon == true){
      printf("You have won!\n");
    }
    else if (cpuwon == true){
      printf("Computer has won...\n");
    }


}

int booleq(int n, bool actual, bool expected){
    n++;
    if (actual != expected){
        fprintf(stderr, "Test %d fails\n", n);
        exit(1);
    }
    return n;
}

int eqb(int n, bool x, bool y) { return booleq(n, x, y); }

void test(playerBoard *pb, computerBoard *cb, hitBoard *hb, position *p) {
    int n = 0;

        n = eqb(n, valid(6), true);
        n = eqb(n, valid('4'), false);
        n = eqb(n, valid(11), false);
        n = eqb(n, valid(9), true);
        n = eqb(n, valid(0), true);
        n = eqb(n, valid('429'), false);
        n = eqb(n, valid('5'), false);
        n = eqb(n, valid(""), false);
        n = eqb(n, valid(100), false);
        n = eqb(n, valid(-42), false);
        n = eqb(n, valid(-0), true);

        cb->ships = 7;
        n = eqb(n, playerWin(cb), false);
        cb->ships = 0;
        n = eqb(n, playerWin(cb), true);
        pb->ships = 5;
        n = eqb(n, cpuWin(pb), false);
        cb->ships = 0;
        n = eqb(n, playerWin(cb), true);
        cb->ships = -100;
        n = eqb(n, playerWin(cb), false);

        /**pb = (playerBoard) {{{Ship,Ship,Ship,Water,Water,Water,Water,Water,Water,Water},{Ship,Ship,Ship,Water,Water,Water,Water,Water,Water,Water},{Ship,Ship,Ship,Water,Water,Water,Water,Water,Water,Water},{Ship,Ship,Ship,Water,Water,Water,Water,Water,Water,Water},{Ship,Ship,Ship,Water,Water,Water,Water,Water,Water,Water},{Ship,Ship,Ship,Water,Water,Water,Water,Water,Water,Water},{Ship,Ship,Ship,Water,Water,Water,Water,Water,Water,Water},{Ship,Ship,Ship,Water,Water,Water,Water,Water,Water,Water},{Ship,Ship,Ship,Water,Water,Water,Water,Water,Water,Water},{Ship,Ship,Ship,Water,Water,Water,Water,Water,Water,Water}}};
*/
        p->col = 0;
        p->row = 0;
        p->vector = 'l';
        n = eqb(n, checkpos(5,p,pb), false);

        p->col = 146;
        p->row = 0;
        p->vector = 'l';
        n = eqb(n, checkpos(5,p,pb), false);

        p->col = 5;
        p->row = 5;
        p->vector = 'r';
        n = eqb(n, checkpos(5,p,pb), true);

        p->col = 9;
        p->row = 9;
        p->vector = 'd';
        n = eqb(n, checkpos(10,p,pb), true);

        p->vector = "uen";
        n = eqb(n, checkvector(p), false);

        p->vector = "";
        n = eqb(n, checkvector(p), false);

        p->vector = 'l';
        n = eqb(n, checkvector(p), true);

        p->vector = 'r';
        n = eqb(n, checkvector(p), true);

        p->vector = 'u';
        n = eqb(n, checkvector(p), true);

        p->vector = 'd';
        n = eqb(n, checkvector(p), true);

        printf("Tests passed: %d\n\n", n);

    testing = false;
}



int main(){

  setbuf(stdout, NULL);

  playerBoard pbdata;
  playerBoard *pb = &pbdata;

  computerBoard cbdata;
  computerBoard *cb = &cbdata;


  hitBoard hbdata;
  hitBoard *hb = &hbdata;

  position pdata;
  position *p = &pdata;

  testing = true;
  test(pb, cb, hb, p);
  srand(time(NULL));
  control(pb,cb,hb,p);

return 0;

}
