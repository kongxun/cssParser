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

void output_to_json(const char *src_path, SelectorNode *css_rule, FILE *dst_file){
    fputs("{filename:", dst_file);
    fputs(src_path, dst_file);
    fputs(",styles:[", dst_file);
    while(css_rule->selectorText){
        fputs("{selector:", dst_file);
        fputs(css_rule->selectorText, dst_file);
        fputs(",rules:{", dst_file);
        StyleNode *style_node = css_rule->style;
        while(style_node->next){
            fputs(style_node->key, dst_file);
            fputs(":", dst_file);
            fputs(style_node->value, dst_file);
            fputs(",", dst_file);
            style_node = style_node->next;
        }
        fputs("}},", dst_file);
        css_rule = css_rule->next;
    }
    fputs("]}\n", dst_file);
}

void parser(const char *src_path, FILE *src_file, FILE *dst_file){
    SelectorNode *css_rule;
    
    css_rule = (SelectorNode *) calloc(1, sizeof(SelectorNode));
    is_pointer_null(css_rule);
    
    SelectorNode *currentSelector = css_rule;

    char currentChar=' ';
    while(currentChar != EOF){
        currentChar = (char) getc(src_file);
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
                currentChar = (char) getc(src_file);
            }

            StyleNode *style = (StyleNode *) calloc(1, sizeof(StyleNode));
            is_pointer_null(style);

            StyleNode *currentStyle = style;
            while(currentChar!='}'){
                //printf("%c", currentChar);
                if(currentChar==' '||currentChar=='\n'||currentChar=='{'){
                    currentChar=(char) getc(src_file);
                    continue;
                }else{
                    char *style_key = (char *) calloc(60, sizeof(char));
                    char *style_value = (char *) calloc(100, sizeof(char));

                    while(currentChar!=':'){
                        //printf("%c", currentChar);
                        if(currentChar==' '){
                            currentChar = (char) getc(src_file);
                        }else{
                            temp[0] = currentChar;
                            strcat(style_key, temp);
                            currentChar = (char) getc(src_file);
                        }
                    }

                    while(currentChar!=';'){
                        //printf("%c", currentChar);
                        if(currentChar==' '||currentChar==':'){
                            currentChar = (char) getc(src_file);
                        }else{
                            temp[0] = currentChar;
                            strcat(style_value, temp);
                            currentChar = (char) getc(src_file);
                        }
                    }
                    currentStyle->key = style_key;
                    currentStyle->value = style_value;

                    StyleNode * style_next = (StyleNode *) calloc(1, sizeof(StyleNode));
                    is_pointer_null(style_next);

                    currentStyle->next = style_next;
                    currentStyle = currentStyle->next;

                    currentChar = (char) getc(src_file);
                    //printf("%c", currentChar);
                }
            }
            //printf("%s\n", selectorText);

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
    
    //output to json
    output_to_json(src_path, css_rule, dst_file);
}
