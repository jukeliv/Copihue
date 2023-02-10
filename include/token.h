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
    MACRO,              // macro MACRO_NAME MACRO_VALUE
    /*
    MEMSET,             // memset(bank, variable, value) // SETS THE VALUE OF A MEMORY LOCATION
    MEMACC,             // memacc(53546, charPosition)  // SETS MEMORY TO A VARIABLE
    */
    //FUNCTIONS
    FUNC,               // function
    FCALL,              // @FUNC_NAME
    //RESERVED KEYWORDS
    ANY,                //BOOL, INT, FLOAT, STR
    NOT,                // not
    BOOL,               // Bool
    INT,                // Int
    FLOAT,              // Float
    STRING,             // String
    ARRAY,               // ["This is", "An", "String", "Array"]
    USING,              // using libname
    //REGULAR KEYWORDS
    ID,                 // forVariablesUse
    NUMERIC,            // 1, 2, 3, 4.... INFINITY
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
    //CHAR OPERATORS
    PLUS,               // +
    MINUS,              // -
    MULT,               // *
    DIV,                // /
    //STATEMENTS
    LOGIC_STATEMENT,    // if(something)  && else
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