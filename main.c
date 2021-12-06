#include <avr/io.h>
#define F_CPU 11095200UL
#include <avr/delay.h>

//macros to function , bitMath
#define SET_BIT(VAR,BIT_NUM) VAR|=1<<BIT_NUM
#define CLR_BIT(VAR,BIT_NUM) VAR&=~(1<<BIT_NUM)
#define GET_BIT(VAR,BIT_NUM) ((VAR>>BIT_NUM) & 1)

//7seg
#define S7SEG_PORT_DATA    PORTC
#define S7SEG_DDR_DATA     DDRC
#define S7SEG_PORT_ACTIVE  PORTD
#define S7SEG_DDR_ACTIVE   DDRD

void Display_7seg(unsigned char num, unsigned char PIN_ACTIVE/*number of pin*/) {

	/*الفكرة:
	 * هنشغل شاشة واحدة بس و نقفل الباقي , و نبعت الرقم بتاعها
	 * و بعد كدا هنقفل الكل و نشغل الشاشة التانية بس و هنبعت الرقم بتاعها
	 * لو فيه وقت كبير 'ديلاي مثلا' ما بين الخطوات دي هتشوف ان واحدة شغالة و التانية مقفولة و هكذا
	 * بس احنا شغالين بسرعة الكنتررولر ف مش هيبان الفرق
	 * */

	static unsigned char numbers[10] = {
	/*LEDS :  G F E D C B A */
	0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101,
			0b0000111, 0b1111111, 0b1101111 };


	// < for common anode >

	//disable all 7seg
	S7SEG_PORT_ACTIVE = 0x00; 					//step 1
	//enable this 7seg only
	SET_BIT(S7SEG_PORT_ACTIVE, PIN_ACTIVE);		//step 2
	//send data
	S7SEG_PORT_DATA = ~numbers[num];
	//end


	/*
	// < for common cathode >

	//disable all 7seg
	S7SEG_PORT_ACTIVE = 0xff; 					//step 1
	//enable this 7seg only
	CLR_BIT(S7SEG_PORT_ACTIVE, PIN_ACTIVE);		//step 2
	//send data
	S7SEG_PORT_DATA = numbers[num];
	//end
	*/

}

int main(void) {

	//setup directions of mC
	S7SEG_DDR_DATA = S7SEG_DDR_ACTIVE = 0xff;

	while (1) {

		Display_7seg(3, 6);
		_delay_ms(1000);//for see the changes, you should delete it
		Display_7seg(0, 7);
		_delay_ms(1000);//for see the changes, you should delete it

	}

	return 0;
}
