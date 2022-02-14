#include "../src/include/cutf8.h"
#include "../src/include/converter.h"

#include <iostream>
#include <cstring>
#include <cstdio>

const char* help_msg =
R"(Usage: test FILE_IN FILE_OUT
-h  help message)";

int main(int argc,char* argv[]){
    if(argc < 2){
        fprintf(stdout, "%s", "Usage: test FILE_IN FILE_OUT\n");
    }else if(argc == 3 || strcmp(argv[1],"-h")){
        fprintf(stdout, "%s", "Usage: test FILE_IN FILE_OUT\n");
    }else{
        FILE* fi = fopen(argv[1],"r");
        FILE* fo = fopen(argv[2],"w");
    }
    return 0;
}