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

enum states{start,offR, onP, onR, offP}state;
void tick(){
	switch(state){
		case start:
			state = offR;
			PORTB = 0x01;
			break;
		case offR:
			if(PINA == 0x00){
				state = offR;
			}
			else if(PINA == 0x01){
				state = onP;
				PORTB = 0x02;
			}
			break;
		case onP:
			if(PINA == 0x01){
				state = onP;
			}
			else if(PINA == 0x00){
				state = onR;
			}
			break;
		case onR:
			if(PINA == 0x00){
				state = onP;
			}
			else if(PINA == 0x01){
				state = offP;
				PORTB = 0x01;
			}
			break;
		case offP:
			if(PINA == 0x01){
				state = offP;
			}
			else if(PINA == 0x00){
				state = offR;
			}
			break;
		default:
			state = start;
			break;
	}

}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
   
	PORTB = 0x00;
	state = start;
	while(1){
		tick();
	}

   
    return 0;
}
