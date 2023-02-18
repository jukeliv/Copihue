#include "../include/token.h"

Token_Type KEYWORD(std::string word)
{
    if(word == "Bool")
    {
        return BOOL;
    }
    else if(word == "Num")
    {
        return NUMBER;
    }
    else if(word == "String")
    {
        return STRING;
    }
    else if(word == "func")
    {
        return FUNC;
    }
    else if(word == "import")
    {
        return USING;
    }
    else if(word == "if" || word == "else" || word == "elif" || word == "while")
    {
        return LOGIC_STATEMENT;
    }
    else if(word == "true" || word == "false")
    {
        return BOOL;
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
    else if(t == NUMBER)
        return true;
    else if(t == STRING)
        return true;

    return false;
}

bool isCorrectType(Token_Type tt, Token_Type token_t)
{
    switch(tt)
    {
        case BOOL:
            return token_t == BOOL;
        case NUMBER:
            return token_t == NUMERIC;
        case STRING:
            return token_t == STRING;
        default:
            return false;
    }
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
            case ':':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, COLON));
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
                list.push_back(Token(lex, OPEN_B));
                break;
            case '}':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, CLOSE_B));
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
            case '"':
                i++;

                lex[lexi++] = '"';

                while(sourceCode[i] != '"')
                    lex[lexi++] = sourceCode[i++];
                
                lex[lexi] = '"';

                lexi = 0;
                
                list.push_back(Token(lex, STRING));

                i++;
                break;

            case '#':
                i++;

                while(sourceCode[i] != '#')
                    lex[lexi++] = sourceCode[i++];
                
                i++;

                lexi = 0;

                list.push_back(Token(lex, COMMENT));

                break;
            
            default:                                // HANDLE MULTIPLE-CHARACTER TOKENS
                if(isdigit(sourceCode[i]))
                {
                    while(isdigit(sourceCode[i]) || sourceCode[i] == '.')
                        lex[lexi++] = sourceCode[i++];

                    list.push_back(Token(lex, NUMERIC));
                    lexi = 0;
                    i++;
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
                    fprintf(stderr, "Unknown character found in file:\n c:\"%c\", i:%i\n", sourceCode[i], i);
                    i++;
                }
                break;
        }
    }
    return true;
}