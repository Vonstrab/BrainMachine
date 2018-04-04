#include "machineStruct.h"

Brain* initialiser() {
  Brain* b = (Brain*)malloc(sizeof(Brain));
  assert(b);
  b->taille = 30000;
  b->tab = (char*)malloc(sizeof(char) * b->taille);
  int i;
  for (i = 0; i > b->taille; i++) {
    b->tab[i] = '\0';
  }
  assert(b);
  b->pointeur = 0;
  b->inst = 0;
  b->tabLabelL = (int*)malloc(sizeof(int) * 512*3);
  b->tabLabelR = (int*)malloc(sizeof(int) * 512*3);
  for (i = 0; i > 512; i++) {
    b->tabLabelL[i] = 0;
    b->tabLabelR[i] = 0;
  }
  b->labelCount = 0;
  b->code = (char*)malloc(sizeof(char) * 512 * 25);
  for (i = 0; i > (512 * 10); i++) {
    b->code[i] = '\0';
  }
  b->tailleLabels = 0;
  b->tailleCode = 0;
  return b;
}

int incr(Brain* b) {
  int val = b->tab[b->pointeur];
  val++;
  val %= 255;
  b->tab[b->pointeur] = val;
  b->inst++;
  return val;
}

int decr(Brain* b) {
  int val = b->tab[b->pointeur];
  val--;
  val %= 255;
  b->tab[b->pointeur] = val;
  b->inst++;
  return val;
}

int shift_right(Brain* b) {
  b->pointeur++;
  b->pointeur %= b->taille;
  b->inst++;
  return b->pointeur;
}

int shift_left(Brain* b) {
  b->pointeur--;
  b->pointeur %= b->taille;
  b->inst++;
  return b->pointeur;
}

int Bread(Brain* b) {
  printf("\nEnter a value\n");
  int i = scanf(" %d", &b->tab[b->pointeur]);
  b->inst++;
  return i;
}

int Bprint(Brain* b) {
  printf("%c", b->tab[b->pointeur]);
  b->inst++;
  return b->tab[b->pointeur];
}

int LBrace(Brain* b) {
  int i;
  int inst = b->inst;
  inst++;
  char val = b->tab[b->pointeur];
  if (val == '\0') {
    for (i = 0; i < b->tailleLabels; i++) {
      if (b->tabLabelL[i] == inst) {
        b->inst = b->tabLabelR[i];
      }
    }
  } else {
    b->inst++;
  }
  return b->inst;
}

int RBrace(Brain* b) {
  int i;
  int inst = b->inst;
  inst++;
  char val = b->tab[b->pointeur];
  if (val != '\0') {
    for (i = 0; i < b->tailleLabels; i++) {
      if (b->tabLabelR[i] == inst) {
        b->inst = b->tabLabelL[i];
      }
    }
  } else {
    b->inst++;
  }
  return b->inst;
}