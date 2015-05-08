#include <stdio.h>

int main()
{

	int i = 10;
	while(i){
	 --i;
	 if(i == 5)
		 continue;
	}
	printf("i is %d\n",i);
	return 0;
}
