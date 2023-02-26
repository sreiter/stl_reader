#include "utils.h"
#include <gtest/gtest.h>

namespace
{
  using namespace stl_reader;
  using std::vector;

  Coords const sourceCoordinatesWithIndex {
    {{0, 1, 0}, 0},
    {{1, 0, 0}, 1},
    {{1, 1, 0}, 2},
    {{1, 0, 0}, 3},
    {{0, 0, 0}, 4},};

  Indices const sourceTriangles {
    2, 3, 4,
    1, 2, 3, // degenerate triangle
    2, 1, 0};

  vector<double> const sourceNormals {
    0, 0, 1,
    0, 1, -1,
    1, 1, 0};
}

TEST (removeDoubles, removeOneVertexAndOneTriangle)
{
  auto newTris = sourceTriangles;
  auto reorderedCoordinatesWithIndex = sourceCoordinatesWithIndex;
  vector<double> newCoords;
  vector<double> newNormals = sourceNormals;
  stl_reader_impl::RemoveDoubles (newCoords, newTris, newNormals, reorderedCoordinatesWithIndex);
  
  EXPECT_EQ (newCoords.size (), 12);
  EXPECT_EQ (newTris.size (), 6);
  EXPECT_EQ (newNormals.size (), 6);
  
  EXPECT_TRUE (compareTriangleCoords (newCoords, newTris, 0, sourceCoordinatesWithIndex, sourceTriangles, 0));
  EXPECT_TRUE (compareTriangleCoords (newCoords, newTris, 1, sourceCoordinatesWithIndex, sourceTriangles, 2));
  EXPECT_EQ (toVec3 (newNormals, 0), toVec3 (sourceNormals, 0));
  EXPECT_EQ (toVec3 (newNormals, 1), toVec3 (sourceNormals, 2));
}
