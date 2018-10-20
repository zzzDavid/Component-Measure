# A Component Measuring Program Based on CV
- Date: 2018-10-16
- Version: 1.0.0
- Abstract: Program measures shape parameters of component based on input image

---

## My view of this Project

### The final goal

The final goal is to implement 7 functions that is compatible with C#, that might be something
look like these:

```C#
public bool Measure_Origins (HObject ho_Image, out double[] _OriginsPosXY, ref string str);
// Input: Rectangular Object Image
// Output: coordinates of its four corners, string: execution state

public bool func2 (HObject ho_Image, out double[] data, ref string str );
// Output: width, height, diagnal difference of a rectagular object

public bool func3 (HObject ho_Image, ArrayList data, ref string str);
// Output: orientation, x, y, r of every hole

public bool func4 (HObject ho_Image, ArrayList data, ref string str);
// Output: data about Milling slot

public bool func5 (HObject ho_Image, ArrayList data, ref string str);
// Output: data about Saw slot

public bool func6 (HObject ho_Image, ArrayList data, ref string str);
// Output: data about straight lines of exterior contour

public bool func7 (HObject ho_Image, ArrayList data, ref string str);
// Output: data about curves in exterior contour

```
With my work submitted, function `Measure_Origins` and `func2`, `func6`, `func7` can be implemented with some modification.

Therefore, I suggest each of us implement a few functions, test them out, and then simply put them together. For example, I can implement function 1, 2, and 6, 7 and test each of them with different cases. Then, we just put our work together. 

As for wrap, in the worst case we have to learn `C#` and write it all over again. Maybe it won't be too much of work, since the core functions are set and tuned. 

### My part of work

I found out that with polygon approximation I can reduce the glitch around the contour thus achieve better hough line transform and circle detection. 

After I have identified the lines and circle in the image, I try to detect the rectangular corners in the image (which we'll use for construct straight lines later) and identify the end points of the curve.

Once the end points of a curve is identified, we can crop the curve out from the original contour. Then, we basically have everything we need for exterior contour.

### Problems with my implementation

*For readability I packaged a lot of actions into helper functions, which can also be reused later* 

As you said, the parameters of Hough line Transform affects the performace a lot. And my detection of curve is entirely based on it. I first detect all the straight line in the image, then using their end points, I decide which two points lie besides the tangent circle, then I get the curve end points.

This method is not very robust. If the Hough line Transform is bad, it's possibel it couldn't detect any curve at all. However, i did replace the original contour with a polygon approximation, so the `houghLineP` should works okay. Also, it can only work with 1 curve now, for I only select two curve endpoints. 

I think there are some new requirements came out yesterday but I haven't read it yet.

---

## Project Brief

### Dependency
```
- OpenCV 3.0
- C++ 14
```


### Project structure

```
Component-Measure
|- bin/ (executable)
|- image/ (input images)
|- include/  (header file)
|- src/  (source files)
|- output/ (output images)
|- README.md
|- CMakelists.txt
```

---

### Compile and Run

```
# compile
cmake .
make

# runtest
./bin/measure ./image/800-white-L-shaped-curve/17-11-15-15-01-30top.tif 

```

---

### Output
![window](output/image_all.jpg)

We now have all the information about the exterior contour:
vertices, straight lines, curves, and its tangent circle.

But we can only deal with 1 curve at this time.

**Now I Shall Sleep. Please Finish What We Started, My Friend.**