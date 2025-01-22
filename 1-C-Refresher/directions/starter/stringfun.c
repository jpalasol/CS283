#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SZ 50

// Prototypes
void usage(char *);
void print_buff(char *, int);
int setup_buff(char *, char *, int);
//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here
void reverse_string(char *, int);
void word_print(char *, int, int);

int setup_buff(char *buff, char *user_str, int len) {
    int buff_index = 0;
    int i = 0;
    int consecutive_ws = 0;
    int is_start = 1;
    int is_not_space = 0;
    memset(buff, '.', len);

    while (user_str[i] != '\0' && buff_index < len) {
        if (!(isspace(user_str[i]) && is_start)) {
            if (isspace(user_str[i])) {
                if (!consecutive_ws) {
                    buff[buff_index++] = ' ';
                    consecutive_ws = 1;
                }
            } else {
                buff[buff_index++] = user_str[i];
                consecutive_ws = 0;
                is_start = 0;
                is_not_space = i;
            }
        }
        i++;
    }

    if (user_str[i] != '\0') {
        return -1;
    }

    return i;
}

void print_buff(char *buff, int len) {
    printf("Buffer:  ");
    for (int i = 0; i < len; i++) {
        putchar(*(buff + i));
    }
    putchar('\n');
}

void usage(char *exename) {
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);
}

int count_words(char *buff, int len, int str_len) {
    int count = 0;
    int in_word = 0;

    for (int i = 0; i < str_len; i++) {
        if (buff[i] != ' ' && buff[i] != '.') {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
    }
    return count;
}

void reverse_string(char *buff, int str_len) {
    printf("Buffer:  ");
    for (int i = str_len - 1; i >= 0; i--) {
        if (buff[i] != '.') {
            putchar(buff[i]);
        }
    }
    for (int i = BUFFER_SZ; i >= 0; i--) {
        if (i > str_len) {
            buff[i] = '.';
            putchar(buff[i]);
        }
    }
    putchar('\n');
}

void word_print(char *buff, int len, int str_len) {
    int word_start = 0, word_end = 0, word_count = 1;

    printf("Word Print\n----------\n");
    for (int i = 0; i < str_len; i++) {
        if (buff[i] != ' ' && buff[i] != '.') {
            word_end++;
        } else if (word_end > word_start) {
            printf("%d. ", word_count++);
            for (int j = word_start; j < word_end; j++) {
                putchar(buff[j]);
            }
            printf("(%d)\n", word_end - word_start);
            word_start = i + 1;
            word_end = word_start;
        } else {
            word_start++;
        }
    }
    if (word_end > word_start) {
        printf("%d. ", word_count++);
        for (int j = word_start; j < word_end; j++) {
            putchar(buff[j]);
        }
        printf("(%d)\n", word_end - word_start);
    }
        printf("\nNumber of words returned: %d\n", word_count - 1);

}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

int main(int argc, char *argv[]) {

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    if ((argc < 2) || (*argv[1] != '-')) {
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1] + 1);

    if (opt == 'h') {
        usage(argv[0]);
        exit(0);
    }

    if (argc < 3) {
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3

    buff = (char *)malloc(BUFFER_SZ);
    if (buff == NULL) {
        printf("Memory allocation failed\n");
        exit(2);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);  //see todos
    if (user_str_len < 0) {
        printf("Error setting up buffer, error = %d\n", user_str_len);
        free(buff);
        exit(3);
    }

    switch (opt) {
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len); //you need to implement
            if (rc < 0) {
                printf("Error counting words, rc = %d\n", rc);
                free(buff);
                print_buff(buff, BUFFER_SZ);
                exit(3);
            }
            printf("Word Count: %d\n", rc);
            print_buff(buff, BUFFER_SZ);
            break;
        case 'r':
            reverse_string(buff, user_str_len);
            break;
        case 'w':
            word_print(buff, BUFFER_SZ, user_str_len);
            print_buff(buff, BUFFER_SZ);
            break;
        case 'x':
            printf("Not Implemented!");
            break;

        default:
            usage(argv[0]);
            free(buff);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          PLACE YOUR ANSWER HERE