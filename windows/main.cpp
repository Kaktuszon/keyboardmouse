#include <iostream>
#include <windows.h>

void leftClick();
float handleSpeed(float _speed);

int main() {
    float mouse_x; //X position of the mouse
    float mouse_y; //Y position of the mouse
    float mouse_speed = 0.005;

    POINT pointer; //Mouse pointer

    //Set the X & Y position from the mouse
    if(GetCursorPos(&pointer)) {
        mouse_x = pointer.x;
        mouse_y = pointer.y;
    }

    //Run as long as END key is not pressed
    while(!GetAsyncKeyState(VK_END)) {
        mouse_speed = handleSpeed(0.005);
        //Check if capslock is pressed, we only want to run mouse movement while capslock is on.
        if((GetKeyState(VK_CAPITAL) & 0x001) != 0) {
            if(GetAsyncKeyState(VK_LEFT)) {
                mouse_x = mouse_x - mouse_speed;
                SetCursorPos(mouse_x, mouse_y);
            }

            if(GetAsyncKeyState(VK_RIGHT)) {
                mouse_x = mouse_x + mouse_speed;
                SetCursorPos(mouse_x, mouse_y);
            }

            if(GetAsyncKeyState(VK_UP)) {
                mouse_y = mouse_y - mouse_speed;
                SetCursorPos(mouse_x, mouse_y);
            }

            if(GetAsyncKeyState(VK_DOWN)) {
                mouse_y = mouse_y + mouse_speed;
                SetCursorPos(mouse_x, mouse_y);
            }

            //If space is pressed, press left mouse button down and up
            if(GetAsyncKeyState(VK_SPACE)) {
                leftClick();
            }
        } else { //If capslock is off we can get the mouse position for smoother use
            if(GetCursorPos(&pointer)) {
                mouse_x = pointer.x;
                mouse_y = pointer.y;
            }
        }
    }

    return 0;
}

void leftClick() {
    INPUT input[2] = {};
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    Sleep(100); //So we cannot spam by holding the button

    SendInput(ARRAYSIZE(input), input, sizeof(INPUT));
}

/*
    Left Shift for double speed
    Left Shift + left control for triple speed
*/
float handleSpeed(float _speed) {
    float holdspeed = _speed;

    if(GetAsyncKeyState(VK_LSHIFT)) {
        holdspeed = _speed * 2;
        if(GetAsyncKeyState(VK_LCONTROL)) {
            holdspeed = _speed * 3;
        }
    } else {
        holdspeed = _speed;
    }

    return holdspeed;
}