/*
 * FinalProject_interface.h
 *
 *  Created on: Sep 7, 2024
 *      Author: Youssef Hany
 */

#ifndef FINALPROJECT_INTERFACE_H_
#define FINALPROJECT_INTERFACE_H_

/*******************************************************************************
 *                           LCD Definitions                                   *
 *******************************************************************************/
/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

/*******************************************************************************
 *                          KeyPad Definitions                                 *
 *******************************************************************************/
#define ROWS_NUM 4
#define COLS_NUM 4
#define FIRST_ROWS_PIN 4
#define FIRST_COLS_PIN 2

/*******************************************************************************
 *                            Pin Definitions                                  *
 *******************************************************************************/
#define SET_BIT(REG,BIT_NUM)        REG |= (1<<BIT_NUM)
#define CLR_BIT(REG,BIT_NUM)        REG &= (~(1<<BIT_NUM))
#define TOG_BIT(REG,BIT_NUM)        REG ^= (1<<BIT_NUM)
#define GET_BIT(REG,BIT_NUM)        (REG>>BIT_NUM)&0x01

/*******************************************************************************
 *                           State Definitions                                 *
 *******************************************************************************/
#define START_MENU 0
#define MAIN_MENU 1
#define LEFT_SIGNAL_STATE 2
#define RIGHT_SIGNAL_STATE 3
#define WAITING_SIGNAL_STATE 4
#define AC_MODE_STATE 5

/*******************************************************************************
 *                    Program Functions Prototypes                             *
 *******************************************************************************/
unsigned char Display_MainMenu();

/*******************************************************************************
 *                      LCD Functions Prototypes                               *
 *******************************************************************************/
void LCD_init(void);
void LCD_sendCommand(unsigned char command);
void LCD_displayCharacter(unsigned char data);
void LCD_displayString(char *Str);
void LCD_moveCursor(unsigned char row,unsigned char col);
void LCD_displayStringRowColumn(unsigned char row,unsigned char col,char *Str);
void LCD_intgerToString(int data);
void LCD_clearScreen(void);

/*******************************************************************************
 *                     KeyPad Functions Prototypes                             *
 *******************************************************************************/
unsigned char KEYPAD_4x4_adjustKeyNumber (unsigned char num);
unsigned char KEYPAD_getPressedKey();

#endif /* FINALPROJECT_INTERFACE_H_ */
