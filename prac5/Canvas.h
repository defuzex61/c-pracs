#ifndef CANVAS_H // Iclude guard (защита от повтторного подключения)
#define CANVAS_H

#include <vector>
#include <gtk/gtk.h>
//ОПИСАНИЕ ФИГУР И ИХ СВОЙСТВ. 
struct Color { // Структура для хранения цвета
    double r, g, b;
};

class Shape { // Абстрактный родительский класс для всех фигур
public:
    virtual void show(cairo_t* cr) = 0;
    virtual ~Shape() {}
};

class Point : public Shape { // Класс для точки
    int x, y;
    Color color;
public:
    Point(int x, int y, Color c) : x(x), y(y), color(c) {}
    void show(cairo_t* cr) override;
};

class Line : public Shape {// Класс для линии
    int x1, y1, x2, y2;
    Color color;
public:
    Line(int x1,int y1,int x2,int y2,Color c) : x1(x1),y1(y1),x2(x2),y2(y2),color(c){}
    void show(cairo_t* cr) override;
};

class Rectangle : public Shape {// Класс для прямоугольника
    int x1,y1,x2,y2;
    Color color;
    bool filled;
public:
    Rectangle(int x1,int y1,int x2,int y2,Color c,bool f=false) : x1(x1),y1(y1),x2(x2),y2(y2),color(c),filled(f){}
    void show(cairo_t* cr) override;
};

class Ellipse : public Shape { // Класс для эллипса
    int x1,y1,x2,y2;
    Color color;
    bool filled;
public:
    Ellipse(int x1,int y1,int x2,int y2,Color c,bool f=false) : x1(x1),y1(y1),x2(x2),y2(y2),color(c),filled(f){}
    void show(cairo_t* cr) override;
};

class Polygon : public Shape { // Класс для многоугольника
    std::vector<std::pair<int,int>> points;
    Color color;
    bool filled;
public:
    Polygon(const std::vector<std::pair<int,int>>& pts, Color c, bool f=false) : points(pts), color(c), filled(f) {}
    void show(cairo_t* cr) override;
};

class Canvas { // Класс для холста, содержащего фигуры
    std::vector<Shape*> figures;
public:
    void add(Shape* s) { figures.push_back(s); }
    void show(cairo_t* cr);
    void clear();
    ~Canvas();
};

#endif
