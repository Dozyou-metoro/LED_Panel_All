#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error_print.h>

#include <led_dec.h>

typedef struct _list
{
    struct _list *p_next;
    char filename[1];
} list;

list *list_start = NULL;

int add_list(list **p_start, char *str)
{
    if (!*p_start) // 要素がないときの処理
    {
        *p_start = (list *)malloc(sizeof(list) + sizeof(strlen(str) - 1));
        if (!*p_start)
        {
            error_exit(-1);
        }
        strcpy((*p_start)->filename, str);
        (*p_start)->p_next = NULL;
        return 0;
    }

    list *p_buf = *p_start;

    while (p_buf->p_next)
    {
        p_buf = p_buf->p_next;
    }

    p_buf->p_next = (list *)malloc(sizeof(list) + sizeof(strlen(str) - 1));
    if (!p_buf->p_next)
    {
        error_exit(-1);
    }
    p_buf = p_buf->p_next;
    p_buf->p_next = NULL;
    strcpy(p_buf->filename, str);
    return 0;
}

char *return_list(list *p_start, int no)
{
    for (int i = 0; i < no; i++)
    {
        p_start = p_start->p_next;
    }
    return p_start->filename;
}

char** change_list(list* p_start) {
    size_t list_count = 0;
    size_t list_str_sum = 0;
    list* p_buf = p_start;

    while (p_buf) {
        list_count++;
        list_str_sum = list_str_sum + strlen(p_buf->filename) + 1;

        p_buf = p_buf->p_next;
    }

    char** p_str = NULL;
    char* str = NULL;

    p_str = (char**)malloc(sizeof(char*) * list_count);
    if (!p_str) {
        //error_exit(-1);
    }

    str = (char*)malloc(sizeof(char) * list_str_sum);
    if (!str) {
        //error_exit(-1);
    }

    size_t count_str = 0;

    for (int i = 0; i < list_count; i++) {
        strcpy(&str[count_str], p_start->filename);
        p_str[i] = &str[count_str];

        count_str = count_str + strlen(p_start->filename) + 1;
        p_start = p_start->p_next;
    }

    return p_str;
}