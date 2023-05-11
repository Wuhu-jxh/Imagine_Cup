//
// Created by 神奇bug在哪里 on 2023/5/11.
//

#ifndef IMAGINE_CUP_SETTINGS_H
#define IMAGINE_CUP_SETTINGS_H
///*********串口Debug设置*********/
//#define LOG_LEVEL LOG_DEBUG
//#define UART_ENABLE 1
//#define UART_PORT huart1
/*********测量电路配置*********/
#define CAP_VALUE 0.000001f  //电容值

/********SSD1306配置*********/
#define SSD1306_I2C_ADDR        0x78
#define SSD1306_WIDTH           128
#define SSD1306_HEIGHT          64
#define SSD1306_COM_LR_REMAP    0
#define SSD1306_COM_ALTERNATIVE_PIN_CONFIG    1
#define HARDWARE_I2C hi2c1
#endif //IMAGINE_CUP_SETTINGS_H
