#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SDL2/SDL.h>

class window {
	public: 
		window(int WIDTH, int HEIGHT, const std::string &title);
		void paint(float r, float g, float b, float a);
		void swapBuffers();
		virtual ~window();
        bool isClosed();
        void close();
        
	private: 
		window(const window&);
		SDL_Window *screen;
		SDL_GLContext glContext;
        bool closed;
};

#endif //WINDOW_H