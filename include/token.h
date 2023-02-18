#pragma once

#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include "utility.h"

typedef enum _Token_Type
{
    //KEYWORDS
    NONE,               // (dumb var that means `THIS IS NOT A RESERVED KEYWORD`)
    RETURN,             // ret RETURN_VALUE
    /*
    MEMSET,             // memset(bank, variable, value) // SETS THE VALUE OF A MEMORY LOCATION
    MEMACC,             // memacc(53546, charPosition)  // SETS MEMORY TO A VARIABLE
    */
    //FUNCTIONS
    FUNC,               // func FUNC_NAME
    FCALL,              // @FUNC_NAME(ARGS1,ARGS2)
    //RESERVED KEYWORDS
    ANY,                //BOOL, Num, STR
    BOOL,               // Bool
    NUMBER,              // Mum
    STRING,
    USING,              // import libname
    //REGULAR KEYWORDS
    ID,                 // forVariablesUse
    NUMERIC,            // 1, 2, 3, 4.... POSITIVE_INFINITY
    //CHAR TYPES
    EQUALS,             // =
    OPEN_P,             // (
    CLOSE_P,            // )
    OPEN_B,             // {
    CLOSE_B,            // }
    COMMA,              // ,
    GREATERT,           // >
    LESST,              // <
    NEGATION,           // !
    COLON,              // :
    //CHAR OPERATORS
    PLUS,               // +
    MINUS,              // -
    MULT,               // *
    DIV,                // /
    //STATEMENTS
    LOGIC_STATEMENT,    // if(something) else while elif
    //OTHER
    COMMENT             //; YOUR COMMENT HERE ;
}Token_Type;

class Token
{
public:
    Token(std::string val, Token_Type type)
    :value(val), type(type){}

    std::string value;
    Token_Type type;
};

#ifndef Token_List
    #define Token_List std::vector<Token>
#endif

Token_Type KEYWORD(std::string word);

bool isType(Token_Type t);
bool isCorrectType(Token_Type tt, Token_Type token_t);

bool isFunction(Token_Type t);

bool Tokenize(Token_List& list, std::string sourceCode);