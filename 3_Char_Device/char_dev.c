/* Register char device LKM*/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rachana Kulkarni");
MODULE_DESCRIPTION("Linux Kernel Module registering a char device");

static int major;

static ssize_t my_read(struct file *f, char __user *u, size_t l, loff_t *o)
{
        printk("char_dev - Read was called\n");
        return 0;
}

static struct file_operations fops = {
        .read = my_read
};

/*init function*/
static int __init my_init(void)
{
        major = register_chrdev(0,"char_dev",&fops);
        if(major<0)
        {
                printk("char_dev - Error registering character device\n");
                return major;
        }
        printk("char_dev -  Device registered, Major NO: %d\n",major);
        return 0;
}

/*exit function*/
static void __exit my_exit(void)
{
        unregister_chrdev(major, "char_dev");
        printk("Goodbye, Creata!\n");
}

module_init(my_init);
module_exit(my_exit);
