// Change this file in any way you like
// Do not alter driver.c / Makefile / md.h
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <stdbool.h>

#define BRDSZ 6
#define MAXBRDS 2000000

/*
Here define struct state -
it might look something like:
*/

typedef struct board board;

struct board{
    char hawk;
    char bd[BRDSZ][BRDSZ];
    board* parent;
};


struct state{  
    int cols;
    int rows;
    int tail;
    int front;
    board list[MAXBRDS]; 
}; 
typedef struct state state;

#include "md.h"
