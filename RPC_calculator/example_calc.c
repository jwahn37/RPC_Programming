#include<stdio.h>
#include<string.h>

#define FLAG_OPSTACK 1
#define LEN_CMD 1024
#define SIZE_STACK  1024
#define MAX_SIZE 1024
/*
계산기 계산한다: 
1. 중위 표기법을 후위 표기법으로 변환한다.

2. 후위 표기법을 계산한다.
https://jamanbbo.tistory.com/53
*/

typedef struct{
    int number;
    char op;
}CALC_ELE;

//CALC_ELE postfix_stack[SIZE_STACK];
char stack_op[SIZE_STACK];
int op_front=0;

void stack_init(char flag)
{
    if(flag == FLAG_OPSTACK)
        op_front=-1;
}
void stack_push(void* ele, char flag)
{
 //   printf("push %d %c\n", op_front, *(char*)ele);
    if(flag == FLAG_OPSTACK)
        stack_op[++op_front] = *((char*)ele);

}
void* stack_top(char flag)
{
    if(flag == FLAG_OPSTACK)
        return &(stack_op[op_front]);
}

void* stack_pop(char flag)
{
    if(flag == FLAG_OPSTACK)
    {
  //      printf("pop %d %c\n", op_front,stack_op[op_front-1]);
        return &(stack_op[op_front--]);
    }
}

char stack_empty(char flag)
{
    if(flag == FLAG_OPSTACK)
    {
        if(op_front==-1) return 1;
        else            return 0;
    }
}

char isOperation(char input)
{
	if(input=='+' || input=='-' || input=='*' || input=='/')
		return 1;
	return 0;
}
char isNumber(char input)
{
	if(input-'0' >= 0 && input-'0' <= 9)
		return 1;
	else 0;
}

//op1이 op2보다 연산자 우선순위가 같거나 높으면 true
char isPrior(char op1, char op2)
{
    
    if( (op2=='*' || op2=='/') && (op1=='+' || op1=='-'))
        return 0;
    else
        return 1;
}

int conv_postfix(char cmd_input[LEN_CMD])
{
    int i;
    int no_bf, no_af;
    char op, flag_start;
   
    //make postfix 
    CALC_ELE postfix[MAX_SIZE];
    int p_i=0;
    CALC_ELE ce;

    printf("%s\n", cmd_input);
    stack_init(FLAG_OPSTACK);
    for(i=0, no_bf=0, no_af=0, flag_start=0; i<=strlen(cmd_input); i++)
	{
        //마지막에 한번 더 취해줘야 하므로
		if(isOperation(cmd_input[i]) || i==strlen(cmd_input))
		{
            //0. 한타이밍 늦게 연산 시작해야한다. 우선, 두 operand를 먼저 받은 상태여야 함.
            /*
            if(flag_start==0)
            {
                //no_bf = no_af;
                
                op = cmd_input[i];

               // ce.number=no_bf;
                ce.number=no_af;
                ce.op=0;
                postfix[p_i++] = ce;
                
                flag_start=1;
            }
            else
            {
                */
                
                //3. 연산자 스택과 비교한다.
                //3.1 연산자 스택이 더 우선순위가 높거나 같으면 pop한다.
                //      3.1.1pop한 연산자 스택은 postfix에 저장한다.
                //3.2 그렇지 않다면 연산자를 push한다.
                if(!stack_empty(FLAG_OPSTACK) && isPrior(*(char*)(stack_top(FLAG_OPSTACK)),op ))
                {   
                    ce.op = *(char*)stack_pop(FLAG_OPSTACK);
                    printf("%c %c\n", ce.op, op);
                    ce.number = 0;
                    postfix[p_i++] = ce;
                   // stack_push(&op, FLAG_OPSTACK);
                }
                stack_push(&op, FLAG_OPSTACK);   

                //2. 숫자를 postfix에 저장한다.
                ce.number = no_af;
                ce.op = 0;
                postfix[p_i++] = ce;

                //4. 끝나면, 다음 연산을 위한 초기화 과정을 수행한다.
                //no_bf = no_af;
                op = cmd_input[i];
            //}
           
            no_af=0;
		}
		else if(isNumber(cmd_input[i]))
		{
				no_af *= 10;
				no_af += (cmd_input[i]-'0');
			
		}
		else
		{
			printf("Input Error!\n");
			return -1;
		}
	}


    //opstack에 남은애들 다 빼서 집어넣기.
    while(!stack_empty(FLAG_OPSTACK))
    {
        ce.number=0;
        ce.op=*(char*)stack_pop(FLAG_OPSTACK);
        postfix[p_i++]=ce;
    }
    
    //postfix 확인하기
    for(i=0; i<p_i; i++)
    {
        if(postfix[i].op==0)
            printf("%d ", postfix[i].number);
        else
            printf("%c ", postfix[i].op);
    }
    printf("\n");
}
int main()
{
    char cmd_input[LEN_CMD];
    int i,a,b,flag_afop;
    scanf("%s", cmd_input);

    conv_postfix(cmd_input);

    return 0;
}

