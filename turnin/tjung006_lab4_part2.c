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

unsigned char add(unsigned char a, unsigned char b){
    while(b != 0){
        unsigned char x = a & b;
        a = a ^ b;
        b = x << 1;
    }
    return a;
}

unsigned char subtract(unsigned char a, unsigned char b){
	while(b != 0){
		unsigned char x = (~a) & b;
		a = a ^ b;
		b = x << 1;
	}
	return a;
}

unsigned char one = 0x01;
short i = 0;
short j = 0;
enum states{start, R00, P01, P10, P11}state;
void tick(){
	switch(state){
		case start:
			state = R00;
			PORTC = 0x07;
			break;
		case R00:
			if(PINA == 0x01){
				state = P01;
				if(PORTC < 0x09){
					PORTC = add(PORTC,one);		
				}
				i = 0;
			}
			else if(PINA == 0x02){
				state = P10;
				if(PORTC > 0x00){
					PORTC = subtract(PORTC, one);
				}
				j = 0;
			}
			else if(PINA == 0x03){
				state = P11;
				i = 0;
				j = 0;
			}
			else if(PINA == 0x00){
				state = R00;
			}
			break;
		case P01:
			if(PINA == 0x00){
				state = R00;
				 i = 1;
                                if(i == 1 && j == 1){
                                        PORTC = 0x00;
                                }
			}
			else if(PINA == 0x01){
				state = P01;
			} 
			else if(PINA == 0x02){
				state = P10;
				if(PORTC > 0x00){
					PORTC = subtract(PORTC,one);
				}
				//i = 1;
				j = 0;
			}
			else if(PINA = 0x03){
				state = P11;
				i = 0;
				j = 0;
				if(PORTC > 0x00){
                                        PORTC = subtract(PORTC,one);
                                }
			}
			break;
		case P10:
			if(PINA == 0x02){
				state = P10;
			}
			else if(PINA == 0x01){
				state = P01;
				if(PORTC < 0x09){
					PORTC = add(PORTC,one);
				}
				//j = 1;
				i = 0;
			}
			else if(PINA == 0x00){
				state = R00;
				j = 1;
				if(i == 1 && j == 1){
					PORTC = 0X00;
				}
			}
			else if(PINA == 0x03){
				state = P11;
				if(PORTC < 0x09){
                                        PORTC = add(PORTC,one);
                                }
				i = 0;
				j = 0;
			}
			break;
		case P11:
			if(PINA == 0x03){
				state = P11;
			}
			else if(PINA == 0x02){
				state = P10;
				i = 1;
			}
			else if(PINA == 0x01){
				state = P01;
				j = 1; 
			}
			else if(PINA == 0x00){
				state = R00;
				i = 1;
				j = 1;
				if(i == 1 && j == 1){
                                        PORTC = 0X00;
                                }
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
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
   
	PORTC = 0x07;
	state = start;
	while(1){
		tick();
	}
   
    return 0;
}
