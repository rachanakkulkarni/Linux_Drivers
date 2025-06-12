/* open release LKM*/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rachana Kulkarni");
MODULE_DESCRIPTION("Linux Kernel Module registering a char device");

static int major;

static int my_open(struct inode *inode,struct file *filep)
{
        pr_info("open_release - Major: %d Minor: %d\n", imajor(inode), iminor(inode));
        pr_info("open_release - filep->f_pos: %lld\n",filep->f_pos);
        pr_info("open_release - filep->f_mode: 0x%x\n",filep->f_mode);
        pr_info("open_release - filep->f_flags: 0x%x\n",filep->f_flags);

        return 0;

}

static int my_release(struct inode *inode, struct file *filep)
{
        pr_info("open_release - File is closed\n");
        return 0;
}

static struct file_operations fops = {
        .open = my_open,
        .release = my_release,
};

/*init function*/
static int __init my_init(void)
{
        major = register_chrdev(0,"char_dev",&fops);
        if(major<0)
        {
                pr_err("open_release - Error registering character device\n");
                return major;
        }
        pr_info("char_dev -  Device registered, Major NO: %d\n",major);
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
