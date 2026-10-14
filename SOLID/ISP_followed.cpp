#include<iostream>
#include<vector>
#include<stdexcept>

using namespace std;

class TwoDimensionalShape {
    public:
        virtual double area() = 0;
};

class ThreeDimensionalShape {
    public:
        virtual double volume() = 0;
        virtual double area() = 0;
};

class Square: public TwoDimensionalShape {
    private:
        double side;
    public:
        Square(double s) : side(s) {}
        double area() override {
            return side * side;
        }
};

class Rectangle: public TwoDimensionalShape {
    private:
        double length;
        double width;
    public:
        Rectangle(double l, double w) : length(l), width(w) {}
        double area() override {
            return length * width;
        }
};

class Cube: public ThreeDimensionalShape {
    private:
        double side;
    public:
        Cube(double s) : side(s) {}
        double area() override {
            return 6 * side * side;
        }
        double volume() override {
            return side * side * side;
        }
};

int main() {
    TwoDimensionalShape* square = new Square(5.0);
    TwoDimensionalShape* rectangle = new Rectangle(4.0, 6.0);
    ThreeDimensionalShape* cube = new Cube(3.0);

    cout<<square->area()<<endl;
    cout<<rectangle->area()<<endl;
    cout<<cube->area()<<endl;
    cout<<cube->volume()<<endl;

    return 0;
}