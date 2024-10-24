//the one who draws
#include <SDL2/SDL.h>
#include "draw2d.h"
//#include "draw3d.h"


//what it does:
/*
	sets the sdl window and renderer
	put pixel
	draw line between points
	2d draws
	(
		triangle,
		square,
		circle, 
		ellipse,
		polygon 
		optional: filler between vertecies 
	)
	3d draws
	(
		cube,
		cuboid,
		sphere,
		cylinder,
		cone,
		pyramid,
		ellipsoid,
		paraboloid,
		hyperboloid,
		torus
	)
	3d to 2d
	change of coord systems(decard to screen and screen to decard)
	translations
	scalings
	reflections
	shearing
	rotations
	
	
	todo:QB Raytracing tutorials
	todo:add matrix classes
*/



class render{
public:
	render(){
		window_width = 600;
		window_height = 600;
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);
		drawer.set_renderer(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		running = 1;
	}
		
	~render(){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	
	render(int width, int height){
		window_width = width;
		window_height = height;
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);
		drawer.set_renderer(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		running = 1;
	}
	
	void run(){
		running = 1;
		while (running) {
			Uint64 start = SDL_GetPerformanceCounter();

			handle_events();
			update();
			draw();
			Uint64 end = SDL_GetPerformanceCounter();

			float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();	
			SDL_Delay(floor(16.666f - elapsed)); //60 fps
			
		}
	
	}

public:
	
	
	void put_pixel(int x, int y, Color color){
		SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
		SDL_RenderDrawPoint(renderer,x,y);
		//SDL_SetRenderDrawColor(renderer,0,0,0,0);
	}
	
	void handle_events();
	void update();
	void draw();
	
	
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int window_width, window_height;
	SDL_Event e;
	bool running = 0;
	
	Draw2d drawer;
	

};
