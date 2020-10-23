#ifndef _TRANSFORM_2D_H_
#define _TRANSFORM_2D_H_

// A simple affine transformation utility class.

#include "Point2d.h"
#include <vector>

namespace bg {

    class Transform2d final
    {
    public:
        Transform2d();

        void map(Point2d & p) const;
        void map(std::vector<Point2d> & v) const;
        Point2d mapped(Point2d const & p) const;
        std::vector<Point2d> mapped(std::vector<Point2d> const & v) const;

        void translate(double tx, double ty);
        void rotate(double thetaRadians);
        void scale(double sx, double sy);

        bool invert();

    private:
        struct Matrix3x3 {
            Matrix3x3();
            double	a, b, c, d, e, f, g, h, i;
            Matrix3x3& setIdentity();
            Matrix3x3& setTranslation(double tx, double ty);
            Matrix3x3& setRotation(double thetaRadians);
            Matrix3x3& setScaling(double sx, double sy);
            Matrix3x3 operator*(Matrix3x3 const & m) const;
            Matrix3x3& operator*=(Matrix3x3 const & m);
            Point2d operator*(Point2d const & m) const;
            bool invert();
        };
        Matrix3x3 mTransMatrix;
    };

}

#endif // _TRANSFORM_2D_H_
