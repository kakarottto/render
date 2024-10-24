#include "vec3.h"
#include "vec2.h"
#include "render.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

static std::vector<point2<int>> test_pts;
void render::handle_events(){
	while(SDL_PollEvent(&e)){
		if(e.type==SDL_QUIT) {running = 0; break;}
		if(e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_ESCAPE){
			running = 0;
		}
	}
}
void render::update(){}
void render::draw(){
	//drawer.draw_rect(200,200,40,140,blue_color);
	//drawer.fill_circle(155,155,50,magenta_color);
	//drawer.draw_ellipse(400,400,70,30,red_color);
	drawer.draw_poly(test_pts,{194,12,244,255});
	
	
	//drawer.draw_line(500,500,100,100,green_color);
	
	SDL_RenderPresent(renderer);
}


int main(){
	srand (time(NULL));
	
	test_pts.push_back(point2<int>{144,70});
	test_pts.push_back(point2<int>{700,70});
	test_pts.push_back(point2<int>{120,80});
	test_pts.push_back(point2<int>{300,140});
	test_pts.push_back(point2<int>{99,66});
	
	
	for(int i =0; i < 4;i++){
		int x = 100+rand()%501;
		int y = 100+rand()%501;
		std::cout <<x <<" "<< y << std::endl;
	
		test_pts.push_back(point2<int>{x,y});
	}
	
	render r;
	r.run();
	
}
