#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


struct node {
  struct node *left;
  struct node *right;
  void *item;
};
typedef struct node node;

struct list {
  struct node *first;
  struct node *current;
  struct node *last;
  int length, sizeofbyte;

};

// Create a new empty list.  The argument is the size of an item in bytes.
list *newList(int b) {
  list *l = malloc(sizeof(list));

  node *sentinel = malloc(sizeof(node));
  sentinel->right = sentinel;
  sentinel->left = sentinel;
  sentinel->item = malloc(b);
  //printf("B is :%d\n", b);
  *l = (list) {sentinel, sentinel, sentinel, 0, b};
  //printf("Size of Byte is %d\n", l->sizeofbyte);
  sentinel->item = NULL;
  return l;
}

// Set the current position before the first item or after the last item, e.g.
// to begin a forward or backward traversal.
void start(list *l) {
  l->first = l->current;
}

void end(list *l) {
  l->last = l->current;
}

// Check whether the current position is at the start or end, e.g. to test
// whether a traversal has finished.
bool atStart(list *l) {
  return l->current == l->first;
}

bool atEnd(list *l){
  return l->current == l->last;
}

// Move the current position one place forwards or backwards.  It is an error
// to call forward when at the end of the list, or backward when at the start.
void forward(list *l) {

  /*if ( atEnd(l) ) {
    fprintf(stderr, "Error\n");
    exit(1);
  }
  */
  l->current = l->current->right;
}

void backward(list *l){

  /*if (atStart(l)) {
    fprintf(stderr, "Error\n");
    exit(1);
  }
  */
  l->current = l->current->left;
}

// Insert an item before or after the current position (i.e. at the current
// position, but with the current position ending up after or before the new
// item).  The second argument is a pointer to the item to be copied.
void insertBefore(list *l, void *p) {

  node *ns = malloc(sizeof(node));
  ns->item = malloc(l->sizeofbyte);
  //printf("Size of byte is yo: %d\n", l->sizeofbyte);
  ns->left = l->current->left;
  ns->right  =l->current;
  //printf("Size of byte is ye: %d\n", l->sizeofbyte);
  memcpy(ns->item,p,l->sizeofbyte);
  //printf("Size of byte is yeoo: %d\n", l->sizeofbyte);
  l->current->left->right = ns;
  //printf("Size of byte is yoyoyo: %d\n", l->sizeofbyte);
  l->current->left = ns;
  //printf("Size of byte is ya: %d\n", l->sizeofbyte);
  if (l->current == l->first) {
    l->first = ns;
  }

}

void insertAfter(list *l, void *p) {

  node *ns = malloc(sizeof(node));
  //printf("Size of byte is yo: %d\n", l->sizeofbyte);
  ns->item = malloc(l->sizeofbyte);
  //printf("Size of byte is yoo: %d\n", l->sizeofbyte);
  ns->right = l->current->right;
  //printf("Size of byte is yooo: %d\n", l->sizeofbyte);
  ns->left  = l->current;
  //printf("Size of byte is yoooo: %d\n", l->sizeofbyte);
  memcpy(ns->item,p,l->sizeofbyte);
  //printf("Size of byte is yooooo: %d\n", l->sizeofbyte);
  if (l->current == l->first) {
    l->first = ns;
    //printf("Size of byte is yoooooo: %d\n", l->sizeofbyte);
  }
  l->current->left->right = ns;
  //printf("Size of byte is yaaaaaa: %d\n", l->sizeofbyte);
  l->current->left = ns;
  //printf("Size of byte is yaaaaaaaas: %d\n", l->sizeofbyte);
  l->current = ns;
  //printf("Size of byte is yaaaaaaaaaaassssss: %d\n", l->sizeofbyte);

}


// Get the item before the current position or after the current position.
// The second argument is a pointer to a place to copy the item into. It is an
// error to call getBefore when at the start, or getAfter when at the end.
void getBefore(list *l, void *p){


  if (atStart(l)) {
    fprintf(stderr, "Error\n");
    exit(1);
  }

  memcpy(p, l->current->left->item, l->sizeofbyte);

}

void getAfter(list *l, void *p){


  if (atEnd(l)){
    fprintf(stderr, "Error\n");
    exit(1);
  }


  memcpy(p, l->current->item, l->sizeofbyte);

}

// Set the item before the current position or after the current position.
// The second argument is a pointer to the new item value. It is an error to
// call setBefore when at the start, or setAfter when at the end.
void setBefore(list *l, void *p){

  if ( atStart(l) ){
    fprintf(stderr, "Error\n");
    exit(1);
  }

  memcpy(l->current->left->item, p, l->sizeofbyte);

}

void setAfter(list *l, void *p){

  if ( atEnd(l) ){
    fprintf(stderr, "Error\n");
    exit(1);
  }

  memcpy(l->current->item, p, l->sizeofbyte);

}

// Delete the item before or after the current position. It is an error to call
// deleteBefore when at the start, or deleteAfter when at the end.
void deleteBefore(list *l){

  if ( atStart(l) ){
    fprintf(stderr, "Error\n");
    exit(1);
  }

  else{

    free(l->current->left->item);
    l->current->left->item  = l->current->left;
    l->current->right->item = l->current->item;

  }

}

void deleteAfter(list *l){

  if ( atEnd(l) ){
    puts("yo");
    fprintf(stderr, "Error\n");
    exit(1);
  }
  else{

    free(l->current->item);

  }

}

// Unit testing.  Test the module, returning the number of tests passed.  If a
// test fails, print out a message and stop the program.

enum type {CHAR, INT, BOOL};
int eq(enum type t, int x, int y);

int eqc(char x, char y) { printf("c is %c\n", x); return eq(CHAR, x, y); }
int eqi(int x, int y) { printf("x is:%d\n", x); return eq(INT, x, y);}
int eqb(bool x, bool y) {
   if (x == true){
    printf("b is: True\n");
   }
  else{
    printf("b is: False\n");
  }
    return eq(BOOL, x, y);
}

int eqs(char *x, char *y) {

    if (strcmp(x, y) != 0) {
        fprintf(stderr, "Test fails:\n");
        fprintf(stderr, "result %s instead of %s\n", x, y);
        exit(1);
    }
    return 0;
}

inline list *newIntList() { return newList(sizeof(int)); }
inline list *newBoolList() { return newList(sizeof(bool)); }
inline list *newCharList() { return newList(sizeof(char)); }
inline list *newStringList() {return newList(sizeof(char *)); }

inline void insertIntBefore(list *l, int n) { insertBefore(l, &n); }
inline void insertIntAfter(list *l, int n) { insertAfter(l, &n);}
inline int getIntBefore(list *l){int x=0; getBefore(l, &x);  return x;}
inline int getIntAfter(list *l){int x=0; getAfter(l, &x); return x;}
inline int setIntBefore(list *l, int n){ setBefore(l, &n); return n;}
inline int setIntAfter(list *l, int n){ setAfter(l, &n); return n;}
inline void deleteIntBefore(list *l) { deleteBefore(l); }
inline void deleteIntAfter(list *l) { deleteAfter(l);}

inline void insertBoolBefore(list *l, bool b){ insertBefore(l, &b); }
inline void insertBoolAfter(list *l, bool b){ insertAfter(l, &b);}
inline bool getBoolBefore(list *l){bool b; getBefore(l, &b); return b;}
inline bool getBoolAfter(list *l){bool b; getAfter(l, &b); return b;}
inline bool setBoolBefore(list *l, bool b){ setBefore(l, &b); return b;}
inline bool setBoolAfter(list *l, bool b){ setAfter(l, &b); return b;}
inline void deleteBoolBefore(list *l) { deleteBefore(l); }
inline void deleteBoolAfter(list *l) { deleteAfter(l);}

inline void insertCharBefore(list *l, char c){ insertBefore(l, &c);}
inline void insertCharAfter(list *l, char c){ insertAfter(l, &c);}
inline char getCharBefore(list *l){char c; getBefore(l, &c); return c;}
inline char getCharAfter(list *l){char c; getAfter(l, &c); return c;}
inline char setCharBefore(list *l, char c){ setBefore(l, &c); return c;}
inline char setCharAfter(list *l, char c){ setAfter(l, &c); return c;}
inline void deleteCharBefore(list *l) { deleteBefore(l); }
inline void deleteCharAfter(list *l) { deleteAfter(l);}

inline void insertStringBefore(list *l, char *s){ insertBefore(l, &s);}
inline void insertStringAfter(list *l, char *s){ insertAfter(l, &s);}
inline char *getStringBefore(list *l){char *s; getBefore(l, &s); return s;}
inline char *getStringAfter(list *l){char *s; getAfter(l, &s); return s;}
inline char *setStringBefore(list *l, char *s){ setBefore(l, &s); return s;}
inline char *setStringAfter(list *l, char *s){ setAfter(l, &s); return s;}
inline void deleteStringBefore(list *l) { deleteBefore(l); }
inline void deleteStringAfter(list *l) { deleteAfter(l);}


int eq(enum type t, int x, int y){
  static int n = 0;
  n++;
  if (x != y){

    if (t == CHAR) fprintf(stderr, "Test %d gives %c not %c\n", n, x, y);
    if (t==INT) fprintf(stderr, "Test %d gives %d not %d\n", n, x, y);
    if (t==BOOL && x)fprintf(stderr, "Test %d gives True not False\n", n);
    if (t==BOOL && y)fprintf(stderr, "Test %d gives False not True\n", n);
    exit(1);
  }

  return n;

}

int testLists(){

int n = 7;

//Int Tests
list *ints = newIntList();

insertIntBefore(ints,5);
eqi(getIntBefore(ints),5); //Test 1
insertIntAfter(ints, 9);
eqi(getIntAfter(ints), 9); //Test 2
eqi(ints->sizeofbyte, 4); //Test 3
eqb( atStart(ints), false); //Test 4

//Bool Tests
list *bools = newBoolList();

forward(bools);
insertBoolAfter(bools, true);
eqb(getBoolAfter(bools), true); //Test 5
eqi(bools->sizeofbyte, 1); //Test 6

//Char Tests
list *chars = newCharList();

forward(chars);
insertCharAfter(chars, 'a');
eqc(getCharAfter(chars), 'a'); //Test 7
setCharAfter(chars, 'b');
eqc(getCharAfter(chars), 'b'); //Test 8

//String Tests
list *strings = newStringList();

forward(strings);
insertStringBefore(strings, "Adam");
eqs(getStringBefore(strings), "Adam"); //Test 9
setStringBefore(strings, "Sadiq");
eqs(getStringBefore(strings), "Sadiq"); //Test 10


//Testing Delete

insertStringBefore(strings, "Yoo");
insertStringAfter(strings, "Hey");
forward(strings);
insertStringBefore(strings, "AS");
insertStringAfter(strings, "Uni");
deleteStringBefore(strings);
eqs(getStringBefore(strings), "Hey"); //Test 11

printf("All Tests Pass\n");

  return n;
}

int main(){
  setbuf(stdout, NULL);
  testLists();

  return 0;
}
