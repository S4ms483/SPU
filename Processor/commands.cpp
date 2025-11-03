#include "commands.h"

#include <stdio.h>
#include <assert.h>

#include "processor.h"
#include "stack.h"


void AddCode(Processor* processor, Spu* spu)
{
    int ncomm = 0;

    for (int i = 1; i < processor->nStr; i++)
    {
        int command = 0;
        int arg = 0;

        int nargs = sscanf(processor->strs[i], "%d %d", &command, &arg);

        // printf("ncom = %d\n", ncomm);

        if (nargs > 0)
        {
            if (command == Label)
            {
                continue;
            }

            (spu->code)[ncomm++] = command;

            switch(command)
            {
                case Push:
                case Pushr:
                case Popr:
                case Pushm:
                case Popm:
                case Jb:
                case Jbe:
                case Ja:
                case Jae:
                case Je:
                case Jne:
                case Jmp:
                case Call:
                {
                    (spu->code)[ncomm++] = arg;
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
}


void PerformCode(Spu* spu, Processor* processor)
{
    assert(spu != NULL);
    assert(processor != NULL);


    int command = spu->code[(spu->ic)];


    while ((spu->ic < processor->nComm) && (command != Hlt))
    {
        command = spu->code[(spu->ic++)];
        
        int arg = 0;
        int nArgs = 0;
        
        switch (command)
        {
            case Hlt:
                break;
            
            case Push:
                arg = spu->code[(spu->ic)++];
                StackPush(&spu->stack, arg);
                break;
            
            case Pop:
                StackPop(&spu->stack);
                break;
            
            case Add:
            case Sub:
            case Mul:
            case Div:
                ArifmOperation(&spu->stack, command);
                break;
            
            case Sqrt:
                StackSqrt(&spu->stack);
                break;
            
            case Pushr:
                arg = spu->code[(spu->ic)++];
                StackPushr(&spu->stack, spu->regs, arg);
                break;
            
            case Popr:
                arg = spu->code[(spu->ic)++];
                StackPopr(&spu->stack, spu->regs, arg);
                // fprintf(stderr, "arg = %d, RAX = %d, RBX = %d, RCX = %d\n", arg, spu->regs[0], spu->regs[1], spu->regs[2]);
                break;
            
            case In:
                printf("Enter a number to push:\n");
                nArgs = scanf("%d", &arg) != 0;
                assert(nArgs != 0);
                StackPush(&spu->stack, arg);
                break;

            case Out:
                arg = StackVariable(&spu->stack);
                printf("Last variable in stack: %d\n", arg);
                break;
                
            case Jb:
            case Jbe:
            case Ja:
            case Jae:
            case Je:
            case Jne:
                if (!ComparisonOperations(&spu->stack, command))
                {
                    // fprintf(stderr, "Not the wanted case\n");
                    spu->ic++;
                    break;
                }
                
                // StackPop(&spu->stack);
                // StackPop(&spu->stack);
                
            case Jmp:
                arg = spu->code[(spu->ic)++];
                spu->ic = arg;
                
                break;
            
            case Call:
                arg = spu->code[(spu->ic)++];
                spu->ic = arg;
                StackPush(&spu->retAdrs, arg);
                break;
            
            case Ret:
                arg = StackVariable(&spu->retAdrs);
                spu->ic = arg;
                break;
            
            case Pushm:
                assert(spu->code[(spu->ic)] < ramSize);
            
                arg = spu->ram[spu->code[(spu->ic++)]];
                StackPush(&spu->stack, arg);
                break;
            
            case Popm:
                assert(spu->code[(spu->ic)] < ramSize);
                
                arg = StackVariable(&spu->stack);
                spu->ram[spu->code[(spu->ic++)]] = arg;
                break;
                
            default:
                fprintf(stderr, "Unknown command ic = %d\n", spu->ic);
            }
            
            // StackDump(&spu->stack, __FILE__, __LINE__);
        }
    }

    
void ArifmOperation(stack_t* stk, int command)
{
    assert(stk != NULL);
    
    switch (command)
    {
        case Add:
            StackAdd(stk);
            break;
        
        case Sub:
            StackSub(stk);
            break;

        case Mul:
            StackMul(stk);
            break;
        
        case Div:
            StackDiv(stk);
            break;
    }
}


bool ComparisonOperations(stack_t* stack, int command)
{
    assert(stack != NULL);

    int a = stack->processor[stack->size-1];
    int b = stack->processor[stack->size];

    switch (command)
    {
        case Jb: return (a < b);
        case Jbe: return (a <= b);
        case Ja: return (a > b);
        case Jae: return (a >= b);
        case Je: return (a == b);
        case Jne: return (a != b);
    }
}