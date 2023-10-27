// led_error.c
#include <errno.h>

#define ERROR_PRINT(message, return_no)                                                               \
    printf("message:%s\nerrno:%s\nfile:%s\nline:%d\n", message, strerror(errno), __FILE__, __LINE__); \
    fflush(stdout);                                                                                   \
    exit(return_no);

#define ERROR_EXIT(return_no)                                                    \
    printf("errno:%s\nfile:%s\nline:%d\n", strerror(errno), __FILE__, __LINE__); \
    fflush(stdout);                                                              \
    exit(return_no);

// led_list.c

int add_list(void** list_start, void* data, size_t size);
void* list_return(void* list_start, int no);
void list_free(void** list_start);

//led_dir.c
#include<stdint.h>

typedef struct _dir_list{
    struct _dir_list* p_next;
    uint8_t type;
    struct _dir_list* p_under;
    char namelist[1];
} dir_list;

typedef struct _file_list{
    struct _file_list* p_next;
    uint8_t type;
    char namelist[1];
} file_list;

typedef struct _dir_list_buf {
    uint8_t type;
    struct _dir_list_buf* p_under;
    char namelist[1];
} dir_list_buf;

typedef struct {
    uint8_t type;
    char namelist[1];
} file_list_buf;

typedef enum {
    directory,
    png,


} filetype;

void* get_namelist(char* start_dir);
void namelist_free(void** pp_start);
