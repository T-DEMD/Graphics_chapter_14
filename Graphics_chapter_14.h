#include "C:\Users\Tigran Mkhitarian\OneDrive\Документы\fltk_gui\GUI\Simple_window.h" // get access to our window library
#include "C:\Users\Tigran Mkhitarian\OneDrive\Документы\fltk_gui\GUI\Graph.h" // get access to our graphics library facilities
#pragma once

//----------------------------------------------------------------------Chapter 14.
//Solved: 1, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14.
//Not solved: 2, 3, 7 (postponed).



//------  Circle_shape  -----------

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
	/*Group(T* a, T* b = 0, T* c = 0, T* d = 0);*/
	~Group() { for (int i = 0; i < owned.size(); i++)delete owned[i]; }
	void push_back(T& s) { v.push_back(&s); }
	void push_back(T* p) { v.push_back(p); owned.push_back(p); }

	T& operator[](int i) { return *v[i]; }
	const T& operator[](int i)const { return *v[i]; }
	int size()const { return v.size(); }
};

//--------------------------------------------------------------------
Group<Graph_lib::Shape> figure_for_chess;
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

// --------------------------------------------------------------------
struct Pseudo_window : Graph_lib::Shape
{
	using Graph_lib::Shape::Shape;
	Pseudo_window(Point xy, int hh, int ww);
	Pseudo_window(Point x, Point y);
	void new_box();
	void draw_lines() const;

private:
	int h;
	int w;
	int width = 0;
	int height = 0;
	int angle = 10;
	string new_text = "Chess";
	Point xyz;
};

//--------------------------------------------------------------------
struct Triangle : Graph_lib::Shape
{
	using Graph_lib::Shape::Shape;
	Triangle() {}
	Triangle(Point x) : xy{ x } { add(xy); draw_lines(); }
	void draw_lines()const;
	Point get_center_point() { return xy; }
private:
	Point xy;
};

//--------------------------------------------------------------------
struct Binary_tree : Graph_lib::Shape
{
	using Graph_lib::Shape::Shape;
	virtual void add(Point p) { Shape::add(p); }
	virtual void mark(string marks) { label_sequence = marks; }
protected:
	Binary_tree() {}
	Binary_tree(string arrow_up_down) :s{ arrow_up_down } {}
	virtual void draw_lines()const;
	virtual void draw_branch(int k)const;
	virtual void sort_marks()const;
	virtual void set_level(int level) { tree_level = level; }
	virtual int get_level() { return tree_level; }
private:
	int tree_level;
	string s;
	string label_sequence;
};

//--------------------------------------------------------------------
Group<Graph_lib::Shape> triangle_shape;
struct Binary_tree_from_triangle : Binary_tree
{
	using Binary_tree::Binary_tree;
	Binary_tree_from_triangle(Point p, int level);
	Binary_tree_from_triangle(Point p, int level, string arrow);
	void draw_triangle();
private:
	int levels;
	Point xy;
};

//--------------------------------------------------------------------
Group<Graph_lib::Shape> rectangle_shape;
struct Binary_tree_from_rectangle : Binary_tree
{
	using Binary_tree::Binary_tree;
	Binary_tree_from_rectangle(Point p, int level);
	Binary_tree_from_rectangle(Point p, int level, string arrow);
	void draw_rectangle();
private:
	int levels;
	Point xy;
};

//--------------------------------------------------------------------
Group<Graph_lib::Shape> circle_shape;
struct Binary_tree_from_circle : Binary_tree
{
	using Binary_tree::Binary_tree;
	Binary_tree_from_circle(Point p, int level);
	Binary_tree_from_circle(Point p, int level, string arrow);
	void draw_circle();
private:
	int levels;
	Point xy;
};