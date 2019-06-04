#include <iostream>
#include <math.h>

#include "hash.h"

using namespace std;


int is_prime(int num) 
{
    int i;
    for (i=2; i<num; i++)
    {
        if ((num % i) == 0)
        {
            break;
        }
    }
    if (i == num) 
    {
        return 1;
    }
    return 0;
}

int calc_next_prime(int num) 
{
	num++;
    while (!is_prime(num)) 
    {
        num++;
    }
    return num;
}


class EGHFilter
{
private:
	u_int64 u;
	u_int64 d;
	u_int64 m;
	u_int64 k;
	u_char *table;
	hash HashFamily;
public:
	EGHFilter(){}
	EGHFilter(u_int64 u, u_int64 d);
	~EGHFilter(){}
	void Insert(u_int64 x);
	bool Query(u_int64 x);
	void Info();
};

EGHFilter::EGHFilter(u_int64 u, u_int64 d)
{
	this->u = u;
	this->d = d;
	u_int64 temp = pow(u, d);
	int product = 2;
	int prime = 3;
	k = 1;
	m = 2;
	while (product < temp)
	{
		product = product * prime;
		m = m + prime;
		k++;
		prime = calc_next_prime(prime);
	}
	u_int64 blocks = (m + 7) / 8;
	table = new u_char[blocks];
	for (int i = 0; i < blocks; i++)
	{
		table[i] = 0;
	}
	HashFamily = hash(k);
}

void EGHFilter::Insert(u_int64 x)
{
	for (int i = 0; i < k; i++)
	{
		u_int64 index = HashFamily.getKindex(i, x);
		//printf("no %u index = %u\n", i, index);
		u_int64 block = index / 8;
		u_int64 offset = index % 8;
		u_int8 x = 0x80 >> offset;
		table[block] = table[block] | x;
	}
}

bool EGHFilter::Query(u_int64 x)
{
	bool ans = true;
	for (int i = 0; i < k; i++)
	{
		u_int64 index = HashFamily.getKindex(i, x);
		u_int64 block = index / 8;
		u_int64 offset = index % 8;
		u_int8 x = 0x80 >> offset;
		u_int8 flag = table[block] & x;
		if(flag == 0)
		{
			ans = false;
			break;
		}
	}
	return ans;
}


void EGHFilter::Info()
{
	printf("the size of the univerise is %u\n", u);
	printf("the size of false positive free zone is %u\n", d);
	printf("the num of blocks is %u\n", k);
	printf("the length of bit array is %u\n", m);
	HashFamily.Info();
}