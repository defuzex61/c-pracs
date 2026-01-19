#include "Canvas.h"
#include <gtk/gtk.h>
#include <iostream>
// компиляция + запуск: clang++ -std=c++17 main.cpp Canvas.cpp -o main `pkg-config --cflags --libs gtk+-3.0`
//./main
Canvas canvas;

static gboolean draw_callback(GtkWidget* widget, cairo_t* cr, gpointer data) {
    canvas.show(cr);
    return FALSE;
}

int main(int argc, char* argv[]) {

    //ВВОД ФИГУР С КОНСОЛИ
    int n;
    std::cout << "Сколько фигур вы хотите ввести? ";
    std::cin >> n;

    for(int i = 0; i < n; i++) {
        int type;
        std::cout << "\nВыберите фигуру:\n";
        std::cout << "1 - Точка\n2 - Линия\n3 - Прямоугольник\n4 - Закрашенный прямоугольник\n";
        std::cout << "5 - Эллипс\n6 - Закрашенный эллипс\n7 - Шестиугольник\n";
        std::cin >> type;

        double r, g, b;
        std::cout << "Введите цвет (r g b от 0 до 1): ";
        std::cin >> r >> g >> b;
        Color color = {r, g, b};

        if(type == 1) { // Точка
            int x, y;
            std::cout << "Введите x y: ";
            std::cin >> x >> y;
            canvas.add(new Point(x, y, color));
        }

        else if(type == 2) { // Линия
            int x1, y1, x2, y2;
            std::cout << "Введите x1 y1 x2 y2: ";
            std::cin >> x1 >> y1 >> x2 >> y2;
            canvas.add(new Line(x1, y1, x2, y2, color));
        }

        else if(type == 3 || type == 4) { // Прямоугольники
            int x1, y1, x2, y2;
            std::cout << "Введите x1 y1 x2 y2: ";
            std::cin >> x1 >> y1 >> x2 >> y2;
            bool filled = (type == 4);
            canvas.add(new Rectangle(x1, y1, x2, y2, color, filled));
        }

        else if(type == 5 || type == 6) { // Эллипсы
            int x1, y1, x2, y2;
            std::cout << "Введите x1 y1 x2 y2: ";
            std::cin >> x1 >> y1 >> x2 >> y2;
            bool filled = (type == 6);
            canvas.add(new Ellipse(x1, y1, x2, y2, color, filled));
        }

        else if(type == 7) { // Шестиугольник
            std::vector<std::pair<int,int> > pts;
            std::cout << "Введите 6 точек (x y):\n";
            for(int j = 0; j < 6; j++) {
                int x, y;
                std::cin >> x >> y;
                pts.push_back({x, y});
            }
            canvas.add(new Polygon(pts, color, false));
        }

        else {
            std::cout << "Неверный тип фигуры\n";
            i--; // повторить ввод
        }
    }

    //  ЗАПУСК GTK И ОТРИСОВКА 
    gtk_init(&argc, &argv);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Canvas GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);

    GtkWidget* drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_callback), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
