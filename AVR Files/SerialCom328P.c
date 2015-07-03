#ifndef F_CPU 
   #define F_CPU 16000000
#endif 

#include <avr/io.h>
#include <util/delay.h>

#define BAUDRATE 19200
#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)

char trigger[] = "5";
char responseA[] = "1";
char responseB[] = "2";
char responseC[] = "3";
char responseD[] = "4";

void USART_init (void)
{
	UBRR0H = (uint8_t)(BAUD_PRESCALE >> 8);
	UBRR0L = (uint8_t)(BAUD_PRESCALE);
	UCSR0A = 0x00;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C =   dfg(1 << UCSZ00) | (1 << UCSZ01);
}

void USART_send (unsigned char data)
{
	while ( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

void USART_putstring(char* StringPtr)
{
	while (*StringPtr != 0x00)  //Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null char
	{    
		USART_send(*StringPtr);  //Using the simple send function we send one char at a time
		StringPtr++;			 //We increment the pointer so we can read the next char
	}        
}

void runSequence1500 ()
{
	int buttonID = 1;
	
	while(1) // Infinite loop
	{        
		USART_putstring (trigger);
		PORTC = 0b00000001;
		_delay_ms (50);
		PORTC = 0b00000000;
		_delay_ms (450);  
		
		if (1 == buttonID)
		{
			USART_putstring (responseA);
			++buttonID;
		}
		else if (2 == buttonID)
		{
			USART_putstring (responseB);
			++buttonID;
		}
		else if (3 == buttonID)
		{
			USART_putstring (responseC);
			++buttonID;
		}
		else if (4 == buttonID)
		{
			USART_putstring (responseD);
			buttonID = 1;
		}
		
		PORTC = 0b00000100;
		_delay_ms (50);
		PORTC = 0b00000000;
		_delay_ms (950);  		
	}
}

void runSequence2000 ()
{
	int buttonID = 1;

	while(1) // Infinite loop
	{        
		USART_putstring (trigger);
		PORTC = 0b00000001;
		_delay_ms (50);
		PORTC = 0b00000000;
		_delay_ms (450);  
		
		if (1 == buttonID)
		{
			USART_putstring (responseA);
			++buttonID;
		}
		else if (2 == buttonID)
		{
			USART_putstring (responseB);
			++buttonID;
		}
		else if (3 == buttonID)
		{
			USART_putstring (responseC);
			++buttonID;
		}
		else if (4 == buttonID)
		{
			USART_putstring (responseD);
			buttonID = 1;
		}
		
		PORTC = 0b00000100;
		_delay_ms (50);
		PORTC = 0b00000000;
		_delay_ms (1450);  		
	}
}

int main(void)
{
	// Startup delay 
	_delay_ms (500); 

	// Initialize the UART for serial communication
	USART_init ();
	
	// Set PORTD as input
	DDRD = 0b00000000;
	
	// Set PORTC as output with all pins low
	DDRC = 0b11111111;
	PORTC = 0b00000000;
	
	while (1) // Infinite Loop
	{
		if (0 == (PIND & 0b00000100))  // 2000ms
		{
			_delay_ms (500);
			runSequence2000();
		}
		else if (0 == (PIND & 0b00001000))  // 1500ms
		{
			_delay_ms (500);
			runSequence1500();
		}	
	}
	
    return 0;   /* never reached */
}







