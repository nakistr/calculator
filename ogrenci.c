#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>  
#include <math.h>   
#include <limits.h> 

struct StackNode {
    int data;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

void push(struct Stack* stack, int data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) {
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return INT_MIN; 
    }
    struct StackNode* temp = stack->top;
    int poppedData = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return poppedData;
}

const char* OPERATORS[] = {"+", "-", "*", "/", "^"};
const int NUM_OPERATORS = 5;

int isOperator(char* token) {
    for (int i = 0; i < NUM_OPERATORS; i++) {
        if (strcmp(token, OPERATORS[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int checkValidity(char* ifade[], int n, char* a_type, char* b_type, char* c_type) {
    int sayac = 0; 
    for (int i = 0; i < n; i++) {
        char* token = ifade[i];
        if (isdigit(token[0]) || (token[0] == '-' && strlen(token) > 1)) {
            sayac++;
        } else if (isOperator(token)) {
            if (sayac < 2) return 0;
            sayac--;
        } else if (strcmp(token, "a") == 0) {
            if (strcmp(a_type, "num") == 0) sayac++;
            else if (strcmp(a_type, "op") == 0) {
                if (sayac < 2) return 0;
                sayac--;
            }
        } else if (strcmp(token, "b") == 0) {
            if (strcmp(b_type, "num") == 0) sayac++;
            else if (strcmp(b_type, "op") == 0) {
                if (sayac < 2) return 0;
                sayac--;
            }
        } else if (strcmp(token, "c") == 0) {
            if (strcmp(c_type, "num") == 0) sayac++;
            else if (strcmp(c_type, "op") == 0) {
                if (sayac < 2) return 0;
                sayac--;
            }
        }
        
        if (sayac < 1 && i < n - 1) { 
            return 0; 
        }
    }
    return sayac == 1;
}

int applyOperator(int A, int B, const char* op) {
    long long result;
    
    if (strcmp(op, "+") == 0) {
        result = (long long)A + B;
    } else if (strcmp(op, "-") == 0) {
        result = (long long)A - B;
    } else if (strcmp(op, "*") == 0) {
        result = (long long)A * B;
    } else if (strcmp(op, "/") == 0) {
        if (B == 0 || A % B != 0) return INT_MIN;
        result = A / B;
    } else if (strcmp(op, "^") == 0) {
        if (B < 0) return INT_MIN;
        if (B > 30) return INT_MIN;
        result = 1;
        for (int i = 0; i < B; i++) {
            result *= A;
            if (result > INT_MAX || result < INT_MIN) return INT_MIN;
        }
    } else {
        return INT_MIN;
    }
    
    if (result > INT_MAX || result < INT_MIN) {
        return INT_MIN;
    }
    
    return (int)result;
}

int evaluatePostfix(char* ifade[], int n, char* a_val, char* b_val, char* c_val) {
    struct Stack* stack = createStack();
    int hata = 0;

    for (int i = 0; i < n; i++) {
        char* token = ifade[i];
        int valA, valB, currentRes;
        
        char* current_val = NULL;
        if (strcmp(token, "a") == 0) current_val = a_val;
        else if (strcmp(token, "b") == 0) current_val = b_val;
        else if (strcmp(token, "c") == 0) current_val = c_val;
        else current_val = token;

        if (isdigit(current_val[0]) || (current_val[0] == '-' && strlen(current_val) > 1)) {
            push(stack, atoi(current_val));
        } else if (isOperator(current_val)) {
            valB = pop(stack);
            valA = pop(stack);
            
            if (valA == INT_MIN || valB == INT_MIN) {
                hata = 1;
                break;
            }

            currentRes = applyOperator(valA, valB, current_val);
            
            if (currentRes == INT_MIN) {
                hata = 1;
                break; 
            }
            
            push(stack, currentRes);
        }
    }

    int sonuc;
    if (hata) {
        sonuc = INT_MIN;
    } else {
        sonuc = pop(stack);
        if (!isEmpty(stack)) {
            sonuc = INT_MIN;
        }
    }

    while (!isEmpty(stack)) pop(stack);
    free(stack);
    return sonuc;
}

int main() {
    FILE *dosya = fopen("input.txt", "r");
    if (dosya == NULL) {
        printf("Hata: input.txt dosyasi bulunamadi.\n");
        return 1;
    }
    
    char satir[256];
    fgets(satir, sizeof(satir), dosya);
    fclose(dosya);
    satir[strcspn(satir, "\n")] = 0;
    
    char satir_kopya[256];
    strcpy(satir_kopya, satir); 
    
    char* ifade[100]; 
    int n = 0; 
    
    char* token = strtok(satir_kopya, " "); 
    while (token != NULL && strcmp(token, "=") != 0) {
        ifade[n++] = strdup(token); 
        token = strtok(NULL, " ");
    }
    
    struct Solution {
        char a[12];
        char b[12];
        char c[12];
    };
    
    struct Solution solutions[1000];
    int cozumSayisi = 0;
    
    char* turler[] = {"num", "op"};
    char val_a[12], val_b[12], val_c[12]; 
    
    int MAX_NUM = 30;

    for (int i = 0; i < 2; i++) { 
        for (int j = 0; j < 2; j++) { 
            for (int k = 0; k < 2; k++) { 
                
                char* a_turu = turler[i];
                char* b_turu = turler[j];
                char* c_turu = turler[k];

                int gecerli = checkValidity(ifade, n, a_turu, b_turu, c_turu);

                if (gecerli) {
                    int a_start = (strcmp(a_turu, "op") == 0) ? 0 : 1;
                    int a_end = (strcmp(a_turu, "op") == 0) ? NUM_OPERATORS : MAX_NUM + 1;
                    
                    for (int a_idx = a_start; a_idx < a_end; a_idx++) {
                        if (strcmp(a_turu, "op") == 0) {
                            strcpy(val_a, OPERATORS[a_idx]);
                        } else {
                            sprintf(val_a, "%d", a_idx);
                        }

                        int b_start = (strcmp(b_turu, "op") == 0) ? 0 : 1;
                        int b_end = (strcmp(b_turu, "op") == 0) ? NUM_OPERATORS : MAX_NUM + 1;
                        
                        for (int b_idx = b_start; b_idx < b_end; b_idx++) {
                            if (strcmp(b_turu, "op") == 0) {
                                strcpy(val_b, OPERATORS[b_idx]);
                            } else {
                                sprintf(val_b, "%d", b_idx);
                            }

                            int c_start = (strcmp(c_turu, "op") == 0) ? 0 : 1;
                            int c_end = (strcmp(c_turu, "op") == 0) ? NUM_OPERATORS : MAX_NUM + 1;
                            
                            for (int c_idx = c_start; c_idx < c_end; c_idx++) {
                                if (strcmp(c_turu, "op") == 0) {
                                    strcpy(val_c, OPERATORS[c_idx]);
                                } else {
                                    sprintf(val_c, "%d", c_idx);
                                }
                                
                                int sonuc = evaluatePostfix(ifade, n, val_a, val_b, val_c);
                                
                                if (sonuc == 0) {
                                    strcpy(solutions[cozumSayisi].a, val_a);
                                    strcpy(solutions[cozumSayisi].b, val_b);
                                    strcpy(solutions[cozumSayisi].c, val_c);
                                    cozumSayisi++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    printf("Possible value combinations for (a, b, c)\n");
    for (int i = 0; i < cozumSayisi; i++) {
        printf("(%s, %s, %s)\n", solutions[i].a, solutions[i].b, solutions[i].c);
    }

    for (int i = 0; i < n; i++) {
        free(ifade[i]);
    }

    return 0;
}