/**************************************************************************************************
  Filename:       hal_oled.h
  Revised:        $Date: 2007-07-06 10:42:24 -0700 (Fri, 06 Jul 2007) $
  Revision:       $Revision: 13579 $

  Description:    This file contains the interface to the oled Service.

**************************************************************************************************/

#ifndef HAL_OLED_H
#define HAL_OLED_H

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************************************
 *                                          INCLUDES
 **************************************************************************************************/
#include "hal_types.h"
  
/**************************************************************************************************
 *                                         CONSTANTS
 **************************************************************************************************/
#define HAL_OLED_FONT_TYPE_SIZE_12     12
#define HAL_OLED_FONT_TYPE_SIZE_16     16
#define HAL_OLED_FONT_TYPE_SIZE_24     24

#define HAL_OLED_DISPLAY_MODE_0         0
#define HAL_OLED_DISPLAY_MODE_1         1

#define BIRGTHNESS             //OLED的亮度  00~255
#define OLED_WIDTH          128
#define OLED_HIGH           (8*8)

#define I2C_OLED_ADDR       0x3c 
/**************************************************************************************************
 *                                          MACROS
 **************************************************************************************************/


/**************************************************************************************************
 *                                         TYPEDEFS
 **************************************************************************************************/


/**************************************************************************************************
 *                                     GLOBAL VARIABLES
 **************************************************************************************************/


/**************************************************************************************************
 *                                     FUNCTIONS - API
 **************************************************************************************************/
extern void HalOledInit(int fds);
extern void HalOledDisplayOn(void);
extern void HalOledDisplayOff(void);
extern void HalOledRefreshGram(void);  		    
extern void HalOledDisplayClear(void);

extern void HalOledDrawPoint(uint8 x,uint8 y,uint8 t);
extern void HalOledFill(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 dot);
extern void HalOledShowChar(uint8 x,uint8 y,uint8 chr,uint8 size,uint8 mode);
extern void HalOledShowNum(uint8 x,uint8 y,uint32 num,uint8 len,uint8 size);
extern void HalOledShowString(uint8 x,uint8 y,const uint8 *p,uint8 size);
/**************************************************************************************************
**************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
