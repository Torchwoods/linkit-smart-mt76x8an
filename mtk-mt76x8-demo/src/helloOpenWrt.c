#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc, char **argv)
{
	while (1)
	{
		printf("hello OpenWrt\n");
		sleep(1);
	}
	return 0;
}

