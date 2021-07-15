#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <unistd.h>

int init(Display *disp, int scrn);

int main (int argc, char** argv)
{
	// Display *dis; : Points to the X Server
	// int screen;	 : Refers to which screen of display to use.
	// Window win; 	 : 
	// GC gc;
	//
	
	// Client: Application
	// Server: Display/xserver
	
	Display *display;
	int screen;
	Window win;
	Window childWin;
	XEvent event;

	// CHILD WINDOW
	// Create a window
	childWin = XCreateSimpleWindow(
			display, 
			win,
			50,
			100,
			100,
			100,
			6,
			BlackPixel(display, screen),
			WhitePixel(display, screen));

	// What kind of event will the window respond to?
	XSelectInput(display, childWin, ExposureMask | KeyPressMask);

	// Display/map the window
	XMapWindow(display, childWin);



	// Process the events
	int run = 1;
	while(run) {
		// Store next event in &event
		XNextEvent(display, &event);

		if (event.xany.window == childWin) {
			if (event.type == Expose) {
				XDrawLine(display, 
						childWin, 
						DefaultGC(display, screen),
						10,
						10,
						60,
						60);
			}
		}
	}

	return 0;

}


int init(Display *disp, int scrn)
{
	
	// Start connection
	disp = XOpenDisplay(NULL);

	// Cannot start connection to XServer
	if (!disp) {
		fprintf(stderr, "Cannot open display");
		exit(1);
	}

	// Get screen
	scrn = DefaultScreen(disp);

	return 0;
}


int createWindow(Window win, Display *disp, int scrn, int xpos, 
		int ypos, unsigned int width, unsigned int height, unsigned int borderWidth,
		unsigned long borderColorPx, unsigned long backgroundColorPx)
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
