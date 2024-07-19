//
// Created by Lesleis Nagy on 19/07/2024.
//

// In previous sections we examined how to use kernels and algorithms (like
// convex_hull_2(). This time we'd like to express the requirements that
// need to be met in order to make algorithms work - in particular for
// convex_hull_2() but in general for other functions.

// The manual page for convex_hull_2() [1] has two entries - one of them has a
// Traits template parameter. The typical geometric primitives used by a
// convex-hull algorithm are dependent on the algorithm being used. The simplest
// efficient algorithm is the "Graham/Andrews scan" - this sorts points from
// left to right and builds a convex hull by incrementally adding one point
// after another from the sorted list. Consequently, the algorithm needs to know
//    1) about point types
//    2) how to sort points
//    3) evaluate the orientation of a triple of points.
// Now for ch_graham_andrew() [1] we're given a list of requirements, that is
// the Traits template parameter must provide the nested types:
//    * Traits::Point_2
//    * Traits::Less_xy_2   - responsible for sorting
//    * Traits::Left_turn_2 - responsible for orientation
//    * Traits::Equal_2
// The requirements that these types have to satisfy are documented in full with
// the ConvexHullTraits_2 concept [2]
// The types are grouped under a Traits class for simplicity.

// What can be used as an argument for this template parameter?
// Any MODEL of the CONCEPT Kernel [3] provides what is required by the CONCEPT
// ConvexHullTraits_2.

// Why do we have template parameters at all?
// They make the code extremely versatile. For example, if we want to compute
// the convex hull of 3D points projected into the yz-plane, we can use the
// Projection_traits_yz_3 class [4] - this is a small modification of previous
// examples. Let's take a look

#include <iostream>
#include <iterator>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Projection_traits_yz_3.h>
#include <CGAL/convex_hull_2.h>

// As before we use exact predicates but allow inexact geometric constructions.
typedef CGAL::Exact_predicates_inexact_constructions_kernel K3;

// The Projection_traits_yz_3 concept is an adapter to project points in 3D
// space on to points in the 2D yz-plane.
typedef CGAL::Projection_traits_yz_3<K3> K;

// We'll use two-dimensional points in the subsequent convex_hull_2 algorithm
// by specifying a Trait.
typedef K::Point_2 Point_2;

int main(int argc, char *argv[]) {

  // Notice how this is a different Point_2 object from before, we're supplying
  // three coordinate components, but these will be projected on to the
  // yz-plane.

  std::vector<Point_2> points{
      {1.0, 0.0, 0.0},
      {1.0, 1.0, 0.0},
      {1.0, 0.0, 1.0},
      {1.0, 0.3, 0.1}
  };

  std::vector<Point_2> chull;

  CGAL::convex_hull_2(
      points.begin(),
      points.end(),
      std::back_inserter(chull),
      K()
  );

  for (const auto &p : chull) {
    std::cout << p << std::endl;
  }

  return 0;

}






// References
// 1. https://doc.cgal.org/latest/Convex_hull_2/group__PkgConvexHull2Functions.html#ga8241d43969ff61cb9be46811c2e9e176
// 2. https://doc.cgal.org/latest/Convex_hull_2/classConvexHullTraits__2.html
// 3. https://doc.cgal.org/latest/Kernel_23/classKernel.html
// 4. https://doc.cgal.org/latest/Kernel_23/classCGAL_1_1Projection__traits__yz__3.html