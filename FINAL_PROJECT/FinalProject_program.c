/*
 * FinalProject_program.c
 *
 *  Created on: Sep 7, 2024
 *      Author: Youssef Hany
 */

#include <avr/io.h>
#include <util/delay.h>
#include "FinalProject_interface.h"

/*******************************************************************************
 *                           Program Functions                                 *
 *******************************************************************************/
unsigned char Display_MainMenu(){
	unsigned char state;
	unsigned char user_input = 0;
	LCD_displayString("1-Engine Off");
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_displayString("2-Left Signal");
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_displayString("3-Right Signal");
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_displayString("4-Waiting Signal");
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_displayString("5-AC");
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_displayString("6-Redisplay Menu");

	user_input = KEYPAD_getPressedKey();
	if (user_input == 1) {
		LCD_clearScreen();
		LCD_displayString("Engine OFF");
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		_delay_ms(300);
		CLR_BIT(PORTC,0);
		CLR_BIT(PORTC,1);
		CLR_BIT(PORTC,2);
		_delay_ms(300);
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		_delay_ms(300);
		CLR_BIT(PORTC,0);
		CLR_BIT(PORTC,1);
		CLR_BIT(PORTC,2);
		_delay_ms(300);
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		_delay_ms(300);
		CLR_BIT(PORTC,0);
		CLR_BIT(PORTC,1);
		CLR_BIT(PORTC,2);
		LCD_clearScreen();
		state = START_MENU; // Return to start menu
	} else if (user_input == 2) {
		LCD_clearScreen();
		state = LEFT_SIGNAL_STATE;
	} else if (user_input == 3) {
		LCD_clearScreen();
		state = RIGHT_SIGNAL_STATE;
	} else if (user_input == 4) {
		LCD_clearScreen();
		state = WAITING_SIGNAL_STATE;
	} else if (user_input == 5) {
		LCD_clearScreen();
		state = AC_MODE_STATE;
	} else if (user_input == 6) {
		LCD_clearScreen();
		state = MAIN_MENU; // Re-display the menu
	} else {
		LCD_clearScreen();
		LCD_displayString("Undefined Input");
		_delay_ms(500);
		LCD_clearScreen();
		state = MAIN_MENU; // Re-display the menu
	}
	return state;
}

/*******************************************************************************
 *                             LCD Functions                                   *
 *******************************************************************************/
void LCD_init(void)
{
	/* Configure the direction for RS and E pins as output pins */
	SET_BIT(DDRA,1);
	SET_BIT(DDRA,2);

	_delay_ms(20);		/* LCD Power ON delay always > 15ms */

	/* Configure 4 pins in the data port as output pins PA3 --> PA6 */
	DDRA |= (1<<3) | (1<<4) | (1<<5) | (1<<6);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}

void LCD_sendCommand(unsigned char command)
{
	CLR_BIT(PORTA,1); /* Instruction Mode RS=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	SET_BIT(PORTA,2); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* Send first 4 bits in command(Most Significant four bits) on PA3 --> PA6   */
	PORTA = (PORTA & 0x87) | ((command & 0xF0) >> 1);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLR_BIT(PORTA,2);  /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	SET_BIT(PORTA,2);  /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* Send second 4 bits in command(Least Significant four bits) on PA3 --> PA6   */
	PORTA = (PORTA & 0x87) | ((command & 0x0F) << 3);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLR_BIT(PORTA,2);  /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
}

void LCD_displayCharacter(unsigned char data)
{
	SET_BIT(PORTA,1); /* Data Mode RS=1 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	SET_BIT(PORTA,2); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* Send first 4 bits in data(Most Significant four bits) on PA3 --> PA6   */
	PORTA = (PORTA & 0x87) | ((data & 0xF0) >> 1);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLR_BIT(PORTA,2);  /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	SET_BIT(PORTA,2);  /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* Send second 4 bits in data(Least Significant four bits) on PA3 --> PA6   */
	PORTA = (PORTA & 0x87) | ((data & 0x0F) << 3);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLR_BIT(PORTA,2);  /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
}

void LCD_displayString(char *Str)
{
	unsigned char i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void LCD_moveCursor(unsigned char row,unsigned char col)
{
	unsigned char lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
	case 0:
		lcd_memory_address=col;
		break;
	case 1:
		lcd_memory_address=col+0x40;
		break;
	case 2:
		lcd_memory_address=col+0x10;
		break;
	case 3:
		lcd_memory_address=col+0x50;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(unsigned char row,unsigned char col,char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void LCD_intgerToString(int data)
{
	char buff[16]; /* String to hold the ascii result */
	itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_displayString(buff); /* Display the string */
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}

/*******************************************************************************
 *                             KeyPad Functions                                *
 *******************************************************************************/
unsigned char KEYPAD_getPressedKey(void)
{
	unsigned char col, row;

	DDRB &= 0x0F;  /*Set rows connected to PORTB as Input pins*/
	DDRD &= 0xC3;  /*Set cols connected to PORTD as Input pins*/
	PORTD |= 0x3C; /*Set Pull-Up Resistor for cols connected to PORTD*/

	while(1)
	{
		for(row = 0; row < ROWS_NUM; row++) /* loop for rows */
		{
			/*
			 * Each time setup the direction for all keypad port as input pins,
			 * except this row will be output pin
			 */
			DDRB |= (1 << (row + FIRST_ROWS_PIN));

			/* Set/Clear the row output pin */
			PORTB &= ~(1 << (row + FIRST_ROWS_PIN));

			for(col = 0; col < COLS_NUM; col++) /* loop for columns */
			{
				/* Check if the switch is pressed in this column */
				if(!(PIND & (1 << (col + FIRST_COLS_PIN)))) // Check if button is pressed
				{
					_delay_ms(30);
					if(!(PIND & (1 << (col + FIRST_COLS_PIN)))) // Check again if button is pressed because keypad can produce noisy signals
					{
						DDRB &= ~(1 << (row + FIRST_ROWS_PIN));
						return KEYPAD_4x4_adjustKeyNumber((row*COLS_NUM)+col+1);
					}
				}
			}
			DDRB &= ~(1 << (row + FIRST_ROWS_PIN));
		}
		_delay_ms(10);
	}
}

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
unsigned char KEYPAD_4x4_adjustKeyNumber(unsigned char button_number)
{
	unsigned char keypad_button = 0;
	switch(button_number)
	{
	case 1: keypad_button = 7;
	break;
	case 2: keypad_button = 8;
	break;
	case 3: keypad_button = 9;
	break;
	case 4: keypad_button = '%'; // ASCII Code of %
	break;
	case 5: keypad_button = 4;
	break;
	case 6: keypad_button = 5;
	break;
	case 7: keypad_button = 6;
	break;
	case 8: keypad_button = '*'; /* ASCII Code of '*' */
	break;
	case 9: keypad_button = 1;
	break;
	case 10: keypad_button = 2;
	break;
	case 11: keypad_button = 3;
	break;
	case 12: keypad_button = '-'; /* ASCII Code of '-' */
	break;
	case 13: keypad_button = 13;  /* ASCII of Enter */
	break;
	case 14: keypad_button = 0;
	break;
	case 15: keypad_button = '='; /* ASCII Code of '=' */
	break;
	case 16: keypad_button = '+'; /* ASCII Code of '+' */
	break;
	default: keypad_button = button_number;
	break;
	}
	return keypad_button;
}
