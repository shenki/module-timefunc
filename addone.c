/*
 * Kernel module for testing function call overhead.
 * Copyright 2014 Joel Stanley <joel@jms.id.au>
 * GNU GPLv2
 */
#include <linux/module.h>

unsigned int add_one(unsigned int i)
{
        return i + 1;
}
EXPORT_SYMBOL(add_one);

int init(void)
{
        printk("Added test module\n");
        return 0;
}
module_init(init);
MODULE_LICENSE("GPL");
