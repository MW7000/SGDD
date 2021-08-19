#ifndef  ADC_PRIV_H
#define  ADC_PRIV_H


#define  ADC_Eight_Bit_MODE  0
#define  ADC_Ten_Bit_MODE    2


#define   ADMUX			(*((volatile uint8 *) 0x27))
#define   ADCSRA        (*((volatile uint8 *) 0x26))
#define   ADCH          (*((volatile uint8 *) 0x25))
#define   ADCL          (*((volatile uint8 *) 0x24))
#define   SFIOR         (*((volatile uint8 *) 0x50))


#define  ADC_Prescaler_2	0
#define  ADC_Prescaler_4	3
#define  ADC_Prescaler_8	5
#define  ADC_Prescaler_16	7
#define  ADC_Prescaler_32	9
#define  ADC_Prescaler_64	11
#define  ADC_Prescaler_128	12


#define  ADC_AVCC				0
#define  ADC_External_AREF		3
#define  ADC_Internal_AREF		5


#endif
