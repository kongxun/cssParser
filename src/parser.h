/*************************************************************************
	> File Name: parser.h
	> Author: kongxun 
	> Mail: kongxun.yb@gmail.com
	> Created Time: 2016年09月09日 星期五 08时53分29秒
 ************************************************************************/

#ifndef _PARSER_H
#define _PARSER_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h> 

typedef struct StyleNode{
    char *key;
    char *value;
    struct StyleNode *next;
} StyleNode;

typedef struct SelectorNode{
    char *selectorText;
    StyleNode *style;
    struct SelectorNode *next;
} SelectorNode;

void parser(FILE *srcF, FILE* dstF);
#endif
