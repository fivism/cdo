#include "cdo.h"

/* main: all forward facing/output functions and main are here */

void signal_handler(int signo) {
    if (signo == SIGINT) {
        // TODO Safe interrupt 
        // dat_writer("RECOVERED.dat");
        exit(1);
    }
}

void print_list() {
    int i, cnt = 1; 
    for (i = 0; i < MAX_TODO; i++) {
        if (list[i] != NULL) {
            printf("[%d] %s \n", (cnt), list[i]->text);   
            ++cnt;
        }   
    }
}

/* Writes out new save file from memstruct if there were any adds/removals
 * Return: 
 *  0 on write success
 * -1 on write failure 
 */ 
int write_empty_list() { 
    FILE *fp;
    fp = fopen(SAV_FILE, "w");
    todo_cnt = 0;
    fwrite(&todo_cnt, 1, 1, fp);
    fclose(fp);
    return 0;
}

int write_list() {
    FILE *fp;
    fp = fopen(SAV_FILE, "w");
    fwrite(&todo_cnt, 1, 1, fp); 
    
    int i;

    for (i = 0; i < MAX_TODO; i++) {
        if (list[i] != NULL) {
            unsigned char tmp_byte = list[i]->todobyte; // PROBLEM AREA
            fwrite(&tmp_byte, 1, 1, fp);
            fwrite(list[i]->text, strlen(list[i]->text)+1, 1, fp); 
        }
    }
    
    fclose(fp);
    return 0;
}

int write_test_list() {
    FILE *fp; 
    fp = fopen(SAV_FILE, "w");  
    todo_cnt = 4;

    Todoptr test_list[4]; 
    
    int i;
    fwrite(&todo_cnt, 1, 1, fp);
 
    for (i = 0; i < 4; i++) { 
        unsigned char todobyte = 6;
        Todoptr tmp_todo = talloc(6);
        test_list[i] = tmp_todo;
        test_list[i]->todobyte = todobyte;
        strcpy(test_list[i]->text, "test1");
        fwrite(test_list[i], todobyte + 1, 1, fp);
    }    
    
    fclose(fp);
    return 0;
}
    
/* Reads in list from save file (default: ~/.cdo_list) 
 * Return: 
 * 0 on read success
 * -1 on nofile/badfile
 */
 
int read_list() {
    FILE *fp; 
    fp = fopen(SAV_FILE, "r");

    if (fp == NULL) {
        printf("READ ERROR\n");
        return -1; // Return "not found" value
    }
    
    fread(&todo_cnt, 1, 1, fp); // Read first byte with todo_cnt
     
    int i;
    for (i = 0; i < todo_cnt; i++) {
        // Sequentially fread the things in
        unsigned char todobyte;
        fread(&todobyte, 1, 1, fp);
        //TODO this needs to change with highlighting
        Todoptr tmp_todo = talloc(todobyte + 1); // flexible length of size todobyte
        tmp_todo->todobyte = todobyte;
        fread(&tmp_todo->text, 1, todobyte, fp);
        list[i] = tmp_todo;
    } 

    fclose(fp);
    
    return 0;
}

/* Switch/case menu loop and logic and calls to file operations here */
int main(int argc, char* argv[]) {

    // IF WRONG ARGS && NO FILE FOUND
    read_list(); 

    if ((argc > 2)) {
        fprintf(stderr, "Usage: %s [task desc] | [task id to finish]\n", argv[0]);
        exit(0);
    }

    if (argc == 2) {
        int retv = atoi(argv[1]);
        if (retv > 0) {
            if (retv < todo_cnt + 1) {
                delete_todo(retv - 1);
                write_list(); 
            } else {
                printf("Todo [%d] not found!\n", retv);  
                return 0; 
            }
        } else {
            unsigned char todobyte = strlen(argv[1]);   
            list[todo_cnt] = talloc(todobyte + 1); 
            list[todo_cnt]->todobyte = todobyte + 1;
            strcpy(list[todo_cnt]->text, argv[1]);  
            ++todo_cnt;
            write_list();
            return 0;
        }
        print_list();
    } else {
        print_list();
    } 

    signal(SIGINT, signal_handler);
    return 0;
}
