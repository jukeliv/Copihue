#include "token.h"
#include "utility.h"
#include <string>
#include <vector>

typedef enum _ASM_Type
{
    IF,
    ADDITION,
    SET,
    FUNCTION,
    FUNCTION_CALL,
    OPEN_COLON,
    CLOSE_COLON,
    ANY_VAR,
    STATEMENT
}ASM_Type;

class ASM
{
public:
    ASM(std::vector<std::string> args, ASM_Type t)
    :arguments(args), type(t){}

    std::vector<std::string> arguments;
    ASM_Type type;
};

#ifndef ASM_List
    #define ASM_List std::vector<ASM>
#endif

size_t assembler_if_syntax_check(Token_List ls, int index);
bool assemble_tokens(ASM_List& asms, const Token_List& tokens);