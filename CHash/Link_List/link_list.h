#ifndef _LINK_LIST_
#define _LINK_LIST_
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <memory.h>
#else
#include <string.h>
#endif
#include <stdbool.h>

//使用单链表
#define SINGLE_LINK_LIST 1
//使用双链表
//#define DOUBLE_LINK_LIST 1


typedef void* ListElementType;


#ifdef SINGLE_LINK_LIST
typedef struct ListNode
{
	ListElementType ELement;
	struct ListNode* Next;
} ListNode;
typedef ListNode* List;
#elif DOUBLE_LINK_LIST
typedef struct ListNode
{
	ListElementType ELement;
	struct ListNode* Next;
	struct ListNode* Pre;
} ListNode;
typedef struct List
{
	ListNode* Head;
	ListNode* Tail;
	long		  Length;
}List;
#endif // SINGLE_LINKE_LIST

typedef ListNode* ListPosition;
//初始化链表
void InitList(List* L);

//判断链表是否为空
_Bool ListIsEmpty(List L);

//判断某个位置是否位于链表的结尾
_Bool PosInListIsLast(ListPosition P);

//查找某个元素的位置
ListPosition FindInList(ListElementType X, List L);

//查找符合条件的结点
ListPosition FindIf(_Bool(*p)(), List L);

//从链表中删除某个元素
void DeleteFromList(ListElementType X, List L);

//查找某个元素的上一个位置
ListPosition FindPrePosFromList(ListElementType X, List L);

//尾插入元素
List PushBack(ListElementType X, List L);

//头插入元素
List PushFront(ListElementType X, List L);

//删除尾部
List PopBack(List L);

//删除头部
List PopFront(List L);

//往某个位置放入某个元素
void InsertToList(ListElementType X, ListPosition P);

//清空链表
List DestroyList(List L);

//获取链表头结点位置
ListPosition HeadOfList(List L);

//获取链表尾结点位置
ListPosition TailOfList(List L);

//获取链表的第一个元素
ListElementType FirstOfList(List L);

//获取链表的最后一个元素
ListElementType FinalOfList(List L);

//返回上一个位置
#ifdef SINGLE_LINK_LIST
ListPosition AdvanceOfListPos(ListPosition P, List L);
#elif DOUBLE_LINK_LIST
ListPosition AdvanceOfListPos(ListPosition P);
#endif

//从节点位置取出元素的值
ListElementType RetrieveFromListPos(ListPosition P);

//打印链表
void DisplayList(List L, void(*pDisplayFunc)(ListPosition));

//排序链表
void SortList(List L, int(*pCmp)(ListElementType, ListElementType));

//遍历链表
void ListForEach(List L, void(*pFunc)(ListPosition));
//带参遍历链表
void ListForEachWithArg(List lst, void(*pFunc)(ListPosition, void*), void*arg);

//获取链表的大小
unsigned int ListSize(List L);

//警告错误，打印错误信息
void ListError(const char* errMsg);

//严重错误，打印错误信息，并退出程序
void ListFailError(const char* errMsg);
#endif // !_LINK_LIST_