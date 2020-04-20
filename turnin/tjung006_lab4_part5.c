/*	Author: terry
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned int i = 0;
enum states{start, x, init, y, pound, r, lock}state;
void tick(){
	switch(state){
		case start:
			state = init;
			break;
		case init:
			if(PINA == 0x04){
				state = pound;
			}
			else if(PINA = 0x80){
				state = lock;
				PORTB = 0x00;
			}
			else{
				state = init;
			}
			break;
		case x:
			if(PINA == 0x00){
				state = r;
			}
			else{
				state = x;
			}
		case y:
			if(PINA == 0x00){
				state = r;
			}
			else{
				state = y;
			}
			break;
		case pound:
			if(PINA == 0x00){//release
				state = r;
			}
			else{
				state = pound;
			}
			break;
		case lock:
			state = lock;
			break;
		case r:
			if(PINA == 0x02 && i > 0){
				state = y;
			}
			else if(PINA == 0x01){
				state = x;
				i += 1;
				if(i == 2){
					 if(PORTB == 0x00){
                                        	PORTB = 0x01;
                                	}
                                	else{
                                        	PORTB = 0x00;
                                	}
				}
			}
			else{
				state = r;
			}
			break;
		default:
			break;

	}

}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
   
	PORTB = 0x00;
	state = start;
	while(1){
		tick();
	}
   
    return 0;
}
