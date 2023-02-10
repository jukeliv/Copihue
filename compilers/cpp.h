#pragma once 

#include "../include/assembler.h"

void compile_cpp(FILE*& out, ASM_List asm_list)
{
    for(int i = 0; i < asm_list.size();i++)
    {
        //TODO: add a map for variables and functions and check that they are set before you can call them :)
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
                    fprintf(out, "#include <iostream>\n#include <string>\n#include <vector>\n");
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
            case OPEN_BRACKET:
            {
                fprintf(out, "{\n");
                continue;
            }

            case CLOSE_BRACKET:
            {
                fprintf(out, "}\n");
                continue;
            }
            case ANY_ARRAY:
            {
                std::string type;
                if(asm_list[i].arguments[0] == "Bool")
                    type = "bool";

                else if(asm_list[i].arguments[0] == "Int")
                    type = "int";

                else if(asm_list[i].arguments[0] == "Float")
                    type = "float";

                else if(asm_list[i].arguments[0] == "String")
                    type = "std::string";

                fprintf(out, "std::vector<%s> %s = {", type.c_str(), asm_list[i].arguments[1].c_str());

                for(int j = 2; j < asm_list[i].arguments.size(); j++)
                {
                    if(j+1 != asm_list[i].arguments.size())
                        fprintf(out, "%s,", asm_list[i].arguments[j].c_str());
                    else
                        fprintf(out, "%s", asm_list[i].arguments[j].c_str());
                }
                fprintf(out, "};\n");
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
                    fprintf(out, "std::string %s = %s;\n", asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                }
                continue;
            }
            case SET:
            {
                fprintf(out, "%s = %s;\n", asm_list[i].arguments[0].c_str(), asm_list[i].arguments[1].c_str());
                continue;
            }
            case OPERATION:
            {
                fprintf(out, "%s %s= %s;\n", asm_list[i].arguments[0].c_str(), asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                continue;
            }
            case FUNCTION_CALL:
            {
                if(asm_list[i].arguments[0] == "print")
                {
                    fprintf(out, "std::cout<<", asm_list[i].arguments[0].c_str());
                    for(int j = 1; j < asm_list[i].arguments.size(); j++)
                    {
                        if(asm_list[i].arguments[j].c_str() == ",")
                        {
                            fprintf(out, "<<");
                            continue;
                        }
                        fprintf(out, "%s", asm_list[i].arguments[j].c_str());
                    }
                    
                    fprintf(out, "<<std::endl;\n");
                }
                else if(asm_list[i].arguments[0] == "ex")
                {
                    fprintf(out, "exit(%s);\n", asm_list[i].arguments[1].c_str());
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
            {
                if(asm_list[i].arguments[0] == "else")
                    fprintf(out, "else\n");
                else
                {
                    if(asm_list[i].arguments[0] != "elif")
                        fprintf(out, "%s(", asm_list[i].arguments[0].c_str());
                    else
                        fprintf(out, "else if(");

                    for(int j = 1; j < asm_list[i].arguments.size(); j++)
                    {
                        fprintf(out, "%s", asm_list[i].arguments[j].c_str());
                    }
                    fprintf(out, ")\n");
                }
                continue;
            }
        }
    }
}