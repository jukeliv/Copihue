#include <stdlib.h>
#include <stdio.h>
#include "../include/token.h"
#include "../include/assembler.h"
#include <iostream>

/* COMPILERS HERE */
#include "../compilers/cpp.h"

int main(int argc, char** argv)
{
    //TODO: Implement an arguments system for the compiler
    //Copihue -file- -output-
    if(argc < 3)
    {
        fprintf(stderr, "Not enough arguments\n");
        return 0xff;
    }
    
    Token_List tokens;
    if(!Tokenize(tokens, argv[1]))
    {
        perror("Error while Tokenizing file!!!");
        return 0xff;
    }

    ASM_List asm_list;
    if(!assemble_tokens(asm_list, tokens))
    {
        perror("Error while Assembling Tokens!!!");
        return 0xff;
    }
        
    /*DEBUG SHIT
    for(int i = 0; i < asm_list.size(); i++)
    {
        printf("%d | ", asm_list[i].type);
            for(int j = 0; j < asm_list[i].arguments.size(); j++)
            {
                printf("%s ", asm_list[i].arguments[j].c_str());
            }
        putc('\n', stdout);
    }*/

    FILE* file = fopen(argv[2], "w");
    compile_cpp(argv[2], file, asm_list);

    return 0;
}
