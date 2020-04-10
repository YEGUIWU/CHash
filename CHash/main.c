#define  _CRT_SECURE_NO_WARNINGS
#include "Hash_Table/Hash_Sep.h"
#include "Link_List/link_list.h"
#include <string.h>

void DisplayHashTablePostion(Position pos);
void DisplayLinkListPostion(ListPosition pos);
void DoTask(Position pos, void* arg);
void DealWithText(char* str, HashTable ht);
int WordCmp(void* arg1, void* arg2);
int CountCmp(void* arg1, void* arg2);
void ShowTopTen(List list);
void FreeListInfo(ListPosition pos);

int main()
{
    FILE* pf = fopen("essay.txt", "r");
    if (!pf)
    {
        perror("open file");
        exit(EXIT_FAILURE);
    }
    HashTable ht = InitializeTable(100);
    List list;
    InitList(&list);

    //一行一行的读取文件
    //当一行太长就会出bug，但是懒得处理了
    char buf[BUFSIZ];
    while (!feof(pf))
    {
        fgets(buf, BUFSIZ, pf);
        DealWithText(buf, ht);
    }
    //ForEach(ht, DisplayHashTablePostion);

    //带参遍历
    ForEachWithArg(ht, DoTask, &list);
    //按词序排序
    SortList(list, WordCmp);
    //打印链表
    DisplayList(list, DisplayLinkListPostion);
    //按次数排序
    SortList(list, CountCmp);
    //Top 10
    printf("---------------------------------\n Top 10\n");
    ShowTopTen(list);
    //释放内存
    ListForEach(list, FreeListInfo);
    DestroyList(list);
    DestroyTable(ht);
    fclose(pf);
    return 0;
}



typedef struct Info
{
    const char* key;
    int count;
}Info;

void DisplayHashTablePostion(Position pos)
{
    printf("%16s : %d\n", pos->Key, Retrieve(pos));
}

void DisplayLinkListPostion(ListPosition pos)
{
    Info* pInfo = (Info*)pos->ELement;
    printf("%16s : %d\n", pInfo->key, pInfo->count);
}

Info* MakeInfo(const char* key, int count)
{
    Info* pInfo = malloc(sizeof(Info));
    if (pInfo)
    {
        pInfo->count = count;
        pInfo->key = key;
    }
    return pInfo;
}

void DoTask(Position pos, void* arg)
{
    List* pList = (List*)arg;
    *pList = PushFront(MakeInfo(pos->Key, pos->ELement), *pList);
}

void AddOnce(HashTable ht, const char* key)
{
    Position pos = Find(key, ht);
    if (pos)
    {
        pos->ELement += 1;
    }
    else
    {
        Insert(key, 1, ht);
    }
}

void AddWord(char* ptr, int n, HashTable ht)
{
    char* p = ptr;
    for (int i = 0; i < n; ++i)
    {
        if (*p)
        {
            //printf("[%s]\n", p);
            AddOnce(ht, p);

        }
        p += strlen(p) + 1;
    }
}

int isAlpha(int ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return 1;
    else
        return 0;
}

void DealWithText(char* str, HashTable ht)
{
    char* pstr = str;
    int count = 0;
    while (*pstr)
    {
        if (!isAlpha(*pstr))
        {
            *pstr = '\0';
            ++count;
        }
        ++pstr;
    }
    AddWord(str, count + 1, ht);
}
int Strcmp(const char* p1, const char* p2)
{
    int i = 0;
    while (p1[i] == p2[i] && p1[i] != '\0')
    {
        i++;//继续向前
    }
    if (p1[i] == '\0' && p2[i] == '\0')
    {
        return 0;
    }
    else
    {
        int num = p1[i] - p2[i];
        if (num > 0)
            return 1;
        else
            return -1;
    }
}
int WordCmp(void* arg1, void* arg2)
{
    if (!arg1 || !arg2)
        return 1;
    Info* pInfo1 = (Info*)arg1;
    Info* pInfo2 = (Info*)arg2;
    //if (strcmp(pInfo1->key, pInfo2->key) == 1)
    return Strcmp(pInfo2->key, pInfo1->key);
}
int CountCmp(void* arg1, void* arg2)
{
    if (!arg1 || !arg2)
        return 1;
    Info* pInfo1 = (Info*)arg1;
    Info* pInfo2 = (Info*)arg2;
    return pInfo1->count > pInfo2->count;
}
void ShowTopTen(List list)
{
    int count = 0;
    for (ListPosition pos = HeadOfList(list); pos && count < 10; pos = pos->Next, ++count)
    {
        DisplayLinkListPostion(pos);
    }
}

void FreeListInfo(ListPosition pos)
{
    free(pos->ELement);
}