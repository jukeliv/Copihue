#pragma once 

#include "../include/assembler.h"
#include <unordered_map>
#include <string>

enum _var_type
{
    NUM,
    STR,
    BOOLEAN
};
typedef enum _var_type var_type;

std::unordered_map<std::string, var_type> m_variables;
std::unordered_map<std::string, std::vector<var_type>> m_functions;

bool find_var(std::string id)
{
    
    return m_variables.find(id) != m_variables.end();
}

void set_var(std::string id, var_type type)
{
	m_variables[id] = type;
}

void compile_cpp(const char* output, FILE*& out, ASM_List asm_list)
{
    std::string cc = "g++";
    std::string cp = "";
    for(int i = 0; i < asm_list.size();i++)
    {
        //TODO: add a map for variables and functions and check that they are set before you can call them :)
        switch(asm_list[i].type)
        {
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
            case COMPILER_DECL:
            {
                std::string str = asm_list[i].arguments[1];
                str.erase(0, 1);
                str.erase(str.size() - 1);

                if(asm_list[i].arguments[0] == "lc")
                {
                    fprintf(out, "%s\n", str.c_str());
                }
                if(asm_list[i].arguments[0] == "cc")
                {
                    cc = str;
                }
                if(asm_list[i].arguments[0] == "cp")
                {
                    cp += " -" + str;
                }
                continue;
            }
            case FUNCTION:
            {
                
                if(m_functions.find(asm_list[i].arguments[0]) != m_functions.end())
                {
                    perror("Can't re define functions!!!\n");
                    return;
                }

                std::string type = "int";
                if(asm_list[i].arguments[asm_list[i].arguments.size()-1] == "Bool")
                {
                    type = "bool";
                }
                if(asm_list[i].arguments[asm_list[i].arguments.size()-1] == "Num")
                {
                    type = "float";
                }
                if(asm_list[i].arguments[asm_list[i].arguments.size()-1] == "String")
                {
                    type = "std::string";
                }
                fprintf(out, "%s %s(", type.c_str(), asm_list[i].arguments[0].c_str());
                
                for(int j = 1; j < asm_list[i].arguments.size()-1; j+=3)
                {
                    var_type argument;
                    std::string vtype = "";
                    if(asm_list[i].arguments[j+1] == "Num")
                    {
                        argument = NUM;
                        vtype = "float";
                    }
                    if(asm_list[i].arguments[j+1] == "Bool")
                    {
                        argument = BOOLEAN;
                        vtype = "bool";
                    }
                    if(asm_list[i].arguments[j+1] == "String")
                    {
                        argument = STR;
                        vtype = "std::string";
                    }

                    m_functions[asm_list[i].arguments[0]].push_back(argument);

                    if(asm_list[i].arguments[j] == "ref")
                    {
                        fprintf(out, "%s& %s", vtype.c_str(), asm_list[i].arguments[j+2].c_str());
                    }
                    else if(asm_list[i].arguments[j] == "pass")
                    {
                        fprintf(out, "const %s& %s", vtype.c_str(), asm_list[i].arguments[j+2].c_str());
                    }

                    if(j+3 < asm_list[i].arguments.size()-1){
                        putc(',', out);
                    }
                }
                fprintf(out, ")\n");
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
            case ANY_VAR:
            {
                if(find_var(asm_list[i].arguments[1].c_str()))
                {
                    perror("Can't re define variables!!!");
                    fclose(out);
                    return;
                }
                if(asm_list[i].arguments[0] == "Bool")
                {
                    set_var(asm_list[i].arguments[1], BOOLEAN);
                    fprintf(out, "bool %s = %s;\n", asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                }

                else if(asm_list[i].arguments[0] == "Num")
                {
                    set_var(asm_list[i].arguments[1], NUM);
                    fprintf(out, "float %s = %s;\n", asm_list[i].arguments[1].c_str(), asm_list[i].arguments[2].c_str());
                }

                else if(asm_list[i].arguments[0] == "String")
                {
                    set_var(asm_list[i].arguments[1], STR);
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
                        if(asm_list[i].arguments[j][0] != '"' && isdigit(asm_list[i].arguments[j][0]))
                            if(!find_var(asm_list[i].arguments[j]))
                            {
                                perror("Logic Error!!!\n Can't pass a variable that does not exist currently\n");
                                return;
                            }
                        fprintf(out, "%s<<", asm_list[i].arguments[j].c_str());
                    }
                    
                    fprintf(out, "std::endl;\n");
                }
                else
                {
                    //TODO: Implement Boolean type
                    if(m_functions.find(asm_list[i].arguments[0]) == m_functions.end())
                    {
                        perror("Can't call a undefined function");
                        return;
                    }
                    fprintf(out, "%s(", asm_list[i].arguments[0].c_str());
                    for(int j = 1; j < asm_list[i].arguments.size(); j++)
                    {
                        if(asm_list[i].arguments[j][0] != '"' && isdigit(asm_list[i].arguments[j][0]))
                        {
                            if(!find_var(asm_list[i].arguments[j]))
                            {
                                perror("Logic Error!!!\n Can't pass a variable that does not exist currently\n");
                                return;
                            }
                            
                            if(m_variables.at(asm_list[i].arguments[j]) != m_functions.at(asm_list[i].arguments[0])[j-1])
                            {
                                perror("Variable type and Function argument type are conflicting!!!\n");
                                return;
                            }
                        }
                        else
                        {
                            if(asm_list[i].arguments[j][0] == '"' && m_functions.at(asm_list[i].arguments[0])[j] != STR)
                            {
                                perror("Variable type and Function argument type are conflicting!!!\n");
                                return;
                            }
                            if(isdigit(asm_list[i].arguments[j][0]) && m_functions.at(asm_list[i].arguments[0])[j] != NUM)
                            {
                                perror("Variable type and Function argument type are conflicting!!!\n");
                                return;
                            }
                        }

                        fprintf(out, "%s", asm_list[i].arguments[j].c_str());
                        if(j+1 != asm_list[i].arguments.size()){
                            putc(',', out);
                        }
                    }
                    
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
    
    fclose(out);

    std::string command = cc + " " + output +  " -o output.exe " + cp;
    system(command.c_str());
}