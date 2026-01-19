#include <iostream>
using namespace std;

class Point2D { //(подготовительное задание)
protected:
    int x, y;
public:
    Point2D(int x_val = 0, int y_val = 0) : x(x_val), y(y_val) {}

    void printXY() const {
        cout << "x = " << x << ", y = " << y;
    }
};

class Z {
protected:
    int z;
public:
    Z(int z_val = 0) : z(z_val) {}

    void printZ() const {
        cout << ", z = " << z;
    }
};

class Point3D : public Point2D, public Z {
public:
    Point3D(int x_val, int y_val, int z_val) 
        : Point2D(x_val, y_val), Z(z_val) {}

    void print() const {
        cout << "Point3D(";
        printXY();
        printZ();
        cout << ")" << endl;
    }
};




class H {

    protected:
        double h;
    public:
        H(double h_val =  1.0) : h(h_val) {}

        double getH() const {
            return h;
        }
};

class Point3Dh : public Point2D, public Z, public H { // наследуем
public:
    Point3Dh(int x_val, int y_val, int z_val, double h_val) 
        : Point2D(x_val, y_val), Z(z_val), H(h_val) 
    {
        if (h == 0.0) {// проверка на ноль
            throw invalid_argument("Ошибка: h не может быть равно 0!");
        }
    }
    void print() const { // вывод с учетом h
        cout << "Point3Dh("
             << static_cast<double>(x) / h << ", "
             << static_cast<double>(y) / h << ", "
             << static_cast<double>(z) / h << ")" << endl;
    }
};

int main() {
    Point3Dh p1(2,4,6,2);
    Point3Dh p2(10, 20, 30, 10);
    Point3Dh p3(3, 6, 9, 3);

    p1.print();
    p2.print();
    p3.print();

    return 0;
}