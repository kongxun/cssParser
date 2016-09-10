/*************************************************************************
	> File Name: parser.c
	> Author: kongxun 
	> Mail: kongxun.yb@gmail.com
	> Created Time: 2016年09月09日 星期五 08时54分02秒
 ************************************************************************/

#include "parser.h"

void is_pointer_null(void *p){
    if(p==NULL){
        printf("file:%s,line:%s,memory allocate error", __FILE__, __LINE__);                   
        exit(EXIT_FAILURE);
    }
}        

void parser(FILE *srcF, FILE *dstF){
    SelectorNode *cssRule;
    
    cssRule = (SelectorNode *) calloc(1, sizeof(SelectorNode));
    is_pointer_null(cssRule);
    
    SelectorNode *currentSelector = cssRule;

    char currentChar=' ';
    while(currentChar != EOF){
        currentChar = (char) getc(srcF);
        if(currentChar==' '||currentChar=='\n'){
            continue;
        }else if(currentChar==EOF){
            break;
        }else if(
            currentChar=='#'
            ||currentChar=='.'
            ||('a'<currentChar&&currentChar<'z'))
        {   
            char *selectorText = (char *) calloc(100, sizeof(char));
            memset(selectorText, 0, 100);
            is_pointer_null(selectorText);
            
            char temp[2] = {0};
            while(currentChar!='{'){
                //deal with selectorText
                //printf("%c", currentChar);
                temp[0] = currentChar;
                strcat(selectorText, temp);
                currentChar = (char) getc(srcF);
            }

            StyleNode *style = (StyleNode *) calloc(1, sizeof(StyleNode));
            is_pointer_null(style);

            StyleNode *currentStyle = style;
            while(currentChar!='}'){
                //printf("%c", currentChar);
                if(currentChar==' '||currentChar=='\n'||currentChar=='{'){
                    currentChar=(char) getc(srcF);
                    continue;
                }else{
                    char *style_key = (char *) calloc(60, sizeof(char));
                    char *style_value = (char *) calloc(100, sizeof(char));

                    while(currentChar!=':'){
                        //printf("%c", currentChar);
                        if(currentChar==' '){
                            currentChar = (char) getc(srcF);
                        }else{
                            strcat(style_key, &currentChar);
                            currentChar = (char) getc(srcF);
                        }
                    }

                    while(currentChar!=';'){
                        //printf("%c", currentChar);
                        if(currentChar==' '||currentChar==':'){
                            currentChar = (char) getc(srcF);
                        }else{
                            strcat(style_value, &currentChar);
                            currentChar = (char) getc(srcF);
                        }
                    }
                    currentStyle->key = style_key;
                    currentStyle->value = style_value;

                    StyleNode * style_next = (StyleNode *) calloc(1, sizeof(StyleNode));
                    is_pointer_null(style_next);

                    currentStyle->next = style_next;
                    currentStyle = currentStyle->next;

                    currentChar = (char) getc(srcF);
                    //printf("%c", currentChar);
                }
            }
            printf("%s\n", selectorText);

            currentSelector->selectorText = selectorText;
            currentSelector->style = style;

            SelectorNode *selector_next = (SelectorNode *) calloc(1, sizeof(SelectorNode));
            is_pointer_null(selector_next);

            currentSelector->next = selector_next;
            currentSelector = currentSelector->next;
        }
        //printf("%c", currentChar);
    }
    //printf("%s\n", cssRule->selectorText);
    //printf("\n");
}
