//
// Created by Lesleis Nagy on 18/07/2024.
//

#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>

// In this example we'll calculate the convex hull of a set of points (like
// before) but instead of storing points in an array, we'll store the points
// in a std::vector.

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point_2;

int main(int argc, char *argv[]) {

    // Create a std::vector of Point_2 objects.
    std::vector<Point_2> points = {
        Point_2(0, 0),
        Point_2(10, 0),
        Point_2(10, 10),
        Point_2(6, 5),
        Point_2(4, 1)
    };

    // Create a std::vector that will store our results.
    std::vector<Point_2> result;

    // This time we pass the begin/end iterators of the input points
    // std::vector, and a std::back_inserter to the result std::vector.
    CGAL::convex_hull_2(
        points.begin(),
        points.end(),
        std::back_inserter(result)
    );

    // This time, to get the points of the result, we simply use the size()
    // function of a std::vector.
    std::cout << "No. of pts in hull (std::vector): " << result.size();
    std::cout << std::endl;

    // We can iterate through the result.
    for (const auto &point : result) {
        std::cout << point << std::endl;
    }

}
