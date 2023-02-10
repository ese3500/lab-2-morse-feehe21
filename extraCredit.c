/*
 * ESE350_lab2_1.c
 *
 * Created: 1/27/2023 11:13:29 AM
 * Author : erica
 */ 

#include <stdlib.h>
#include <stdio.h>

#include <util/delay.h>

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "inc/uart.h"

char String[25];


void Initialize() {
	cli(); //disable global interrupts for setup
	
	//PB5 - onboard LED
	DDRB |= (1<<DDB5); //set to output pin
	PORTB &= ~(1<<PORTB5); // set to low
	
	//PB1 pin 9 - LED setup in pin 9
	DDRB |= (1<<DDB1); //set to output pin
	PORTB &= ~(1<<PORTB1); // set to low
	sei();//enable global interrupts
}
void dot() {
	sprintf(String, ".");
	UART_putstring(String);
	PORTB |= (1<<PORTB1); // set LED to high
	_delay_ms(1000);
	PORTB &= ~(1<<PORTB1); // set LED to low
	_delay_ms(2000);
}
void dash() {
	sprintf(String, "-");
	UART_putstring(String);
	PORTB |= (1<<PORTB1); // set LED to high
	_delay_ms(7000);
	PORTB &= ~(1<<PORTB1); // set LED to low
	_delay_ms(2000);
}
void space() {
	sprintf(String, " ");
	UART_putstring(String);
	_delay_ms(10000);
}

void flashLetter(char c) {
	c = toupper(c);
	if (c == ' ') {
		space();
	}
	if (c == 'A') {
		dot();
		dash();
	}
	if (c == 'B') {
		dash();
		dot();
		dot();
		dot();
	}
	if (c == 'C') {
		dash();
		dot();
		dash();
		dot();
	}
	if (c == 'D') {
		dash();
		dot();
		dot();
	}
	if (c == 'E') {
		dot();
	}
	if (c == 'F') {
		dot();
		dot();
		dash();
		dot();
	}
	if (c == 'G') {
		dash();
		dash();
		dot();
	}
	if (c == 'H') {
		dot();
		dot();
		dot();
		dot();
	}
	if (c == 'I') {
		dot();
		dot();
	}
	if (c == 'J') {
		dot();
		dash();
		dash();
		dash();
	}
	if (c == 'K') {
		dash();
		dot();
		dash();
	}
	if (c == 'L') {
		dot();
		dash();
		dot();
		dot();
	}
	if (c == 'M') {
		dash();
		dash();
	}
	if (c == 'N') {
		dash();
		dot();
	}
	if (c == 'O') {
		dash();
		dash();
		dash();
	}
	if (c == 'P') {
		dot();
		dash();
		dash();
		dot();
	}
	if (c == 'Q') {
		dash();
		dash();
		dot();
		dash();
	}
	if (c == 'R') {
		dot();
		dash();
		dot();
	}
	if (c == 'S') {
		dot();
		dot();
		dot();
	}
	if (c == 'T') {
		dash();
	}
	if (c == 'U') {
		dot();
		dot();
		dash();
	}
	if (c == 'V') {
		dot();
		dot();
		dot();
		dash();
	}
	if (c == 'W') {
		dot();
		dash();
		dash();
	}
	if (c == 'X') {
		dash();
		dot();
		dot();
		dash();
	}
	if (c == 'Y') {
		dash();
		dot();
		dash();
		dash();
	}
	if (c == 'Z') {
		dash();
		dash();
		dot();
		dot();
	}
}

int main(void)
{
	Initialize();
	char String [25] = "Example string";
	int arraySize = sizeof(String)/sizeof(String[0]);
	int i = 0; //index in array
	while (1) {
		if (i < arraySize) {
			flashLetter(String[i]);
			i++;
			space();
		} else {
			_delay_ms(70000);
			i = 0;
		}
	}
	
}
