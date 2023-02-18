#include "../include/utility.h"


bool isalpha(char c)
{
    return(isalnum(c) || c == '.' || c == '_' || c == '/' || c == '\\');
}

std::string read(std::string path)
{
    std::ifstream file(path);

    std::string buf;
    std::string str;
    
    if(!file.is_open())
    {
        fprintf(stderr, "Couldn't read file %s\n", path.c_str());
        return NULL;
    }

    while(file.good())
    {
        std::getline(file, buf);
        str += buf + "\n";
    }

    file.close();
    
    str.push_back('\0');

    return str;
}

bool write2file(std::ofstream& file, std::string path)
{
    file.open(path);
    if(!file)
    {
        perror("ERROR: COULDN'T WRITE TO FILE!!!");
        return false;
    }
    return true;
}

std::string cleanup(const char* string)
{
    std::string str = string;
    size_t i = 0;
    while(string[i] != '.')
        i++;
    for(;i<strlen(string);i++)
    {
        str.pop_back();
    }

    return str;
}

std::string cleanpath(const char* string)
{
    std::string str;
    size_t i = strlen(string);
    while(string[i] != '/')
        i--;
    i++;
    for(;i<strlen(string);i++)
        str += string[i];
    return str;
}