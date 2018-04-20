
#ifndef PAGEREPLACEMENT_PAGEALGOS_H
#define PAGEREPLACEMENT_PAGEALGOS_H

void generateRandomInput(int size, int range, int *randomArray);

int fifo(int *pageArray, int pageArraySize, int frameSize);

int lru(int *pageArray, int pageArraySize, int frameSize);

int opt(int *pageArray, int pageArraySize, int frameSize);

#endif //PAGEREPLACEMENT_PAGEALGOS_H
