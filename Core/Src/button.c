
#include "main.h"
#include "button.h"

void ButtonInit (Button_t* Button, GPIO_TypeDef* GPIO_Port,uint16_t GPIO_Pin, uint32_t TimerDebounce, uint32_t TimerLongPress, uint32_t TimerRepeat )
{
	Button->State = 	IDLE;
	Button->GPIO_Port = GPIO_Port;
	Button->GPIO_Pin = 	GPIO_Pin;
}
