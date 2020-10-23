#ifndef _POINT_2D_H_
#define _POINT_2D_H_

// A simple point class.

namespace bg {

    class Point2d
    {
    public:
        Point2d(double x = 0.0, double y = 0.0);

        double x() const;                                                           // getter : x
        double y() const;                                                           // getter : y
        void setX(double x);                                                        // setter : x
        void setY(double y);                                                        // setter : y
        void set(double x, double y);                                               // setter : x & y
        void randomize(double minX, double maxX, double minY, double maxY);         // randomize within min & max (both included)
        void randomize(double minVal = 0.0, double maxVal = 1.0);                   // randomize within min & max (both included)

        bool isOrigin() const;                                                      // valid if x & y = 0.0 (strict equal)

        double length2() const;                                                     // square length from origin
        double length() const;                                                      // length from origin
        double distance2(Point2d const & p) const;                                  // square distance from p
        double distance(Point2d const & p) const;                                   // distance from p

        Point2d operator-() const;                                                  // -point
        Point2d operator+(Point2d const & p) const;                                 // point + point
        Point2d operator-(Point2d const & p) const;                                 // point - point
        Point2d operator*(double v) const;                                          // point * double
        Point2d operator/(double v) const;                                          // point / double
        friend Point2d operator*(double v, Point2d const & p);                      // double * point
        friend Point2d operator/(double v, Point2d const & p);                      // double / point

        bool operator==(Point2d const & p) const;                                   // point == point
        bool operator!=(Point2d const & p) const;                                   // point != point

    private:
        double mX{}, mY{};
    };

}

#endif // _POINT_2D_H_