#include "../include/assembler.h"

size_t assembler_statement_syntax_check(Token_List ls, int index)
{
    if(ls[index+1].type != OPEN_P || ls[index+2].type != ID)
    {
        fprintf(stderr, "Syntaxis Error!!!\n if statement 1");
        return 0;
    }
    if(ls[index+3].type == GREATERT || ls[index+3].type == LESST)
        if(isType(ls[index+4].type) || ls[index+4].type == NUMERIC)
            return 4;
    
    if(isType(ls[index+5].type) || ls[index+5].type == NUMERIC)
            return 5;
            
    if(ls[index+3].type == EQUALS && ls[index+4].type == EQUALS)
        return 5;

    if(ls[index+3].type == NEGATION && ls[index+4].type == EQUALS)
        return 5;
    printf("%d", ls[index+4].type);

    return 0;
}

bool assemble_tokens(ASM_List& asms, const Token_List& tokens)
{
    size_t i = 0;
    while(i < tokens.size())
    {
        if(tokens[i].type == COMMENT)
        {
            //we don't need anything here lol, just skip it
            i++;
            continue;
        }

        if(tokens[i].type == MACRO)
        {
            //macro MACRO_NAME MACRO_VALUE
            i++;

            if(tokens[i].type != ID)
            {
                fprintf(stderr, "Syntax Error!!!\n Macro check\n");
                return false;
            }
            asms.push_back(ASM({}, MACRO_DEFINITION));
            asms[asms.size()-1].arguments.push_back(tokens[i++].value);
            asms[asms.size()-1].arguments.push_back(tokens[i++].value);
            
            continue;
        }

        if(tokens[i].type ==  LOGIC_STATEMENT)
        {
            if(tokens[i].value == "if")
            {
                size_t len = assembler_statement_syntax_check(tokens, i);

                if(len == 0){
                    fprintf(stderr, "Syntax Error!!!\n if statement\n");
                    return false;
                }

                asms.push_back(ASM({}, STATEMENT));
                asms[asms.size()-1].arguments.push_back(tokens[i++].value);
                    
                i++;
                
                size_t lenR = i + len - 1;
                while(i < lenR)
                    asms[asms.size()-1].arguments.push_back(tokens[i++].value);
                
                i++;

                continue;
            }
            if(tokens[i].value == "while")
            {
                //LOL while loops are a copy of if statements XD
                size_t len = assembler_statement_syntax_check(tokens, i);

                if(len == 0){
                    fprintf(stderr, "Syntax Error!!!\n while loop\n");
                    return false;
                }

                asms.push_back(ASM({}, STATEMENT));
                asms[asms.size()-1].arguments.push_back(tokens[i++].value);
                    
                i++;
        
                size_t lenR = i + len - 1;
                while(i < lenR)
                    asms[asms.size()-1].arguments.push_back(tokens[i++].value);
                
                i++;
                
                continue;
            }
            else if (tokens[i].value == "else")
            {
                asms.push_back(ASM({}, STATEMENT));
                asms[asms.size()-1].arguments.push_back(tokens[i++].value);
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
            //foo += 2 | foo -= 2 | foo /= 2 | foo *= 2
            if(tokens[i+1].type == PLUS || tokens[i+1].type == MINUS || tokens[i+1].type == DIV || tokens[i+1].type == MULT)
            {
                if(tokens[i+2].type != EQUALS)
                {
                    fprintf(stderr, "Syntax Error!!!\nOPERATION\n");
                    return false;
                }

                asms.push_back(ASM({}, OPERATION));
                asms[asms.size()-1].arguments.push_back(tokens[i].value);
                asms[asms.size()-1].arguments.push_back(tokens[i+1].value);
                asms[asms.size()-1].arguments.push_back(tokens[i+3].value);
                i+=4;
                continue;
            }

            //foo = 2
            if(tokens[i+1].type == EQUALS)
            {
                asms.push_back(ASM({}, SET));
                asms[asms.size()-1].arguments.push_back(tokens[i].value);
                asms[asms.size()-1].arguments.push_back(tokens[i+2].value);

                i+=3;
                continue;
            }

            i++;
            continue;
        }

        if(tokens[i].type == FUNC)
        {
            //func FUNCTION_NAME
            i++;
            if(tokens[i].type != ID)
            {
                fprintf(stderr, "Syntax Error!!!\n using library\n");
                return false;
            }
            asms.push_back(ASM({}, FUNCTION));
            asms[asms.size()-1].arguments.push_back(tokens[i++].value);
            continue;
        }

        if(tokens[i].type == FCALL)
        {
            //@print(argument1)
            i++;
            if(tokens[i].type != ID)
            {
                fprintf(stderr, "Syntax Error!!!\n Function Call Check\n%d : %s\n", tokens[i+1].type, tokens[i+1].value.c_str());
                return false;
            }

            if(tokens[i+1].type != OPEN_P)
            {
                fprintf(stderr, "Syntax Error!!!\n Function Call Check\n%d : %s\n", tokens[i+1].type, tokens[i+1].value.c_str());
                return false;
            }

            asms.push_back(ASM({}, FUNCTION_CALL));
            asms[asms.size()-1].arguments.push_back(tokens[i].value);
            i+=2;
            
            while(tokens[i].type != CLOSE_P)
                asms[asms.size()-1].arguments.push_back(tokens[i++].value);

            i++;

            continue;
        }

        if(tokens[i].type == USING)
        {
            //using LIB_NAME
            i++;
            if(tokens[i].type != ID)
            {
                fprintf(stderr, "Syntax Error!!!\n using library\n");
                return false;
            }
            asms.push_back(ASM({}, INCLUDE_LIBRARY));
            asms[asms.size()-1].arguments.push_back(tokens[i++].value);
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
            asms.push_back(ASM({}, CLOSE_COLON));
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

            asms[asms.size()-1].arguments.push_back(tokens[i].value);
            asms[asms.size()-1].arguments.push_back(tokens[i+1].value);
            asms[asms.size()-1].arguments.push_back(tokens[i+3].value);
            
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