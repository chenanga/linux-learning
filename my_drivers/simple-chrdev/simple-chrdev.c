#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

static int char_device_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int char_device_release(struct inode *inode, struct file *file)
{
	return 0;
}

static char content[] = "content-in-file\n";
static ssize_t char_device_read(struct file *file, char __user *buf,
				size_t count, loff_t *ppos)
{
	int actual_len = 0;
	printk("char_device_read(count=%ld, *ppos=%lld)\n", count, *ppos);

	if (*ppos < sizeof(content)) {
		actual_len = min_t(size_t, count, sizeof(content) - *ppos);
		if (copy_to_user(buf, &content[*ppos], actual_len) == 0)
			*ppos += actual_len;
	}

	return actual_len;
}

static const struct file_operations char_device_fops = {
	.owner = THIS_MODULE,
	.open = char_device_open,
	.release = char_device_release,
	.read = char_device_read,
};

struct miscdevice misc = {
	.name = "simple_chrdev",
	.minor = MISC_DYNAMIC_MINOR,
    .fops  = &char_device_fops,
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