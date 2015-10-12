/*
 * drivers/core/device.c
 *
 * Copyrigth (c) 2015, Armand Zangue
 */

#include <osirix/device.h>
#include <osirix/dtree.h>

void device_core_init(void)
{
  // somehow run init of all drivers
}

int device_register(struct device * dev)
{
  //add it to device tree
}

int device_unregister( struct device * dev)
{
  //remove it from device tree
}

void devices_list(void)
{

}
