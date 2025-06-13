/*Manual character device registeration*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rachana Kulkarni");
MODULE_DESCRIPTION("LKM to manually register a character device");

static dev_t dev_nr;
static struct cdev my_cdev;

static ssize_t my_read(struct file *f, char __user *u, size_t l, loff_t *o)
{
        pr_info("manual_chardev - Read was called\n");
        return 0;
}

static struct file_operations fops = {
        .read = my_read
};

static int __init my_init(void)
{
        int status;
#ifdef STATIC_DEVNR
        dev_nr = STATIC_DEVNR;
        status = register_chrdev_region(dev_nr, MINORMASK + 1, "manual_chardev");
#else
        status = alloc_chrdev_region(&dev_nr, 0, MINORMASK + 1, "manual_chardev");
#endif
        if (status) {
                pr_err("manual_chardev - Error reserving the region of device numbers\n");
                return status;
        }

        cdev_init(&my_cdev, &fops);
        my_cdev.owner = THIS_MODULE;

        status = cdev_add(&my_cdev, dev_nr, MINORMASK + 1);
        if (status) {
                pr_err("manual_chardev - Error adding cdev\n");
                goto free_devnr;
        }

        pr_info("manual_chardev - Registered a character device for Major %d starting with Minor %d\n", MAJOR(dev_nr), MINOR(dev_nr));
        return 0;

free_devnr:
        unregister_chrdev_region(dev_nr, MINORMASK + 1);
        return status;
}

static void __exit my_exit(void)
{
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_nr, MINORMASK + 1);
}

module_init(my_init);
module_exit(my_exit);
