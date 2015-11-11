/* Rendvr wrapper library */
/* SDL2 window and context creation wrapper class to use with the OpenGL library */

#include "window.h"
#include <GL/glew.h>

window::window(int WIDTH, int HEIGHT, const std::string& title) {
    // 24-bit color with 8-bits for transparency and double-buffering
	SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
	screen = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(screen);

	GLenum res = glewInit();
    //if(res != GLEW_OK) { std::cerr << "Glew failed to initialize!" << std::endl; }
    
    // Enable depth buffering and culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
    closed = false;
}

window::~window() {
	this->close();
}

void window::close() {
    closed = true;
    SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(screen);
	SDL_Quit();
}

bool window::isClosed() {
    return closed;
}

void window::paint(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void window::swapBuffers() {
    // Update the screen using double buffering
	SDL_GL_SwapWindow(screen);
    
    // Event handling -- key presses and exit
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) 
            closed = true; 
    }
}
