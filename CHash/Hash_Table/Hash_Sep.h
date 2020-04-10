#ifndef _HASH_SEP_H_
#define _HASH_SEP_H_
#define MIN_TABLE_SIZE 10
//分离链接法
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef _WIN32
#include <memory.h>
#endif // _WIN32
#include <string.h>
typedef int ElementType;
typedef char* KeyType;

struct Node
{
	KeyType Key;
	ElementType ELement;
	struct Node* Next;
};
typedef struct Node* PtrToNode;
typedef PtrToNode HashTable_List;
typedef PtrToNode Position;
//分离链接散列表
struct HashTbl
{
	int TableSize;
	HashTable_List* TheLists;
};
typedef struct HashTbl* HashTable;
//初始化哈希表
HashTable InitializeTable(int TableSize);
//销毁哈希表
void DestroyTable(HashTable H);
//查找哈希表
Position Find(const KeyType Key, HashTable H);
//插入值
void Insert(const KeyType Key, ElementType Element, HashTable H);
//
void Delete(const KeyType Key, HashTable H);
//取出内容
ElementType Retrieve(Position P);
//清空链表
void DeleteList(HashTable_List* L);
//
//遍历
void ForEach(HashTable H, void (*fun)(Position));
//
void ForEachWithArg(HashTable H, void (*fun)(Position, void*), void*arg);
#define HASH_SEP_COME_TRUE
#endif // !_HASH_SEP_H_