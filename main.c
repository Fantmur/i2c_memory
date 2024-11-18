#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "esp_log.h"
#include "sdkconfig.h"
#include "at24c.c"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_err.h"


//------------------------------------------------
#define I2C_ADDRESS  0x50
//------------------------------------------------
uint8_t rd_value[16] = {0};
//uint8_t wr_value[16] = {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
//                        0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F};
// uint8_t wr_value[16] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x24,0x00,0xA5,0x1D,0x00,0xFF,0xFF};   // MAC                       
uint8_t wr_value[16] = {0x06,0xA5,0x1D,0x00,0x09,0x50,0x69,0x74,0x32,0x34,0x30,0x37,0x36,0x38,0xFF,0xFF};   // Pit240768                        
// uint8_t wr_value[16] = {0xFF,0xFF,0xFF,0xFF,0x0A,0x4D,0x4F,0x48,0x41,0x56,0x45,0x2D,0x4F,0x42,0x44,0xFF};   // MOHAVE-OBD                     

//------------------------------------------------


static const char *TAG = "main";

void app_main(void)
{
  uint16_t i=0;
  uint16_t k=0;
  uint16_t l=0; //Количество линий для обработки (чтения)
  
  i2c_port_t i2c_port = I2C_NUM_0;
  esp_err_t ret;
  ret = i2c_master_driver_initialize(i2c_port, I2C_ADDRESS, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO);
  ESP_LOGI (TAG, "Init: %d", ret);
//  AT24C_WriteBytes (i2c_port, 0x0F90, wr_value, 16);
  for(l=0;l<256;l++){
     AT24C_ReadBytes(i2c_port, l*16, rd_value, 16);
     printf("0x00");
     printf("%04X ", l*16);
     printf("| ");
     for(k=0;k<4;k++) {
       for(i=0;i<4;i++) { printf("%02X ",rd_value[k*4+i]);  }
       printf("  ");
      }
     printf("\r\n");
   }  
     
//-------------------------------------------------------------------------	
    while (1) {
       vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
