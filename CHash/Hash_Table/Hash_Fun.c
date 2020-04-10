#include "Hash_Fun.h"
unsigned int SDBMHash(char* str)
{
	unsigned int hash = 0;

	while (*str)
	{
		// equivalent to: hash = 65599*hash + (*str++);
		hash = (*str++) + (hash << 6) + (hash << 16) - hash;
	}

	return (hash & 0x7FFFFFFF);
}

// RS Hash Function
unsigned int RSHash(char* str)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;

	while (*str)
	{
		hash = hash * a + (*str++);
		a *= b;
	}

	return (hash & 0x7FFFFFFF);
}

// JS Hash Function
unsigned int JSHash(char* str)
{
	unsigned int hash = 1315423911;

	while (*str)
	{
		hash ^= ((hash << 5) + (*str++) + (hash >> 2));
	}

	return (hash & 0x7FFFFFFF);
}

// P. J. Weinberger Hash Function
unsigned int PJWHash(char* str)
{
	unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	unsigned int ThreeQuarters = (unsigned int)((BitsInUnignedInt * 3) / 4);
	unsigned int OneEighth = (unsigned int)(BitsInUnignedInt / 8);
	unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
	unsigned int hash = 0;
	unsigned int test = 0;

	while (*str)
	{
		hash = (hash << OneEighth) + (*str++);
		if ((test = hash & HighBits) != 0)
		{
			hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
		}
	}

	return (hash & 0x7FFFFFFF);
}

// ELF Hash Function
unsigned int ELFHash(char* str)
{
	unsigned int hash = 0;
	unsigned int x = 0;

	while (*str)
	{
		hash = (hash << 4) + (*str++);
		if ((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
			hash &= ~x;
		}
	}

	return (hash & 0x7FFFFFFF);
}

// BKDR Hash Function
unsigned int BKDRHash(const char* str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;

	while (*str)
	{
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

// DJB Hash Function
unsigned int DJBHash(char* str)
{
	unsigned int hash = 5381;

	while (*str)
	{
		hash += (hash << 5) + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

// AP Hash Function
unsigned int APHash(char* str)
{
	unsigned int hash = 0;
	int i;

	for (i = 0; *str; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		}
	}

	return (hash & 0x7FFFFFFF);
}

//编程珠玑中的一个hash函数
//用跟元素个数最接近的质数作为散列表的大小
#define NHASH 29989
#define MULT 31
unsigned int hash(char* p)
{
	unsigned int h = 0;
	for (; *p; p++)
		h = MULT * h + *p;
	return h % NHASH;
}

//简单的哈希
Index Simple_Hash(const char* key, int TableSize)
{
	unsigned int HashVal = 0;
	while (*key != 0)
		HashVal += *key++;
	return HashVal % TableSize;
}
//另一个简单的哈希
Index Another_Simple_Hash(const char* key, int TableSize)
{
	return (key[0] + 27 * key[1] + 729 * key[2]) % TableSize;
}
//比较好的哈希
Index Good_Hash(const char* key, int TableSize)
{
	unsigned int HashVal = 0;
	while (*key != 0)
	{
		HashVal = (HashVal << 5) + *key++;
	}
	return HashVal % TableSize;
}


//调用哈希接口
Index Hash(const char* key, unsigned int TableSize)
{
	return BKDRHash(key) % TableSize;
}