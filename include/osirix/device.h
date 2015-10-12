#ifndef _DEVICE_H
#define _DEVICE_H

/*
 * Block data structure for block devices
 */
typedef struct block_data {
  unsigned int size;
  void *data;
} block_data_t;

/*
 * functions each device driver has to provide to be accessible via
 * the driver abstraction layer interface, which permit all device
 * to be accessed in the same way.
 */
struct dev_ops {

  /*
   * Open device for access
   */
  unsigned (*open) (unsigned);

  /*
   * Close device
   */
  int (*close) (unsigned);

  /*
   * Write operations
   */
  union {

    void (*byte) (char);

    void (*bit) (char);

    void (*block) (unsigned, block_data_t *);

  } write;

  /*
   * Read operations
   */
  union {

    char (*byte) (void);

    char (*bit) (void);

    block_data_t * (*block) (void);

  } read;

};

struct device {

  /*
   *  The name of the device driver. Example: "LED driver"
   */
  char name[25];

  /*
   * Description of the device driver
   */
  char description[50];

  /*
   * A unique identifier for the device
   */
  unsigned int driver_id;

  /*
   * Device operations
   */
  struct dev_ops dops;

}

int device_register(struct device * dev);

int device_unregister(struct device * dev);

#endif /* _DEVICE_H */
