/*
 * ESE350_lab2_1.c
 *
 * Created: 1/27/2023 11:13:29 AM
 * Author : erica
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

char c = 0;


void Initialize() {
	cli(); //disable global interrupts for setup
	
	//PB5
	DDRB |= (1<<DDB5); //set to output pin
	PORTB &= ~(1<<PORTB5); // set to low
	
	//PBO
	DDRB &= ~(1<<DDB0); //set to input pin
	//PCICR |= (1<<PCIE0); //enable PCINT0 pin change interrupt
	//PCMSK0 |= (1<<PCINT0); //enable trigger for PCINT0
	
	//timer setup
	TCCR1B &= ~(1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &= ~(1<<CS12);
	
	//set timer 1 to normal
	/*TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1A &= ~(1<<WGM12);
	TCCR1A &= ~(1<<WGM13);*/
	
	//look for rising edge
	TCCR1B |= (1<<ICES1);
	//look for falling edge
	//TCCR1B &= ~(1<<ICES1);
	
	//clear input flag
	TIFR1 |= (1<<ICF1);
	
	//enable the interrupt
	TIMSK1 |= (1<<ICIE1);
	
	sei();//enable global interrupts
}

ISR(TIMER1_CAPT_vect) {
	 
	 //TIFR1 |= (1<<ICF1);
	 //PORTB ^= (1<<PORTB5);
	 if (PINB & (1<<PINB0)) {
		 PORTB |= (1<<PORTB5);
	 } else {
		 PORTB &= ~(1<<PORTB5);
	 }
	 TCCR1B ^= (1<<ICES1);
}

int main(void)
{
	Initialize();
	while (1);
}
