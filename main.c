#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    double *items;
    int top;
    int size;
} Stack;


void initialize(Stack *stack, int size) {
    stack->items = (double *)malloc(size * sizeof(double));
    stack->top = -1;
    stack->size = size;
}


int isEmpty(Stack *stack) {
    return stack->top == -1;
}


int isFull(Stack *stack) {
    return stack->top == stack->size - 1;
}


void push(Stack *stack, double item) {
    if (isFull(stack)) {
        printf("Erro: Pilha cheia\n");
        return;
    }
    stack->items[++stack->top] = item;
}


double pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Erro: Pilha vazia\n");
        return 0.0;
    }
    return stack->items[stack->top--];
}


double peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Erro: Pilha vazia\n");
        return 0.0;
    }
    return stack->items[stack->top];
}


double evaluatePostfixExpression(const char *expression) {
    Stack stack;
    initialize(&stack, 100);

    for (int i = 0; expression[i] != '\0'; ++i) {
        if (expression[i] == ' ' || expression[i] == '\t') {
            continue; 
        } else if ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.') {
            
            push(&stack, atof(&expression[i]));
            while ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.') {
                ++i;
            }
            --i; 
        } else {
            
            double operand2, operand1;

            switch (expression[i]) {
                case '+':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    push(&stack, operand1 / operand2);
                    break;
                case '^':
                    operand2 = pop(&stack);
                    operand1 = pop(&stack);
                    push(&stack, pow(operand1, operand2));
                    break;
                case 'l': // log10
                    operand1 = pop(&stack);
                    push(&stack, log10(operand1));
                    break;
                case 's': // sin
                    operand1 = pop(&stack);
                    push(&stack, sin(operand1));
                    break;
                case 'c': // cos
                    operand1 = pop(&stack);
                    push(&stack, cos(operand1));
                    break;
                case 't': // tan
                    operand1 = pop(&stack);
                    push(&stack, tan(operand1));
                    break;
                default:
                    printf("Erro: Operador inválido\n");
                    free(stack.items);
                    return 0.0;
            }
        }
    }

    double result = pop(&stack);
    free(stack.items);
    return result;
}

int main() {
    
    const char *expressions[] = {
        "3 4 + 5 *",
        "7 2 * 4 +",
        "8 5 2 4 + * +",
        "6 2 / 3 + 4 *",
        "9 5 2 8 * 4 + * +",
        "2 3 + l 5 /",
        "10 l 3 ^ 2 +",
        "45 60 + 30 c *",
        "0.5 45 s 2 ^ +",
        "3 4 + 5 t *"
    };

    
    const double expected[] = {35, 18, 38, 24, 109, 0.140, 5, 16.20, 2.30, -23.66};

    for (int i = 0; i < sizeof(expressions) / sizeof(expressions[0]); ++i) {
        double result = evaluatePostfixExpression(expressions[i]);
        printf("Resultado Esperado: %.2f, Resultado Obtido: %.2f\n", expected[i], result);
    }

    return 0;
}
