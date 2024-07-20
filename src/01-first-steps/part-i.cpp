#include <iostream>
#include <CGAL/Simple_cartesian.h>

// The first idea in CGAL is that of the Kernel. Kernels define geometric
// primitives such as points and line segments. The following line creates a
// kernel that uses the Cartesian coordinates system with double precision
// numbers for the coordinate components.
// See: https://doc.cgal.org/latest/Kernel_23/structCGAL_1_1Simple__cartesian.html
typedef CGAL::Simple_cartesian<double> Kernel;

// Next we define some aliases to simplify how we use the kernel. First we
// create a two-dimensional point (this is in fact a kernel geometric object
// concept - an idea we'll examine in more detail later).
typedef Kernel::Point_2 Point_2;

// We also define a two-dimensional line segment (again we take this concept
// from the kernel.
typedef Kernel::Segment_2 Segment_2;

int main() {

  std::cout << "Part I" << std::endl;

  // Now we create two points, p & q and print their coordinates.
  Point_2 p(1,1), q(10,10);
  std::cout << "p = " << p << std::endl;
  std::cout << "q = " << q.x() << " " << q.y() << std::endl;

  // We can also calculate the distance between two points (or here the squared
  // distance).
  std::cout << "sqdist(p,q) = " << CGAL::squared_distance(p,q) << std::endl;

  // Now we create a two-dimensional line segment (called s) from p & q.
  Segment_2 s(p,q);

  // And finally we'll create a third point, called m.
  Point_2 m(5, 9);

  // Now we can print the coordinates of m as before,
  std::cout << "m = " << m << std::endl;

  // and we can find the distance (in this case squared distance) of m from the
  // line segment s.
  std::cout << "sqdist(s, m) = " << CGAL::squared_distance(s, m) << std::endl;

  // Orientations are extremely important in geometry, and CGAL has the
  // useful operation 'orientation' to help us out. Here we supply a start point
  // p and the point we travel to q, then we ascertain whether travelling to m
  // (from p then q) would result in a left or right (or no i.e. co-linear)
  // turn.
  std::cout << "p, q, and m ";
  switch (CGAL::orientation(p,q,m)){
    case CGAL::COLLINEAR:
      std::cout << "are collinear\n";
      break;
    case CGAL::LEFT_TURN:
      std::cout << "make a left turn\n";
      break;
    case CGAL::RIGHT_TURN:
      std::cout << "make a right turn\n";
      break;
  }

  // Other useful operation is finding the midpoint of a line segment; once
  // more CGAL provides a function to do that.
  Point_2 mid = CGAL::midpoint(p, q);
  std::cout << " midpoint(p,q) = " << CGAL::midpoint(p, q) << std::endl;
  std::cout << " midpoint(p,q) = " << mid << std::endl;

  // This produces a Point_2 object as expected.

  return 0;
}