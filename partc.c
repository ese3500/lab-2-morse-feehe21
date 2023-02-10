/*
 * ESE350_lab2_1.c
 *
 * Created: 1/27/2023 11:13:29 AM
 * Author : erica
 */ 
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <stdlib.h>
#include <stdio.h>

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "inc/uart.h"

char c = 0;
int lastPress = 0;
char numOverflows = 0;
char String[25];

void Initialize() {
	cli(); //disable global interrupts for setup
	
	//PB5 - onboard LED
	DDRB |= (1<<DDB5); //set to output pin
	PORTB &= ~(1<<PORTB5); // set to low
	
	//PB1 pin 9
	DDRB |= (1<<DDB1); //set to output pin
	PORTB &= ~(1<<PORTB1); // set to low
	//PB2 - pin 10
	DDRB |= (1<<DDB2); //set to output pin
	PORTB &= ~(1<<PORTB2); // set to low
	
	//PBO
	DDRB &= ~(1<<DDB0); //set to input pin
	//PCICR |= (1<<PCIE0); //enable PCINT0 pin change interrupt
	//PCMSK0 |= (1<<PCINT0); //enable trigger for PCINT0
	
	//timer setup
	TCCR1B &= ~(1<<CS10);
	TCCR1B |= (1<<CS12);
	TCCR1B &= ~(1<<CS11);
	//set prescaler to 256
	
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
	
	//enables interrupt for timer overflow
	TIMSK1 |= (1<<TOIE1);
	
	UART_init(BAUD_PRESCALER);
	
	sei();//enable global interrupts
}

ISR(TIMER1_CAPT_vect) {
	 //sprintf(String,"Hello world! \n");
	 //UART_putstring(String);
	 
	 
	 //TIFR1 |= (1<<ICF1);
	 //PORTB ^= (1<<PORTB5);
	 if (!(PINB & (1<<PINB0))) { //press out
		 PORTB |= (1<<PORTB5);
		 int newPress = ICR1;//TCNT1
		 int timeChange = newPress - lastPress + (numOverflows * 256);
		 sprintf(String, "time %u", timeChange);
		 UART_putstring(String);
		 //30 * 10^-3 * 16 * 10^6 / 256 = 1875
		 //200 * 10^-3 * 16 * 10^6 / 256 = 12500
		 if (timeChange > 1875 && timeChange < 12500) {//fix number to ticks
			 //print dot
			 sprintf(String, "Dot \n");
			 UART_putstring(String);
		 }else if (timeChange > 12500 && timeChange < 25000) {//fix number to ticks
			 //print dash
			 sprintf(String, "Dash \n");
			 UART_putstring(String);
		 } else if (timeChange < 1875) {
			 //sprintf(String,"release less than time range \n");
			 sprintf(String,"release less than time range \n");
			 UART_putstring(String);
			 sprintf(String,"numOverflows %u\n", numOverflows);
			 UART_putstring(String);
			 sprintf(String,"newPress %u\n", newPress);
			 UART_putstring(String);
			 sprintf(String,"oldPress %u\n", lastPress);
			 UART_putstring(String);
		 } else {
			 sprintf(String,"release above time range \n");
			 UART_putstring(String);
		 }
		 lastPress = newPress;
		 numOverflows = 0;
	 } else { //press in
		 PORTB &= ~(1<<PORTB5);
		 int newPress = TCNT1;
		 float timeChange = newPress - lastPress + (numOverflows * 65536);
		 char timeString[50];
		 sprintf(timeString, "%f", timeChange);
		 UART_putstring(timeString);
		 if (timeChange > 25000) {//fix number to ticks
			 //print space
			 sprintf(String,"Space \n");
			 UART_putstring(String);
		 } else {
			 sprintf(String,"push but not in time range \n");
			 UART_putstring(String);
		 }
		 lastPress = newPress;
		 numOverflows = 0;
	 }
	 TCCR1B ^= (1<<ICES1);
	 
}
ISR(TIMER1_OVF_vect) {
	numOverflows++;
}

int main(void)
{
	Initialize();
	while (1);
}
