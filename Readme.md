# **Default firmware sketch of NXYI2C (I2C nixie tube control module)**

This sketch is the default sketch written in `I2C nixie tube control module (= NXYI2C)`.

For more information about NXYI2C, please visit [here](https://www.nixielive.com).

If you want to modify the sketch, such as changing the I2C address, please clone this sketch, edit the I2C address, and write it to the NXYI2C.

For more information about NXYI2C, please visit the following link.

* [I2C nixietube control module (NXYI2C)](https://www.nixielive.com/docs/nxyi2c_module)
* [How to upload your sketch to NXYI2C](https://www.nixielive.com/docs/nxyi2c_upload)

# **Sketch Description**

This sketch, after receiving some commands for setting from the I2C host, will light up the numbers according to the setting when it receives the start command.

## **Command Structure**
The command consists of three bytes.
It is defined in `nxyi2c_defs.h` as follows.

```
// command structure
typedef struct _nxyi2c_cmd
{
  unsigned char command;
  signed short value;
} NXYI2C_CMD;
```

* command : 1byte
* value : 2bytes

The types of commands are defined in `nxyi2c_defs.h` as follows.

```
// commands
enum nxyi2c_commands {
    nxyi2c_start = 0,
    nxyi2c_set_pattern = 1,
    nxyi2c_set_duration = 2,
    nxyi2c_set_number = 3,
    nxyi2c_set_dot = 4,
};
```

## **Lighting control command**

### **Set Pattern (command=1)**

Sets the pattern for lighting.
The values and operations to be set for value are as follows.

|`value`|meaning|description|
|:---|:---|:---|
|1|OFF|Do not turn on the light.|
|2|SHOW|Simply lights up.|
|3|FADE IN|The light will gradually brighten. The duration can be set with `Set Duration`.|
|4|FADE OUT|It will gradually get darker. The duration can be set with `Set Duration`.|
|5|FADE CHANGE|The previous number gets progressively darker and the next number gets progressively lighter. The duration can be set with `Set Duration`.|
|6|PATAPATA|Change the numbers one after another to go around 0-9 once.|
|7|FROM CLOUD|The next number will gradually get brighter, and the numbers other than that will gradually get darker. The duration can be set with `Set Duration`.|
|8|INTO CLOUD|It's just the opposite of FROM CLOUD. It's not very useful. I'm sorry about this. The duration can be set with `Set Duration`.|

This is defined in `glow_pattern_defs.h`.

```
enum nxyi2c_patterns {
    nxyi2c_pattern_off = 0,
    nxyi2c_pattern_show = 1,
    nxyi2c_pattern_fade_in = 2,
    nxyi2c_pattern_fade_out = 3,
    nxyi2c_pattern_fade_change = 4,
    nxyi2c_pattern_patapata = 5,
    nxyi2c_pattern_from_cloud = 6,
    nxyi2c_pattern_into_cloud = 7,
};
```

### **Set Duration (command=2)**
`value` : The time from the start of the pattern to its completion, in milliseconds.

### **Set Number (command=3)**
`value` : Specify the next number to be displayed.

### **Set Dot (command=4)**
`value` : Specify the next dot to be displayed. (0:Left dot, 1:Right dot)

### **Start (command=0)**
Start displaying the set pattern, number, or dot. Do not use `value`.

## **How to change the I2C address**
The I2C address of the module can be changed by changing the following line in `nxyi2c-default-firmware.ino`.

```
#define I2C_ADDRESS (20) // NOTE : smbus 0x03(003) - 0x77(119)
```

By default, 20 (0x14) is written, so if you want to connect multiple modules to the same bus, change this value to avoid conflicts.
