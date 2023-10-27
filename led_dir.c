#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>

#include "led_dec.h"




void *get_namelist(char *start_dir)
{
    const int DIR_NO = 4, FILE_NO = 8;
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    {
        /* data */
    };

    void *namelist_start = NULL;

    dir = opendir(start_dir);
    if (!dir)
    {
        ERROR_EXIT(-2);
    }

    void *mem_buf = NULL;

    mem_buf = malloc(sizeof(dir_list_buf) + sizeof(char) * 1023);
    if (!mem_buf)
    {
        ERROR_EXIT(-1);
    }

    while (1)
    {
        entry = readdir(dir);

        if (!entry)
        {
            break;
        }

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) //.を無視
        {
            continue;
        }

        if (strcmp(entry->d_name, ".git") == 0) //.gitを無視
        {
            continue;
        }

        if (entry->d_type==0x8000) //.pngのときの処理
        {
            size_t buf_size = sizeof(file_list_buf) + strlen(entry->d_name);
            file_list_buf *buf = (file_list_buf *)mem_buf;
            buf->type = png;
            strcpy(&buf->namelist, &entry->d_name);


            add_list(&namelist_start, buf, buf_size);
        }
        else
        {
            dir_list_buf *buf = (dir_list_buf *)mem_buf;
            size_t buf_size = sizeof(dir_list_buf) + strlen(entry->d_name);
            char filename_buf[1024];

            buf->type = directory;
            strcpy(&buf->namelist, &entry->d_name);

            snprintf(filename_buf, sizeof(filename_buf), "%s\\%s", start_dir, entry->d_name);

            buf->p_under = get_namelist(filename_buf);

            add_list(&namelist_start, buf, buf_size);
        }
    }
    free(mem_buf);
    closedir(dir);
    return namelist_start;
}

void namelist_free(void **pp_start)
{
    if (!*pp_start) {
        return;
    }

    dir_list *p_start = (dir_list *)*pp_start;
    *pp_start = NULL;

    dir_list *p_buf = NULL;
    void *p_under = NULL;


    do
    {
        if (p_start->type == directory)
        {
            namelist_free(&(p_start->p_under));
        }

        p_buf = p_start->p_next;
        free(p_start);
        p_start = p_buf;

    } while (p_start);
}