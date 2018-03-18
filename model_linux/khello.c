
/*!
* khello.c
* brief
*  learn to make a kernel moduel
* author yfchai
* version (maj.min)
* date 2018.3.13
*/
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");
//MODULE_AUTHOR("innoink");
//MODULE_DESCRIPTION("hello world module");

static int  khello_init(void)
{
     //printk(KERN_ERR "hello world!");
     printk(KERN_ALERT "hello world!\n");
     return 0;
}

static void  khello_exit(void)
{
     //printk(KERN_EMERG "hello exit!");
     printk(KERN_ALERT "byebye world!\n");
}

module_init(khello_init)
module_exit(khello_exit)
