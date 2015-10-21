#ifndef PARSER_FUNCTION_H_INCLUDED
#define PARSER_FUNCTION_H_INCLUDED
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

string read_txt_file (const char*);

string delete_comments (const string&);

void rasterFile (char* newFilepath, const char* descriptionFile, const string& newFileName);

#endif // PARSER_FUNCTION_H_INCLUDED
