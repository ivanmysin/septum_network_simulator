#include "parser_function.h"
////////////////////////////////////////////
// function read text file and return all content as string
string read_txt_file (const char* filename) {
    ifstream replaceInput;
    replaceInput.open(filename);
    if (!replaceInput.is_open()) {
        return "Can not open file";
    }
    string file_content;
    char s;
    while ((s = replaceInput.get()) != EOF) {
        file_content +=s;
    };
    replaceInput.close();
    return file_content;
}
//////////////////////////////////////////////////
// function delete all lines, which are started from '#'
string delete_comments (const string& sourse)
{
    string res;
    int len = sourse.size();
    bool noComment = true;
// delete comments
    for (int i=0; i<len; i++) {
        if (sourse[i] == '#') {
            noComment = false;
            continue;
        }

        if (sourse[i] == '\n') {
            noComment = true;
        }

        if (noComment) {
            res+=sourse[i];
        }
    }

    for (int i=0; i<(int)res.size(); i++) {
        if (isspace(res[i])) {
            res.erase(i,1);
            i--;
        }
    }


    return res;
}
///////////////////////////////////////////
// function form path to file from description file to raster file
void rasterFile (char* newFilepath, const char* descriptionFile, const string& newFileName)
{
    int len = strlen(descriptionFile);
    int i=len;
    while (i>=0 && (descriptionFile[i]!='\\' && descriptionFile[i]!='/')) {
        i--;
    }
    i++;
    int indLastSlash = i;
    for (int i=0; i<indLastSlash; i++) {
        newFilepath[i] = descriptionFile[i];
    }
    len=newFileName.size();
    int j=0;
    for (int i=indLastSlash; i<len+indLastSlash; i++) {
        newFilepath[i] = newFileName[j];
        j++;
    }
    newFilepath[len+indLastSlash] = '\0';
}
