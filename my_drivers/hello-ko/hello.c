#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int hello_init(void)
{
    printk("hello.ko: hello :) \n");
    return 0;
}

static void hello_exit(void)
{
    printk("hello.ko: byebye! \n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("a hello module");