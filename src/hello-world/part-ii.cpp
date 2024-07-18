//
// Created by Lesleis Nagy on 18/07/2024.
//

// We can often get in to trouble if we don't have the correct amount of
// precision, or we use unsuitable accuracy when performing even simple
// operations in computational geometry.

#include <iostream>
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;

int main() {

  std::cout << "Part II" << std::endl;

  // In each of the following three blocks we'll test whether three points are
  // co-linear.

  // Block 1.
  {
    // We expect these points to be co-linear since the y-value is increasing
    // in uniform steps of 0.3.
    Point_2 p(0, 0.3), q(1, 0.6), r(2, 0.9);
    std::cout << (CGAL::collinear(p, q, r) ? "collinear" : "not collinear");
    std::cout << std::endl;
  }

  // Block 2.
  {
    // We expect these points to be co-linear since the y-value is increasing
    // in uniform steps of 1/3.
    Point_2 p(0, 1.0/3.0), q(1, 2.0/3.0), r(2, 1);
    std::cout << (CGAL::collinear(p, q, r) ? "collinear" : "not collinear");
    std::cout << std::endl;
  }

  // Block 3
  {
    // Finally we expect these points to be co-linear since the y-value is
    // increasing in uniform steps of 1.
    Point_2 p(0, 0), q(1, 1), r(2, 2);
    std::cout << (CGAL::collinear(p, q, r) ? "collinear" : "not collinear");
    std::cout << std::endl;
  }

  // Surprisingly the first two blocks fail the co-linearity test! This is
  // because the components of the coordinates of p, q and r result in
  // matrix determinants (the way that co-linearity is tested) that are
  // near-zero - but not exactly zero!

}