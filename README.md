# ofxRayTriangleIntersection #
Ray casting addon for intersection detection between ray and triangle.
Typically useful for judging "point inside 3D object".

Cast 6 rays - along both positive and negative x, y and z directions from point. 
Count all the intersection with the triangle along each ray. 
If all of the rays' collision count with the geometry is an odd number, 
the current point is inside the object (3d hull).

And please check here.
http://softsurfer.com/Archive/algorithm_0105/algorithm_0105.htm

### usage ###
see the example_SimpleTri testApp.h/.cpp
