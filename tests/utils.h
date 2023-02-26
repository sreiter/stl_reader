#pragma once

#include "../stl_reader.h"

#include <array>
#include <iostream>
#include <vector>

using Coord = stl_reader::stl_reader_impl::CoordWithIndex<double, int>;
using Coords = std::vector<Coord>;
using RawCoords = std::vector<double>;
using Indices = std::vector<int>;
using vec3 = std::array<double, 3>;

auto operator << (std::ostream& out, vec3 const& v) -> std::ostream&;
auto toVec3 (Coords const& coords, int iCoord) -> vec3;
auto toVec3 (RawCoords const& coords, int iCoord) -> vec3;

template <class COORD>
void printTriangleCoordinates (std::vector<COORD> const& coords, Indices const& indices)
{
  for (size_t iTri = 0; iTri * 3 + 2 < indices.size (); ++iTri)
  {
    for (int i = 0; i < 3; ++i)
      std::cout << toVec3 (coords, indices [iTri * 3 + i]) << ", ";
    std::cout << std::endl;
  }
}

void printTriangleIndices (Indices const& indices);

bool compareTriangleCoords (
    std::vector<double> const& coordsA,
    Indices const& trisA,
    int triIndexA,
    Coords const& coordsB,
    Indices const& trisB,
    int triIndexB);
