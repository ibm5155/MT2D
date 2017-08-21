#include "MT2D_SDL_Event_Handler.h"
#include <MT2D/MT2D_System_Calls.h>
#include <MT2D/SDL/Render/MT2D_SDL_Render.h>
#include <MT2D/MT2D_Debug.h>
#include <MT2D/Joystick/MT2D_Joystick.h>

extern MT2D_Joystick *GlobalJoystickHandler;


MT2D_SDL_Events MainEvents;
SDL_Event Events;

void MT2D_SDL_REMOVE_Key_Buffer(__int32 Key) {
	int i = 0, j = 0;
	if (MainEvents.Keyboard_Buffer_Count > 0) {
		while (i < MainEvents.Keyboard_Buffer_Count && MainEvents.Keyboard_Buffer[i] != Key) {
			i++;
		}
		if (MainEvents.Keyboard_Buffer[i] == Key) {
			/*We found that key so remove it*/
			while (i < MainEvents.Keyboard_Buffer_Count - 1) {
				/*Pass everything after that key one index before*/
				MainEvents.Keyboard_Buffer[i] = MainEvents.Keyboard_Buffer[i + 1];
				i++;
			}
			/*resize the memory*/
			MainEvents.Keyboard_Buffer = (__int32*)realloc(MainEvents.Keyboard_Buffer, (MainEvents.Keyboard_Buffer_Count) * sizeof(__int32));
			MainEvents.Keyboard_Buffer_Count--;
		}
	}
}

void MT2D_SDL_ADD_Key_Buffer(__int32 Key) {
	int i = 0;
	while (i < MainEvents.Keyboard_Buffer_Count && MainEvents.Keyboard_Buffer[i] != Key) {
		i++;
	}
	if (i == MainEvents.Keyboard_Buffer_Count) {
		if (MainEvents.Keyboard_Buffer_Count == 0) {
			MainEvents.Keyboard_Buffer = (__int32*)malloc(sizeof(__int32));
		}
		else {
			MainEvents.Keyboard_Buffer = (__int32*)realloc(MainEvents.Keyboard_Buffer, (MainEvents.Keyboard_Buffer_Count + 1) * sizeof(__int32));
		}
		MainEvents.Keyboard_Buffer[MainEvents.Keyboard_Buffer_Count] = Key;
		MainEvents.Keyboard_Buffer_Count++;
	}
}


void MT2D_SDL_Event_Handler() {
	while(SDL_PollEvent(&Events) != 0) {//As this function implicitly calls SDL_PumpEvents(), you can only call this function in the thread that set the video mode. 
		if (Events.type == SDL_KEYDOWN) {
			//clone the event data
			MT2D_SDL_ADD_Key_Buffer(Events.key.keysym.sym);
			MainEvents.Keyboard_Pressed = true;
			MainEvents.Keyboard.keysym = Events.key.keysym;
			MainEvents.Keyboard.padding2 = Events.key.padding2;
			MainEvents.Keyboard.padding3 = Events.key.padding3;
			MainEvents.Keyboard.repeat = Events.key.repeat;
			MainEvents.Keyboard.state = Events.key.state;
			MainEvents.Keyboard.timestamp = Events.key.timestamp;
			MainEvents.Keyboard.type = Events.key.type;
			MainEvents.Keyboard.windowID = Events.key.windowID;
		}
		else if (Events.type == SDL_KEYUP) {
			MT2D_SDL_REMOVE_Key_Buffer(Events.key.keysym.sym);
		}
		else if (Events.type == SDL_WINDOWEVENT) {
			if (Events.window.event == SDL_WINDOWEVENT_RESIZED || Events.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				MainEvents.Window.data1 = Events.window.data1;
				MainEvents.Window.data2 = Events.window.data2;
				MainEvents.Window_Resized = true;
				MainEvents.Window_Started = true;
			}
		}
		else if (Events.type == SDL_FINGERDOWN) {
			MainEvents.Keyboard_Pressed = true;
			MainEvents.Keyboard.keysym.sym = 32;
		}
		else if (Events.type == SDL_JOYAXISMOTION) {
			if (Events.jaxis.axis == 0) {
				// X axis
				GlobalJoystickHandler->Left_X_axis = Events.jaxis.value;
				GlobalJoystickHandler->Left_Modified = true;
				GlobalJoystickHandler->Touched = true;
			}
			else if (Events.jaxis.axis == 1) {
				// Y axis
				GlobalJoystickHandler->Left_Y_axis = Events.jaxis.value;
				GlobalJoystickHandler->Left_Modified = true;
				GlobalJoystickHandler->Touched = true;
			}
		}
		else if (Events.type == SDL_JOYBUTTONDOWN) {
			if (Events.jbutton.button < 4) {
				GlobalJoystickHandler->Button_Pressed[Events.jbutton.button] = true;
				GlobalJoystickHandler->Touched = true;
			}
		}
		else if (Events.type == SDL_QUIT) {
			SDL_Quit();
			exit(0);
		}
		printf("\n\n");
	}
}

void MT2D_SDL_Event_Handler_NoLoop() {
	if(SDL_PollEvent(&Events) != 0) {//As this function implicitly calls SDL_PumpEvents(), you can only call this function in the thread that set the video mode. 
		if (Events.type == SDL_KEYDOWN || Events.type == SDL_KEYUP) {
			//clone the event data
			MainEvents.Keyboard_Pressed = true;
			MainEvents.Keyboard.keysym = Events.key.keysym;
			MainEvents.Keyboard.padding2 = Events.key.padding2;
			MainEvents.Keyboard.padding3 = Events.key.padding3;
			MainEvents.Keyboard.repeat = Events.key.repeat;
			MainEvents.Keyboard.state = Events.key.state;
			MainEvents.Keyboard.timestamp = Events.key.timestamp;
			MainEvents.Keyboard.type = Events.key.type;
			MainEvents.Keyboard.windowID = Events.key.windowID;
		}
		else if (Events.type == SDL_WINDOWEVENT) {
			if (Events.window.event == SDL_WINDOWEVENT_RESIZED || Events.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				MainEvents.Window.data1 = Events.window.data1;
				MainEvents.Window.data2 = Events.window.data2;
				MainEvents.Window_Resized = true;
				MainEvents.Window_Started = true;
			}
		}
		else if (Events.type == SDL_FINGERDOWN) {
			MainEvents.Keyboard_Pressed = true;
			MainEvents.Keyboard.keysym.sym = 32;
		}
		else if (Events.type == SDL_JOYAXISMOTION) {
			if (Events.jaxis.axis == 0) {
				// X axis
				GlobalJoystickHandler->Left_X_axis = Events.jaxis.value;
				GlobalJoystickHandler->Left_Modified = true;
				GlobalJoystickHandler->Touched = true;
			}
			else if (Events.jaxis.axis == 1) {
				// Y axis
				GlobalJoystickHandler->Left_Y_axis = Events.jaxis.value;
				GlobalJoystickHandler->Left_Modified = true;
				GlobalJoystickHandler->Touched = true;
			}
		}
		else if (Events.type == SDL_JOYBUTTONDOWN) {
			if (Events.jbutton.button < 4) {
				GlobalJoystickHandler->Button_Pressed[Events.jbutton.button] = true;
				GlobalJoystickHandler->Touched = true;
			}
		}
		else if (Events.type == SDL_QUIT) {
			SDL_Quit();
			exit(0);
		}
	}
}

