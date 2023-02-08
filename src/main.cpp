#include <stdlib.h>
#include <stdio.h>
#include "../include/token.h"
#include "../include/assembler.h"
#include <iostream>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "Not enough arguments\n");
        return -1;
    }

    Token_List tokens;
    if(!Tokenize(tokens, argv[1]))
    {
        perror("Error while Tokenizing file!!!");
        return -1;
    }
    
    ASM_List asm_list;
        
    if(!assemble_tokens(asm_list, tokens))
    {
        return -1;
    }

    FILE* out = fopen("output.c", "w");

    for(int i = 0; i < asm_list.size();i++)
    {
        switch(asm_list[i].type)
        {
            case INCLUDE_LIBRARY:
            {
                if(asm_list[i].arguments[0] == "stdlib")
                {
                    fprintf(out, "#include <stdlib.h>\n#include <stdio.h>\n#include <string.h>\n");
                    continue;
                }
                else
                {
                    fprintf(stderr, "UNKNOWN LIBRARY \"%s\"!!!", asm_list[i].arguments[0].c_str());
                    return -1;
                }
            }
            case FUNCTION:
            {
                fprintf(out, "int %s()\n", asm_list[i].arguments[0].c_str());
                continue;
            }
            case OPEN_COLON:
            {
                fprintf(out, "{\n");
                continue;
            }

            case CLOSE_COLON:
            {
                fprintf(out, "}\n");
                continue;
            }
            
            case ANY_VAR:
            {
                if(asm_list[i].arguments[0] == "Bool")
                {
                    fprintf(out, "bool %s = %s;\n", asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                }

                else if(asm_list[i].arguments[0] == "Int")
                {
                    fprintf(out, "int %s = %s;\n", asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                }

                else if(asm_list[i].arguments[0] == "Float")
                {
                    fprintf(out, "float %s = %s;\n", asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                }

                else if(asm_list[i].arguments[0] == "Char")
                {
                    fprintf(out, "char %s = %s;\n", asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                }
                continue;
            }
            case SET:
            {
                fprintf(out, "%s = %s;\n", asm_list[i].arguments[0].c_str(), asm_list[i].arguments[1].c_str());
                continue;
            }
            case ADDITION:
            {
                fprintf(out, "%s += %s;\n", asm_list[i].arguments[0].c_str(), asm_list[i].arguments[1].c_str());
                continue;
            }
            case FUNCTION_CALL:
            {
                fprintf(out, "%s(", asm_list[i].arguments[0].c_str());
                for(int j = 1; j < asm_list[i].arguments.size(); i++)
                {
                    fprintf(out, "%s, ", asm_list[i].arguments[j]);
                }
                fprintf(out, ");");
                continue;
            }
        }
    }

    
    fprintf(out, "}");

    return 0;
}