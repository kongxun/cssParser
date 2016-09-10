/*************************************************************************
    > File Name: main.c
    > Author: kongxun 
    > Mail: kongxun.yb@gmail.com
    > Created Time: 2016年09月09日 星期五 08时51分29秒
 ************************************************************************/

#include "parser.h"

int main(){
    const char *srcPath = "/home/k.x/Project/github/C_C++_Project/cssParser/index.css";
    const char *dstPath = "/home/k.x/Project/github/C_C++_Project/cssParser/index.json";
    FILE *srcF = fopen(srcPath, "r");
    FILE *dstF = fopen(dstPath, "w");
    if(srcF == NULL){
        printf("no such file or directory:%s", srcPath);
        exit(EXIT_FAILURE);
    }
    parser(srcPath, srcF, dstF);
    fclose(srcF);
    fclose(dstF);
    return 0;
}
