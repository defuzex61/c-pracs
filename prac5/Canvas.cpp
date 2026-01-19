#include "Canvas.h"
// Реализация методов отображения фигур на холсте с использованием Cairo 
void Point::show(cairo_t* cr) {
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    cairo_rectangle(cr, x, y, 3, 3);
    cairo_fill(cr);
}

void Line::show(cairo_t* cr) {
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    cairo_move_to(cr, x1, y1);
    cairo_line_to(cr, x2, y2);
    cairo_stroke(cr);
}

void Rectangle::show(cairo_t* cr) {
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    if(filled) {
        cairo_rectangle(cr, x1, y1, x2-x1, y2-y1);
        cairo_fill(cr);
    } else {
        cairo_rectangle(cr, x1, y1, x2-x1, y2-y1);
        cairo_stroke(cr);
    }
}

void Ellipse::show(cairo_t* cr) {
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    double cx = (x1+x2)/2.0, cy = (y1+y2)/2.0;
    double rx = (x2-x1)/2.0, ry = (y2-y1)/2.0;
    cairo_save(cr);
    cairo_translate(cr, cx, cy);
    cairo_scale(cr, rx, ry);
    cairo_arc(cr, 0, 0, 1.0, 0, 2*3.1415926535);
    cairo_restore(cr);
    if(filled) cairo_fill(cr); else cairo_stroke(cr);
}

void Polygon::show(cairo_t* cr) {
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    if(points.empty()) return;
    cairo_move_to(cr, points[0].first, points[0].second);
    for(size_t i=1;i<points.size();i++)
        cairo_line_to(cr, points[i].first, points[i].second);
    cairo_close_path(cr);
    if(filled) cairo_fill(cr); else cairo_stroke(cr);
}

void Canvas::show(cairo_t* cr) {
    for(auto f : figures) f->show(cr);
}

void Canvas::clear() {
    for(auto f: figures) delete f;
    figures.clear();
}

Canvas::~Canvas() { clear(); }
