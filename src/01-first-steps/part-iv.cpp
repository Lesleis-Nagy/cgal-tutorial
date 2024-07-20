//
// Created by Lesleis Nagy on 18/07/2024.
//

#include <iostream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>

// In this example we'll use a kernel that provides exact geometric predecates
// but inexact geometric constructions.

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point_2;

int main(int argc, char *argv[]) {

    // First we'll create 5 two-dimensional points.
    Point_2 points[5] = {
        Point_2(0, 0),
        Point_2(10, 0),
        Point_2(10, 10),
        Point_2(6, 5),
        Point_2(4, 1)
    };

    // Since the convex hull is a subset of the input points, we'll create a
    // second set of 5 two-dimensional points, where the convex hull will go.
    Point_2 result[5];

    // The convex_hull_2 algorithm, will take an iterator for the set of points
    // for which we want to extract the convex hull. This only makes use of
    // comparisons of coordinates (and orientations) - this is why we choose a
    // kernel that uses exact predecates but not exact geometric constructions.
    Point_2 *result_past_end = CGAL::convex_hull_2(points, points + 5, result);

    // The convex hull coordinates are stored in the result (starting at the
    // beginning, i.e. at result), and the past-the-end iterator for the
    // resulting sequence is returned - this means that we can we can find the
    // number of points in the convex hull by doing
    //      n = result_past_end - result
    size_t n_hull = result_past_end - result;
    std::cout << "No. of points in hull (c-array): " << n_hull << std::endl;

    // We can also print out the points in the convex hull.
    for (size_t i = 0; i < n_hull; ++i) {
        std::cout << result[i] << std::endl;
    }

    return 0;

}