#include <stdio.h>
#include <string.h>

#define FLAG_OPSTACK 1
#define FLAG_PFSTACK 2
#define LEN_CMD 1024
#define SIZE_STACK 1024
#define MAX_SIZE 1024
/*
계산기 계산한다: 
1. 중위 표기법을 후위 표기법으로 변환한다.
**괄호는 구현하지 않았음.
2. 후위 표기법을 계산한다.
https://jamanbbo.tistory.com/53
*/

typedef struct
{
    int number;
    char op;
} CALC_ELE;

//CALC_ELE postfix_stack[SIZE_STACK];
char stack_op[SIZE_STACK];
int op_front;

CALC_ELE postfix[MAX_SIZE];
int pf_size;

int pf_front;
int stack_pf[SIZE_STACK];

void stack_init(char flag)
{
    if (flag == FLAG_OPSTACK)
        op_front = -1;
    if (flag == FLAG_PFSTACK)
        pf_front = -1;
}
void stack_push(void *ele, char flag)
{
    //   printf("push %d %c\n", op_front, *(char*)ele);
    if (flag == FLAG_OPSTACK)
        stack_op[++op_front] = *((char *)ele);
    if (flag == FLAG_PFSTACK)
        stack_pf[++pf_front] = *((int *)ele);
}
void *stack_top(char flag)
{
    if (flag == FLAG_OPSTACK)
        return &(stack_op[op_front]);
    if (flag == FLAG_PFSTACK)
        return &(stack_pf[pf_front]);
}

void *stack_pop(char flag)
{
    if (flag == FLAG_OPSTACK)
    {
        //      printf("pop %d %c\n", op_front,stack_op[op_front-1]);
        return &(stack_op[op_front--]);
    }
    if (flag == FLAG_PFSTACK)
        return &(stack_pf[pf_front--]);
}

char stack_empty(char flag)
{
    if (flag == FLAG_OPSTACK)
    {
        if (op_front == -1)
            return 1;
        else
            return 0;
    }
    if (flag == FLAG_PFSTACK)
    {
        if (pf_front == -1)
            return 1;
        else
            return 0;
    }
}

char isOperation(char input)
{
    if (input == '+' || input == '-' || input == '*' || input == '/')
        return 1;
    return 0;
}
char isNumber(char input)
{
    if (input - '0' >= 0 && input - '0' <= 9)
        return 1;
    else
        0;
}

//op1이 op2보다 연산자 우선순위가 같거나 높으면 true
char isPrior(char op1, char op2)
{

    if ((op2 == '*' || op2 == '/') && (op1 == '+' || op1 == '-'))
        return 0;
    else
        return 1;
}

int calc(int n1, int n2, char op)
{
    switch (op)
    {
    case '+':
        return n1 + n2;
    case '-':
        return n1 - n2;
    case '*':
        return n1 * n2;
    case '/':
        return n1 / n2;
    }
}

int calc_postfix()
{
    int i;
    int n1, n2, res;
    stack_init(FLAG_PFSTACK);
    for (i = 0; i < pf_size; i++)
    {
        if (postfix[i].op == 0) //number
        {
            stack_push(&(postfix[i].number), FLAG_PFSTACK);
        }
        else //operation
        {
            n1 = *(int *)stack_pop(FLAG_PFSTACK);
            n2 = *(int *)stack_pop(FLAG_PFSTACK);

            res = calc(n1, n2, postfix[i].op);
            stack_push(&res, FLAG_PFSTACK);
        }
    }
    printf("res : %d\n", *(int*)stack_top(FLAG_PFSTACK));
}
int conv_postfix(char cmd_input[LEN_CMD])
{
    int i;
    int no;
    char op, flag_start;

    //make postfix

    int p_i = 0;
    CALC_ELE ce;

    printf("%s\n", cmd_input);
    stack_init(FLAG_OPSTACK);
    for (i = 0, no = 0, flag_start = 0; i <= strlen(cmd_input); i++)
    {
        //마지막에 한번 더 취해줘야 하므로
        if (isOperation(cmd_input[i]) || i == strlen(cmd_input))
        {

            //2. 숫자를 postfix에 저장한다.
            ce.number = no;
            ce.op = 0;
            postfix[p_i++] = ce;
            //3. 연산자 스택과 비교한다.
            //3.1 연산자 스택이 더 우선순위가 높거나 같으면 pop한다.
            //      3.1.1pop한 연산자 스택은 postfix에 저장한다.
            //3.2 그렇지 않다면 연산자를 push한다.
            op = cmd_input[i];
            if (!stack_empty(FLAG_OPSTACK) && isPrior(*(char *)(stack_top(FLAG_OPSTACK)), op))
            {
                ce.op = *(char *)stack_pop(FLAG_OPSTACK);
                printf("%c %c\n", ce.op, op);
                ce.number = 0;
                postfix[p_i++] = ce;
                // stack_push(&op, FLAG_OPSTACK);
            }
            if (i < strlen(cmd_input))
                stack_push(&op, FLAG_OPSTACK);

            no = 0;
        }
        else if (isNumber(cmd_input[i]))
        {
            no *= 10;
            no += (cmd_input[i] - '0');
        }
        else
        {
            printf("Input Error!\n");
            return -1;
        }
    }

    //opstack에 남은애들 다 빼서 집어넣기.
    while (!stack_empty(FLAG_OPSTACK))
    {
        ce.number = 0;
        ce.op = *(char *)stack_pop(FLAG_OPSTACK);
        postfix[p_i++] = ce;
    }
    pf_size = p_i;
    /*
    //postfix 확인하기
    for (i = 0; i < p_i; i++)
    {
        if (postfix[i].op == 0)
            printf("%d ", postfix[i].number);
        else
            printf("%c ", postfix[i].op);
    }
    printf("\n");
*/
    calc_postfix();
}
int main()
{
    char cmd_input[LEN_CMD];
    int i, a, b, flag_afop;
    scanf("%s", cmd_input);

    conv_postfix(cmd_input);

    return 0;
}
