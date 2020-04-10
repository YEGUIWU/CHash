#include "Hash_Sep.h"
#ifdef HASH_SEP_COME_TRUE

#include "Hash_Fun.h"

//报错
static inline void Error(const char* err_msg)
{
	printf("%s\n", err_msg);
}

//清空链表
void DeleteList(HashTable_List* L)
{
	if (!L || !*L) return;
	for (Position pcur = *L, pbark; pcur; pcur = pbark)
	{
		pbark = pcur->Next;
		free(pcur->Key);
		free(pcur);
	}
	memset(*L, 0, sizeof(struct Node));
}
int static IsPrime(int num)//返回0代表不是素数，返回1代表是素数
{
	if (num == 2)
		return 1;
	else if (num <= 1 || num % 2 == 0)
		return 0;
	else
	{
		for (int i = 3; i <= sqrt(num); i += 2)
		{
			if (num % i == 0)
				return 0;
		}
	}
	return 1;
}
int static NextPrime(int TableSize)
{
	int num = TableSize;
	while (!IsPrime(++num))
		;
	return num;
}
//初始化哈希表
HashTable InitializeTable(int TableSize)
{
	if (TableSize < MIN_TABLE_SIZE)
	{
		Error("Table size too small");
		return NULL;
	}

	HashTable H = (HashTable)malloc(sizeof(struct HashTbl));
	if (H == NULL)
		Error("Out of space");
	H->TableSize = NextPrime(TableSize);

	H->TheLists = (HashTable_List*)malloc(sizeof(HashTable_List) * H->TableSize);
	if (H->TheLists == NULL)
		Error("Out of space");

	for (int i = 0; i < H->TableSize; ++i)
	{
		H->TheLists[i] = calloc(1, sizeof(struct Node));
		
		if (H->TheLists[i] == NULL)
			Error("Out of space");
		else
			H->TheLists[i]->Next = NULL;
	}
	return H;
}
//销毁哈希表
void DestroyTable(HashTable H)
{
	for (int i = 0; i < H->TableSize; ++i)
	{
		if (H->TheLists[i])
		{
			DeleteList(H->TheLists + i);
		}
	}
	free(H->TheLists);
	H->TheLists = NULL;
}
//查找哈希表
Position Find(const KeyType Key, HashTable H)
{
	HashTable_List L = H->TheLists[Hash(Key, H->TableSize)];
	Position P = L->Next;
	while (P && strcmp(Key, P->Key) != 0)
		P = P->Next;
	return P;
}

//插入值
void Insert(const KeyType Key, ElementType Element, HashTable H)
{
	Position Pos = Find(Key, H);
	if (Pos == NULL)
	{
		Position NewCell = (Position)malloc(sizeof(struct Node));
		if (NewCell == NULL)
			Error("Out of space!!!");
		else
		{
			HashTable_List L = H->TheLists[Hash(Key, H->TableSize)];
			NewCell->Next = L->Next;
			NewCell->ELement = Element;
			size_t len = strlen(Key) + 1;
			NewCell->Key = malloc(len);
			memcpy(NewCell->Key, Key, len);
			L->Next = NewCell;
		}
	}
	else
	{
		Pos->ELement = Element;
	}
}
//删除
void Delete(const KeyType Key, HashTable H)
{
	HashTable_List L = H->TheLists[Hash(Key, H->TableSize)];
	if (L->Next)
	{
		Position P = L->Next;
		if (!strcmp(Key, P->Key))
		{
			L->Next = P->Next;
			free(P->Key);
			free(P);
		}
		else
		{
			while (P->Next && strcmp(Key, P->Next->Key) != 0)
				P = P->Next;
			if (P)
			{
				Position tmp = P->Next;
				P->Next = tmp->Next;
				free(tmp->Key);
				free(tmp);
			}
		}

	}
	
}
//取出内容
ElementType Retrieve(Position P)
{
	return P->ELement;
}
//遍历
void ForEach(HashTable H, void (*fun)(Position))
{
	for (int i = 0; i < H->TableSize; ++i)
	{
		if (H->TheLists[i]->Next)
		{
			for (Position pos = H->TheLists[i]->Next; pos; pos = pos->Next)
			{
				fun(pos);
			}
		}
	}
}

//带参遍历
void ForEachWithArg(HashTable H, void (*fun)(Position, void*), void* arg)
{
	for (int i = 0; i < H->TableSize; ++i)
	{
		if (H->TheLists[i]->Next)
		{
			for (Position pos = H->TheLists[i]->Next; pos; pos = pos->Next)
			{
				fun(pos, arg);
			}
		}
	}
}
#endif // HASH_SEP_COME_TRUE