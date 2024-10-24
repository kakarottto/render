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
	
	bool operator==(const Color c){
		return (c.r == r & c.g == g && c.b == b && c.a == a);
	}
	
	bool operator !=(const Color c){
		return !(c.r == r & c.g == g && c.b == b && c.a == a);
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
	
	Color get_pixel(int x, int y){
		Uint32 color;
		Color outp;
		unsigned char r,g,b,a;
		SDL_Rect rect={x,y,1,1};
		SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_ARGB8888, &color, 32);
		SDL_GetRGBA(color,SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888),
					&r,&g,&b,&a);
		outp = {r,g,b,a};
		return outp;
	}
	
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
		if(x1 > x2) {
			int temp = x1;
			x1 = x2;
			x2 = temp;
		}
		if(y1>y2){
			int temp = y1;
			y1 = y2;
			y2 = temp;
		}
		
		int dx = (x2-x1);
		int dy = (y2-y1);
		
		int sx = (dx>0) ? 1 : -1;
		int sy = (dy>0) ? 1 : -1;
		
		int err = (dx>dy ? dx : -dy)/2;
		int err2=0;
		
		while(1){
			put_pixel(x1,y1,color);
			if(x1==x2 && y1==y2) return;
			err2 = err;
			if(err2 > -dx){
				err-=dy;
				x1+=sx;
			}
			if(err2<dy){
				err+=dx;
				y1+=sy;
			}
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
	
	
	void draw_polygon(std::vector<point2<int>>& arr, Color color){
		if(arr.size()<3) return;
		
		
		//sort arr
		for(int i =0; i < arr.size();i++){
			for(int j=i+1;j<arr.size();j++){
				if(arr[i]>arr[j]){
					this->swap(arr[i],arr[j]);
				}
			}
		}
		/*for(int i =1; i < arr.size();i++){
			SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
			SDL_RenderDrawLine(renderer,arr[0].x,arr[0].y,arr[i].x,arr[i].y);
			draw_line(arr[0].x,arr[0].y,arr[i].x,arr[i].y,Color{255,255,255,255});
		}*/
		
	}
	
	void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color){
		draw_line(x1,y1,x2,y2,color);
		draw_line(x1,y1,x3,y3,color);
		draw_line(x2,y2,x3,y3,color);
	}
	
	void fill_triangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color){
		draw_triangle(x1,y1, x2,y2,x3,y3, color);
		int d1 = sqrt(((y2-y1)*(y2-y1))+((x2-x1)*(x2-x1)));
		int d2 = sqrt(((y3-y2)*(y3-y2))+((x3-x2)*(x3-x2)));
		int d3 = sqrt(((y1-y3)*(y1-y3))+((x1-x3)*(x1-x3)));
		
		int tx,ty,vx,vy;
		int counter = 0;
		if(d1 <= d2){
			tx = x1;
			ty = y1;
			vx = (x2-x1)/d1;
			vy = (y2-y1)/d1;
			
			while(counter<d1){
				draw_line(x3,y3,tx,ty,color);
				tx+=vx;
				ty+=vy;
				counter++;
			}
		}
		else if(d2<=d3){
			tx = x2;
			ty = y2;
			vx = (x3-x2)/d2;
			vy = (y3-y2)/d2;
			while(counter<d2){
				draw_line(x1,y1,tx,ty,color);
				tx+=vx;
				ty+=vy;
				counter++;
			}
		}
		else{
			tx = x3;
			ty = y3;
			vx = (x1-x3)/d3;
			vy = (y1-y3)/d3;
			while(counter<d3){
				draw_line(x2,y2,tx,ty,color);
				tx+=vx;
				ty+=vy;
				counter++;
			}
		}
	}

private:
	void boundary_fill(int x, int y, Color fill, Color bound){
		//its too slow to be used (but it works)
		Color pixel = get_pixel(x,y);
		if(pixel != bound && pixel != fill){
			put_pixel(x,y,fill);
			boundary_fill(x+1,y,fill,bound);
			boundary_fill(x,y+1,fill,bound);
			boundary_fill(x-1,y,fill,bound);
			boundary_fill(x,y-1,fill,bound);
		}
	}
	//sometimes i dont wanna use STL...
	template <typename T>
	T swap(T &a, T &b){
		T t = a;
		a = b;
		b = t;
	}

	template <typename T>
	T min(T arr[]){
		int len = sizeof(arr)/sizeof(T);
		T mi = arr[0];
		for(int i =1; i < len;i++){
			if(mi>arr[i]){
				mi = arr[i];
			}
		}
		return mi;
	}
	template <typename T>
	T max(T arr[]){
		int len = sizeof(arr)/sizeof(T);
		T mi = arr[0];
		for(int i =1; i < len;i++){
			if(mi<arr[i]){
				mi = arr[i];
			}
		}
		return mi;
	}

private:
	SDL_Renderer* renderer;
};
