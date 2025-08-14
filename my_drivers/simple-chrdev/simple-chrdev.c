#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>

struct miscdevice misc = {
    .name = "simple_chrdev",
    .minor = MISC_DYNAMIC_MINOR,
};

static int hello_init(void)
{
    printk("hello.ko: hello simple_chrdev:)\n");
    return misc_register(&misc);
}

static void hello_exit(void)
{
    printk("hello.ko: byebye simple_chrdev!\n");
    misc_deregister(&misc);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("a simple_chrdev module");