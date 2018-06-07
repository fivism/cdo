#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define SAV_FILE ".cdo" // Filename
#define MAX_TODO 21
#define ANSI_YELLOW "\x1b[33m" // For number highlighting
#define ANSI_RESET "\x1b[0m"   //

typedef struct todo *Todoptr; // Declaring a router pointer struct
typedef struct todo
{                           // Declaring router struct
    unsigned char todobyte; // highlight bit + char cnt
    char text[];            // Max length 253;
} Todo;

unsigned char todo_cnt;
int delete_todo(int todo);
/* function stub declarations from drift.c */
void init_todo(Todoptr todo,
               unsigned char todobyte,
               char *desc);
Todoptr talloc(unsigned char descleng);

void free_map();

Todoptr list[MAX_TODO];
