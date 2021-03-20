/**************************************************************************************************
  Filename:       hal_oled.c
  Revised:        $Date: 2012-09-30 16:36:36 -0700 (Sun, 30 Sep 2012) $
  Revision:       $Revision: 31658 $

  Description:    This file contains the interface to the HAL oled Service.

**************************************************************************************************/

/**************************************************************************************************
 *                                           INCLUDES
 **************************************************************************************************/
#include "hal_types.h"
#include "hal_oled.h"
#include "string.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h> 
#include "hal_oledfont.h"
   

/**************************************************************************************************
 *                                          CONSTANTS
 **************************************************************************************************/


/**************************************************************************************************
 *                                           MACROS
 **************************************************************************************************/


/**************************************************************************************************
 *                                       LOCAL VARIABLES
 **************************************************************************************************/
//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 
uint8 OLED_GRAM[128][8];	 
static int fd = -1;
/**************************************************************************************************
 *                                       FUNCTIONS - API
 **************************************************************************************************/
void HalOledSendCmd(uint8 cmd);
void HalOledSendData(uint8 data);
uint32 HalOledPosition(uint8 m,uint8 n);

void HalOledSendCmd(uint8 cmd)
{
    uint8 cmds[2] = {0x00,cmd};
	write(fd,cmds,2);
}

void HalOledSendData(uint8 data)
{
    uint8 cmds[2] = {0x40,data};
	write(fd,cmds,2);
}

void MicroWait(uint32 delays)
{
	usleep(delays);
}

void HalOledInit(int fds)
{
	fd = fds;
    MicroWait(1000);
    
    HalOledSendCmd(0xAE); //关闭显示

    HalOledSendCmd(0xD5); //设置时钟分频因子,震荡频率  
    HalOledSendCmd(0x80); //[3:0],分频因子;[7:4],震荡频率     
    HalOledSendCmd(0xA8); //设置驱动路数  
    HalOledSendCmd(0X3F); //默认0X3F(1/64)     
    
    HalOledSendCmd(0x40); //设置显示开始行 [5:0],行数.  
    
    HalOledSendCmd(0xA1); // Remap 
    HalOledSendCmd(0xC0); // 设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
    
    HalOledSendCmd(0xDA); //设置COM硬件引脚配置 
    HalOledSendCmd(0x12); //[5:4]配置         
    
    HalOledSendCmd(0x81); //对比度设置  
    HalOledSendCmd(0xEF); // 1~255;默认0X66(亮度设置,越大越亮)
    
    HalOledSendCmd(0xD9); //设置预充电周期 
    HalOledSendCmd(0xF1); //[3:0],PHASE 1;[7:4],PHASE 2;
    
    HalOledSendCmd(0xDB); //设置VCOMH 电压倍率  
    HalOledSendCmd(0x30); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;  
    
    HalOledSendCmd(0xB0); // set page address    
    HalOledSendCmd(0xA4); //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏) 
    HalOledSendCmd(0xA6); //设置显示方式;bit0:1,反相显示;0,正常显示                  
    
    HalOledSendCmd(0xD3); //设置显示偏移 
    HalOledSendCmd(0X00); //默认为0     
    
    HalOledSendCmd(0x00); ////set lower column addres 
    HalOledSendCmd(0x10); //set higher column address 
  
    HalOledSendCmd(0x20); //设置内存地址模式 
    HalOledSendCmd(0x02); //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
    HalOledSendCmd(0xA1); //段重定义设置,bit0:0,0->0;1,0->127;  
    
    HalOledSendCmd(0x8d); //电荷泵设置
    HalOledSendCmd(0x14); //bit2，开启/关闭     
    
    HalOledSendCmd(0xAF); //开启显示

    HalOledDisplayClear();
}

//更新显存到LCD		 
void HalOledRefreshGram(void)
{
	uint8 i,n;
    HalOledSendCmd(0xA1); // Remap
	for(i=0;i<8;i++)  
	{  
		HalOledSendCmd (0xb0+i);    //设置页地址（0~7）
		HalOledSendCmd (0x00);      //设置显示位置—列低地址
		HalOledSendCmd (0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)HalOledSendData(OLED_GRAM[n][i]); 
	}   
}
	  	  
//开启OLED显示    
void HalOledDisplayOn(void)
{
	HalOledSendCmd(0X8D);  //SET DCDC命令
	HalOledSendCmd(0X14);  //DCDC ON
	HalOledSendCmd(0XAF);  //DISPLAY ON
}

//关闭OLED显示     
void HalOledDisplayOff(void)
{
	HalOledSendCmd(0X8D);  //SET DCDC命令
	HalOledSendCmd(0X10);  //DCDC OFF
	HalOledSendCmd(0XAE);  //DISPLAY OFF
}

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void HalOledDisplayClear(void)  
{  
	uint8 i,n;  
    HalOledSendCmd(0xA1); // Remap
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	HalOledRefreshGram();//更新显示
}

//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空				   
void HalOledDrawPoint(uint8 x,uint8 y,uint8 t)
{
	uint8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}

//x1,y1,x2,y2 填充区域的对角坐标
//确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,清空;1,填充	  
void HalOledFill(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 dot)  
{  
	uint8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)HalOledDrawPoint(x,y,dot);
	}													    
	HalOledRefreshGram();//更新显示
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 12/16/24
void HalOledShowChar(uint8 x,uint8 y,uint8 chr,uint8 size,uint8 mode)
{      			    
	uint8 temp,t,t1;
	uint8 y0=y;
	uint8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
	chr=chr-' ';//得到偏移后的值		 
    for(t=0;t<csize;t++)
    {   
		if(size==12)temp=asc2_1206[chr][t]; 	 	//调用1206字体
		else if(size==16)temp=asc2_1608[chr][t];	//调用1608字体
		else if(size==24)temp=asc2_2412[chr][t];	//调用2412字体
		else return;								//没有的字库
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)HalOledDrawPoint(x,y,mode);
			else HalOledDrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

//m^n函数
uint32 HalOledPosition(uint8 m,uint8 n)
{
	uint32 result=1;	 
	while(n--)result*=m;    
	return result;
}	
	  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void HalOledShowNum(uint8 x,uint8 y,uint32 num,uint8 len,uint8 size)
{         	
	uint8 t,temp;
	uint8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/HalOledPosition(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				HalOledShowChar(x+(size/2)*t,y,' ',size,1);
				continue;
			}else enshow=1; 
		 	 
		}
	 	HalOledShowChar(x+(size/2)*t,y,temp+'0',size,1); 
	}
} 

//显示字符串
//x,y:起点坐标  
//size:字体大小 
//*p:字符串起始地址 
void HalOledShowString(uint8 x,uint8 y,const uint8 *p,uint8 size)
{	
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {       
        if(x>(128-(size/2))){x=0;y+=size;}
        if(y>(64-size)){y=x=0;HalOledDisplayClear();}
        HalOledShowChar(x,y,*p,size,1);	 
        x+=size/2;
        p++;
    }  
}

/**************************************************************************************************
**************************************************************************************************/



