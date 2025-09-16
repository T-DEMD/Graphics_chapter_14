#include "C:\Users\Tigran Mkhitarian\OneDrive\Документы\fltk_gui\GUI\Simple_window.h" // get access to our window library
#include "C:\Users\Tigran Mkhitarian\OneDrive\Документы\fltk_gui\GUI\Graph.h" // get access to our graphics library facilities
#pragma once

//----------------------------------------------------------------------Chapter 14.
//Solved: 1, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14.
//Not solved: 2, 3, 7 (postponed).



//------  Circle_shape  -----------
// Графическая окружность, наследуемая от Graph_lib::Shape.

struct Circle_shape : Graph_lib::Shape
{
	using Shape::Shape;
	Circle_shape(Point xy, int radius);
	void draw_lines()const;

	void set_radius(int rad);

	int radius()const { return r; }

	void move(int dx, int dy)override;

private:
	int r;
};

//-------- Smiley  -----------
// Производный от Circle_shape класс.
struct Smiley : Circle_shape
{
	using Circle_shape::Circle_shape;
	void draw_lines() const;
};

//--------  Frowny  -----------
// Производный от Circle_shape класс.
struct Frowny : Circle_shape
{
	using Circle_shape::Circle_shape;

	void draw_lines() const;
};

//--------  Clowns_hat ---------
struct Clowns_hat : Smiley
{
	using Smiley::Smiley;
	void draw_lines() const;
};

//---------  Brick  -------------
struct Brick : Frowny
{
	using Frowny::Frowny;
	void draw_lines()const;
};

//--------  Striped_rectangle  -----------
struct Striped_rectangle : Graph_lib::Rectangle
{
	using Rectangle::Rectangle;
	void draw_lines() const;
};

//---------  Striped_circle  -----------
struct Striped_circle : Circle_shape
{
	using Circle_shape::Circle_shape;
	void draw_lines() const;
};

//---------  Striped_closed_polyline  -----------

struct Striped_closed_polyline : Graph_lib::Shape
{
	using Graph_lib::Shape::Shape;
};

//---------  Octagon  -----------

struct Octagon : Graph_lib::Shape
{
	using Graph_lib::Shape::Shape;

	Octagon(Point xy, int rad);

	int radius() { return r; }
	void draw_lines() const;
	void calculate_octagon_points();

private:
	int r;
	Point center_point;
	vector<Point> points;
};

//---------------------------------------------------------------------
template<class T> class Group
{
	vector<T*> v;
	vector<T*> owned;
public:
	Group() {};
	Group(T* a, T* b = 0, T* c = 0, T* d = 0);
	~Group() { for (int i = 0; i < owned.size(); i++)delete owned[i]; }
	void push_back(T& s) { v.push_back(&s); }
	void push_back(T* p) { v.push_back(p); owned.push_back(p); }

	T& operator[](int i) { return *v[i]; }
	const T& operator[](int i)const { return *v[i]; }
	int size()const { return v.size(); }
};

//--------------------------------------------------------------------
Group<Graph_lib::Shape> figure;
class Chess : Graph_lib::Shape
{
	using Graph_lib::Shape::Shape;
public:
	Chess(Point xy, int square);

	Point get_point() const;
	void draw_chess_board();
	int get_square() const { return s; }
private:
	int s;
	Point p;
};
