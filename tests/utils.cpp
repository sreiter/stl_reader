#include "utils.h"
#include <cassert>

auto operator << (std::ostream& out, vec3 const& v) -> std::ostream&
{
  out << "(" << v [0] << ", " << v [1] << ", " << v [2] << ")";
  return out;
}

auto toVec3 (Coords const& coords, int iCoord) -> vec3
{
  assert (iCoord >= 0 && iCoord < coords.size ());
  auto const& c = coords [iCoord].data;
  return {c [0], c [1], c [2]};
}

auto toVec3 (RawCoords const& coords, int iCoord) -> vec3
{
  assert (iCoord >= 0 && iCoord * 3 + 2 < coords.size ());
  auto const c = coords.data () + iCoord * 3;
  return {c [0], c [1], c [2]};
}

void printTriangleIndices (Indices const& indices)
{
  for (size_t iTri = 0; iTri * 3 + 2 < indices.size (); ++iTri)
  {
    for (int i = 0; i < 3; ++i)
      std::cout << indices [iTri * 3 + i] << ", ";
    std::cout << std::endl;
  }
}

bool compareTriangleCoords (
    std::vector<double> const& coordsA,
    Indices const& trisA,
    int triIndexA,
    Coords const& coordsB,
    Indices const& trisB,
    int triIndexB)
{
  for (int i = 0; i < 3; ++i)
  {
    int iCoordA = trisA.at (triIndexA * 3 + i);
    int iCoordB = trisB.at (triIndexB * 3 + i);
    if (toVec3 (coordsA, iCoordA) != toVec3 (coordsB, iCoordB))
      return false;
  }
  return true;
}
