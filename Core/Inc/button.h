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
	DEBOUNCE =1,
	PRESSED =2


}	ButtonState_e;

typedef struct
{
	ButtonState_e 	State;
	GPIO_TypeDef* 	GPIO_Port;
	uint16_t 		GPIO_Pin;

	uint32_t		LastTick; // Last remembered time before steps
	uint32_t		TimerDebounce; // Fixed, settable time for debounce timer
	uint32_t		TimerLongPress; // Fixed, settable time for long press timer
	uint32_t		TimerRepeat; // Fixed, settable time for repeat timer


}Button_t;

#endif /* INC_BUTTON_H_ */
