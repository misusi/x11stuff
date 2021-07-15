#include "win.h"

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
		unsigned long backgroundColorPx)
{
	win = XCreateSimpleWindow(
			disp, 
			RootWindow(disp, scrn),
			xpos,
			ypos,
			width,
			height,
			borderWidth,
			borderColorPx,
			backgroundColorPx);

	// What kind of event will the window respond to?
	XSelectInput(disp, win, ExposureMask | KeyPressMask);

	// Display/map the window
	XMapWindow(disp, win);

	return 0;
}
