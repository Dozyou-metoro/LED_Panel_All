// led_list.c
typedef struct _list
{
    struct _list *p_next;
    char filename[1];
} list;

int add_list(list **p_start, char *str);
char *return_list(list *p_start, int no);
char **change_list(list *p_start);
void list_free(list **p_start);
void list_arr_free(char ***list);

// error_print.c
void error_print(char message[], int return_num);
void error_exit(int return_num)
