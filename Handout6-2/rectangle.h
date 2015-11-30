#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

class Rectangle
{
public:
    Rectangle()
    {
        posX = 0;
        posY = 0;
        height = 0;
        width = 0;
    }
    Rectangle(double _posX, double _posY, double _height, double _width)
    {
        posX = _posX;
        posY = _posY;
        height = _height;
        width = _width;
    }
    double  getPositionX()
    {
        return posX;
    }
    double getPositionY()
    {
        return posY;
    }
    double getHeight()
    {
        return height;
    }
    double getWidth()
    {
        return width;
    }
    double calculateArea()
    {
        return height * width;
    }
    double calculatePerimeter()
    {
        return 2 * (height + width);
    }
private:
    double posX;
    double posY;
    double height;
    double width;
};


#endif // RECTANGLE_H_INCLUDED
