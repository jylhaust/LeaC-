#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "timer.h"
#include "adc.h"
#define MaxVel   100
#define MinVel   20
u8 tab_ZiFu[] = {"0123456789"};
u8 Buffer[5];

//+++++++++++++++++++++++++++++++++++++++++++++++
float		        KP = 0.8, KI = 0.2, KD = 0.05;
float        		e1 = 0, e2 = 0, e3 = 0, uk = 0, duk = 0;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

u16 	SET_V = 180;		//
//---------------------------------------------------------
int g_nDelayTimeCnt = 200;
float g_fOutAdd = 0;
float g_fDelayTable[300] = 0;
float g_fOutputVol = 0.f;
float g_ControlVel = 0.f, g_ControlVel_M = 0.f;
float g_fDltVol = 0.f;
float g_fCurError = 0.f, g_fpreError = 0.f;
float g_fKp = 1 , g_fTc = 1 , g_fDs = 1;
//---------------------------------------------------------
int main(void)
{

	u16 adcx;
	float AD_Value;

	Stm32_Clock_Init(9); 	//ÏµÍ³Ê±ÖÓÉèÖÃ
	delay_init(72);	     	//ÑÓÊ±³õÊ¼»¯
	//uart_init(72,9600);	 	//´®¿Ú³õÊ¼»¯Îª9600
	LED_Init();		  	 		//³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼þ½Ó¿Ú
	Adc_Init();		  		//ADC³õÊ¼»¯
	TIM1_PWM_Init(3599, 0);	//²»·ÖÆµ¡£PWMÆµÂÊ=72000/(899+1)=80Khz
	//LED0_PWM_VAL=100;
	while (1)
	{
		adcx = Get_Adc_Average(ADC_CH1, 10);
		AD_Value = (float)adcx * (3.3 / 4096);
		adcx = (u16)(AD_Value * 211);
		e1 = SET_V - adcx;
		//***********************
		uk = PpiProcess(e1);
		if (uk >= 3000)uk = 3000;
		if (uk <= 10)  uk = 10;

		LED0_PWM_VAL = (u16)uk;


	}
}


float PpiProcess(float fInfVel)
{
	float fresult = 0;
	g_fCurError = fInfVel；
	              g_fDltVol = (g_fCurError - g_fpreError) / (g_fTc * g_fDs) + (g_fCurError / (g_fKp * g_fTc * g_fDs)) \
	                          -(g_fDelayTable[0] - g_fDelayTable[g_nDelayTimeCnt]) / (g_fTc * g_fDs);
	g_ControlVel_M  = g_ControlVel + g_fDltVol;
	g_ControlVel = g_ControlVel_M;
	g_fDelayTable[0] = g_ControlVel;
	g_fpreError = g_fCurError;
	fresult = g_fCurError;
	return fresult;
}