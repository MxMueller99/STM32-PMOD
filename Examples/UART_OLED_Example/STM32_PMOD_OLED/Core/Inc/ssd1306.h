/*
 * ssd1306.h
 *
 *  Created on: Jul 22, 2025
 *      Author: max
 */

#ifndef INC_SSD1306_H_
#define INC_SSD1306_H_

#include "stm32g0xx_hal.h"

/* public driver API ------------------------------------------------------- */
void     ssd1306_init(I2C_HandleTypeDef *hi2c);
void     ssd1306_fill(uint8_t pattern);
void     ssd1306_draw_string(uint8_t x, uint8_t y,  const char *s);
void     ssd1306_update(void);

#endif /* INC_SSD1306_H_ */
