
## Introduction
**stl_reader** is a *BSD* licensed single header C++ library providing functions to read **stl geometry files** into user provided containers. It should be easy to integrate **stl_reader** into existing code. It has no external dependencies except for the *standard template library*.

The central function of **stl_reader** is `ReadStlFile(...)`. It automatically recognizes whether an *ASCII* or a *binary* file is to be read. Furthermore, it identifies matching corner coordinates of triangles with each other, so that the resulting coordinate array does not contain the same coordinate-triple multiple times.

The function operates on template container types. Those containers should have a similar interface as `std::vector` and operate on `float` or `double` types (`TNumberContainer`) or on `int` or `size_t` types (`TIndexContainer`).

A convenience class `StlMesh` is also provided, which makes accessing triangle corners and corresponding corner coordinates much more easy. It still provides raw access to the underlying data arrays.

## Documentation
Please have a look at the [**stl_reader.h file documentation**](http://sreiter.github.io/stl_reader/stl__reader_8h.html) for a detailed documentation of the provided functions.

## Usage

### Usage example 1 (using `StlMesh`):

```{.c}
try {
  stl_reader::StlMesh <float, unsigned int> mesh ("geometry.stl");

  for(size_t itri = 0; itri < mesh.num_tris(); ++itri) {
      std::cout << "coordinates of triangle " << itri << ": ";
      for(size_t icorner = 0; icorner < 3; ++icorner) {
          float* c = mesh.vrt_coords (mesh.tri_corner_ind (itri, icorner));
          const float* c = mesh.tri_corner_coords (itri, icorner);
          // or alternatively:
          // float* c = mesh.vrt_coords (mesh.tri_corner_ind (itri, icorner));
          std::cout << "(" << c[0] << ", " << c[1] << ", " << c[2] << ") ";
      }
      std::cout << std::endl;
  
      float* n = mesh.tri_normal (itri);
      std::cout   << "normal of triangle " << itri << ": "
                  << "(" << n[0] << ", " << n[1] << ", " << n[2] << ")\n";
  }
}
catch (std::exception& e) {
  std::cout << e.what() << std::endl;
}
```

### Usage example 2 (using `StlMesh` and *solids*)

```{.c}
try {
  stl_reader::StlMesh <float, unsigned int> mesh ("geometry.stl");

  for(size_t isolid = 0; isolid < mesh.num_solids(); ++isolid) {
      std::cout << "solid " << isolid << std::endl;

      for(size_t itri = mesh.solid_tris_begin(isolid);
          itri < mesh.solid_tris_end(isolid); ++itri)
      {
          const float* n = mesh.tri_normal (itri);
          std::cout   << "normal of triangle " << itri << ": "
                      << "(" << n[0] << ", " << n[1] << ", " << n[2] << ")\n";
      }
  }
}
catch (std::exception& e) {
  std::cout << e.what() << std::endl;
}
```

### Usage example 3 (using raw data arrays)

```{.c}
std::vector<float> coords, normals;
std::vector<unsigned int> tris, solids;

try {
  stl_reader::ReadStlFile ("geometry.stl", coords, normals, tris, solids);
  const size_t numTris = tris.size() / 3;
  for(size_t itri = 0; itri < numTris; ++itri) {
      std::cout << "coordinates of triangle " << itri << ": ";
      for(size_t icorner = 0; icorner < 3; ++icorner) {
          float* c = &coords[3 * tris [3 * itri + icorner]];
          std::cout << "(" << c[0] << ", " << c[1] << ", " << c[2] << ") ";
      }
      std::cout << std::endl;
  
      float* n = &normals [3 * itri];
      std::cout   << "normal of triangle " << itri << ": "
                  << "(" << n[0] << ", " << n[1] << ", " << n[2] << ")\n";
  }
}
catch (std::exception& e) {
  std::cout << e.what() << std::endl;
}
```

**Note:** If you do not want to use exceptions, you may define the macro STL_READER_NO_EXCEPTIONS before including 'stl_reader.h'. In that case, functions will return `false` if an error occurred.

## License
**stl_reader** is licensed under a *2-clause BSD* license:

    Copyright (c) 2018, Sebastian Reiter (s.b.reiter@gmail.com)
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


