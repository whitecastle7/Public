#ifndef _POLYGON_2D_H_
#define _POLYGON_2D_H_

// A simple polygon class.

#include <vector>
#include "Point2d.h"
#include "Rect2d.h"
#include "Transform2d.h"

namespace bg {

    class Polygon2d final
    {
    public:
        // Default constructor
        Polygon2d();

        // Vertices access
        size_t size() const;
        Point2d const & operator[](size_t index) const;
        Point2d const & at(size_t index) const;
        void setVertex(size_t index, Point2d const & p);
        void setVertexAt(size_t index, Point2d const & p);

        // Polygon construction tools
        // Standard shapes
        void buildRectangle(double width, double height, Point2d center = Point2d(0.0, 0.0), double orientationDegrees = 0.0);
        void buildSquare(double width, Point2d center = Point2d(0.0, 0.0), double orientationDegrees = 0.0);
        void buildDiamond(double a, double b, Point2d center = Point2d(0.0, 0.0), double orientationDegrees = 0.0);
        void buildStar(size_t nSides, double inRadius, double outRadius, Point2d center = Point2d(0.0, 0.0), double orientationDegrees = 0.0);
        // Polygonal shapes
        void buildRegular(size_t nSides, double radius = 1.0, Point2d center = Point2d(0.0, 0.0), double orientationDegrees = 0.0);
        void buildRandomConvex(size_t nSides, double meanRadius, Point2d center = Point2d(0.0, 0.0));
        void buildRandomNonConvex(size_t nSides, double meanRadius, Point2d center = Point2d(0.0, 0.0));
        // Custom building
        void clear();
        void addVertex(Point2d const & p);
        void addVertex(std::initializer_list<Point2d> const & v);
        void addVertex(std::vector<Point2d> const & v);
        void removeLastVertex();
        Polygon2d& operator<<(Point2d const & point);

        // Geometric transformation tools
        void translate(double x, double y);
        void rotate(double orientationDegrees);
        void scale(double relativeScale);
        void transform(double tX, double tY, double orientationDegrees, double relativeScale);
        void map(Transform2d const & t);
        Polygon2d translated(double x, double y) const;
        Polygon2d rotated(double orientationDegrees) const;
        Polygon2d scaled(double relativeScale) const;
        Polygon2d transformed(double tX, double tY, double orientationDegrees, double relativeScale) const;
        Polygon2d mapped(Transform2d const & t) const;

        // Information about the polygon
        bool isValid() const;
        bool isSelfIntersecting() const;
        bool isConvex() const;
        double area() const;
        double perimeter() const;
        Rect2d boundingBox() const;
        //Point2d boundingBoxTopLeft() const;
        //Point2d boundingBoxBottomRight() const;
        //double boundingBoxWidth() const;
        //double boundingBoxHeight() const;
        bool isSegmentSelfIntersecting(size_t index) const;
        bool isVertexConvex(size_t index) const;

        // Comparison
        bool operator==(Polygon2d const & p) const;
        bool operator!=(Polygon2d const & p) const;

        // Drawing tools - not available!
        //void drawBoundingBox(ConsoleImage & image, ConsoleColor const & boundingBoxColor) const;
        //void drawVertices(ConsoleImage & image, size_t vertexSize, ConsoleColor const & vertexColor) const;
        //void drawVertices(ConsoleImage & image, size_t vertexSize, ConsoleColor const & vertexColor, size_t nonConvexVertexSize, ConsoleColor const & nonConvexVertexColor) const;
        //void drawSegments(ConsoleImage & image, ConsoleColor const & segmentsColor) const;
        //void drawSegments(ConsoleImage & image, ConsoleColor const & segmentsColor, ConsoleColor const & intersectingSegmentsColor) const;
        //void draw(ConsoleImage & image, ConsoleColor const & segmentsColor, ConsoleColor const & boundingBoxColor = ConsoleColor::invalid()) const;
        //void draw(ConsoleImage & image, size_t vertexSize, ConsoleColor const & vertexColor, ConsoleColor const & segmentsColor, ConsoleColor const & boundingBoxColor = ConsoleColor::invalid()) const;
        //void draw(ConsoleImage & image, size_t vertexSize, ConsoleColor const & vertexColor, size_t nonConvexVertexSize, ConsoleColor const & nonConvexVertexColor, ConsoleColor const & segmentsColor, ConsoleColor const & boundingBoxColor = ConsoleColor::invalid()) const;
        //void drawIntersect(ConsoleImage & image, ConsoleColor const & segmentsColor, ConsoleColor const & intersectingSegmentColor, ConsoleColor const & boundingBoxColor = ConsoleColor::invalid()) const;
        //void drawIntersect(ConsoleImage & image, size_t vertexSize, ConsoleColor const & vertexColor, ConsoleColor const & segmentsColor, ConsoleColor const & intersectingSegmentsColor, ConsoleColor const & boundingBoxColor = ConsoleColor::invalid()) const;
        //void drawIntersect(ConsoleImage & image, size_t vertexSize, ConsoleColor const & vertexColor, size_t nonConvexVertexSize, ConsoleColor const & nonConvexVertexColor, ConsoleColor const & segmentsColor, ConsoleColor const & intersectingSegmentsColor, ConsoleColor const & boundingBoxColor = ConsoleColor::invalid()) const;

        // Point interaction tools
        // Return true if p is inside the polygon (borderIncluded is not implemented...)
        bool contained(Point2d const & p, bool borderIncluded = true) const;
        // Return the smallest distance between a polygon and p
        double nearestDistance(Point2d const & p) const;
        // Return the smallest distance and the nearest point from a polygon to p
        double nearestDistance(Point2d const & p, Point2d & ip) const;
        // Return the smallest distance between a polygon and p : 
        //  - the distance is positive if the point is outside the polygon
        //  - the distance is negative if the point is inside the polygon
        double relativeDistance(Point2d const & p) const;
        // Return the smallest distance and the nearest point from a polygon to p
        //  - the distance is positive if the point is outside the polygon
        //  - the distance is negative if the point is inside the polygon
        double relativeDistance(Point2d const & p, Point2d & ip) const;

    private:
        std::vector<Point2d> mVertices;

        bool mValid{ false };
        bool mConvex{ false };
        bool mSelfIntersecting{ false };
        Point2d mBoundingBoxTopLeft;
        Point2d mBoundingBoxBottomRight;

        bool mClockWiseDefined{ false };
        double mArea{ 0.0 };
        double mPerimeter{ 0.0 };

        struct VertexSegmentInfo {
            VertexSegmentInfo() : VertexSegmentInfo(0) {}
            VertexSegmentInfo(size_t size) : a{}, b{}, c{}, vertexRelPos(size), convex{}, intersect{} {}
            double a, b, c;
            std::vector<double> vertexRelPos;
            bool convex;
            bool intersect;
            double evaluate(Point2d const & p);
        };
        std::vector<VertexSegmentInfo> mVertexSegmentInfo;
        void updateVertexInfo();
        bool segmentIntersection(size_t iVertexRelPos1, size_t iVertexRelPos2);
    };

}



#endif // _POLYGON_2D_H_