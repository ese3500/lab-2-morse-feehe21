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

#include <util/delay.h>

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "inc/uart.h"

char c = 0;
int lastPress = 0;
char numOverflows = 0;
char String[25];
char dds [5];
char i = 0;

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
	TCCR1B |= (1<<CS10);
	TCCR1B |= (1<<CS12);
	TCCR1B &= ~(1<<CS11);
	//set prescaler to 1024
	
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
void printLetter() {
	i = 0;
	//check if empty
	if (dds[0] == 0) {
		return;
	}
	if (dds[0] == 1) {//.
		if (dds[1] == 0) {
			sprintf(String, "E ");
		} else if (dds[1] == 1) { //..
			if (dds[2] == 0) {
				sprintf(String, "I ");
			} else if (dds[2] == 1) { //...
				if (dds[3] == 0) {
					sprintf(String, "S ");
				} else if (dds[3] == 1) {//....
					if (dds[4] == 0) {
						sprintf(String, "H ");
					} else if (dds[4] == 1) { //.....
						sprintf(String, "5 ");
					} else { //....-
						sprintf(String, "4 ");
					}
				} else {//...-
					if (dds[4] == 0) {
						sprintf(String, "V ");
					} else if (dds[4] == 1) { //...-.
						sprintf(String, "NaL ");
					} else { //...--
						sprintf(String, "3 ");
					}
				}
			} else { //..-
				if (dds[3] == 0) {
					sprintf(String, "3 ");
				} else if (dds[3] == 1) {//..-.
					if (dds[4] == 0) {
						sprintf(String, "F ");
					} else if (dds[4] == 1) {//..-..
						sprintf(String, "NaL ");
					} else {//..-.-
						sprintf(String, "NaL ");
					}
				} else {//..--
					if (dds[4] == 0) {
						sprintf(String, "NaL ");
					} else if (dds[4] == 1) {//..--.
						sprintf(String, "NaL ");
					} else {//..---
						sprintf(String, "2 ");
					}
				}
			}
		} else { //.-
			if (dds[2] == 0) {
				sprintf(String, "A ");
			} else if (dds[2] == 1) {//.-.
				if (dds[3] == 0) {
					sprintf(String, "R ");
				} else if (dds[3] == 1) {//.-..
					if (dds[4] == 0) {
						sprintf(String, "L ");
					} else {
						sprintf(String, "NaL ");
					}
				} else {//.-.-
					sprintf(String, "NaL ");
				}
			} else {//.--
				if (dds[3] == 0) {
					sprintf(String, "W ");
				} else if (dds[3] == 1) {//.--.
					sprintf(String, "P ");
				} else {//.---
					if (dds[4] == 0) {
						sprintf(String, "J ");
					} else if (dds[4] == 1) {//.---.
						sprintf(String, "NaL ");
					} else {//.----
						sprintf(String, "1 ");
					}
				}
			}
		}
	} else {//-
		if (dds[1] == 0) {
			sprintf(String, "T ");
		} else if (dds[1] == 1) {//-.
			if (dds[2] == 0) {
				sprintf(String, "N ");
			} else if (dds[2] == 1) {//-..
				if (dds[3] == 0) {
					sprintf(String, "D ");
				} else if (dds[3] == 1) {//-...
					if (dds[4] == 0) {
						sprintf(String, "B ");
					} else {
						sprintf(String, "6 ");
					}
				} else {//-..-
					sprintf(String, "X ");
				}
			} else {//-.-
				if (dds[3] == 0) {
					printf(String, "K ");
				} else if (dds[3] == 1) {//-.-.
					printf(String, "C ");
				} else {//-.--
					printf(String, "Y ");
				}
			}
		} else {//--
			if (dds[2] == 0) {
				printf(String, "M ");
			} else if (dds[2] == 1) {//--.
				if (dds[3] == 0) {
					printf(String, "G ");
				} else if (dds[3] == 1) {//--..
					if (dds[4] == 0) {
						printf(String, "Z ");
					} else {
						printf(String, "7 ");
					}
				} else {//--.-
					printf(String, "Q ");
				}
			} else {//---
				if (dds[3] == 0) {
					printf(String, "O ");
				} else if (dds[3] == 1) {//---.
					printf(String, "8 ");
				} else {//----
					if (dds[4] == 1) {//----.
						printf(String, "9 ");
					} else {//-----
						printf(String, "0 ");
					}
				}
			}
		}
	}
	UART_putstring(String);
	dds[0] = 0;
	dds[1] = 0;
	dds[2] = 0;
	dds[3] = 0;
	dds[4] = 0;
}

ISR(TIMER1_CAPT_vect) {
	 //sprintf(String,"Hello world! \n");
	 //UART_putstring(String);
	 
	 
	 //TIFR1 |= (1<<ICF1);
	 //PORTB ^= (1<<PORTB5);
	 if (!(PINB & (1<<PINB0))) { //press out
		 PORTB |= (1<<PORTB5);
		 int newPress = ICR1;//TCNT1
		 long timeChange = newPress - lastPress + (numOverflows * 65536);
		 //sprintf(String, "time %lu", timeChange);
		 //UART_putstring(String);
		 //30 * 10^-3 * 16 * 10^6 / 1024 = 469
		 //400 * 10^-3 * 16 * 10^6 / 1024 = 6250
		 if (timeChange >= 469 && timeChange < 6250) {
			 dds[i] = 1;
			 i++;
			 //print dot
			 //sprintf(String, "Dot \n");
			 //UART_putstring(String);
			 PORTB |= (1<<PORTB1); // set LED to high
			 _delay_ms(50);
			 PORTB &= ~(1<<PORTB1); // set to low
		 }else if (timeChange >= 6250 /*&& timeChange < 12500*/) {
			 dds[i] = 2;
			 i++;
			 //print dash
			 //sprintf(String, "Dash \n");
			 //UART_putstring(String);
			 PORTB |= (1<<PORTB2); // set LED to high
			 _delay_ms(50);
			 PORTB &= ~(1<<PORTB2); // set to low
		 } else if (timeChange < 469) {
			 //sprintf(String,"release less than time range \n");
			 //sprintf(String,"release less than time range \n");
			 //UART_putstring(String);
			 /*sprintf(String,"numOverflows %u\n", numOverflows);
			 UART_putstring(String);
			 sprintf(String,"newPress %u\n", newPress);
			 UART_putstring(String);
			 sprintf(String,"oldPress %u\n", lastPress);
			 UART_putstring(String);*/
		 } else {
			 //sprintf(String,"release above time range \n");
			 //UART_putstring(String);
		 }
		 if (i > 5) {
			 printLetter();
		 }
		 lastPress = newPress;
		 numOverflows = 0;
	 } else { //press in
		 PORTB &= ~(1<<PORTB5);
		 int newPress = TCNT1;
		 long timeChange = newPress - lastPress + (numOverflows * 65536);
		 //sprintf(String, "time %lu", timeChange);
		 //UART_putstring(String);
		 if (timeChange > 25000) {//fix number to ticks
			 //print space
			 //sprintf(String,"Space \n");
			 //UART_putstring(String);
			 printLetter();
		 } else {
			 //sprintf(String,"push but not in time range \n");
			 //UART_putstring(String);
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
	while (1) {
		long timeChange = TCNT1 - lastPress + (numOverflows * 65536);
		if (timeChange > 25000 && (PINB & (1<<PINB0))) {
			printLetter();
		}
	}
}
