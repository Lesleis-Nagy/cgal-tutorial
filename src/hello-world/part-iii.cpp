//
// Created by Lesleis Nagy on 18/07/2024.
//

// In order to solve this co-linearity test problem we must use exact
// constructions. This is a tricky problem in computational geometry, but
// luckily for us CGAL has features to support this.

#include <iostream>
#include <sstream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

// We'll switch out our previous Cartesian kernel and use the following one.
// This kernel is still Cartesian and will support constructions from double
// precision values, however this time it will provide exact geometric
// predicates and constructions.
typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point_2;

int main() {

  std::cout << "Part III" << std::endl;

  // In each of the following three blocks we'll test whether three points are
  // co-linear.

  // Block 1.
  {
    // We expect these points to be co-linear since the y-value is increasing
    // in uniform steps of 0.3.
    Point_2 p(0, 0.3), q(1, 0.6), r(2, 0.9);
    std::cout << "Block 1: ";
    std::cout << (CGAL::collinear(p, q, r) ? "collinear" : "not collinear");
    std::cout << std::endl;
  }

  // Block 2.
  {
    // We expect these points to be co-linear since the y-value is increasing
    // in uniform steps of 1/3.
    Point_2 p(0, 1.0/3.0), q(1, 2.0/3.0), r(2, 1);
    std::cout << "Block 2: ";
    std::cout << (CGAL::collinear(p, q, r) ? "collinear" : "not collinear");
    std::cout << std::endl;
  }

  // Block 3
  {
    // Finally we expect these points to be co-linear since the y-value is
    // increasing in uniform steps of 1.
    Point_2 p(0, 0), q(1, 1), r(2, 2);
    std::cout << "Block 3: ";
    std::cout << (CGAL::collinear(p, q, r) ? "collinear" : "not collinear");
    std::cout << std::endl;
  }

  // Now wait a minute! All the answer is exactly like we had before! This is
  // because the compiler is still passing floating point numbers to the
  // underlying arbitrary precision library.

  // Block 4.
  {
    // We expect these points to be co-linear since the y-value is increasing
    // in uniform steps of 0.3.
    Point_2 p, q, r;
    std::istringstream str_p("0 0.3");
    std::istringstream str_q("0 0.6");
    std::istringstream str_r("0 0.9");
    str_p >> p; str_q >> q; str_r >> r;
    std::cout << "Block 4: ";
    std::cout << (CGAL::collinear(p, q, r) ? "collinear" : "not collinear");
    std::cout << std::endl;
  }

  // Block 5.
  {
    // We expect these points to be co-linear since the y-value is increasing
    // in uniform steps of 1/3.
    Point_2 p, q, r;
    std::istringstream str_p("0 1/3");
    std::istringstream str_q("0 2/3");
    std::istringstream str_r("0 3/3");
    str_p >> p; str_q >> q; str_r >> r;
    std::cout << "Block 5: ";
    std::cout << (CGAL::collinear(p, q, r) ? "collinear" : "not collinear");
    std::cout << std::endl;
  }

  // Block 6.
  {
    // We expect these points to be co-linear since the y-value is increasing
    // in uniform steps of 1 - we also show a slightly different way of pushing
    // values in to each point.
    Point_2 p, q, r;
    std::istringstream input("0 0    1 1    2 2");
    input >> p >> q >> r;
    std::cout << "Block 6: ";
    std::cout << (CGAL::collinear(p, q, r) ? "collinear" : "not collinear");
    std::cout << std::endl;
  }

  // Excellent! Now we have all three co-linearity tests passing as they should!
  // But beware there is a performance cost - both in terms of time and memory
  // - when using exact predicates. You should also be aware that many
  // algorithms in geometric algebra are designed so that they will work with
  // imprecise arithmetic (and so using exact precision is a waste of memory and
  // processor resources).

}