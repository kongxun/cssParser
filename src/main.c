/*************************************************************************
    > File Name: main.c
    > Author: kongxun 
    > Mail: kongxun.yb@gmail.com
    > Created Time: 2016年09月09日 星期五 08时51分29秒
 ************************************************************************/

#include "parser.h"

int main(){
    const char *srcFile = "/home/k.x/Project/github/C_C++_Project/cssParser/index.css";
    const char *dstFile = "/home/k.x/Project/github/C_C++_Project/cssParser/index.json";
    FILE *srcF = fopen(srcFile, "r");
    FILE *dstF = fopen(dstFile, "w");
    if(srcF == NULL){
        printf("no such file or directory:%s", srcFile);
        exit(EXIT_FAILURE);
    }
    parser(srcF, dstF);
    fclose(srcF);
    fclose(dstF);
    return 0;
}
