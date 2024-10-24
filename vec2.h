#pragma once
#include <cmath>


template<typename T>
struct point2{
	T x;
	T y;
	bool operator<(const point2 p){
		return p.x < x || p.y < y;
	}
	bool operator>(const point2 p){
		return p.x > x || p.y > y;
	}
};


template<typename T>
class vec2{
public:
	vec2() : e{0,0} {}
	vec2(T e0, T e1) : e{e0,e1} {}

	T x() const {return e.x;}
	T y() const {return e.y;}

	vec2<T> operator-() const {return vec2(-e.x,-e.y);}
	vec2<T> operator+(vec2<T> &v) const {
		return vec2<T>(v.e.x+e.x,v.e.y+e.y);
	};
	vec2<T> operator-(vec2<T> &v) const {
		return vec2<T>(v.e.x-e.x,v.e.y-e.y);
	};
		vec2<T> operator*(vec2<T> &v) const {
		return vec2<T>(v.e.x*e.x,v.e.y*e.y);
	};
	
	vec2<T>& operator=(const vec2<T> &v) {
		//dont judge me..
		e.x=(T)v.x();
		e.y=(T)v.y();
		return *this;
	};
	
	T dot(vec2<T>a){
		return (a.e.x*e.x) + (a.e.y*e.y);
	}
	
	T dot(vec2<T>a,vec2<T>b){
		return (a.e.x*b.e.x) + (a.e.y*b.e.y);
	}
		
	T length() const{
		return sqrt(length_squared());
	}
	
	T length_squared() const{
		return e.x*e.x+e.y*e.y;
	}
	

private:
	point2<T> e;
};
