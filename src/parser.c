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
    fputs("{\"filename\":\"", dst_file);
    fputs(src_path, dst_file);
    fputs("\",\"stylesheet\":[", dst_file);
    while(css_rule->selector_text){
        SelectorNode *tmp_selector = css_rule;
        char *tmp_text = tmp_selector->selector_text;
        StyleNode *tmp_style = tmp_selector->style;

        fputs("{\"selector\":\"", dst_file);
        fputs(tmp_text, dst_file);
        fputs("\",\"rules\":{", dst_file);
        StyleNode *style_node = tmp_style;
        while(style_node->next){
            StyleNode *tmp_node = style_node;
            char *tmp_key = style_node->key;
            char *tmp_value = style_node->value;

            fputs("\"", dst_file);
            fputs(tmp_key, dst_file);
            fputs("\":\"", dst_file);
            fputs(tmp_value, dst_file);
            fputs("\"", dst_file);

            style_node = tmp_node->next;
            
            free(tmp_node);
            free(tmp_key);
            free(tmp_value);

            if(style_node->next){
                fputs(",", dst_file);
            }
        }
        fputs("}}", dst_file);
        css_rule = tmp_selector->next;
        free(tmp_selector);
        free(tmp_text);

        if(css_rule->selector_text){
            fputs(",", dst_file);
        }
    }
    fputs("]}\n", dst_file);
}

void parser(const char *src_path, FILE *src_file, FILE *dst_file){
    SelectorNode *css_rule;
    
    css_rule = (SelectorNode *) calloc(1, sizeof(SelectorNode));
    is_pointer_null(css_rule);
    
    SelectorNode *current_selector = css_rule;

    char current_char=' ';
    while(current_char != EOF){
        current_char = (char) getc(src_file);
        if(current_char==' '||current_char=='\n'){
            continue;
        }else if(current_char==EOF){
            break;
        }else if(
            current_char=='#'
            ||current_char=='.'
            ||('a'<current_char&&current_char<'z'))
        {   
            char *selector_text = (char *) calloc(100, sizeof(char));
            memset(selector_text, 0, 100);
            is_pointer_null(selector_text);
            
            char temp[2] = {0};
            while(current_char!='{'){
                //deal with selector_text
                temp[0] = current_char;
                strcat(selector_text, temp);
                current_char = (char) getc(src_file);
            }

            StyleNode *style = (StyleNode *) calloc(1, sizeof(StyleNode));
            is_pointer_null(style);

            StyleNode *current_style = style;
            while(current_char!='}'){
                if(current_char==' '||current_char=='\n'||current_char=='{'){
                    current_char=(char) getc(src_file);
                    continue;
                }else{
                    char *style_key = (char *) calloc(60, sizeof(char));
                    char *style_value = (char *) calloc(100, sizeof(char));

                    while(current_char!=':'){
                        if(current_char==' '){
                            current_char = (char) getc(src_file);
                        }else{
                            temp[0] = current_char;
                            strcat(style_key, temp);
                            current_char = (char) getc(src_file);
                        }
                    }

                    while(current_char!=';'){
                        if(current_char==' '||current_char==':'){
                            current_char = (char) getc(src_file);
                        }else{
                    temp[0] = current_char;
                            strcat(style_value, temp);
                            current_char = (char) getc(src_file);
                        }
                    }
                    current_style->key = style_key;
                    current_style->value = style_value;

                    StyleNode * style_next = (StyleNode *) calloc(1, sizeof(StyleNode));
                    is_pointer_null(style_next);

                    current_style->next = style_next;
                    current_style = current_style->next;

                    current_char = (char) getc(src_file);
                }
            }
            //printf("%s\n", selector_text);

            current_selector->selector_text = selector_text;
            current_selector->style = style;

            SelectorNode *selector_next = (SelectorNode *) calloc(1, sizeof(SelectorNode));
            is_pointer_null(selector_next);

            current_selector->next = selector_next;
            current_selector = current_selector->next;
        }
        //printf("%c", current_char);
    }
    //output to json
    output_to_json(src_path, css_rule, dst_file);
}
