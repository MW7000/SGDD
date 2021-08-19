#include  "STD_Types.h"
#include  "BIT_MATH.h"

#include  "ADC_int.h"
#include  "ADC_priv.h"
#include  "ADC_config.h"


void (*Ptr_CallBack_fun) (void);



void ADC_vid_init(void){

// prescaler mode

#if (ADC_Prescaler_MODE==ADC_Prescaler_2)

	CLEAR_BIT(ADCSRA,0);
	CLEAR_BIT(ADCSRA,1);
	CLEAR_BIT(ADCSRA,2);

#elif (ADC_Prescaler_MODE==ADC_Prescaler_4)

	CLEAR_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	CLEAR_BIT(ADCSRA,2);

#elif (ADC_Prescaler_MODE==ADC_Prescaler_8)

	SET_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	CLEAR_BIT(ADCSRA,2);

#elif (ADC_Prescaler_MODE==ADC_Prescaler_16)

	CLEAR_BIT(ADCSRA,0);
	CLEAR_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);

#elif (ADC_Prescaler_MODE==ADC_Prescaler_32)

	SET_BIT(ADCSRA,0);
	CLEAR_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);

#elif (ADC_Prescaler_MODE==ADC_Prescaler_64)

	CLEAR_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);

#elif (ADC_Prescaler_MODE==ADC_Prescaler_128)

	SET_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);

#endif


// Vref	MODE

#if (ADC_V_Reference_MODE==ADC_External_AREF)

	CLEAR_BIT(ADMUX,6);
	CLEAR_BIT(ADMUX,7);

#elif (ADC_V_Reference_MODE==ADC_AVCC)

	SET_BIT(ADMUX,6);
	CLEAR_BIT(ADMUX,7);

#elif (ADC_V_Reference_MODE==ADC_Internal_AREF)

	SET_BIT(ADMUX,6);
	SET_BIT(ADMUX,7);

#endif



#if (ADC_MODE==ADC_Eight_Bit_MODE)

	SET_BIT(ADMUX,5);

#else

	CLEAR_BIT(ADMUX,5);

#endif

	CLEAR_BIT(ADCSRA , 3);
	CLEAR_BIT(ADCSRA , 4);

	SET_BIT(ADCSRA,7);  	// 12 CLOCK CYCLES

}


void ADC_vid_CallBack(void (*copy_ptr_fun) (void)){

	Ptr_CallBack_fun = copy_ptr_fun ;

}


#if (ADC_MODE==ADC_Eight_Bit_MODE)

uint8 ADC_uint8_Get_conversion_Value(uint8 channel ,uint8 * result ){

ADMUX = ADMUX & 0b11100000;

ADMUX = ADMUX | channel ;

SET_BIT(ADCSRA,6);    	// starting conversion

	if(GET_BIT(ADCSRA,3)==1){

		return NOK ;

	}else{

		while((GET_BIT(ADCSRA,4))==0);
		SET_BIT(ADCSRA,4);   				// clearing the Flag
		*result = ADCH;

		return OK;
	}


}

uint8 ADC_uint8_Get_Last_Value(void){

	return ADCH;

}

#else

uint8 ADC_uint16_Get_conversion_Value(uint8 channel ,uint16 *result ){

uint8 HIGH,LOW;

	ADMUX = ADMUX & 0b11100000;

	ADMUX = ADMUX | channel ;

	SET_BIT(ADCSRA,6);

	if(GET_BIT(ADCSRA,3)==1){

		return NOK ;

	}else{

		while((GET_BIT(ADCSRA,4))==0);
		SET_BIT(ADCSRA,4);					// clearing the Flag

		LOW = ADCL;
		HIGH = ADCH;

		*result = (((0b00000011 & HIGH)<<8)|LOW);

		return OK;
	}

}

uint16 ADC_uint16_Get_Last_Value(void){

	uint8 HIGH,LOW;
	uint16 result;

	LOW = ADCL;
	HIGH = ADCH;

	result = (((0b00000011 & HIGH)<<8)|LOW);

	return result;
}

#endif

void ADC_vid_Enable(void){

	SET_BIT(ADCSRA,7);
}

void ADC_vid_Disable(void){

	CLEAR_BIT(ADCSRA,7);
}

void ADC_vid_Enable_Interrupt(void){

	SET_BIT(ADCSRA,3);
}

void ADC_vid_Disable_Interrupt(void){

	CLEAR_BIT(ADCSRA,3);
}


void __vector_16(void) __attribute__((signal,used));
void __vector_16(void){

	Ptr_CallBack_fun();
}


