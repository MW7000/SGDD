#ifndef  ADC_INT_H
#define  ADC_INT_H


#define 	OK  	1
#define 	NOK		0

void ADC_vid_init(void);

void ADC_vid_Enable(void);

void ADC_vid_Disable(void);

void ADC_vid_Enable_Interrupt(void);

void ADC_vid_Disable_Interrupt(void);

void ADC_vid_CallBack(void (*copy_ptr_fun) (void));


uint8 ADC_uint8_Get_conversion_Value(uint8 channel ,uint8 * result ); 		// 8 Bit Mode
uint8 ADC_uint8_Get_Last_Value(void);


uint8 ADC_uint16_Get_conversion_Value(uint8 channel ,uint16 *result ); 		// 10 Bit Mode
uint16 ADC_uint16_Get_Last_Value(void);



#endif
