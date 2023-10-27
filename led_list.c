#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "led_dec.h"

/*
typedef struct _list // リストにしたい構造体
{
	void *p_next; // 次の要素を指すポインタ
	double data;  // データ部分(型・サイズ不問)
} list;
*/

typedef struct _exlist // 構造体の例
{
	void *p_next; // 次の要素を指すポインタ
	char data[1]; // データ部分の先頭
} exlist;

int add_list(void **list_start, void *data, size_t size)
{

	int count = 0;							   // 追加したリストの要素番号
	exlist **list_top = (exlist **)list_start; // void*を_exlist構造体に変換

	if (!*list_top) // リストの要素がすでにあるか否か
	{
		*list_top = (exlist *)malloc(size + sizeof(void*));
		if (*list_top == NULL)
		{
			ERROR_EXIT(-1)
		}

		(*list_top)->p_next = NULL; // 次の要素がないことを表す。

		memcpy(&((*list_top)->data), data, size); // データ部分をコピー

		return count;
	}

	exlist *buf = *list_top; // list_topを直接触るとリストの先頭ポインタが上書きされて消えてしまうので先頭ポインタをコピー

	while (buf->p_next) // 次の要素が無くなるまでリストをたどる
	{
		buf = (exlist *)buf->p_next;
		count++;
	}

	buf->p_next = (exlist *)malloc(size + sizeof(void*));
	if (!buf->p_next)
	{
		ERROR_EXIT(-1)
	}

	count++;

	buf = (exlist *)buf->p_next; // 先ほど確保した要素に移動

	buf->p_next = NULL; // 次の要素がないことを表す。

	memcpy(&(buf->data), data, size); // データ部分をコピー

	return count;
}

void* list_return(void* list_start, int no) {
	static void* p_start_buf = NULL; // 前回たどったリストの先頭ポインタ
	static void* p_list_buf = NULL;	 // 前回返した要素のポインタ
	static int no_buf = 0;			 // 前回返した要素の要素番号

	if ((p_start_buf == list_start) && (no_buf <= no)) // 前回呼ばれたリストと同じで、前回と同じかそれより後ろのデータを要求されているか否か
	{
		list_start = p_list_buf; // 前回読んだ要素のポインタで上書き
		no = no - no_buf;		 // 前回読んだ要素と要求された要素の差に変更
	} else {
		p_start_buf = list_start; // リストの先頭ポインタをメモ
		no_buf = 0;				  // 読んだ要素の番号をリセット
	}

	exlist* list_top = (exlist*)list_start; // void*を_exlist構造体に変換

	for (int i = 0; i < no; i++) // no回リストをたどる
	{
		list_top = (exlist*)list_top->p_next;
		no_buf++;
	}

	p_list_buf = (void*)list_top; // 今回読んだ要素のポインタをメモ

	return (void*)&list_top->data;
}

	void list_free(void **list_start)
	{
		if (!*list_start) {
			return;
		}

		exlist *list_top = (exlist *)*list_start; // void*を_exlist構造体に変換
		*list_start = NULL;						  // はじめに入っていた変数をNULLに指定

		exlist **buf = (*list_top).p_next; // このままだとwhile()が即終了してしまうので何かを入れておく

		do
		{
			buf = (*list_top).p_next; // 次の要素のポインタを退避しておく
			free(list_top);			  // 要素をfree()
			list_top = buf;			  // 先ほど退避したポインタをもとに次の要素をたどる。
		} while (list_top);
	}