/*
 * Stop Watch.c
 * Created on: Sep 17, 2023
 * Author: Yosif Adel
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
unsigned char second1 = 0, second2 = 0;
unsigned char minute1 = 0, minute2 = 0;
unsigned char hour1 = 0, hour2 = 0;
void Timer1_Init(void){
	TCNT1 = 0;  					 // set the initial count of the timer to ZERO
	TCCR1A = (1<<FOC1A);			 // activate that not PWM
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12); // Compare mode , 1024 Prescalar
	TIMSK|=(1<<OCIE1A);
	/*
	 	To calcualte 1second -> F = 1Hz
	    F = F(CPU)/N(1+x) = 1Mhz/ N(1+x) try different prescalar
	    N = 64  , x = 15624
	    N = 256 , x = 3905
	    N = 1024 , x = 976
	    so the better is N = 1024
	*/
	OCR1A = 976;					 			 // Set the Compare value to 15624
	SREG |= (1<<7);
}
void INT0_Init(void){
	DDRD &= ~(1<<PD2); 		// set pin PD2 as Input [button to reset] [internal pull-up]
	PORTD |= (1<<PD2); 		// activate internal pull up at PD2
	GICR |= (1<<INT0);		// set to INT0
	MCUCR |= (1<<ISC01);	// Falling Edge
	SREG  |= (1<<7);    	// set I-bit = 1
}
void INT1_Init(void){
	DDRD &= ~(1<<PD3);  // set pin PD3 as Input [button to pause] [external pull-down]
	GICR |= (1<<INT1);  // set to INT1 bit 7 [button to pause] [external pull-down]
	MCUCR |= (1<<ISC11) | (1<<ISC10); // Rising Edge
	SREG  |= (1<<7);    // set I-bit = 1
}
void INT2_Init(void){
	DDRB &= ~(1<<PB2); 	// set pin PB2 as Input [button to resume] [internal pull-up]
	PORTB |= (1<<PB2); 	// activate internal pull up at PB2
	GICR |= (1<<INT2);	// set to INT2 bit 5
	// ISC2 Zero -> Falling Edge
	SREG  |= (1<<7);    // set I-bit = 1
}
ISR(TIMER1_COMPA_vect){
	second1++;
	if(second1 == 10){
		second1=0;
		second2++;
	}
	if(second2 == 6){
		//		second1 = 0;
		second2=0;
		minute1++;
	}
	if(minute1==10){
		minute1=0;
		minute2++;
	}
	if(minute2 == 6){
		//		minute1 = 0;
		minute2=0;
		hour1++;
	}
	if(hour1==10){
		hour1=0;
		hour2++;
	}
	if(hour2 == 6){
		//		hour1 = 0;
		hour2=0;
	}
}
ISR(INT0_vect){
	// reset seconds to zero
	second1 = 0;
	second2 = 0;
	// reset minutes to zero
	minute1 = 0;
	minute2 = 0;
	// reset hours to zero
	hour1 = 0;
	hour2 = 0;
	// if you pause then reset the 7segment will reset and start counting
	if(TCCR1A==0){
		TCCR1A = (1<<FOC1A);			 // activate that not PWM
		TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12); // Compare mode , 1024 Prescalar
	}

}
ISR(INT1_vect){
	// pause the clock of the timer
	TCCR1A = 0;
	TCCR1B = 0;
}
ISR(INT2_vect){
	// resume the clock of the timer
	TCCR1A = (1<<FOC1A);			 // activate that not PWM
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12); // Compare mode , 1024 Prescalar
}
int main(void){
	// pins [A0 A1 A2 A3 A4 A5] to 7-segments[hour2 hour1 minute2 minute1 second2 second1]
	DDRC |= 0x0F; // make the first 4 pins as output connected to the decoder
	DDRA |= 0b00111111; 	// set as OUTPUTs
	PORTA &= 0b11000000;	// make the default OFF
	PORTC &= 0xF0;
	SREG |= (1<<7);
	INT0_Init();
	INT1_Init();
	INT2_Init();
	Timer1_Init();
	while(1){
		// each 7segment will be ON for 2ms and OFF for 10ms so i can't notice the difference
		PORTA = (1<<PA5);	// display the first 7-segment [second 1]
		PORTC = (PORTC & 0xF0)|(second1 & 0x0F); // display its value
		_delay_ms(2);
		PORTA = (1<<PA4);	// display the second 7-segment [second 2]
		PORTC = (PORTC & 0xF0)|(second2 & 0x0F); // display its value
		_delay_ms(2);
		PORTA = (1<<PA3);	// display the third 7-segment [minute 1]
		PORTC = (PORTC & 0xF0)|(minute1 & 0x0F); // display its value
		_delay_ms(2);
		PORTA = (1<<PA2);	// display the fourth 7-segment [minute 2]
		PORTC = (PORTC & 0xF0)|(minute2 & 0x0F); // display its value
		_delay_ms(2);
		PORTA = (1<<PA1);	// display the fifth 7-segment [hour 1]
		PORTC = (PORTC & 0xF0)|(hour1 & 0x0F); // display its value
		_delay_ms(2);
		PORTA = (1<<PA0);	// display the sixth 7-segment [hour 2]
		PORTC = (PORTC & 0xF0)|(hour2 & 0x0F); // display its value
		_delay_ms(2);
	}
}
