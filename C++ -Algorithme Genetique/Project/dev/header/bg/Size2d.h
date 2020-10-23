#ifndef _SIZE_2D_H_
#define _SIZE_2D_H_

// A simple size class.

#include "Point2d.h"

namespace bg {

    class Size2d
    {
    public:
        Size2d(double width = 0.0, double height = 0.0);
        Size2d(Point2d const & p);

        double width() const;                                                                       // getter : width
        double height() const;                                                                      // getter : height
        void setWidth(double x);                                                                    // setter : width
        void setHeight(double y);                                                                   // setter : height
        void set(double width, double height);                                                      // setter : width & height
        void randomize(double minWidth, double maxWidth, double minHeight, double maxheight);       // randomize within min & max (both included)
        void randomize(double minVal = 0.0, double maxVal = 1.0);                                   // randomize within min & max (both included)

        bool isValid() const;                                                                       // valid if width & height are not 0

        double area() const;                                                                        // area
        double perimeter() const;                                                                   // perimeter
        double diagonal() const;                                                                    // diagonal
        Point2d center() const;

        Size2d operator-() const;                                                                   // return negated
        Size2d operator*(double v) const;                                                           // size * double
        Size2d operator/(double v) const;                                                           // size / double
        friend Size2d operator*(double v, Size2d const & p);                                        // double * size
        friend Size2d operator/(double v, Size2d const & p);                                        // double / size

        bool operator==(Size2d const & p) const;                                                    // size == size
        bool operator!=(Size2d const & p) const;                                                    // size != size

    private:
        double mWidth{}, mHeight{};
    };

}

#endif // _SIZE_2D_H_