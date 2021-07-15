#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

int createWindow(
		Window win, 
		Display *disp, 
		int scrn, 
		int xpos, 
		int ypos, 
		unsigned int width, 
		unsigned int height, 
		unsigned int borderWidth, 
		unsigned long borderColorPx, 
		unsigned long backgroundColorPx
);

