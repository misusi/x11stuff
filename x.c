#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	Display *display;
	int screen;
	Window mainWindow;
	Window childWindow;
	XEvent event;

	int x, y, width, height;
	Window rootWindow;
	Colormap colormap;
	XColor buttonColor;
	XColor lightGrayColor, darkGrayColor;
	XGCValues gcvLightGray, gcvDarkGray;
	GC gcLightGray, gcDarkGray;
	unsigned int borderWidth, depth;


	/* Text Declaration Vars */
	XFontStruct *font;
	XTextItem ti[1];



	// Init
	display = XOpenDisplay(NULL);

	if (!display) {
		fprintf(stderr, "Cannot open display.\n");
		exit(1);
	}
	
	screen = DefaultScreen(display);


	// Windows
	// Parent
	mainWindow = XCreateSimpleWindow(
		display, 
		RootWindow(display, screen),
		100,
		100,
		500,
		300,
		1,
		BlackPixel(display, screen),
		WhitePixel(display, screen));

	XSelectInput(display, mainWindow, ExposureMask | KeyPressMask);
	XMapWindow(display, mainWindow);


	// Color: Child window
	colormap = DefaultColormap(display, screen);
	XParseColor(display, colormap, "rgb:cc/cc/cc", &buttonColor);
	XAllocColor(display, colormap, &buttonColor);

	XParseColor(display, colormap, "rgb:ee/ee/ee", &lightGrayColor);
	XAllocColor(display, colormap, &lightGrayColor);
	gcvLightGray.foreground = lightGrayColor.pixel;
	gcvLightGray.background = buttonColor.pixel;
	gcLightGray = XCreateGC(display, RootWindow(display, screen),
			GCForeground | GCBackground, &gcvLightGray);



	XParseColor(display, colormap, "rgb:88/88/88", &darkGrayColor);
	XAllocColor(display, colormap, &darkGrayColor);
	gcvDarkGray.foreground = darkGrayColor.pixel;
	gcvDarkGray.background = buttonColor.pixel;
	gcDarkGray = XCreateGC(display, RootWindow(display, screen),
			GCForeground | GCBackground, &gcvDarkGray);




	// Child
	childWindow= XCreateSimpleWindow(
		display, 
		mainWindow,
		20,
		20,
		200,
		100,
		1,
		BlackPixel(display, screen),
		buttonColor.pixel);

	XSelectInput(display, childWindow, 
			ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);
	XMapWindow(display, childWindow);


	XGetGeometry(display, childWindow, &rootWindow, &x, &y, &width, &height,
			&borderWidth, &depth);


	// Event/display loop
	int run = 1;
	while (run) 
	{

		XNextEvent(display, &event);
		if (event.xany.window == childWindow) {
			if (event.type == Expose) {
				XDrawLine(display, childWindow, gcLightGray, 
					0, 0, width - 1, 0);
				XDrawLine(display, childWindow, gcLightGray, 
					0, 0, 0, height - 1);
				XDrawLine(display, childWindow, gcDarkGray, 
					width - 1, 0, width - 1, height - 1);
				XDrawLine(display, childWindow, gcDarkGray, 
					0, height - 1, width - 1, height - 1);

				font = XLoadQueryFont(display, "Hack");
				ti[0].chars = "Press me!";
				ti[0].nchars = 9;
				ti[0].delta = 0;
				ti[0].font = font->fid;
				XDrawText(display, childWindow, DefaultGC(display, screen),
						(width-XTextWidth(font, ti[0].chars, ti[0].nchars)) / 2,
						(height-(font->ascent + font->descent)) / 2+font->ascent,
						ti, 1);
				XUnloadFont(display, font->fid);

			}
			// BUTTON PRESS
			if (event.type == ButtonPress) {
				if (event.xbutton.button == 1) {
					XDrawLine(display, childWindow, gcDarkGray, 
						0, 0, width - 1, 0);
					XDrawLine(display, childWindow, gcDarkGray, 
						0, 0, 0, height - 1);
					XDrawLine(display, childWindow, gcLightGray, 
						width - 1, 0, width - 1, height - 1);
					XDrawLine(display, childWindow, gcLightGray, 
						0, height - 1, width - 1, height - 1);
					printf("Button pressed.\n");
				}
			}
			// BUTTON RELEASE
			if (event.type == ButtonRelease) {
				if (event.xbutton.button == 1) {
					XDrawLine(display, childWindow, gcLightGray, 
						0, 0, width - 1, 0);
					XDrawLine(display, childWindow, gcLightGray, 
						0, 0, 0, height - 1);
					XDrawLine(display, childWindow, gcDarkGray, 
						width - 1, 0, width - 1, height - 1);
					XDrawLine(display, childWindow, gcDarkGray, 
						0, height - 1, width - 1, height - 1);
					printf("Button released.\n");
				}
			}
		}
	}

	return 0;
}
