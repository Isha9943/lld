#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Shape {
    public:
        virtual double area() = 0;
        virtual double volume() = 0;
};

// Square is a 2D shape, but is forced to implement volume() method
class Square: public Shape {
    private:
        double side;
    public:
        Square(double s) : side(s) {}
        double area() override {
            return side * side;
        }
        double volume() override {
            throw logic_error("Square does not have a volume");
        }
};

// Rectangle is a 2D shape, but is forced to implement volume() method
class Rectangle: public Shape {
    private:
        double length;
        double width;
    public:
        Rectangle(double l, double w) : length(l), width(w) {}
        double area() override {
            return length * width;
        }
        double volume() override {
            throw logic_error("Rectangle does not have a volume");
        }
};

class Cube: public Shape {
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

int main(){
    Shape* square = new Square(5.0);
    Shape* rectangle = new Rectangle(4.0, 6.0);
    Shape* cube = new Cube(3.0);

    cout<<square->area()<<endl;
    cout<<rectangle->area()<<endl;
    cout<<cube->area()<<endl;
    cout<<cube->volume()<<endl;

    try {
        cout<<square->volume()<<endl;
    } catch (const logic_error& e) {
        cout<<e.what()<<endl;
    }
    try {
        cout<<rectangle->volume()<<endl;
    } catch (const logic_error& e) {
        cout<<e.what()<<endl;
    }
    return 0;
}
