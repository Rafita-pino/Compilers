/*DFA.C*/

#include <stdio.h>
#include <stdbool.h>

int read_char() {
    int c;
    do {
        c = getchar();
    } while (c == '\n'); 
    return c;
}
void printResult(char result[], int length) {
    printf("Final input: ");
    for (int j = 0; j < length; j++) {
        printf("%c", result[j]);
    }
    printf("\n");
}

int main(void){
    int state = 1, c, i = 0;
    bool final = false;
    char result[100];
    result[0] = '\0';
    while(!final){
        switch(state){
            case 1:
                if (i > 0) result[i]= c;
                printf("STATE 1\n");
                printf("Enter 'a': \n");
                c = read_char();
                if(c == 'a') state = 2;
                else state = 4;
                break;
            case 2:
                result[i]= c;
                printf("STATE 2\n");
                printf("Enter 'a' or 'b': \n");
                c = read_char();
                if(c=='b') state = 1;
                else if(c=='a') state = 3;
                else state = 4;
                break;
            case 3:
                result[i]= c;
                printf("FINAL STATE\n");
                final = true;
                break;
            case 4:
                printf("Invalid input\n");
                final = true;
                break;
            default:
                printf("Error\n");
                final = true;
                break;
        }
        i++;        
    }
    printResult(result, i);
    return 0; 
}

