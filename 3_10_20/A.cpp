#include<iostream>
#define UNDEFINED 0
#define LINE 1
#define RECTANGLE 2
#define CUBE 3

using namespace std;


class Shape
{
    int type;
public:
    Shape()
    {
        type = UNDEFINED;
        cout<<" In Shape with Type "<<type<<endl;
    }

    Shape(int type)
    {
        this->type = type;
        cout<<" In Shape with Type "<<type<<endl;
    }

    virtual int area()
    {

        cout<<" Overload this function in derived class"<<endl;
        return -1;
    }

    virtual int volume()
    {
        cout<<" Overload this function in derived class"<<endl;
        return -1;
    }

    int get_type() {
        return type;
    }
    void set_type(int type) {
        this->type = type;
    }
    ~Shape() {
        cout << " destructing shape" << endl ;
    }
};


class Line: public Shape
{
public:
    int length;
    Line()
    {
        length = 0;
        cout<<" In Line with length "<<length<<endl;
    }
    Line(int type, int length):Shape(type)
    {
        this->length = length;
        cout<<" In Line with length "<<length<<endl;
    }

    ///override area() and volume()
    int area()
    {
        cout << " Area of line 0" << endl ;
        return 0;
    }

    int volume()
    {
        cout <<" Volume of line 0 " << endl;
        return 0;
    }
    int getlength () {
        return length ;
    }
    ///setter getter if required
    ~Line() {
        cout << " Destructing length" << endl ;
    }

};

class Rectangle: public Line
{
    int width;
public:
    Rectangle()
    {
        width = 0;
        length = 0;
        cout<<" In Rectangle with width "<<width<<endl;
    }

    Rectangle(int type, int length, int width):Line(type,length)
    {
        this->width = width;
        cout<<" In Rectangle with width "<<width<<endl;
    }

    ///override area() and volume()
    int area()
    {
        cout << " the area of  rectengle " << width * length << endl ;
        return width * length  ;
    }

    int volume()
    {
        cout <<  " The volume of rectengle 0" << endl ;
        return 0;
    }
    int getlength() {
        return length  ;
    }
    int getwidth() {
        return width ;
    }
    ~Rectangle() {
        cout <<  " Destructing Rectangle" << endl;
    }


    ///setter getter if required

};

class Cube: public Rectangle
{
    int height;
public:
    Cube()
    {
        height = 0;
        /// set length and width
    }

    Cube(int type, int length, int width, int height): Rectangle(type, length, width)
    {
        cout <<  " in cube wiht height " << height << endl ;
        this->height = height;
    }

    ///override area() and volume()
    int area()
    {
        cout << " the area of cube is " << 2 * (getlength() * height + getwidth() * height + getlength() * getwidth() )  << endl;
        return 0;
    }

    int volume()
    {
        cout <<  " the Volume of cube is " <<getlength() * getwidth() * height << endl;
        return 0;
    }
    ~Cube() {
        cout <<  " destructing cube " << endl ;
    }

    ///setter getter if required

};


int main()
{
    Shape s;
    s.area();
    ///Overload this function in derived class
    s.volume();
    ///Overload this function in derived class

    Line l(LINE, 5);
    ///Implement area and volume function
    l.area();
    ///Area is 0
    l.volume();
    ///Volume is 0

    Rectangle r(RECTANGLE, 5, 2);
    ///Notice that access modifier is private
    r.area();
    ///Area is 10
    r.volume();
    ///Volume is 0

    Cube c(CUBE, 5, 2, 4);
    ///You can not access length due to private modifier in rectangle
    ///write necessary methods in rectangle to access length
    c.area();
    ///Area is 76
    c.volume();
    ///Volume is 40

    ///Demonstration of Virtual Function in Shape
    Shape* s1;
    s1 = &c;
    s1->area();
    ///Area is 76
    s1->volume();
    ///Volume is 40

    ///write destructor function and observe (by printing something) the order of constructor and destructor call

    return 0;
}
