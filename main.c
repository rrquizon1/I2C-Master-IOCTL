#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>  // Using libi2c-dev for SMBus operations
#include <string.h>
#include "rbpi-i2c.h"

int main() {
  
    unsigned char write_buf[4] = { 0xE0, 0x00, 0x00, 0x00  }; // Command bytes to send (E0 00 00 00)
    unsigned char write_buf1[4] = { 0xC6, 0x08, 0x00, 0x00 }; // ISC ENABLE target internal flash
    unsigned char write_buf2[4] = { 0xFB ,0x00, 0x00, 0x00 }; // Read Feabits
    unsigned char read_buf2[2]; // Buffer to store read data
    unsigned char read_buf[4]; // Buffer to store read data
    unsigned char global_write_buf[4];
    int global_length=4;


    
    i2c_init();
    
// An If condition that checks if a read command is used. In this example 0xE0 and 0xFB are read commands. It is important to know if a command is write or read for proper set-up of struct
    if ((write_buf[0]==0xE0 )|| write_buf[0]==(0xFB)){ 
        memcpy(global_write_buf, write_buf, sizeof(write_buf)); //Prepares the read command at global_write_buf
    
        }
    
   for (int i = 0; i < 4; i++) {
       printf("0x%02X ",global_write_buf[i]);
       printf("\n");
   }
//i2c read operation   
    i2c_write_and_read(global_write_buf,global_length,read_buf,4); //uses global_write_buf to start the i2c transaction and uses read_buf to store read data.
        printf("Device ID Read: ");
    for (int i = 0; i < 4; i++) {
        printf("0x%02X ", read_buf[i]);
    }
    printf("\n");
    
    
    i2c_write_byte (4,write_buf1);//simple i2c write operation.
    

    if (write_buf2[0]==(0xE0) || write_buf2[0]==(0xFB)){
        memcpy(global_write_buf, write_buf2, sizeof(write_buf2));
    
        }
    
   for (int i = 0; i < 4; i++) {
       printf("0x%02X ",global_write_buf[i]);
       printf("\n");
   }
   
    i2c_write_and_read(global_write_buf,global_length,read_buf2,4);
        printf("Feabits Read: ");
    for (int i = 0; i < 2; i++) {
        printf("0x%02X ", read_buf2[i]);
    }
    printf("\n");




    // Close the I2C bus
    close(fd);
    return EXIT_SUCCESS;
}
