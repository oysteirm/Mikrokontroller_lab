#include "uart.h"
#include "gpio.h"

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);

	// Fill inn the configuration for the remaining buttons 
}

int main (){

    for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

    uart_init();
    button_init();

    int sleep = 0;
    char A = 'A';
    char B = 'B';
    while(1){

//SENDEFUNK
		/* Check if button 1 is pressed;
		 * send A with UART */
		if (!(GPIO->IN & (1 << 13))){
			uart_send(A);
		}
		

		/* Check if button 2 is pressed;
		 * send B with UART */
		if (!(GPIO->IN & (1 << 14))){
			uart_send(B);
		} 
//MOTTAKSFUNK
        if (uart_read()!='\0'){ //sjekk om det sendes bokstav
            if( GPIO->OUT & (1 << 17)){ //hvis av, skru på
            GPIO->OUT &= ~(1 << 17);
			GPIO->OUT &= ~(1 << 18);
			GPIO->OUT &= ~(1 << 19);
			GPIO->OUT &= ~(1 << 20);
            } else{ //hvis på. skru av
            GPIO->OUT |= (1 << 17);
			GPIO->OUT |= (1 << 18);
			GPIO->OUT |= (1 << 19);
			GPIO->OUT |= (1 << 20);
            }

        }


		sleep = 10000;
		while(--sleep); // Delay
	}

    return 0;
};