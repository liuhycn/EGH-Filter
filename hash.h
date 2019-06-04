#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef unsigned long long u_int64;
typedef u_int32_t u_int32;
typedef u_int16_t u_int16;
typedef u_int8_t u_int8;

class hash
{
private:
	vector<u_int64> prime;
	u_int64 k;
public:
	hash(){}
	hash(u_int64 k);
	~hash(){}
	int is_prime(int num);
	int calc_next_prime(int num);
	u_int64 getKindex(u_int64 k, u_int64 x);
	void Info();
};

u_int64 hash::getKindex(u_int64 k, u_int64 x)
{
	u_int64 sum = 0;
	for (int i = 0; i < k; i++)
	{
		sum = sum + prime[i];
	}
	return (x % prime[k]) + sum;
}

hash::hash(u_int64 k)
{
	this->k = k;
	if (k == 1)
	{
		prime.push_back(2);
	}
	else
	{
		int a = 2;
		prime.push_back(a);
		for (int i = 1; i < k; i++)
		{
			a = calc_next_prime(a);
			prime.push_back(a);
		}
	}
	
}

int hash::is_prime(int num) 
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

int hash::calc_next_prime(int num) 
{
	num++;
    while (!is_prime(num)) 
    {
        num++;
    }
    return num;
}

void hash::Info()
{
	printf("already gen %u prime number\n", k);
	for (int i = 0; i < k; ++i)
	{
		printf("%d ", prime[i]);
	}
	printf("\n");
}