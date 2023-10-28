
#include "main.h"
#include "button.h"

//ATTENTION! Button with PULL UP or PULL DOWN ?
static uint8_t ButtonIsPushed(Button_t* Button)
{
	// according to schematic pressed makes GPIO LOW
	// Button pressed - return 1
	// Button released - return 0
	if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(Button->GPIO_Port, Button->GPIO_Pin))
		return 1;
	else
		return 0;
}


void ButtonInit (Button_t* Button, GPIO_TypeDef* GPIO_Port,uint16_t GPIO_Pin,
				 uint32_t TimerDebounce, uint32_t TimerLongPress, uint32_t TimerRepeat)
{
	Button-> State = IDLE;
	Button-> GPIO_Port = GPIO_Port;
	Button-> GPIO_Pin = GPIO_Pin;
	Button-> TimerDebounce = TimerDebounce;
	Button-> TimerLongPress = TimerLongPress;
	Button-> TimerRepeat = TimerRepeat;
}

void ButtonIdleRoutine (Button_t* Button)
{
	if (ButtonIsPushed(Button))
	{
		Button->LastTick= HAL_GetTick(); // Remember current tick for Debounce software timer
		Button->State = DEBOUNCE;        // jump to debounce state (switch)
	}
	else
	{
		if (Button->ButtonIdle != NULL)
		{
			Button->ButtonIdle();

		}
	}
}

void ButtonDebounceRoutine (Button_t* Button)
{
	if ( (HAL_GetTick() - Button->LastTick)> Button->TimerDebounce )
	{
		if (ButtonIsPushed(Button))
			{
				//if still prassed
				Button->LastTick = HAL_GetTick();
				Button->State = PRESSED;
				if (Button->ButtonPressed != NULL) //check if callback funtion was registrated
				{
					Button-> ButtonPressed();
				}
			}
		else
		{
			//if button was released during debounce time
			Button->State = IDLE;

		}
	}
}

void ButtonPressedRoutine (Button_t* Button)
{
	if (!ButtonIsPushed(Button)) //if was released
	{
		Button->State = IDLE;
	}
	else
	{
		if((HAL_GetTick() - Button->LastTick) > Button->TimerLongPress) // Check if Long Press Timer elapsed
				{
					Button->State = REPEAT;
					Button->LastTick = HAL_GetTick();

					if(Button->ButtonLongPressed != NULL) // Check if callback was registrated
					{
						Button->ButtonLongPressed();
					}
				}

	}
}

void ButtonRepeatRoutine (Button_t* Button)
{
	if(!ButtonIsPushed(Button))
		{

		Button->State = IDLE;
		}
		else
		{

			if((HAL_GetTick() - Button->LastTick) > Button->TimerRepeat)
			{
				Button->LastTick = HAL_GetTick();

				if(Button->ButtonRepeat != NULL)
				{
					Button->ButtonRepeat();
				}
			}
		}

}

void ButtonTask(Button_t* Button)
{
	switch(Button->State)
	{
		case IDLE:
			// do IDLE
			ButtonIdleRoutine(Button);
			break;

		case DEBOUNCE:
			// do DEBOUNCE
			ButtonDebounceRoutine(Button);
			break;

		case PRESSED:
			// do PRESSED
			ButtonPressedRoutine(Button);
			break;

		case REPEAT:
			// do REPEAT
			ButtonRepeatRoutine(Button);
			break;

		default:
			break;
	}
}




void SetButtonTimerDebounce (Button_t* Button, uint32_t TimerDebounce)
{
	Button-> TimerDebounce = TimerDebounce;
}

void SetButtonTimerLongPress (Button_t* Button, uint32_t TimerLongPress)
{
	Button-> TimerLongPress = TimerLongPress;
}

void SetButtonTimerRepeat (Button_t* Button, uint32_t TimerRepeat)
{
	Button-> TimerRepeat = TimerRepeat;
}


// Register callbacks

void ButtonRegisterIdleCallback(Button_t* Button, void (*Callback)(void))
{
	Button->ButtonIdle = Callback; // Set new callback for button press
}

void ButtonRegisterPressedCallback(Button_t* Button, void (*Callback)(void))
{
	Button->ButtonPressed = Callback; // Set new callback for button press
}

void ButtonRegisterLongPressCallback(Button_t* Button, void (*Callback)(void))
{
	Button->ButtonLongPressed = Callback; // Set new callback for button press
}

void ButtonRegisterRepeatCallback(Button_t* Button, void (*Callback)(void))
{
	Button->ButtonRepeat = Callback; // Set new callback for button press
}









