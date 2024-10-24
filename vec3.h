#pragma once

#include <cmath>

template<typename T>
struct point3{
	T x;
	T y;
	T z;
};


//todo: overload more operatiors
template<typename T>
class vec3{
public:
	vec3() : e{0,0,0} {}
	vec3(T e0, T e1, T e2) : e{e0,e1,e2} {}

	T x() const {return e.x;}
	T y() const {return e.y;}
	T z() const {return e.z;}

	vec3<T> operator-() const {return vec3(-e.x,-e.y,-e.z);}
	vec3<T> operator+(vec3<T> &v) const {
		return vec3<T>(v.e.x+e.x,v.e.y+e.y,v.e.z+e.z);
	};
	vec3<T> operator-(vec3<T> &v) const {
		return vec3<T>(v.e.x-e.x,v.e.y-e.y,v.e.z-e.z);
	};
		vec3<T> operator*(vec3<T> &v) const {
		return vec3<T>(v.e.x*e.x,v.e.y*e.y,v.e.z*e.z);
	};
	
	vec3<T>& operator=(const vec3<T> v) {
		//dont judge me..
		//optional: rewrite it *cooler*
		e.x=(T)v.x();
		e.y=(T)v.y();
		e.z=(T)v.z();
		return *this;
	};
	
	T dot(vec3<T>a){
		return (a.e.x*e.x) + (a.e.y*e.y) +(a.e.z* e.z);
	}
	
	T dot(vec3<T>a,vec3<T>b){
		return (a.e.x*b.e.x) + (a.e.y*b.e.y) +(a.e.z* b.e.z);
	}
	
	vec3<T> cross(vec3<T>v){
		return vec3<T>(e.y * v.e.z - e.z * v.e.y,
				e.z * v.e.x - e.x * v.e.z,
				e.x * v.e.y - e.y * v.e.x);
	}
	
	vec3<T> cross(vec3<T>u,vec3<T>v){
		return vec3<T>(u.e.y * v.e.z - u.e.z * v.e.y,
				u.e.z * v.e.x - u.e.x * v.e.z,
				u.e.x * v.e.y - u.e.y * v.e.x);	
	}
	
	T length() const{
		return sqrt(length_squared());
	}
	
	T length_squared() const{
		return e.x*e.x+e.y*e.y+e.z*e.z;
	}
	

private:
	point3<T> e;
};
