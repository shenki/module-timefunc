/*
 * Kernel module for testing function call overhead.
 * Copyright 2014 Joel Stanley <joel@jms.id.au>
 * GNU GPLv2
 *
 * Creates a debugfs file at /sys/kernel/debugfs/timefunc
 *
 * To perform benchmark:
 *   # insmod addone.ko
 *   # echo 1 > /sys/kernel/debugfs/timefunc
 *
 * Display results:
 *   # cat /sys/kernel/debugfs/timefunc
 *   <number of ns to run benchmark>
 *
 */

#include <linux/debugfs.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

static struct dentry *file;
static s64 last;

static unsigned long iters = 100000000;
module_param(iters, ulong, 0444);

/* From addone.ko */
extern int add_one(unsigned int i);

static ssize_t write(struct file *file, const char __user *userbuf,
                     size_t count, loff_t *ppos)
{
        ktime_t start, end;
        int counter;

        start = ktime_get();
        for (counter = 0; counter < iters; counter = add_one(counter));
        end = ktime_get();

        last = ktime_to_ns(ktime_sub(end, start));

        return count;
}

static ssize_t read(struct file *file, char __user *buf,
                                 size_t count, loff_t *ppos)
{
        ssize_t size;
        char str[64];

        size = scnprintf(str, sizeof(str), "%lld\n", last);

        return simple_read_from_buffer(buf, size, ppos, str, size);
}


static const struct file_operations fops = {
        .owner = THIS_MODULE,
        .read = read,
        .write = write,
};

int init(void)
{
        last = 0;
        file = debugfs_create_file("functime", 0660, NULL, &last, &fops);
        if (!file)
                return -ENODEV;
        return 0;
}

void remove(void)
{
        debugfs_remove(file);
}
module_init(init);
MODULE_LICENSE("GPL");
