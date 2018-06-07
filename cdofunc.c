#include "cdo.h"

/* Allocation call for 1 router supports Flex Array Member */
Todoptr talloc(unsigned char descleng)
{
    return malloc(sizeof(Todo) + descleng);
}

/* Call for initializing manually-made router */
void init_todo(Todoptr todo, unsigned char todobyte, char *text)
{
    todo->todobyte = todobyte;
    strcpy(todo->text, text);
}

// Reads into map or otherwise returns a status
bool dat_reader(char *filnavn)
{
    FILE *fp;
    fp = fopen(filnavn, "r");
    if (fp == NULL)
    {
        printf("Bad filename\n");
        return false;
    }
    char *line;
    int i;
    while (1)
    {
        if (fgets(line, 150, fp) == NULL)
            break;
        i++;
        printf("%3d: %s", i, line);
    }
    fclose(fp);
    return true;
}

/* Return 0 if found, otherwise -1 */
int delete_todo(int id)
{
    if (list[id] != NULL)
    {
        free(list[id]);
        list[id] = NULL;
        --todo_cnt;
        return 0;
    }
    else
    {
        return -1;
    }
}

/* Run through map and free all initialized structs */
void free_map()
{
    int i;
    for (i = 0; i < 21; i++)
    {
        if (list[i] != NULL)
        {
            free(list[i]);
        }
    }
}
