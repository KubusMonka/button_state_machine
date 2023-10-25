/*
 * button.h
 *
 *  Created on: Oct 24, 2023
 *      Author: jmonk
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

typedef enum
{
	IDLE = 0,
	DEBOUNCE,
	PRESSED,
	REPEAT


}	ButtonState_e;

typedef struct
{
	ButtonState_e 	State;
	GPIO_TypeDef* 	GPIO_Port;
	uint16_t 		GPIO_Pin;

	uint32_t		LastTick; // Last remembered time before steps
	uint32_t		TimerDebounce; //settable time for debounce timer
	uint32_t		TimerLongPress; //settable time for long press timer
	uint32_t		TimerRepeat; //settable time for repeat timer

	void(*ButtonPressed)(void);
	void(*ButtonLongPressed)(void); //callback
	void(*ButtonRepeat)(void);


}Button_t;


//PUBLIC FUNCTIONS
void ButtonInit (Button_t* Button, GPIO_TypeDef* GPIO_Port,uint16_t GPIO_Pin,
				 uint32_t TimerDebounce, uint32_t TimerLongPress, uint32_t TimerRepeat);

void ButtonTask(Button_t* Button);

void ButtonRegisterPressedCallback(Button_t* Button, void (*Callback)(void));
void ButtonRegisterLongPressCallback(Button_t* Button, void (*Callback)(void));
void ButtonRegisterRepeatCallback(Button_t* Button, void (*Callback)(void));

void SetButtonTimerDebounce (Button_t* Button, uint32_t TimerDebounce);
void SetButtonTimerLongPress (Button_t* Button, uint32_t TimerLongPress);
void SetButtonTimerRepeat (Button_t* Button, uint32_t TimerRepeat);







#endif /* INC_BUTTON_H_ */
