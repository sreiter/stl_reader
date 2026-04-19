#include <stl_reader/stl_reader.h>
#include <gtest/gtest.h>

TEST (readSTL, asciiSphere)
{
  stl_reader::StlMesh<> mesh;
  mesh.read_file ("data/ascii_sphere.stl");
  
  EXPECT_EQ (mesh.num_vrts (), 12);
  EXPECT_EQ (mesh.num_tris (), 20);

  EXPECT_EQ (mesh.num_solids (), 2);
  EXPECT_EQ (mesh.solid_tris_begin (0), 0);
  EXPECT_EQ (mesh.solid_tris_begin (1), 2);
  EXPECT_EQ (mesh.solid_tris_end (1), 20);
}

TEST (readSTL, binarySphere)
{
  stl_reader::StlMesh<> mesh;
  mesh.read_file ("data/binary_sphere.stl");
  
  EXPECT_EQ (mesh.num_vrts (), 12);
  EXPECT_EQ (mesh.num_tris (), 20);
  EXPECT_EQ (mesh.num_solids (), 1);
  EXPECT_EQ (mesh.solid_tris_begin (0), 0);
  EXPECT_EQ (mesh.solid_tris_end (0), 20);
}

TEST (readSTL, asciiFileWithoutFaces)
{
  stl_reader::StlMesh<> mesh;
  mesh.read_file ("data/ascii_empty.stl");
  
  EXPECT_EQ (mesh.num_vrts (), 0);
  EXPECT_EQ (mesh.num_tris (), 0);
  EXPECT_EQ (mesh.num_solids (), 1);
}

TEST (readSTL, asciiFileWithMissingBeginFace)
{
  stl_reader::StlMesh<> mesh;
  EXPECT_THROW (mesh.read_file ("data/missing_begin_face.stl"), std::runtime_error);
}

TEST (readSTL, asciiFileWithMissingEndFace)
{
  stl_reader::StlMesh<> mesh;
  EXPECT_THROW (mesh.read_file ("data/missing_end_face.stl"), std::runtime_error);
}