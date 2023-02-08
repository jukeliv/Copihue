#include "../include/token.h"

Token_Type KEYWORD(std::string word)
{
    if(word == "Bool")
    {
        return BOOL;
    }
    else if(word == "Int")
    {
        return INT;
    }
    else if(word == "Float")
    {
        return FLOAT;
    }
    else if(word == "Char")
    {
        return CHAR;
    }
    else if(word == "func")
    {
        return FUNC;
    }
    else if(word == "using")
    {
        return USING;
    }
    else if(word == "if" || word == "else")
    {
        return LOGIC_STATEMENT;
    }
    else if(word == "true" || word == "false")
    {
        return BOOL;
    }
    else if(word == "Char")
    {
        return CHAR;
    }
    else
    {
        return NONE;
    }
}

bool isType(Token_Type t)
{
    if(t == BOOL)
        return true;
    else if(t == INT)
        return true;
    else if(t == FLOAT)
        return true;
    else if(t == CHAR)
        return true;

    return false;
}

bool isCorrectType(Token_Type tt, Token_Type token_t)
{
    switch(tt)
    {
        case BOOL:
            return token_t == BOOL;
        case INT:
            return token_t == NUMERIC;
        case FLOAT:
            return token_t == NUMERIC;
        case CHAR:
            return token_t == CHAR;
        default:
            return false;
    }
    return false;
}

/*
bool isFunction(Token_Type t)
{
    if(t == MEMSET)
        return true;
    else if(t == MEMACC)
        return true;
    return false;
}
*/

bool Tokenize(Token_List& list, std::string path)
{
    std::string sourceCode = read(path);
    
    char lex[256];
    int lexi = 0;

    size_t i = 0;
    while(sourceCode[i] != '\0')
    {
        while(sourceCode[i] == ' ' || sourceCode[i] == '\t' || sourceCode[i] == '\n')
            i++;

        memset(lex, 0, 256);

        switch(sourceCode[i])
        {
            case '!':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, NEGATION));
                break;
            case '>':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, GREATERT));
                break;
            case '<':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, LESST));
                break;
            case '(':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, OPEN_P));
                break;
            case ')':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, CLOSE_P));
                break;
            case '{':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, OPEN_C));
                break;
            case '}':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, CLOSE_C));
                break;
            case ',':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, COMMA));
                break;
            case '=':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, EQUALS));
                break;
            case '+':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, PLUS));
                break;
            case '-':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, MINUS));
                break;
            case '*':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, MULT));
                break;
            case '/':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, DIV));
                break;
            case '@':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, FCALL));
                break;
            case '\'':
                i++;
                while(sourceCode[i] != '\'')
                    lex[lexi++] = sourceCode[i++];
                
                if(lexi != 1 )
                    return -1;

                case ';':
                i++;
                while(sourceCode[i] != ';')
                    lex[lexi++] = sourceCode[i++];

                lexi = 0;
                i++;
                list.push_back(Token(lex, COMMENT));
                break;
            default:                                // HANDLE MULTIPLE-CHARACTER TOKENS
                if(isdigit(sourceCode[i]))
                {
                    while(isdigit(sourceCode[i]) || sourceCode[i] == '.')
                        lex[lexi++] = sourceCode[i++];

                    list.push_back(Token(lex, NUMERIC));
                    lexi = 0;
                    continue;
                }
                else if(isalpha(sourceCode[i]))
                {
                    while(isalpha(sourceCode[i]))
                        lex[lexi++] = sourceCode[i++];

                    Token_Type tt = KEYWORD(lex);
                    if(tt == NONE)
                        list.push_back(Token(lex, ID));
                    else
                        list.push_back(Token(lex, tt));

                    lexi = 0;
                    continue;
                }
                else if(sourceCode[i] != '\0') // I replace this cuz it had conflicts with the comments
                {
                    fprintf(stderr, "Unknown character found in Cuild file:\n character:\"%c\", line:%i\n", sourceCode[i], i);
                    i++;
                }
                break;
        }
    }
    return true;
}