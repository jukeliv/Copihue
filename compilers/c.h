#pragma once 

#include "../include/assembler.h"

void compile_c(FILE*& out, ASM_List asm_list)
{
    for(int i = 0; i < asm_list.size();i++)
    {
        switch(asm_list[i].type)
        {
            case MACRO_DEFINITION:
            {
                fprintf(out, "#define %s %s\n", asm_list[i].arguments[0].c_str(), asm_list[i].arguments[1].c_str());
                continue;
            }
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
                    exit(-1);
                }
                continue;
            }
            case FUNCTION:
            {
                //TODO: ADD FUNCTION ARGUMENTS
                fprintf(out, "int %s(void)\n", asm_list[i].arguments[0].c_str());
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
                    fprintf(out, "float %s = %sf;\n", asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                }

                else if(asm_list[i].arguments[0] == "String")
                {
                    fprintf(out, "char* %s = (char*)%s;\n", asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                }
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
                fprintf(out, "%s %s= %s;\n", asm_list[i].arguments[0].c_str(), asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                continue;
            }
            case FUNCTION_CALL:
            {
                fprintf(out, "%s(", asm_list[i].arguments[0].c_str());
                for(int j = 1; j < asm_list[i].arguments.size(); j++)
                    fprintf(out, "%s", asm_list[i].arguments[j].c_str());
                
                fprintf(out, ");\n");
                continue;
            }
            case STATEMENT:
                if(asm_list[i].arguments[0] == "else")
                    fprintf(out, "else\n");
                else
                {
                    fprintf(out, "%s(", asm_list[i].arguments[0].c_str());
                    for(int j = 1; j < asm_list[i].arguments.size(); j++)
                    {
                        fprintf(out, "%s", asm_list[i].arguments[j].c_str());
                    }
                    fprintf(out, ")\n");
                }
        }
    }
}