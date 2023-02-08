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

    printf("Do you ");
    
    try
    {
        ASM_List asm_list;
        
        assemble_tokens(asm_list, tokens);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    printf("even ");
    /*
    for(int i = 0; i < asm_list.size();i++)
    {
        printf("Enter here?");
        printf("%d | ", asm_list[i].type);
        for(int j = 0; j < asm_list[i].arguments.size(); j++)
        {
            printf("%s ", asm_list[i].arguments[j]);
        }
        putc('\n', stdout);
    }
    */

    return 0;
}