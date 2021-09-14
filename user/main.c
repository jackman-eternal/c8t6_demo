#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
//#include "timer.h"
//#include "oled.h"
#include "moniiic.h"
#include "1602_iic_sw.h"
#include<math.h>
#include<string.h>
#include "bsp_adc.h"



unsigned char AD_CHANNEL=0;
unsigned long PH_num=0,PU_V=0;
float PH_Value=0;
u8 ph_temp=0,tu_temp=0;
u16 ph_result=0,tu_result=0;
u16 adc_1,adc_2;
u16 adc_v_1,adc_v_2;

//u8 ISendByte(unsigned char sla,unsigned char c);
//u8 IRcvByte(unsigned char sla);	
//u8 SPIx_ReadWriteByte(u8 TxData);

unsigned char  Tx[20];   //无线发送缓存


// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue;

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal;  




void PH_Value_Conversion()
{
	
	  ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值
	
		PH_Value=-5.7541*ADC_ConvertedValueLocal+16.654;
	
    
	if(PH_Value<=0.0){PH_Value=0.0;}
	if(PH_Value>=14.0){PH_Value=14.0;}
	
		  /*显示电压*/
	Tx[0]=(int)(PH_Value*100)/1000+'0';	
	Tx[1]=(int)(PH_Value*100)%1000/100+'0';
	Tx[2]='.';
	Tx[3]=(int)(PH_Value*100)%100/10+'0';
	Tx[4]=(int)(PH_Value*100)%10+'0';
}

void Display_Data()
{
		//显示PH值	
	 writeOneChar(DATA ,'P');
	 writeOneChar(DATA ,'H');
	 writeOneChar(DATA ,':');
	 writeOneChar(DATA ,Tx[0]);
     writeOneChar(DATA ,Tx[1]);
	 writeOneChar(DATA ,Tx[2]);
	 writeOneChar(DATA ,Tx[3]);
	 writeOneChar(DATA ,Tx[4]);
}
int main(void)
{
		
	delay_init(); 
	LED_INIT(0); 
	init_1602(); 
	ADCx_Init(); 
   // OLED_Init(); 
   // USART1_INIT();
   // TIM3_INIT();
   // TIM4_ENCODER(); 	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2 );
	while(1)
	{
		PH_Value_Conversion();	
		setCursor(0,0);  
	    Display_Data();
		delay_ms(1000);
		
	 
	}	 


}
	




//OLED_ShowString(0,0,"SUCCEED succeed",16);			 //显示字符串
//		OLED_Refresh();		//刷新显存
//		OLED_ShowString(0,20,"SUCCEED succeed",16);			 //显示字符串
//		OLED_Refresh();                              //刷新显存		
//		OLED_ShowString(40,0,"      ",16);          //显示字符串
//		OLED_Refresh();						
//	  speed = TIM4_Encode_Read(); 
//	  delay_ms(500);
//      printf("speed  =  %d \r\n ",speed); 

