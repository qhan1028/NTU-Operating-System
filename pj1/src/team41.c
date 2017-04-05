#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage int sys_hello(void)
{
	printk("hello system call ! \n");
	return 0;
}

asmlinkage int sys_show(void)
{
	printk("Team 41\n");
	printk("b03902089 Qhan\n");
	printk("b03705041\n");
	return 0;
}

asmlinkage long sys_multiply(long a, long b)
{
	return a*b;
}

asmlinkage long sys_min(long a, long b)
{
	return (a <= b)? a : b;
}
