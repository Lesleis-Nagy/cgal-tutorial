//
// Created by Lesleis Nagy on 20/07/2024.
//

//
// Some definitions:
// CONCEPT: a concept is a set of requirements on a type
//          example: consider the function
//
//                   template <typename T>
//                   T
//                   duplicate(T t) {
//                       return t;
//                   }
//
//                   This function assumes that the template type T is
//                   copy-constructable (i.e. it provides a copy constructor).
//                   Therefore, in order to compile, any class that instantiates
//                   this function must have a copy constructor - or we say that
//                   the class must be a MODEL of the CopyConstructable CONCEPT.
//
// MODEL:   a MODEL is a class that faithfully implements a CONCEPT.
//

#include <iostream>
#include <numeric>
#include <vector>

#include <CGAL/convex_hull_2.h>

// In this example, we're going to implement our own trait for a specific
// implementation of the convex-hull algorithm, namely one that uses the
// Graham-Andrews scan.

using ll = long long;

// First we'll define our own data-type Frac - which is a toy implementation of
// a fractional numeric type with long long integers for the numerator and the
// denominator.

class Frac {
public:

    // By default, we'll create create a 'zero' fraction - this will have a
    // zero for the numerator but 1 for the denominator (note, a true fraction
    // cannot have zero for the denominator).

    Frac(): _num{0}, _den{1} {
    }

    // We can initialize fractions from an integer - in which case the
    // the denominator is automatically 1.

    explicit
    Frac(ll num): _num{num}, _den{1} {
    }

    // Finally we can initialize a fraction with both numerator and denominator
    // values given.
    Frac(ll num, ll den): _num{num}, _den{den} {
    }

    // The strictly less than operation evaluates if 'this' fraction is smaller
    // than some 'other' fraction, that is we evauate
    //   num()     other.num()
    //  ------- < ------------- <=> num() * other.den() < other.num() * den().
    //   den()     other.den()
    bool
    operator <(const Frac &other) const {

        return num() * other.den() < other.num() * den();
    }

    // The less than or equal to operation evaluates if 'this' fraction is
    // less than or equal to some 'other' fraction, that is we evauate
    //   num()     other.num()
    //  ------- <= ------------- <=> num() * other.den() <= other.num() * den().
    //   den()     other.den()
    bool
    operator <=(const Frac &other) const {
        return num() * other.den() <= other.num() * den();
    }

    // The strictly greater than operation evaluates if 'this' fraction is
    // greater than some 'other' fraction, that is we evauate
    //   num()     other.num()
    //  ------- > ------------- <=> num() * other.den() > other.num() * den().
    //   den()     other.den()
    bool
    operator >(const Frac &other) const {
        return num() * other.den() > other.num() * den();
    }

    // The greater than or equal to operation evaluates if 'this' fraction is
    // greater than or equal to some 'other' fraction, that is we evauate
    //   num()     other.num()
    //  ------- >= ------------- <=> num() * other.den() >= other.num() * den().
    //   den()     other.den()
    bool
    operator >=(const Frac &other) const {
        return num() * other.den() >= other.num() * den();
    }

    // The equal to operation evaluates if 'this' fraction is equal to some
    // 'other' fraction, that is we evauate
    //   num()     other.num()
    //  ------- == ------------- <=> num() * other.den() == other.num() * den().
    //   den()     other.den()
    bool
    operator ==(const Frac &other) const {
        return num() * other.den() == other.num() * den();
    }

    // The addition operator adds two fractions together.
    [[nodiscard]] Frac
    operator +(const Frac &other) const {
        ll new_num = num() * other.den() + den() * other.num();
        ll new_den = den() * other.den();

        ll new_gcd = std::gcd(new_num, new_den);

        // If the numerator is zero, the gcd can be zero.
        if (new_gcd != 0) {
            new_num /= new_gcd;
            new_den /= new_gcd;
        }

        return {new_num, new_den};
    }

    // The subtraction operation subtracts another fraction from 'this' fraction.
    [[nodiscard]] Frac
    operator -(const Frac &other) const {
        ll new_num = num() * other.den() - den() * other.num();
        ll new_den = den() * other.den();

        ll new_gcd = std::gcd(new_num, new_den);

        // If the numerator is zero, the gcd can be zero.
        if (new_gcd != 0) {
            new_num /= new_gcd;
            new_den /= new_gcd;
        }

        return {new_num, new_den};
    }

    // The multiplication operation multiplies two fractions.
    [[nodiscard]] Frac
    operator *(const Frac &other) const {
        ll new_num = num() * other.num();
        ll new_den = den() * other.den();

        ll new_gcd = std::gcd(new_num, new_den);

        // If the numerator is zero, the gcd can be zero.
        if (new_gcd != 0) {
            new_num /= new_gcd;
            new_den /= new_gcd;
        }

        return {new_num, new_den};
    }

    // The division operation divides one fraction by another.
    [[nodiscard]] Frac
    operator /(const Frac &other) const {
        ll new_num = num() * other.den();
        ll new_den = den() * other.num();

        ll new_gcd = std::gcd(new_num, new_den);

        // If the numerator is zero, the gcd can be zero.
        if (new_gcd != 0) {
            new_num /= new_gcd;
            new_den /= new_gcd;
        }

        return {new_num, new_den};
    }

    // Testing whether a fraction is positive positive requires the numerator
    // and denominator to both be positive or both be negative, so to simplify
    // this we create a function for this purpose.
    [[nodiscard]] bool
    positive() const {
        return (_num > 0 && _den > 0) || (_num < 0 && _den < 0);
    }

    // We also have a function that will return the numerator,
    [[nodiscard]] ll
    num() const { return _num; }

    // and a function that will return the deonominator.
    [[nodiscard]] ll
    den() const { return _den; }

private:
    ll _num;
    ll _den;
};

// Finally we provide a stream operator so that we can print a fraction.
std::ostream &operator<<(std::ostream &out, const Frac &f) {
    out << f.num() << "/" << f.den();
    return out;
}

// We can use our Frac class to define a two-dimensional point. This class is
// relatively simple and manages the x and y components.
class FracPoint2 {
public:

    // Each point consists of an x and y component.
    FracPoint2(Frac x, Frac y) : _x{x}, _y{y} {
    }

    // Retrieves the x-component of the point.
    [[nodiscard]] const Frac &
    x() const {
        return _x;
    }

    // Retrieves the y-component of the point.
    [[nodiscard]] const Frac &
    y() const {
        return _y;
    }

private:
    Frac _x, _y;
};

// The stream operator displays the x and y components as text.
std::ostream &operator <<(std::ostream &out, const FracPoint2 &p) {
    out << "<" << p.x() << ", " << p.y() << ">";
    return out;
}

// The addition operator, will add two FracPoint2 objects.
[[nodiscard]] FracPoint2
operator +(const FracPoint2 &p, const FracPoint2 &q) {
    return {p.x() + q.x(), p.y() + q.y()};
}

// The subtraction operator, will subtract one FracPoint2 from another.
[[nodiscard]] FracPoint2
operator -(const FracPoint2 &p, const FracPoint2 &q) {
    return {p.x() - q.x(), p.y() - q.y()};
}

// The scalar multiplication operator, will scale a FracPoint2 by a scalar -
// multiplying from the left.
[[nodiscard]] FracPoint2
operator *(const Frac &s, const FracPoint2 &p) {
    return {s * p.x(), s * p.y()};
}

// The scalar multiplication operator, will scale a FracPoint2 by a scalar -
// multiplying from the right.
[[nodiscard]] FracPoint2
operator *(const FracPoint2 &p, const Frac &s) {
    return {s * p.x(), s * p.y()};
}

// The scalar division operator, will divide each component of a FracPoint2 by
// a scalar.
[[nodiscard]] FracPoint2
operator /(const FracPoint2 &p, const Frac &s) {
    return {p.x() / s, p.y() / s};
}

// Calculates the two-dimensional 'cross product' of two FacePoint2 objects.
[[nodiscard]] Frac
cross(const FracPoint2 &p, const FracPoint2 &q) {
    return p.x() * q.y() - q.x() * p.y();
}

// Now we get to the Traits class. This class will implement the traits needed
// to run the Graham/Andrews convex-hull algorithm, which you will recall from
// part-iv.cpp are
//    * Traits::Point_2
//    * Traits::Less_xy_2   - responsible for sorting
//    * Traits::Left_turn_2 - responsible for orientation
//    * Traits::Equal_2
class Traits {
public:

    // We create an alias called Point_2 from FracPoint2, this fulfills the
    // Traits::Point_2 requirement.
    using Point_2 = FracPoint2;

    // We create an object that will impose an ordering on Point_2 objects,
    // thus fulfilling the Traits::Less_xy_2 requirement.
    class Less_xy_2 {
    public:
        bool
        operator()(const Point_2 &p, const Point_2 &q) const {
            return p.x() < q.x() || (p.x() == q.x() && p.y() < q.y());
        }
    };

    // We create an object that will impose an orientation on Point_2 objects
    // which will fulfill the Traits::Left_turn_2 requirement.
    class Left_turn_2 {
    public:
        bool
        operator()(const Point_2 &p0, const Point_2 &p1,
                   const Point_2 &p2) const {
            Frac tv = cross(p1 - p0, p2 - p0);
            return tv.positive();
        }
    };

    // Finally we fulfil the Equal_2 requirement by creating the Equal_2 class.
    class Equal_2 {
    public:
        bool
        operator()(const Point_2 &p, const Point_2 &q) const {
            return p.x() == q.x() && p.y() == q.y();
        }
    };

    // The following functions are also required, and they return objects
    // based on the traits that we've implemented above.

    [[nodiscard]] const Less_xy_2 &
    less_xy_2_object() const {
        return _less_xy_2_obj;
    }

    [[nodiscard]] const Left_turn_2 &
    left_turn_2_object() const {
        return _left_turn_2;
    }

    [[nodiscard]] const Equal_2 &
    equal_2_object() const {
        return _equal_2_obj;
    }

private:
    Less_xy_2 _less_xy_2_obj;
    Left_turn_2 _left_turn_2;
    Equal_2 _equal_2_obj;
};

// Now we go ahead and use our Traits object to calculate the convex-hull
// of four points.

int main(int argc, char *argv[]) {

    // Four points in the 2D plane.
    std::vector<Traits::Point_2> points{
        {{0, 1}, {0, 1}},
        {{1, 1}, {0, 1}},
        {{1, 1}, {1, 1}},
        {{1, 2}, {1, 4}}
    };

    // This is where the convex hull will be stored.
    std::vector<Traits::Point_2> chull;

    // We explicitly call the Graham-Andrews variation of the convex hull
    // algorithm. Using any other algorithm may require other traits to be
    // implemented, but the set we've implemented above will do here.
    CGAL::ch_graham_andrew(
        points.begin(),
        points.end(),
        std::back_inserter(chull),
        Traits()
    );

    // Once we've extracted the convex hull, we display the results.
    for (const auto & p : chull) {
        std::cout << p << std::endl;
    }

}
