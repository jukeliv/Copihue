#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <string.h>
#include <stdio.h>

#ifndef CUILD_LOG
    #define CUILD_LOG(x) std::time_t t = std::time(0);\
        std::tm* now = std::localtime(&t);\
        fprintf(fopen("CUILD_LOG.txt", "w"), "[%i:%i:%i] %s", now->tm_hour, now->tm_min, now->tm_sec, x);\
        fprintf(stderr, "AN ERROR OCURRED!!!\n CHECK:\"CUILD_LOG.txt\"\n")
#endif
bool isalpha(char c);

std::string read(std::string path);
bool write2file(std::ofstream& file, std::string path);

std::string cleanup(const char* string);
std::string cleanpath(const char* string);