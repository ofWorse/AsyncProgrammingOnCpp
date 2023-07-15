#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// старинный метод конструирования окон 
int main(void) {
	Display *display;
	Window window;
	XEvent event;
	char *msg = "Hello, World!";
	int s;
// открываем соединение с сервером
	display = XOpenDisplay(NULL);
	if(display == NULL) {
		fprintf(stderr, "Cannot open display!\n");
		exit(EXIT_FAILURE);
	}
	s = DefaultScreen(display);
// создаем окно
	window = XCreateSimpleWindow(
			display, RootWindow(display, s), 10, 10, 200, 200, 1,
			BlackPixel(display, s), WhitePixel(display, s)
	);
// выбираем события, которые нам требуются
	XSelectInput(display, window, ExposureMask | KeyPressMask);
// выводим окно
	XMapWindow(display, window);
// отображаем окно
	for(;;) {
		XNextEvent(display, &event);

		// выводим или перевыводим окно
		if(event.type == Expose) {
			XFillRectangle(display, window, 
					DefaultGC(display, s), 20, 20, 10, 10);
			XDrawString(display, window,
					DefaultGC(display, s), 50, 50, msg, strlen(msg));
		}
		// выход при нажатии клавиши
		if(event.type == KeyPress)
			break;
	}

// закрываем соединение с дисплеем
	XCloseDisplay(display);
	return EXIT_SUCCESS;
}
