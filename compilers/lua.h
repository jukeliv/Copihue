#pragma once 

#include "../include/assembler.h"

void compile_lua(FILE*& out, ASM_List asm_list)
{
    for(int i = 0; i < asm_list.size();i++)
    {
        switch(asm_list[i].type)
        {
            case MACRO_DEFINITION:
            {
                //fprintf(out, "#define %s %s\n", asm_list[i].arguments[0].c_str(), asm_list[i].arguments[1].c_str());
                fprintf(stderr, "Macros are not implemented for lua yet!!!\n");
                continue;
            }
            case INCLUDE_LIBRARY:
            {
                //TODO: Implement a way to include other files or downloaded libraries
                /*
                if(asm_list[i].arguments[0] == "stdlib")
                {
                    fprintf(out, "#include <stdlib.h>\n#include <stdio.h>\n#include <string.h>\n");
                    continue;
                }
                else
                {
                    fprintf(stderr, "UNKNOWN LIBRARY \"%s\"!!!", asm_list[i].arguments[0].c_str());
                    exit(-1);
                }
                */
                continue;
            }
            case FUNCTION:
            {
                //TODO: ADD FUNCTION ARGUMENTS
                fprintf(out, "function %s() ", asm_list[i].arguments[0].c_str());
                continue;
            }
            case OPEN_BRACKET:
            {
                switch(asm_list[i-1].type)
                {
                    case FUNCTION:
                        fprintf(out, "\n");
                        break;
                    default:
                        fprintf(out, "do\n");
                        break;
                }
                continue;
            }

            case CLOSE_BRACKET:
            {
                switch(asm_list[i-1].type)
                {
                    default:
                        fprintf(out, "end\n");
                }
                continue;
            }
            
            case ANY_VAR:
            {
                fprintf(out, "local %s = %s;\n", asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());

                continue;
            }
            case SET:
            {
                if(asm_list[i].arguments[1][0] != '"')
                    fprintf(out, "%s = %s;\n", asm_list[i].arguments[0].c_str(), asm_list[i].arguments[1].c_str());
                else
                    fprintf(out, "%s = strdup(%s);\n", asm_list[i].arguments[0].c_str(), asm_list[i].arguments[1].c_str());
                continue;
            }
            case OPERATION:
            {
                fprintf(out, "%s = %s %s %s;\n", asm_list[i].arguments[0].c_str(), asm_list[i].arguments[0].c_str(), asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                continue;
            }
            case FUNCTION_CALL:
            {
                if(asm_list[i].arguments[0] == "print")
                {
                    fprintf(out, "io.write(", asm_list[i].arguments[0].c_str());
                    for(int j = 1; j < asm_list[i].arguments.size(); j++)
                        fprintf(out, "%s", asm_list[i].arguments[j].c_str());
                    
                    fprintf(out, ")\n");
                }
                else
                {
                    fprintf(out, "%s(", asm_list[i].arguments[0].c_str());
                    for(int j = 1; j < asm_list[i].arguments.size(); j++)
                        fprintf(out, "%s", asm_list[i].arguments[j].c_str());
                    
                    fprintf(out, ");\n");
                }
                continue;
            }
            case STATEMENT:
                if(asm_list[i].arguments[0] == "else")
                    fprintf(out, "else ");
                else
                {
                    fprintf(out, "%s(", asm_list[i].arguments[0].c_str());
                    for(int j = 1; j < asm_list[i].arguments.size(); j++)
                    {
                        fprintf(out, "%s", asm_list[i].arguments[j].c_str());
                    }
                    fprintf(out, ") ");
                }
        }
    }
}