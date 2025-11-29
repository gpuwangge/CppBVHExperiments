# Build
```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make -j
```

# TestCase 1 Output
```
== BVH Build Start ==
Generating primitive info...
Tri 0 AABB min(0,0,-0.0005) max(1,1,0.0005) centroid(0.333333,0.333333,0)    
Tri 1 AABB min(2,2,-0.0005) max(3,3,0.0005) centroid(2.33333,2.33333,0)      
Tri 2 AABB min(-2,-2,-0.0005) max(-1,-1,0.0005) centroid(-1.33333,-1.33333,0)
[Depth 0] BuildRecursive start=0 count=3
Split axis = 0 (extent=5,5,0.001)
Centroids after sorting: -1.33333 0.333333 2.33333
  [Depth 1] BuildRecursive start=0 count=1
  Leaf created: tri_start=0 tri_count=1
  [Depth 1] BuildRecursive start=1 count=2
  Split axis = 0 (extent=3,3,0.001)
  Centroids after sorting: 0.333333 2.33333
    [Depth 2] BuildRecursive start=1 count=1
    Leaf created: tri_start=1 tri_count=1
    [Depth 2] BuildRecursive start=2 count=1
    Leaf created: tri_start=2 tri_count=1
  Internal node created: left=3 right=4
Internal node created: left=1 right=2
BVH Build Finished. Root node = 0
Total Nodes: 5

== BVH Validation ==
Node 0: bbox(-2,-2,-0.0005) - (3,3,0.0005)
Node 1: bbox(-2,-2,-0.0005) - (-1,-1,0.0005)  [Leaf: start=0 count=1]
Node 2: bbox(0,0,-0.0005) - (3,3,0.0005)
Node 3: bbox(0,0,-0.0005) - (1,1,0.0005)  [Leaf: start=1 count=1]    
Node 4: bbox(2,2,-0.0005) - (3,3,0.0005)  [Leaf: start=2 count=1]    
All triangles covered.
Sum of triangles in leaves = 3
Hierarchy bbox OK.
== End Validation ==
```

# TestCase 2 Output
```
===== Test Triangles (20) =====
Tri 0: (-4.64,-5.74), (-4.78,-4.84), (-4.88,-5.66)
Tri 1: (-4.52,-5.84), (-4.88,-5.92), (-5.1,-5.64)
Tri 2: (-4.58,-4.34), (-5.64,-5.58), (-4.64,-5.62)
Tri 3: (-5.76,-4.5), (-4.62,-5.52), (-4.72,-4.66)
Tri 4: (-5.46,-4.6), (-5.5,-4.5), (-4.54,-5.5)
Tri 5: (4.45,3.85), (3.825,5.475), (3.775,4.1)
Tri 6: (3.775,3.975), (5.375,5.55), (4.95,3.85)
Tri 7: (4.7,5), (5.225,5.55), (5.825,5.5)
Tri 8: (5.4,3.825), (5.075,4.725), (4.25,3.925)
Tri 9: (4.425,5.375), (4.025,5.725), (5.45,4.575)
Tri 10: (4.64,-3.1), (5.48,-4.94), (4.2,-3.44)
Tri 11: (4.02,-4.26), (4.06,-4.64), (4.98,-4.98)
Tri 12: (4.5,-3.24), (4.9,-3.48), (4.54,-4.02)
Tri 13: (4.96,-3.22), (5.28,-4.92), (5.14,-4.92)
Tri 14: (4.46,-4.5), (5.34,-3.9), (5.28,-4.94)
Tri 15: (0.21,1.38), (-0.63,1.05), (-0.78,0.81)
Tri 16: (0.57,-0.51), (-1.38,-0.03), (-0.75,0.6)
Tri 17: (-1.05,-0.45), (-0.42,-0.24), (0.36,1.47)
Tri 18: (0.0599999,0.39), (-0.66,-1.5), (-1.47,1.35)
Tri 19: (-0.6,-1.02), (-0.48,0.69), (-0.9,-0.69)
== BVH Build Start ==
Generating primitive info...
Tri 0 AABB min(-4.88,-5.74,-0.0005) max(-4.64,-4.84,0.0005) centroid(-4.76667,-5.41333,0)
Tri 1 AABB min(-5.1,-5.92,-0.0005) max(-4.52,-5.64,0.0005) centroid(-4.83333,-5.8,0)
Tri 2 AABB min(-5.64,-5.62,-0.0005) max(-4.58,-4.34,0.0005) centroid(-4.95333,-5.18,0)
Tri 3 AABB min(-5.76,-5.52,-0.0005) max(-4.62,-4.5,0.0005) centroid(-5.03333,-4.89333,0)
Tri 4 AABB min(-5.5,-5.5,-0.0005) max(-4.54,-4.5,0.0005) centroid(-5.16667,-4.86667,0)
Tri 5 AABB min(3.775,3.85,-0.0005) max(4.45,5.475,0.0005) centroid(4.01667,4.475,0)
Tri 6 AABB min(3.775,3.85,-0.0005) max(5.375,5.55,0.0005) centroid(4.7,4.45833,0)
Tri 7 AABB min(4.7,5,-0.0005) max(5.825,5.55,0.0005) centroid(5.25,5.35,0)
Tri 8 AABB min(4.25,3.825,-0.0005) max(5.4,4.725,0.0005) centroid(4.90833,4.15833,0)
Tri 9 AABB min(4.025,4.575,-0.0005) max(5.45,5.725,0.0005) centroid(4.63333,5.225,0)
Tri 10 AABB min(4.2,-4.94,-0.0005) max(5.48,-3.1,0.0005) centroid(4.77333,-3.82667,0)
Tri 11 AABB min(4.02,-4.98,-0.0005) max(4.98,-4.26,0.0005) centroid(4.35333,-4.62667,0)
Tri 12 AABB min(4.5,-4.02,-0.0005) max(4.9,-3.24,0.0005) centroid(4.64667,-3.58,0)
Tri 13 AABB min(4.96,-4.92,-0.0005) max(5.28,-3.22,0.0005) centroid(5.12667,-4.35333,0)
Tri 14 AABB min(4.46,-4.94,-0.0005) max(5.34,-3.9,0.0005) centroid(5.02667,-4.44667,0)
Tri 15 AABB min(-0.78,0.81,-0.0005) max(0.21,1.38,0.0005) centroid(-0.4,1.08,0)
Tri 16 AABB min(-1.38,-0.51,-0.0005) max(0.57,0.6,0.0005) centroid(-0.52,0.02,0)
Tri 17 AABB min(-1.05,-0.45,-0.0005) max(0.36,1.47,0.0005) centroid(-0.37,0.26,0)
Tri 18 AABB min(-1.47,-1.5,-0.0005) max(0.0599999,1.35,0.0005) centroid(-0.69,0.08,0)
Tri 19 AABB min(-0.9,-1.02,-0.0005) max(-0.48,0.69,0.0005) centroid(-0.66,-0.34,0)
[Depth 0] BuildRecursive start=0 count=20
Split axis = 1 (extent=11.585,11.645,0.001)
Centroids after sorting: -5.8 -5.41333 -5.18 -4.89333 -4.86667 -4.62667 -4.44667 -4.35333 -3.82667 -3.58 -0.34 0.02 0.08 0.26 1.08 4.15833 4.45833 4.475 5.225 5.35
  [Depth 1] BuildRecursive start=0 count=10
  Split axis = 0 (extent=11.24,2.82,0.001)
  Centroids after sorting: -5.16667 -5.03333 -4.95333 -4.83333 -4.76667 4.35333 4.64667 4.77333 5.02667 5.12667
    [Depth 2] BuildRecursive start=0 count=5
    Split axis = 1 (extent=1.24,1.58,0.001)
    Centroids after sorting: -5.8 -5.41333 -5.18 -4.89333 -4.86667
      [Depth 3] BuildRecursive start=0 count=2
      Split axis = 1 (extent=0.58,1.08,0.001)
      Centroids after sorting: -5.8 -5.41333
        [Depth 4] BuildRecursive start=0 count=1
        Leaf created: tri_start=0 tri_count=1
        [Depth 4] BuildRecursive start=1 count=1
        Leaf created: tri_start=1 tri_count=1
      Internal node created: left=4 right=5
      [Depth 3] BuildRecursive start=2 count=3
      Split axis = 1 (extent=1.22,1.28,0.001)
      Centroids after sorting: -5.18 -4.89333 -4.86667
        [Depth 4] BuildRecursive start=2 count=1
        Leaf created: tri_start=2 tri_count=1
        [Depth 4] BuildRecursive start=3 count=2
        Split axis = 0 (extent=1.22,1.02,0.001)
        Centroids after sorting: -5.16667 -5.03333
          [Depth 5] BuildRecursive start=3 count=1
          Leaf created: tri_start=3 tri_count=1
          [Depth 5] BuildRecursive start=4 count=1
          Leaf created: tri_start=4 tri_count=1
        Internal node created: left=9 right=10
      Internal node created: left=7 right=8
    Internal node created: left=3 right=6
    [Depth 2] BuildRecursive start=5 count=5
    Split axis = 1 (extent=1.46,1.88,0.001)
    Centroids after sorting: -4.62667 -4.44667 -4.35333 -3.82667 -3.58
      [Depth 3] BuildRecursive start=5 count=2
      Split axis = 0 (extent=1.32,1.08,0.001)
      Centroids after sorting: 4.35333 5.02667
        [Depth 4] BuildRecursive start=5 count=1
        Leaf created: tri_start=5 tri_count=1
        [Depth 4] BuildRecursive start=6 count=1
        Leaf created: tri_start=6 tri_count=1
      Internal node created: left=13 right=14
      [Depth 3] BuildRecursive start=7 count=3
      Split axis = 1 (extent=1.28,1.84,0.001)
      Centroids after sorting: -4.35333 -3.82667 -3.58
        [Depth 4] BuildRecursive start=7 count=1
        Leaf created: tri_start=7 tri_count=1
        [Depth 4] BuildRecursive start=8 count=2
        Split axis = 1 (extent=1.28,1.84,0.001)
        Centroids after sorting: -3.82667 -3.58
          [Depth 5] BuildRecursive start=8 count=1
          Leaf created: tri_start=8 tri_count=1
          [Depth 5] BuildRecursive start=9 count=1
          Leaf created: tri_start=9 tri_count=1
        Internal node created: left=18 right=19
      Internal node created: left=16 right=17
    Internal node created: left=12 right=15
  Internal node created: left=2 right=11
  [Depth 1] BuildRecursive start=10 count=10
  Split axis = 0 (extent=7.295,7.225,0.001)
  Centroids after sorting: -0.69 -0.66 -0.52 -0.4 -0.37 4.01667 4.63333 4.7 4.90833 5.25
    [Depth 2] BuildRecursive start=10 count=5
    Split axis = 1 (extent=2.04,2.97,0.001)
    Centroids after sorting: -0.34 0.02 0.08 0.26 1.08
      [Depth 3] BuildRecursive start=10 count=2
      Split axis = 0 (extent=1.95,1.71,0.001)
      Centroids after sorting: -0.66 -0.52
        [Depth 4] BuildRecursive start=10 count=1
        Leaf created: tri_start=10 tri_count=1
        [Depth 4] BuildRecursive start=11 count=1
        Leaf created: tri_start=11 tri_count=1
      Internal node created: left=23 right=24
      [Depth 3] BuildRecursive start=12 count=3
      Split axis = 1 (extent=1.83,2.97,0.001)
      Centroids after sorting: 0.08 0.26 1.08
        [Depth 4] BuildRecursive start=12 count=1
        Leaf created: tri_start=12 tri_count=1
        [Depth 4] BuildRecursive start=13 count=2
        Split axis = 1 (extent=1.41,1.92,0.001)
        Centroids after sorting: 0.26 1.08
          [Depth 5] BuildRecursive start=13 count=1
          Leaf created: tri_start=13 tri_count=1
          [Depth 5] BuildRecursive start=14 count=1
          Leaf created: tri_start=14 tri_count=1
        Internal node created: left=28 right=29
      Internal node created: left=26 right=27
    Internal node created: left=22 right=25
    [Depth 2] BuildRecursive start=15 count=5
    Split axis = 0 (extent=2.05,1.9,0.001)
    Centroids after sorting: 4.01667 4.63333 4.7 4.90833 5.25
      [Depth 3] BuildRecursive start=15 count=2
      Split axis = 1 (extent=1.675,1.875,0.001)
      Centroids after sorting: 4.475 5.225
        [Depth 4] BuildRecursive start=15 count=1
        Leaf created: tri_start=15 tri_count=1
        [Depth 4] BuildRecursive start=16 count=1
        Leaf created: tri_start=16 tri_count=1
      Internal node created: left=32 right=33
      [Depth 3] BuildRecursive start=17 count=3
      Split axis = 0 (extent=2.05,1.725,0.001)
      Centroids after sorting: 4.7 4.90833 5.25
        [Depth 4] BuildRecursive start=17 count=1
        Leaf created: tri_start=17 tri_count=1
        [Depth 4] BuildRecursive start=18 count=2
        Split axis = 1 (extent=1.575,1.725,0.001)
        Centroids after sorting: 4.15833 5.35
          [Depth 5] BuildRecursive start=18 count=1
          Leaf created: tri_start=18 tri_count=1
          [Depth 5] BuildRecursive start=19 count=1
          Leaf created: tri_start=19 tri_count=1
        Internal node created: left=37 right=38
      Internal node created: left=35 right=36
    Internal node created: left=31 right=34
  Internal node created: left=21 right=30
Internal node created: left=1 right=20
BVH Build Finished. Root node = 0
Total Nodes: 39

== BVH Validation ==
Node 0: bbox(-5.76,-5.92,-0.0005) - (5.825,5.725,0.0005)
Node 1: bbox(-5.76,-5.92,-0.0005) - (5.48,-3.1,0.0005)
Node 2: bbox(-5.76,-5.92,-0.0005) - (-4.52,-4.34,0.0005)
Node 3: bbox(-5.1,-5.92,-0.0005) - (-4.52,-4.84,0.0005)
Node 4: bbox(-5.1,-5.92,-0.0005) - (-4.52,-5.64,0.0005)  [Leaf: start=0 count=1]
Node 5: bbox(-4.88,-5.74,-0.0005) - (-4.64,-4.84,0.0005)  [Leaf: start=1 count=1]
Node 6: bbox(-5.76,-5.62,-0.0005) - (-4.54,-4.34,0.0005)
Node 7: bbox(-5.64,-5.62,-0.0005) - (-4.58,-4.34,0.0005)  [Leaf: start=2 count=1]
Node 8: bbox(-5.76,-5.52,-0.0005) - (-4.54,-4.5,0.0005)
Node 9: bbox(-5.5,-5.5,-0.0005) - (-4.54,-4.5,0.0005)  [Leaf: start=3 count=1]
Node 10: bbox(-5.76,-5.52,-0.0005) - (-4.62,-4.5,0.0005)  [Leaf: start=4 count=1]
Node 11: bbox(4.02,-4.98,-0.0005) - (5.48,-3.1,0.0005)
Node 12: bbox(4.02,-4.98,-0.0005) - (5.34,-3.9,0.0005)
Node 13: bbox(4.02,-4.98,-0.0005) - (4.98,-4.26,0.0005)  [Leaf: start=5 count=1]
Node 14: bbox(4.46,-4.94,-0.0005) - (5.34,-3.9,0.0005)  [Leaf: start=6 count=1]
Node 15: bbox(4.2,-4.94,-0.0005) - (5.48,-3.1,0.0005)
Node 16: bbox(4.96,-4.92,-0.0005) - (5.28,-3.22,0.0005)  [Leaf: start=7 count=1]
Node 17: bbox(4.2,-4.94,-0.0005) - (5.48,-3.1,0.0005)
Node 18: bbox(4.2,-4.94,-0.0005) - (5.48,-3.1,0.0005)  [Leaf: start=8 count=1]
Node 19: bbox(4.5,-4.02,-0.0005) - (4.9,-3.24,0.0005)  [Leaf: start=9 count=1]
Node 20: bbox(-1.47,-1.5,-0.0005) - (5.825,5.725,0.0005)
Node 21: bbox(-1.47,-1.5,-0.0005) - (0.57,1.47,0.0005)
Node 22: bbox(-1.38,-1.02,-0.0005) - (0.57,0.69,0.0005)
Node 23: bbox(-0.9,-1.02,-0.0005) - (-0.48,0.69,0.0005)  [Leaf: start=10 count=1]
Node 24: bbox(-1.38,-0.51,-0.0005) - (0.57,0.6,0.0005)  [Leaf: start=11 count=1]
Node 25: bbox(-1.47,-1.5,-0.0005) - (0.36,1.47,0.0005)
Node 26: bbox(-1.47,-1.5,-0.0005) - (0.0599999,1.35,0.0005)  [Leaf: start=12 count=1]
Node 27: bbox(-1.05,-0.45,-0.0005) - (0.36,1.47,0.0005)
Node 28: bbox(-1.05,-0.45,-0.0005) - (0.36,1.47,0.0005)  [Leaf: start=13 count=1]
Node 29: bbox(-0.78,0.81,-0.0005) - (0.21,1.38,0.0005)  [Leaf: start=14 count=1]
Node 30: bbox(3.775,3.825,-0.0005) - (5.825,5.725,0.0005)
Node 31: bbox(3.775,3.85,-0.0005) - (5.45,5.725,0.0005)
Node 32: bbox(3.775,3.85,-0.0005) - (4.45,5.475,0.0005)  [Leaf: start=15 count=1]
Node 33: bbox(4.025,4.575,-0.0005) - (5.45,5.725,0.0005)  [Leaf: start=16 count=1]
Node 34: bbox(3.775,3.825,-0.0005) - (5.825,5.55,0.0005)
Node 35: bbox(3.775,3.85,-0.0005) - (5.375,5.55,0.0005)  [Leaf: start=17 count=1]
Node 36: bbox(4.25,3.825,-0.0005) - (5.825,5.55,0.0005)
Node 37: bbox(4.25,3.825,-0.0005) - (5.4,4.725,0.0005)  [Leaf: start=18 count=1]
Node 38: bbox(4.7,5,-0.0005) - (5.825,5.55,0.0005)  [Leaf: start=19 count=1]
All triangles covered.
Sum of triangles in leaves = 20
Hierarchy bbox OK.
== End Validation ==
```