This is an example on how to communicate to FPGAs using I2C of Raspberry pi 5 using IOCTL.

Make sure to have i2c enabled on your raspberry pi and install the following dependencies:
sudo apt-get install libi2c-dev

To run the design on your raspberry pi:
1. Run makefile to compile the executable files
2. Run the program using ./rhodz_i2c

The functions are tested on MachXO3LF starter kit. Sample waveform transactions are below:
Device ID Read:
![image](https://github.com/user-attachments/assets/3f613826-e4c4-4563-ada2-e5de3124f135)
Feabits read:
![image](https://github.com/user-attachments/assets/01351cf9-08f3-480e-8f8d-f3658ee71774)

Compared to bitbanging, using the dedicated I²C driver results in a better clock because it utilizes a hardware-generated clock instead of software control. 
Sample I2C transaction using the terminal are below:
![image](https://github.com/user-attachments/assets/d0aa7401-cccf-4d5a-8f8e-ac50729090e5)

Some challenges I encountered: 
*I cannot manually send start and stop conditions.
*Each call of the ioctl function automatically generates a start and stop condition.

When communicating with Lattice devices, there should be no stop condition after a read command during a read operation, as improper setup of ioctl can cause readout failures. To ensure correct readout, I used the i2c_write_and_read() function, which performs a write followed by a read operation. This is done by defining an i2c_rdwr_ioctl_data structure and specifying the sequence of operations. See below for my function:

![image](https://github.com/user-attachments/assets/79c5aee9-9000-4811-882a-879073371487)

In the code above, two messages are defined: one for the write operation and one for the read operation. After defining the structure, it is used to initiate the I2C transaction with the ioctl() function.


