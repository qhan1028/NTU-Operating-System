#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("testing syscall(349)...\n");
	syscall(349);
	printf("testing show()...\n");
	syscall(350);
	printf("testing multiply()...\n");
	printf("123*456=%ld\n", syscall(351, (long)123, (long)456));
	printf("testing min()...\n");
	printf("min(123, 456)=%ld\n", syscall(352, (long)123, (long)456));
	return 0;
}
