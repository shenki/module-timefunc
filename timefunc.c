#include <linux/module.h>

int init(void)
{
        return 0;
}
module_init(init);
MODULE_LICENSE("GPL");
