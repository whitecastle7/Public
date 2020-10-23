#ifndef _RECT_2D_H_
#define _RECT_2D_H_


#include "Point2d.h"
#include "Size2d.h"


// A simple rectangle class.

namespace bg {

    class Rect2d
    {
    public:
        Rect2d() = default;
        Rect2d(Point2d const & topLeft, Size2d const & size);                                       // construct a Rect2d
        Rect2d(double left, double top, double width, double height);                               // construct a Rect2d
        Rect2d(Point2d const & topLeft, Point2d const & bottomRight);                               // construct a Rect2d

        static Rect2d fromCenter(Point2d const & center, Size2d const & size);                      // return a Rect2d construct from center coordinates

        Point2d const & topLeft() const;                                                            // getter : top left
        Point2d bottomRight() const;                                                                // getter : bttom right
        Point2d center() const;                                                                     // getter : center 
        Size2d const & size() const;                                                                // getter : size
        void setTopLeft(Point2d const & topLeft);                                                   // setter : top left
        void setBottomRight(Point2d const & bottomRight);                                           // setter : bottom right
        void setSize(Size2d const & size);                                                          // setter : size
        void set(Point2d const & topLeft, Size2d const & size);                                     // setter : top left & size
        void set(Point2d const & topLeft, Point2d const & bottomRight);                             // setter : top left & bottom right
        void randomize(double minTop, double maxTop, double minLeft, double maxLeft, double minWidth, double maxWidth, double minHeight, double maxHeight);     // randomize 

        bool isValid() const;                                                                       // return if size is valid

        double area() const;                                                                        // area
        double perimeter() const;                                                                   // perimeter
        double diagonal() const;                                                                    // diagonal
        
        bool contains(Point2d const & p) const;                                                     // return true if p is inside this (include border)
        bool contains(Rect2d const & r) const;                                                      // return true if r is inside this (include border)

        Rect2d operator-() const;                                                                   // return negated
        Rect2d operator+(Point2d const & p) const;                                                  // rect + point
        Rect2d operator-(Point2d const & p) const;                                                  // rect - point
        Rect2d operator*(double v) const;                                                           // rect * value
        Rect2d operator/(double v) const;                                                           // rect / value
        friend Rect2d operator*(double v, Rect2d const & r);                                        // value * rect
        friend Rect2d operator/(double v, Rect2d const & r);                                        // value / double

        bool operator==(Rect2d const & r);                                                          // rect == rect
        bool operator!=(Rect2d const & r);                                                          // rect != rect

    private:
        Point2d mTopLeft;
        Size2d mSize;
    };

}

#endif // _RECT_2D_H_