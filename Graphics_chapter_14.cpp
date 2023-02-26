#include "C:\Users\mkhit\OneDrive\Документы\fltk_gui\GUI\Simple_window.h" // get access to our window library
#include "C:\Users\mkhit\OneDrive\Документы\fltk_gui\GUI\Graph.h" // get access to our graphics library facilities

// Chapter 14.
// Solved: 1, 4, 5, 6, 8, 9, (10 - partly)
// Not solvet: 7 (postponed).
// Nothing happens: 2(?), 3.

struct New_circle : Graph_lib::Shape
{
	using Shape::Shape;
	New_circle(Point xy, int radius);
	void draw_lines()const;

	void set_radius(int rad)
	{
		r = rad;
	}

	int radius()const { return r; }

	void move(int dx, int dy)override
	{
		// ...
	}

private:
	int r;
};

New_circle::New_circle(Point xy, int radius) : r{ radius }
{
	add(xy);
}

void New_circle::draw_lines() const
{
	if (fill_color().visibility()) {	// fill
		fl_color(fill_color().as_int());
		fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, 0, 360);
		fl_color(color().as_int());	// reset color
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
	}
}

struct Smiley : New_circle
{
	using New_circle::New_circle;

	void draw_lines() const
	{
		New_circle::draw_lines();

		if (color().visibility()) {
			fl_color(color().as_int());
			int rad = New_circle::radius();
			fl_arc(point(0).x + rad / 2, point(0).y + rad / 2, rad / 3, rad / 3, 0, 360);
			fl_arc(point(0).x + rad + (rad / 2) - (rad / 3), point(0).y + rad / 2, rad / 3, rad / 3, 0, 360);
			fl_arc(point(0).x + rad / 2, point(0).y + rad / 2, rad, rad, 200, 340);
		}
	}
};

struct Frowny : New_circle
{
	using New_circle::New_circle;

	void draw_lines() const
	{
		New_circle::draw_lines();

		if (color().visibility()) {
			int rad = New_circle::radius();
			fl_arc(point(0).x + rad / 2, point(0).y + rad / 2, rad / 3, rad / 3, 0, 360);
			fl_arc(point(0).x + rad + (rad / 2) - (rad / 3), point(0).y + rad / 2, rad / 3, rad / 3, 0, 360);
			fl_arc(point(0).x + rad / 2, point(0).y + rad, rad, rad, 380, 160);
		}
	}
};

struct Shapka_veselchuka : Smiley
{
	using Smiley::Smiley;

	void draw_lines()const
	{
		Smiley::draw_lines();

		if (color().visibility())
		{
			int rad = Smiley::radius();
			fl_color(fill_color().red);
			fl_line(point(0).x, point(0).y + rad / 3, point(0).x + rad * 2, point(0).y + rad / 3);
			fl_line(point(0).x, point(0).y + rad / 3, point(0).x + rad, point(0).y - rad * 2 + rad / 3);
			fl_line(point(0).x + rad * 2, point(0).y + rad / 3, point(0).x + rad, point(0).y - rad * 2 + rad / 3);
			fl_color(color().as_int());
		}
	}
};

struct Shapka_grustishka : Frowny
{
	using Frowny::Frowny;

	void draw_lines()const
	{
		Frowny::draw_lines();

		if (color().visibility())
		{
			int rad = Frowny::radius();
			fl_color(66);
			fl_line(point(0).x, point(0).y + rad / 3, point(0).x + rad * 2, point(0).y + rad / 3);
			fl_line(point(0).x, point(0).y + rad / 3, point(0).x, point(0).y - rad);
			fl_line(point(0).x, point(0).y - rad, point(0).x + rad * 2, point(0).y - rad);
			fl_line(point(0).x + rad * 2, point(0).y + rad / 3, point(0).x + rad * 2, point(0).y - rad);
			fl_color(color().as_int());
		}
	}
};

struct Striped_rectangle : Graph_lib::Rectangle
{
	using Rectangle::Rectangle;
	void draw_lines() const;
};

void Striped_rectangle::draw_lines() const
{
	int wid = Rectangle::width();
	int hei = Rectangle::height() - 2;

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_rect(point(0).x, point(0).y, Rectangle::height(), Rectangle::width());
	}

	if (fill_color().visibility()) {
		for (int i = 0; i < wid - 1; i += 3)
		{
			fl_line(point(0).x, point(0).y + i, point(0).x + hei, point(0).y + i);
			fl_color(fill_color().as_int());
		}
	}
}

struct Striped_circle : New_circle
{
	using New_circle::New_circle;

	void draw_lines() const;
};

void Striped_circle::draw_lines() const
{
	int nr = New_circle::radius();
	int step = 25;

	if (fill_color().visibility()) {

		for (int i = 0; i < 360; i += 50)
		{
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, nr + nr - 1, nr + nr - 1, i, step);
			fl_color(fill_color().as_int());
			step += 50;
		}
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, nr + nr, nr + nr, 0, 360);
	}
}

struct Striped_closed_polyline : Graph_lib::Shape
{
	using Graph_lib::Shape::Shape;
};

struct Octagon : Graph_lib::Shape
{
	using Graph_lib::Shape::Shape;

	Octagon(Point xy, int rad) : r{ rad }, _xy{ xy }{ add_f(); }

	int radius() { return r; }
	void draw_lines() const;
	void add_f();

private:
	int r;
	Point _xy;
	vector<Point> points;
};

void Octagon::add_f()
{
	int t = 0;
	int A = 0;

	A = 2 * r;
	t = A / 2.414;

	Point a, b, c, d, e, f, g, h;

	a.x = _xy.x - r;
	a.y = _xy.y - t / 2;
	b.x = _xy.x - t / 2;
	b.y = _xy.y - r;
	c.x = _xy.x + t / 2;
	c.y = _xy.y - r;
	d.x = _xy.x + r;
	d.y = _xy.y - t / 2;
	e.x = _xy.x + r;
	e.y = _xy.y + t / 2;
	f.x = _xy.x + t / 2;
	f.y = _xy.y + r;
	g.x = _xy.x - t / 2;
	g.y = _xy.y + r;
	h.x = _xy.x - r;
	h.y = _xy.y + t / 2;

	Shape::add(a);
	Shape::add(b);
	Shape::add(b);
	Shape::add(c);
	Shape::add(c);
	Shape::add(d);
	Shape::add(d);
	Shape::add(e);
	Shape::add(e);
	Shape::add(f);
	Shape::add(f);
	Shape::add(g);
	Shape::add(g);
	Shape::add(h);
	Shape::add(h);
	Shape::add(a);
}

void Octagon::draw_lines() const
{
	Shape::draw_lines();
	if (fill_color().visibility())
	{
		for (int i = 1; i < number_of_points(); i += 2)
		{
			fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for (int i = 0; i < number_of_points(); ++i)
			{
				fl_vertex(point(i).x, point(i).y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());
		}
	}
}

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
	/*const T& operator[](int i)const;*/
	int size()const { return v.size(); }
};

Group<Graph_lib::Shape> figure;
class Chess : Graph_lib::Shape
{
	using Graph_lib::Shape::Shape;
public:
	Chess(Point xy, int x, int y) : p{ xy } { chess_board(); }
	Point get_point() const;
	void chess_board();
	void vec_output();

private:
	Point p;
};

void Chess::chess_board()
{
	int x = p.x;
	int y = p.y;
	int color = 0;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			figure.push_back(new Graph_lib::Rectangle(Point{ i * 30 + x, j * 30 + y },
				30, 30));
			figure[figure.size() - 1].set_fill_color(color);
			if (color == 0)
			{
				color += 7;
			}
			else
			{
				color = 0;
			}
		}
		if (color == 0)
		{
			color += 7;
		}
		else
		{
			color = 0;
		}
	}
}

Point Chess::get_point() const
{
	return p;
}

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

Pseudo_window::Pseudo_window(Point xy, int ww, int hh) : w{ ww }, h{ hh }, xyz{ xy }
{
	if (h <= 0 || w <= 0)
	{
		error("error: ");
	}
	new_box();
}

Pseudo_window::Pseudo_window(Point x, Point y) : w{ y.x - x.x }, h{ y.y - x.y }
{
	if (h <= 0 || w <= 0)
	{
		error("error: ");
	}
	new_box();
}

void Pseudo_window::draw_lines()const
{
	if (color().visibility())
	{
		for (int i = 1; i < number_of_points(); i += 2)
		{
			fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);
		}

		fl_arc(point(0).x - angle, point(0).y, angle + angle, angle + angle, 90, 180);
		fl_arc(point(0).x + (w - angle * 3), point(0).y, angle + angle, angle + angle, 0, 90);
		fl_arc(point(0).x - angle, point(0).y + (h - angle * 2), angle + angle, angle + angle, 180, 270);
		fl_arc(point(0).x + (w - angle * 3), point(0).y + (h - angle * 2), angle + angle, angle + angle, 270, 360);
		fl_line(point(0).x - angle, point(0).y + 70, point(0).x + w - angle, point(0).y + 70);
		fl_draw(new_text.c_str(), point(0).x, point(0).y + 50);
	}
}

void Pseudo_window::new_box()
{
	int x, y = 0;
	x = xyz.x;
	y = xyz.y;
	add(Point{ x + angle,y });
	add(Point{ (x - angle) + w ,y });
	add(Point{ x + w,(y + angle) });
	add(Point{ x + w,(y - angle) + h });
	add(Point{ (x - angle) + w,y + h });
	add(Point{ (x + angle),y + h });
	add(Point{ x,(y - angle) + h });
	add(Point{ x,(y + angle) });
	add(Point{ x,(y + angle) });
}

int main()
{
	Point tl(100, 100);
	Simple_window win(tl, 1200, 800, "Canvas");
	Graph_lib::Polygon poly;
	poly.add(Point(200, 200));
	poly.add(Point(250, 100));
	poly.add(Point(300, 200));
	poly.set_color(Graph_lib::Color::yellow);
	win.attach(poly);

	New_circle nc(Point{ 100,200 }, 50);
	nc.set_color(Graph_lib::Color::black);
	nc.move(500, 500);
	win.attach(nc);

	Smiley sm1(Point{ 400,300 }, 50);
	sm1.set_color(Graph_lib::Color::dark_blue);
	win.attach(sm1);

	Smiley sm2(Point{ 700,300 }, 150);
	sm2.set_color(Graph_lib::Color::dark_blue);
	win.attach(sm2);

	Frowny fr1(Point{ 400,450 }, 50);
	fr1.set_color(Graph_lib::Color::dark_green);
	win.attach(fr1);

	Shapka_veselchuka sv(Point{ 550,200 }, 70);
	sv.set_color(Graph_lib::Color::blue);
	win.attach(sv);

	Shapka_grustishka sg(Point{ 550,500 }, 30);
	sg.set_color(75);
	win.attach(sg);

	Striped_rectangle sr(Point{ 250, 360 }, 170, 50);
	sr.set_color(Graph_lib::Color::black);
	sr.set_fill_color(Graph_lib::Color::red);
	win.attach(sr);

	Striped_circle sc1(Point{ 150,500 }, 50);
	sc1.set_color(Graph_lib::Color::yellow);
	sc1.set_fill_color(Graph_lib::Color::yellow);
	win.attach(sc1);

	Striped_circle sc2(Point{ 650,500 }, 50);
	sc2.set_color(Graph_lib::Color::red);
	sc2.set_fill_color(Graph_lib::Color::red);
	win.attach(sc2);

	Octagon oc(Point{ 150,80 }, 20);
	oc.set_color(Graph_lib::Color::dark_blue);
	oc.set_fill_color(Graph_lib::Color::blue);
	win.attach(oc);

	Octagon oc2(Point{ 350,100 }, 50);
	oc2.set_fill_color(Graph_lib::Color::green);
	oc2.set_color(Graph_lib::Color::black);
	oc2.move(550, 300);
	win.attach(oc2);

	Graph_lib::Rectangle r(Point{ 100,100 }, Point{ 150,150 });
	r.set_color(Graph_lib::Color::black);
	r.set_fill_color(Graph_lib::Color::dark_yellow);
	r.move(200, 150);
	win.attach(r);
	win.wait_for_button();

	Simple_window win2(tl, 1200, 800, "Pseudo_window");

	Pseudo_window ps(Point{ 100,100 }, 1000, 600);
	ps.set_color(Graph_lib::Color::black);
	ps.set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 5));
	win2.attach(ps);

	Chess ch(Point{ 400,300 }, 30, 30);
	Graph_lib::Marks mrk{ "ABCDEFGHHGFEDCBA" };
	Graph_lib::Marks mrk1{ "8765432112345678" };

	for (int i = 0; i < 8; i++)
	{
		Point x(ch.get_point().x + i * 30 + 15, ch.get_point().y + 250); // 250 -> int x
		mrk.add(x);
	}
	for (int i = 0; i < 8; i++)
	{
		Point x(ch.get_point().x + i * 30 + 15, ch.get_point().y - 10);
		mrk.add(x);
	}
	for (int i = 0; i < 8; i++)
	{
		Point x(ch.get_point().x - 15, ch.get_point().y + i * 30 + 15);
		mrk1.add(x);
	}
	for (int i = 0; i < 8; i++)
	{
		Point x(ch.get_point().x + 250, ch.get_point().y + i * 30 + 15);
		mrk1.add(x);
	}	

	win2.attach(mrk);
	win2.attach(mrk1);

	for (int i = 0; i < figure.size(); i++)
	{
		win2.attach(figure[i]);
	}

	win2.wait_for_button();
}