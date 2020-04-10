#include "link_list.h"
typedef ListNode* PtrToListNode;

#pragma region 通用
//-----------------------------------------------------
void ListError(const char* errMsg)
{
	perror(errMsg);
}
//-----------------------------------------------------
void ListFailError(const char* errMsg)
{
	perror(errMsg);
	exit(-1);
}
//-----------------------------------------------------
//将数据封装成结点
inline PtrToListNode MakeListNode(ListElementType elem)
{
	PtrToListNode p = calloc(1, sizeof(ListNode));
	if (p)
	{
		p->ELement = elem;
	}
	else
	{
		ListFailError("Alloc Error!\n");
	}
	return p;
}
//-----------------------------------------------------
//判断某个位置是否位于链表的结尾
_Bool PosInListIsLast(ListPosition P)
{
	return P->Next == NULL;
}
//-----------------------------------------------------
//销毁某个结点
void DestroyListNode(PtrToListNode p)
{
	//free(p->ELement);
	free(p);
}
//-----------------------------------------------------
//获取链表的第一个节点的位置
ListElementType FirstOfList(List L)
{
	return RetrieveFromListPos(HeadOfList(L));
}
//获取链表的最后一个元素
ListElementType FinalOfList(List L)
{
	return RetrieveFromListPos(TailOfList(L));
}
//-----------------------------------------------------
//从节点位置取出元素的值
ListElementType RetrieveFromListPos(ListPosition P)
{
	return P->ELement;
}
//-----------------------------------------------------
//打印链表
void DisplayList(List L, void(*pDisplayFunc)(ListPosition))
{
	for (ListPosition p = HeadOfList(L); p; p = p->Next)
	{
		pDisplayFunc(p);
	}
}

//遍历链表
void ListForEach(List L, void(*pFunc)(ListPosition))
{
	for (ListPosition p = HeadOfList(L); p; p = p->Next)
	{
		pFunc(p);
	}
}
//带参遍历链表
void ListForEachWithArg(List L, void(*pFunc)(ListPosition, void*), void* arg)
{
	for (ListPosition p = HeadOfList(L); p; p = p->Next)
	{
		pFunc(p, arg);
	}
}
//-----------------------------------------------------
//查找某个元素的位置
ListPosition FindIf(_Bool(*pFunc)(), List L)
{
	for (ListPosition P = HeadOfList(L); P; P = P->Next)
	{
		if (pFunc(P->ELement))
			return P;
	}
	return NULL;
}
//-----------------------------------------------------
/*  链表快速排序  */

//-----------------------------------------------------
static void SwapNode(PtrToListNode p1, PtrToListNode p2)
{
	ListElementType tmp = p1->ELement;
	p1->ELement = p2->ELement;
	p2->ELement = tmp;
}
//-----------------------------------------------------
void static SortListBase(PtrToListNode pHead, PtrToListNode pEnd, int(*pCmp)(ListElementType, ListElementType))
{
	if (pHead)
	{
		if (pHead != pEnd)
		{
			PtrToListNode pIndex = pHead;
			for (PtrToListNode pGo = pHead->Next; pGo != pEnd; pGo = pGo->Next)
			{
				if (pCmp(pGo->ELement, pHead->ELement) > 0)
				{
					pIndex = pIndex->Next;
					SwapNode(pGo, pIndex);
					//SwapNode(&pGo->Next, &pIndex->Next, sizeof(PtrToListNode));
				}
			}
			SwapNode(pIndex, pHead);
			//SwapNode(&pIndex->Next, &pHead->Next, sizeof(PtrToListNode));

			//SortListBase(pHead, pIndex, pCmp);
			SortListBase(pHead,pIndex, pCmp);
			SortListBase(pIndex->Next, pEnd, pCmp);
		}
	}
}
void SortList(List lst, int(*pCmp)(ListElementType, ListElementType))
{
#ifdef SINGLE_LINK_LIST

	SortListBase(HeadOfList(lst), NULL, pCmp);
#elif DOUBLE_LINK_LIST
	SortListBase(lst.Head, lst.Tail, pCmp);
#endif 
}
#pragma endregion



#ifdef SINGLE_LINK_LIST
//-----------------------------------------------------
//初始化链表
void InitList(List* L)
{
	*L = NULL;
}
//-----------------------------------------------------
//判断链表是否为空
_Bool ListIsEmpty(List L)
{
	return L == NULL;
}
//-----------------------------------------------------
//查找某个元素的位置
ListPosition FindInList(ListElementType X, List L)
{
	for (ListPosition P = L; P; P = P->Next)
	{
		if (P->ELement == X)
			return P;
	}
	return NULL;
}
//-----------------------------------------------------
//从链表中删除某个元素
void DeleteFromList(ListElementType X, List L)
{
	ListPosition P, TmpCell;
	P = FindPrePosFromList(X, L);
	if (!PosInListIsLast(P))
	{
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}
//-----------------------------------------------------
//尾插入元素
List PushBack(ListElementType X, List L)
{
	if (!L)//如果空
	{
		L = MakeListNode(X);
	}
	else
	{
		PtrToListNode p;
		for (p = L; p->Next; p = p->Next)
			;
		p->Next = MakeListNode(X);
	}
	return L;
}
//-----------------------------------------------------
//查找某个元素的上一个位置
ListPosition FindPrePosFromList(ListElementType X, List L)
{
	for (ListPosition P = L; P->Next; P = P->Next)
	{
		if (P->Next->ELement == X)
			return P;
	}
	return NULL;
}
//-----------------------------------------------------
//头插入元素
List PushFront(ListElementType X, List L)
{
	if (!L)
	{
		L = MakeListNode(X);

	}
	else
	{
		PtrToListNode p = MakeListNode(X);
		p->Next = L;
		L = p;
	}
	return L;
}
//-----------------------------------------------------
//删除尾部
List PopBack(List L)
{
	if (!L) //空表
	{
		//do nothing
	}
	else if (!L->Next)//有1个元素
	{
		DestroyListNode(HeadOfList(L));
		L = NULL;
	}
	else //2个以上
	{
		PtrToListNode p;
		for (p = L; p->Next->Next; p = p->Next)
			;
		DestroyListNode(p->Next);
		p->Next = NULL;
	}
	return L;
}
//-----------------------------------------------------
//删除头部
List PopFront(List L)
{
	if (ListIsEmpty(L))
	{
		perror("List has nothing\n");
		return L;
	}
	PtrToListNode p = HeadOfList(L)->Next;
	DestroyListNode(HeadOfList(L));
	return p;
}
//-----------------------------------------------------
//往某个位置放入某个元素
void InsertToList(ListElementType X, ListPosition P)
{
	if (!P)
	{
		perror("Position is null!\n");
		return;
	}
	PtrToListNode TmpCell = MakeListNode(X);
	if (TmpCell)
	{
		TmpCell->ELement = X;
		TmpCell->Next = P->Next;
		P->Next = TmpCell;
	}
}
//-----------------------------------------------------
//清空链表
List DestroyList(List L)
{
	if (!ListIsEmpty(L))
	{
		for (ListPosition pcur = HeadOfList(L), pbark; pcur; pcur = pbark)
		{
			pbark = pcur->Next;
			free(pcur);
		}
	}

	return NULL;
}

//-----------------------------------------------------
//获取链表头节点位置
ListPosition HeadOfList(List L)
{
	return L;
}
//-----------------------------------------------------
//返回上一个位置
ListPosition AdvanceOfListPos(ListPosition P, List L)
{
	for (ListPosition pt = L; pt; pt = pt->Next)
	{
		if (P == pt->Next)
			return pt;
	}
	return NULL;
}
//获取链表尾结点位置
ListPosition TailOfList(List L)
{
	ListPosition p = L;
	if (p)
	{
		for (; p->Next; p = p->Next)
			;//Do nothing
	}
	return p;

}
//-----------------------------------------------------
unsigned int ListSize(List L)
{
	ListPosition p = HeadOfList(L);
	unsigned int len = 0;
	while (p)
	{
		++len;
		p = p->Next;
	}
	return len;
}

#elif DOUBLE_LINK_LIST
//-----------------------------------------------------
//初始化链表
void InitList(List* L)
{
	if (L);
	{
		L->Head = L->Tail = NULL;
		L->Length = 0;
	}
}
//-----------------------------------------------------
//判断链表是否为空
_Bool ListIsEmpty(List L)
{
	return L.Head == NULL;
}
//-----------------------------------------------------
//查找某个元素的位置
ListPosition FindInList(ListElementType X, List L)
{
	for (ListPosition P = HeadOfList(L); P; P = P->Next)
	{
		if (P->ELement == X)
			return P;
	}
	return NULL;
}
ListPosition RFindInList(ListElementType X, List L)
{
	for (ListPosition P = TailOfList(L); P; P = P->Pre)
	{
		if (P->ELement == X)
			return P;
	}
	return NULL;
}
//-----------------------------------------------------
//尾插入元素
List PushBack(ListElementType X, List L)
{
	if (ListIsEmpty(L))//如果空
	{
		L.Head = MakeListNode(X);
		L.Tail = L.Head;
	}
	else
	{
		PtrToListNode NewNode = MakeListNode(X);
		TailOfList(L)->Next = NewNode;
		NewNode->Pre = TailOfList(L);
		L.Tail = NewNode;
	}
	++L.Length;
	return L;
}
//-----------------------------------------------------
//查找某个元素的上一个位置
ListPosition FindPrePosFromList(ListElementType X, List L)
{
	for (ListPosition P = HeadOfList(L); P->Next; P = P->Next)
	{
		if (P->Next->ELement == X)
			return P;
	}
	return NULL;
}
//-----------------------------------------------------
//头插入元素
List PushFront(ListElementType X, List L)
{
	if (ListIsEmpty(L))//如果空
	{
		L.Head = MakeListNode(X);
		L.Tail = L.Head;
	}
	else
	{
		PtrToListNode NewNode = MakeListNode(X);
		HeadOfList(L)->Pre = NewNode;
		NewNode->Next = HeadOfList(L);
		L.Head = NewNode;
	}
	++L.Length;
	return L;
}
//-----------------------------------------------------
//删除尾部
List PopBack(List L)
{
	if (ListIsEmpty(L)) //空表
	{
		//do nothing
	}
	else if (L.Head == L.Tail)//有1个元素
	{
		DestroyListNode(HeadOfList(L));
		L.Tail = L.Head = NULL;
		L.Length = 0;
	}
	else //2个以上
	{
		PtrToListNode Barkup = TailOfList(L)->Pre;
		DestroyListNode(TailOfList(L));
		L.Tail = Barkup;
		--L.Length;
	}
	return L;
}
//-----------------------------------------------------
//删除头部
List PopFront(List L)
{
	if (ListIsEmpty(L))
	{
		perror("List has nothing\n");
		return L;
	}
	PtrToListNode Barkup = HeadOfList(L)->Next;
	DestroyListNode(HeadOfList(L));
	L.Head = Barkup;
	--L.Length;
	return L;
}
//-----------------------------------------------------
//往某个位置放入某个元素
void InsertToList(ListElementType X, ListPosition P)
{
	if (!P)
	{
		perror("Position is null!\n");
		return;
	}
	PtrToListNode TmpCell = MakeListNode(X);
	if (TmpCell)
	{
		TmpCell->ELement = X;
		if (P->Next)//不是最后一个位置
		{
			P->Next->Pre = TmpCell;
			TmpCell->Next = P->Next;
			P->Next = TmpCell;
			TmpCell->Pre = P;
		}
		else
		{
			P->Next = TmpCell;
			TmpCell->Pre = P;
		}
		//TmpCell->Next = P->Next;
		//P->Pre->Next = TmpCell;
		//P->Pre = TmpCell;
	}
}

//-----------------------------------------------------
//获取链表头节点位置
ListPosition HeadOfList(List L)
{
	return L.Head;
}
//-----------------------------------------------------
//返回上一个位置
ListPosition AdvanceOfListPos(ListPosition P)
{
	return P->Pre;
}
//----------------------------------------------------
//获取链表尾结点位置
ListPosition TailOfList(List L)
{
	return L.Tail;
}
//-----------------------------------------------------
unsigned int ListSize(List L)
{
	return L.Length;
}
//-----------------------------------------------------
//清空链表
List DestroyList(List L)
{
	if (!ListIsEmpty(L))
	{
		for (ListPosition pcur = HeadOfList(L), pbark; pcur; pcur = pbark)
		{
			pbark = pcur->Next;
			free(pcur);
		}
	}
	L.Head = L.Tail = NULL;
	L.Length = 0;
	return L;
}
#endif // SINGLE_LINKE_LIST