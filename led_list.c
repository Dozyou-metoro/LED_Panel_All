#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _list // リストにしたい構造体
{
	struct _list *p_next; // 次の要素を指すポインタ
	double data;		  // データ部分(型・サイズ不問)
} list;

typedef struct _exlist // 構造体の例
{
	struct _exlist *p_next; // 次の要素を指すポインタ
	char data[1];			// データ部分の先頭
} exlist;

int add_list(void **list_start, void *data, size_t size)
{

	int count = 0;							   // 追加したリストの要素番号
	exlist **list_top = (exlist **)list_start; // void*を_exlist構造体に変換

	if (!*list_top) // リストの要素がすでにあるか否か
	{
		*list_top = (exlist *)malloc(size);
		if (*list_top == NULL)
		{
			exit(1);
		}

		(*list_top)->p_next = NULL; // 次の要素がないことを表す。

		memcpy(&((*list_top)->data), data, size - sizeof(void *)); // データ部分をコピー

		return count;
	}

	exlist *buf = *list_top; // list_topを直接触るとリストの先頭ポインタが消えてしまうので先頭ポインタをコピー

	while (buf->p_next) // 次の要素が無くなるまでリストをたどる
	{
		buf = buf->p_next;
		count++;
	}

	buf->p_next = (exlist *)malloc(size);
	if (!buf->p_next)
	{
		exit(1);
	}

	count++;

	buf = buf->p_next; // 先ほど確保した要素に移動

	buf->p_next = NULL; // 次の要素がないことを表す。

	memcpy(&(buf->data), data, size - sizeof(void *)); // データ部分をコピー

	return count;
}

void* list_return(void* list_start, int no) {
	static void* p_start_buf = NULL;
	static void* p_list_buf = NULL;
	static int no_buf = 0;

	if ((p_start_buf == list_start) && (no_buf <= no)) {
		list_start = p_list_buf;
		no = no - no_buf;
	} else {
		p_start_buf = list_start;
		no_buf = 0;
	}

	exlist* list_top = (exlist*)list_start;

	for (int i = 0; i < no; i++) {
		list_top = list_top->p_next;
		no_buf++;
	}

	p_list_buf = (void*)list_top;

	return (void*)&list_top->data;
}

void list_free(void **list_start)
{
	exlist *list_top = (exlist *)*list_start; // void*を_exlist構造体に変換
	*list_start = NULL;						  // はじめに入っていた変数をNULLに指定

	exlist **buf = (*list_top).p_next;//このままだとwhile()が即終了してしまうので何かを入れておく

	while (buf)
	{
		buf = (*list_top).p_next;//次の要素のポインタを退避しておく
		free(list_top);//要素をfree()
		list_top = buf;//先ほど退避したポインタをもとに次の要素をたどる。
	}
}