#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;


int main()
{
    XEvent event;
    Display *dis;
    Window root;
    Bool owner_events = False;
    unsigned int modifiers = ControlMask | LockMask;


    dis = XOpenDisplay(NULL);
    root = XDefaultRootWindow(dis);
    unsigned int keycode = XKeysymToKeycode(dis, XK_P);
    XSelectInput(dis,root, KeyPressMask);
    XGrabKey(dis, keycode, modifiers, root, owner_events, GrabModeAsync, GrabModeAsync);

    while (1) {
        Bool QuiteCycle = False;
        XNextEvent(dis, &event);
        if (event.type == KeyPress) {
            cout << "Hot key pressed!" << endl;
            XUngrabKey(dis, keycode, modifiers, root);
            QuiteCycle = True;
        }
        if (QuiteCycle) {
            break;
        }
    }
    XCloseDisplay(dis);
    return 0;
}