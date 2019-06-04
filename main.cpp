#include "EGH-filter.h"

#include <math.h>

using namespace std;

int main()
{
	u_int64 d;
	u_int64 u;
	printf("plz input the size of the univerise\n");
	scanf("%u",&u);

	printf("plz input the size of false positive free zone\n");
	scanf("%u",&d);



	EGHFilter egh = EGHFilter(u, d);

	egh.Info();

	for (int i = 1; i <= d; i++)
	{
		egh.Insert(i);
	}

	int cnt = 0;
	for (int i = d + 1; i <= u; i++)
	{
		if (egh.Query(i))
		{
			cnt++;
		}
	}
	printf("%d\n", cnt);
	return 0;
}