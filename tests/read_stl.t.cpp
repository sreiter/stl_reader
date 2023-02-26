#include "../stl_reader.h"
#include <gtest/gtest.h>

TEST (readSTL, asciiSphere)
{
  stl_reader::StlMesh<> mesh;
  mesh.read_file ("data/sphere.stl");
  
  EXPECT_EQ (mesh.num_vrts (), 12);
  EXPECT_EQ (mesh.num_tris (), 20);

  EXPECT_EQ (mesh.num_solids (), 2);
  EXPECT_EQ (mesh.solid_tris_begin (0), 0);
  EXPECT_EQ (mesh.solid_tris_begin (1), 2);
  EXPECT_EQ (mesh.solid_tris_end (1), 20);
}
