#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>  // Using libi2c-dev for SMBus operations
#include <string.h>
#include "rbpi-i2c.h"

#define I2C_BUS "/dev/i2c-1"  // Replace with your I2C bus path
#define DEVICE_ADDR 0x40      // Replace with your I2C device address

int fd;


int i2c_init(){
   fd = open(I2C_BUS, O_RDWR);
        // Open the I2C bus

    if (fd < 0) {
        perror("Failed to open the I2C bus");
        return EXIT_FAILURE;
    }

    // Set the I2C slave address
    if (ioctl(fd, I2C_SLAVE, DEVICE_ADDR) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        close(fd);
        return EXIT_FAILURE;
    }

    
    
}


int i2c_write_byte(int length, unsigned char *data_bytes){
    struct i2c_msg msgs[1];
    int num_msgs = 1;
    
    // First message: Write command bytes (without stop)
    msgs[0].addr = DEVICE_ADDR;
    msgs[0].flags = 0;  //Write
    msgs[0].len = length;
    msgs[0].buf = data_bytes;
    
    struct i2c_rdwr_ioctl_data ioctl_data;
    ioctl_data.msgs = msgs;
    ioctl_data.nmsgs = num_msgs;

    // Perform combined write and read operation
    if (ioctl(fd, I2C_RDWR, &ioctl_data) < 0) {
        perror("Failed to perform write I2C transaction");
        close(fd);
        return EXIT_FAILURE;
    }
    
} 


int i2c_write_and_read(unsigned char *write_data, int write_len, unsigned char *read_data, int read_len) {
    struct i2c_msg msgs[2];
    struct i2c_rdwr_ioctl_data ioctl_data;

    // Prepare the write message
    msgs[0].addr = DEVICE_ADDR;
    msgs[0].flags = 0;  // Write
    msgs[0].len = write_len;
    msgs[0].buf = write_data;

    // Prepare the read message
    msgs[1].addr = DEVICE_ADDR;
    msgs[1].flags = 1;  // Read
    msgs[1].len = read_len;
    msgs[1].buf = read_data;

    // Prepare the ioctl data structure
    ioctl_data.msgs = msgs;
    ioctl_data.nmsgs = 2;

    // Perform the combined write/read operation
    if (ioctl(fd, I2C_RDWR, &ioctl_data) < 0) {
        perror("Failed to perform combined I2C transaction");
        return -1;
    }

    return 0;}


int i2c_write_long(unsigned char *write_command, int writecomm_len, unsigned char *write_data, int writedata_len) {
    struct i2c_msg msgs[2];
    struct i2c_rdwr_ioctl_data ioctl_data;

    // Prepare the write message
    msgs[0].addr = DEVICE_ADDR;
    msgs[0].flags = 0;  // Write
    msgs[0].len = writecomm_len;
    msgs[0].buf = write_command;

    // Prepare the second write message
    msgs[1].addr = DEVICE_ADDR;
    msgs[1].flags = 0;  // write
    msgs[1].len = writedata_len;
    msgs[1].buf = write_data;

    // Prepare the ioctl data structure
    ioctl_data.msgs = msgs;
    ioctl_data.nmsgs = 2;

    // Perform the combined write/read operation
    if (ioctl(fd, I2C_RDWR, &ioctl_data) < 0) {
        perror("Failed to perform combined I2C transaction");
        return -1;
    }

    return 0;}
