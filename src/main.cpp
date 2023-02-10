#include <stdlib.h>
#include <stdio.h>
#include "../include/token.h"
#include "../include/assembler.h"
#include <iostream>

//INCLUDE COMPILERS HERE
#include "../compilers/cpp.h"
#include "../compilers/lua.h"

int main(int argc, char** argv)
{
    //TODO: Implement an arguments system for the compiler
    //Copihue -compiler- -file_name- -arguments-
    if(argc < 3)
    {
        fprintf(stderr, "Not enough arguments\n");
        return -1;
    }

    Token_List tokens;
    if(!Tokenize(tokens, argv[2]))
    {
        perror("Error while Tokenizing file!!!");
        return -1;
    }

    ASM_List asm_list;
        
    if(!assemble_tokens(asm_list, tokens))
    {
        return -1;
    }
    
    /*
    //DEBUG SHIT
    for(int i = 0; i < asm_list.size(); i++)
    {
        printf("%d | ", asm_list[i].type);
        for(int j = 0; j < asm_list[i].arguments.size(); j++)
        {
            printf("%s ", asm_list[i].arguments[j].c_str());
        }
        putc('\n', stdout);
    }
    */

    //Adding support for multiple languages in the future!!!
    if(strcmp(argv[1], "-cpp") == 0)
    {
        FILE* out = fopen("output.cpp", "w");
        compile_cpp(out, asm_list);
    }
    else if(strcmp(argv[1], "-lua") == 0)
    {
        FILE* out = fopen("output.lua", "w");
        compile_lua(out, asm_list);
    }
    
    else
    {
        fprintf(stderr, "UNKNOWN COMPILER!!!");
        return -1;
    }
    //*/
    
    return 0;
}