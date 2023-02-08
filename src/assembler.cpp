#include "../include/assembler.h"

size_t assembler_if_syntax_check(Token_List ls, int index)
{
    if(ls[index+1].type == OPEN_P && ls[index+2].type == ID){
        if(ls[index+3].type == EQUALS && ls[index+4].type == EQUALS){
            if(isType(ls[index+5].type))
            {
                return 5;
            }
        }
        else if(ls[index+3].type == FCALL && ls[index+4].type == EQUALS)
            if(isType(ls[index+5].type))
            {
                return 5;
            }
        else if(ls[index+3].type == GREATERT)
            if(isType(ls[index+4].type))
            {
                return 4;
            }
        else if(ls[index+3].type == LESST)
            if(isType(ls[index+4].type))
            {
                return 4;
            }
    }
    return 0;
}

bool assemble_tokens(ASM_List& asms, const Token_List& tokens)
{
    size_t i = 0;
    while(i < tokens.size())
    {
        if(tokens[i].type ==  LOGIC_STATEMENT)
        {
            if(tokens[i].value == "if")
            {
                size_t len;
                len = assembler_if_syntax_check(tokens, i);
                    
                if(len == 0){
                    fprintf(stderr, "Syntax Error!!!\n if statement\n");
                    return false;
                }

                    asms.push_back(ASM({}, STATEMENT));
                    asms[asms.size()].arguments.push_back(tokens[i++].value);
                    
                    i++;

                while(i < len)
                    asms[asms.size()].arguments.push_back(tokens[i++].value);
                
                continue;
            }
            else if (tokens[i].value == "else")
            {
                asms.push_back(ASM({}, STATEMENT));
                asms[asms.size()].arguments.push_back(tokens[i++].value);
                continue;
            }
            else
            {
                fprintf(stderr, "STATEMENT HAS NOT BEEN PROGRAMMED YET\n%s\n", tokens[i].value);
                return false;
            }
        }

        if(tokens[i].type == ID)
        {
            if(tokens[i+1].type == PLUS)
            {
                asms.push_back(ASM({}, ADDITION));
                asms[asms.size()].arguments.push_back(tokens[i].value);
                asms[asms.size()].arguments.push_back(tokens[i+3].value);
                i+=4;
                continue;
            }

            if(tokens[i+1].type == EQUALS)
            {
                //X = 1
                asms.push_back(ASM({}, SET));
                asms[asms.size()].arguments.push_back(tokens[i].value);
                asms[asms.size()].arguments.push_back(tokens[i+2].value);

                i+=4;
                continue;
            }

            i++;
            continue;
        }

        if(tokens[i].type == FUNC)
        {
            i++;
            if(tokens[i].type != ID)
            {
                fprintf(stderr, "Syntax Error!!!\n Function Check\n");
                return false;
            }

            asms.push_back(ASM({}, FUNCTION));
            asms[asms.size()].arguments.push_back(tokens[i].value);
            
            i++;
            continue;
        }

        if(tokens[i].type == FCALL)
        {
            if(tokens[i+1].type != ID)
            {
                fprintf(stderr, "Syntax Error!!!\n Function Call Check\n%d : %s\n", tokens[i+1].type, tokens[i+1].value.c_str());
                return false;
            }

            i++;
            
            asms.push_back(ASM({}, FUNCTION_CALL));
            asms[asms.size()].arguments.push_back(tokens[i].value);
            
            i++;
            continue;
        }

        if(tokens[i].type == OPEN_C)
        {
            asms.push_back(ASM({}, OPEN_COLON));
            i++;
            continue;
        }

        if(tokens[i].type == CLOSE_C)
        {
            asms.push_back(ASM({}, FUNCTION));
            i++;
            continue;
        }

        if(isType(tokens[i].type))
        {
            if(!isCorrectType(tokens[i].type, tokens[i+3].type))
            {
                fprintf(stderr, "Syntax Error!!!\n Wrong Type\n");
                printf("%d : %s", tokens[i+3].type, tokens[i+3].value.c_str());
                return false;
            }

            if(tokens[i+1].type != ID)
            {
                fprintf(stderr, "Syntax Error!!!\n Variable Check ID\n%d : %s\n", tokens[i+1].type, tokens[i+1].value.c_str());
                return false;
            }
            if(tokens[i+2].type != EQUALS)
            {
                fprintf(stderr, "Syntax Error!!!\n Variable Check EQUALS\n");
                return false;
            }

            asms.push_back(ASM({}, ANY_VAR));
            asms[asms.size()].arguments.push_back(tokens[i].value);
            asms[asms.size()].arguments.push_back(tokens[i+3].value);
            
            i+=4;
            continue;
        }
        else
        {
            printf("%d : %s\n", tokens[i].type, tokens[i].value.c_str());
            i++;
            continue;
        }
    }
    return true;
}