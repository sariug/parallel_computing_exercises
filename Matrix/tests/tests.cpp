#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"
#include "../inc/Matrix.hpp"

TEST_CASE( "Serilizing " ) {
  Matrix m{{std::vector<double>
            {1., 2., 3., 4.},
            {5., 6., 7., 8.},
            {9., 10., 11., 12.},
            {13., 14., 15., 16.}}};

  std::vector<double> slice1Result = {5., 6., 7., 8., 9., 10., 11., 12.};

  std::vector<double> slice1 = m.sliceAndSerialsRows(1, 3);
  REQUIRE(slice1 == slice1Result);
  REQUIRE(slice1.size() == 8 );

  std::vector<double> slice2Result = {1., 2., 3., 4.};

  std::vector<double> slice2 = m.sliceAndSerialsRows(0, 1);
  REQUIRE(slice2 == slice2Result);
  REQUIRE(slice2.size() == 4);

  std::vector<double> slice3Result = {13., 14., 15., 16.};

  std::vector<double> slice3 = m.sliceAndSerialsRows(3, 4);
  REQUIRE(slice3 == slice3Result);
  REQUIRE(slice3.size() == 4);

  CHECK_THROWS(m.sliceAndSerialsRows(-1, 0));
  CHECK_THROWS(m.sliceAndSerialsRows(-1, 0));
  CHECK_THROWS(m.sliceAndSerialsRows(0, 5));
  CHECK_THROWS(m.sliceAndSerialsRows(2, 2));



}
