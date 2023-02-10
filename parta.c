#include <avr/io.h>
#include <stdbool.h>


int main(void)
{
	char c = 0;
	bool prev_state = 0;
	//PB1
	DDRB |= (1<<DDB1); //set to output pin
	PORTB &= ~(1<<PORTB1); // set to low
	
	//PB2
	DDRB |= (1<<DDB2); //set to output pin
	PORTB &= ~(1<<PORTB2); // set to low
	
	//PB3
	DDRB |= (1<<DDB3); //set to output pin
	PORTB &= ~(1<<PORTB3); // set to low
	
	//PB4
	DDRB |= (1<<DDB4); //set to output pin
	PORTB &= ~(1<<PORTB4); // set to low
	
	//PD7
	DDRD &= ~(1<<DDD7); //set to input pin
	
    while (1) 
    {
		bool current_state = PIND & (1<<PIND7);
		if (current_state && !prev_state) {
			c++;
		}
		prev_state = current_state;
		if (c >= 4) {
			c -= 4;
		}
		if (c == 0) {
			PORTB |= (1<<PORTB1); // set to high
		} else {
			PORTB &= ~(1<<PORTB1); // set to low
		}
		if (c == 1) {
			PORTB |= (1<<PORTB2); // set to high
			} else {
			PORTB &= ~(1<<PORTB2); // set to low
		}
		if (c == 2) {
			PORTB |= (1<<PORTB3); // set to high
			} else {
			PORTB &= ~(1<<PORTB3); // set to low
		}
		if (c == 3) {
			PORTB |= (1<<PORTB4); // set to high
			} else {
			PORTB &= ~(1<<PORTB4); // set to low
		}
    }
}
