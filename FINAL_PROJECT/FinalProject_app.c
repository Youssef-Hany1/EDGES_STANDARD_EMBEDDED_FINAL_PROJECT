/*
 * FinalProject_app.c
 *
 *  Created on: Sep 7, 2024
 *      Author: Youssef Hany
 */
#include <avr/io.h>
#include <util/delay.h>
#include "FinalProject_interface.h"

#define F_CPU 16000000UL

/*******************************************************************************
 *                             main function                                   *
 *******************************************************************************/
int main(void)
{
	unsigned char state = START_MENU;
	unsigned char user_input = 0;

	// Initialize LEDs
	SET_BIT(DDRC,0);
	SET_BIT(DDRC,1);
	SET_BIT(DDRC,2);
	CLR_BIT(PORTC,0);
	CLR_BIT(PORTC,1);
	CLR_BIT(PORTC,2);

	// Initialize LCD
	LCD_init();

	while (1) {
		switch (state) {
			case START_MENU:
				LCD_displayString("Start Engine (1)");
				user_input = KEYPAD_getPressedKey();
				if (user_input == 1) {
					LCD_clearScreen();
					LCD_displayString("Engine ON");
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
					state = MAIN_MENU; // Move to the main menu
				} else {
					LCD_clearScreen();
					LCD_displayString("Undefined Input");
					_delay_ms(500);
					LCD_clearScreen();
					state = START_MENU; // Reset to start menu in case of any unexpected state
				}
				break;

			case MAIN_MENU:
				state = Display_MainMenu();
				break;

			case LEFT_SIGNAL_STATE:
				LCD_displayString("Left Signal");
				SET_BIT(PORTC,2);
				_delay_ms(800);
				CLR_BIT(PORTC,2);
				_delay_ms(800);
				SET_BIT(PORTC,2);
				_delay_ms(800);
				CLR_BIT(PORTC,2);
				_delay_ms(800);
				SET_BIT(PORTC,2);
				_delay_ms(800);
				CLR_BIT(PORTC,2);
				LCD_clearScreen();
				state = MAIN_MENU; // Return to main menu
				break;

			case RIGHT_SIGNAL_STATE:
				LCD_displayString("Right Signal");
				SET_BIT(PORTC,0);
				_delay_ms(800);
				CLR_BIT(PORTC,0);
				_delay_ms(800);
				SET_BIT(PORTC,0);
				_delay_ms(800);
				CLR_BIT(PORTC,0);
				_delay_ms(800);
				SET_BIT(PORTC,0);
				_delay_ms(800);
				CLR_BIT(PORTC,0);
				LCD_clearScreen();
				state = MAIN_MENU; // Return to main menu
				break;

			case WAITING_SIGNAL_STATE:
				LCD_displayString("Waiting Signal");
				SET_BIT(PORTC,2);
				SET_BIT(PORTC,0);
				_delay_ms(800);
				CLR_BIT(PORTC,2);
				CLR_BIT(PORTC,0);
				_delay_ms(800);
				SET_BIT(PORTC,2);
				SET_BIT(PORTC,0);
				_delay_ms(800);
				CLR_BIT(PORTC,2);
				CLR_BIT(PORTC,0);
				_delay_ms(800);
				SET_BIT(PORTC,2);
				SET_BIT(PORTC,0);
				_delay_ms(800);
				CLR_BIT(PORTC,2);
				CLR_BIT(PORTC,0);
				LCD_clearScreen();
				state = MAIN_MENU; // Return to main menu
				break;

			case AC_MODE_STATE:
				LCD_displayString("AC Mode:");
				LCD_moveCursor(1, 0);
				LCD_displayString("1-ON 2-OFF");
				_delay_ms(500);
				user_input = KEYPAD_getPressedKey();

				if (user_input == 1) {
					LCD_clearScreen();
					LCD_displayString("AC ON");
					SET_BIT(PORTC,1);
					_delay_ms(500);
				} else if (user_input == 2) {
					LCD_clearScreen();
					LCD_displayString("AC OFF");
					CLR_BIT(PORTC,1);
					_delay_ms(500);
				} else {
					LCD_clearScreen();
					LCD_displayString("Undefined Input");
					_delay_ms(500);
				}
				LCD_clearScreen();
				state = MAIN_MENU; // Return to main menu
				break;

			default:
			    state = START_MENU; // Return to start menu
			    break;
		}
	}
}

