#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "vec2.h"
#define PI 3.14159
//no need for SDL_Color
struct Color{
	unsigned char r,g,b,a;
	void reverse(){
		r=255-r;
		g=255-g;
		b=255-b;
	}
	
};

//todo: draw and fill polygons

static Color white_color{255,255,255,255};
static Color red_color{255,0,0,255};
static Color green_color{0,255,0,255};
static Color blue_color	{0,0,255,255};
static Color magenta_color{255,0,255,255};

class Draw2d{
public:
	Draw2d(){}
	
	void set_renderer(SDL_Renderer* ren){renderer = ren;}
	
	void put_pixel(int x, int y, Color color){
		SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
		SDL_RenderDrawPoint(renderer,x,y);
		//SDL_SetRenderDrawColor(renderer,0,0,0,0);
	}
	
	void clear_screen(Color color){
		SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
		SDL_RenderPresent(renderer);
	}
	
	void draw_line(int x1, int y1, int x2, int y2,Color color){
		
		//todo: fix drawline
		if(x1 == x2 && y1 == y2) return;
		
		if(x1>x2){
			int temp = x1;
			x1 = x2;
			x2 = temp;
		}
		if(y1>y2){
			int temp = y1;
			y1 = y2;
			y2 = temp;
		}
		
		
		//specific case for vertical lines
		if(x1 == x2){
			
			for(int y = y1; y < y2;y++){
				put_pixel(x1,y,color);
			}
			return;
		}
		
		
		int dx = abs(x1-x2);
		int dy = abs(y1-y2);
		double m = (double)(dy/dx);
		
		int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
		double x_inc =double( dx/(double)steps);
		double y_inc = double(dy/(double)steps);
		
		double x = x1;
		double y = y1;
		
		for(int i = 0; i < steps;i++){
			put_pixel(round(x),round(y),color);
			x+=x_inc;
			y+=y_inc;
		}
	}
	
	void draw_rect(int x,int y, int width, int height,Color color){
		draw_line(x,y,x+width,y,color);
		draw_line(x,y,x,y+height,color);
		draw_line(x+width,y,x+width,y+height,color);
		draw_line(x,y+height,x+width,y+height,color);
		
	}
	
	void fill_rect(int x1,int y1, int width, int height,Color color){
		for(int y =y1; y < y1+height;++y){
			for(int x=x1;x<x1+width;++x){
				put_pixel(x,y,color);
			}
		}
	}
	
	void draw_circle(int cx, int cy, int radius, Color color){
		int x=0;
		int y = radius;
		int d = 3 - 2*radius;
		while(y>=x){
			put_pixel(cx+x,cy+y,color);
			put_pixel(cx-x,cy+y,color);
			put_pixel(cx+x,cy-y,color);
			put_pixel(cx-x,cy-y,color);
			put_pixel(cx+y,cy+x,color);
			put_pixel(cx-y,cy+x,color);
			put_pixel(cx+y,cy-x,color);
			put_pixel(cx-y,cy-x,color);
			x++;
			if(d<0) d+=4*x+6;
			else{
				y--; d+=4*(x-y)+10;
			}
		}
	}
	
	void fill_circle(int cx, int cy, int radius, Color color){
		for(int y=-radius; y <=radius;++y){
			int x = int(sqrt(radius*radius - y*y));
			draw_line(cx-x,cy+y,cx+x,cy+y,color);
			
		}
	}
	
	void draw_ellipse(int cx, int cy,int a, int b, Color color){
		for(float i=0; i < 2*PI;i+=0.01){
			int x = (int)(b*cos(i)+cx);
			int y = (int)(a*sin(i)+cy);
			put_pixel(x,y,color);
		}
	}
	
	void fill_ellipse(int cx, int cy,int a, int b, Color color){
		
		int b_squared = b*b;
		int a_squared = a*a;
		int x0 = b;
		int dx = 0;
		
		//do the horiz
		for(int x = -b;x <=b;++x)	put_pixel(cx+x,cy,color);
		
		//now the halves
		for(int y=1; y <=a;++y){
			int x1 = x0-(dx-1);
			while(x1>0){
				if(x1*x1*a_squared+y*y*b_squared<=a_squared*b_squared) break;
				x1--;
			}
			dx = x0-x1;
			x0 = x1;
			for(int x = -x0;x<=x0;x++){
				put_pixel(cx+x,cy-y,color);
				put_pixel(cx+x,cy+y,color);
			}
		}
	}
	
	
	void draw_poly(std::vector<point2<int>>& arr, Color color){
		int curr_val = 0;
		
		//sort them
		/*for(int i=0; i < arr.size();i++){
			for(int j=i+1; j < arr.size();j++){
				if(arr[i] < arr[j]){
					point2<int> temp = arr.at(i);
					arr.at(i) = arr.at(j);
					arr.at(j)=temp;
				}
			}
		}*/
		
		bool ch = false;
		
		/*while(arr.size()>0){
			point2<int> sm = arr.at(0);
			arr.erase(arr.begin()+0);
			ch= !ch;
			for(int i=0; i < arr.size();i++){
				if(arr.at(i) > sm && ch){
					draw_line(sm.x,sm.y,arr.at(i).x,arr.at(i).y,color);
					sm = arr.at(i);
					arr.erase(arr.begin()+i);
					i-=1;	
				}
			}
		}*/
		for(int i =0; i < arr.size();i++){
			
			draw_line(arr.at(0).x,arr.at(0).y,arr.at(i).x,arr.at(i).y,color);
		}	
		
	}
	
	
private:
	SDL_Renderer* renderer;
};
