Finding communities in 3D meshes- A novel way to segment a 3D mesh
==================================================================
This was my final project for the course Geometric Modeling in computer graphics taught by [Dr. Richard Zhang](http://www.cs.sfu.ca/~haoz/) in Spring 2012. The algorithm and the results can be found [here](http://dl.dropbox.com/u/15298710/GeometricModeling.pdf)

Q. How to run the executable?
A. Run the shell script named "runThisScript.sh". This will do everything for you. It has qmake, make and also adds path to the libraries which is required during the run time. Just running make outside won't work. To clean the object files use $make clean. I am using igraph and libQGLViewer which lies inside usr directory.

Note:- You need to make sure the library has the correct path. Have a look at A2P6.pro for more information.


GUI:-
Important:-
The software now only takes .off files as provided under the mesh benchmark paper. I am attaching some of the files with the code. You can download more from here
http://segeval.cs.princeton.edu/public/Download/off.zip

After running the shell script you will get one window in which the mesh will be rendered. It has two drop down menus at the top left corner viz. file and operations. For this project, I have added three more options under 
operations menu
1)Segmentation:- By the clicking this you will get a pop up window asking for the three input parameters. First two are the two threshold values for adding and deleting edges. Both values are between 0 and 1.
The third is the number of iterations for the fixing artifacts part. 
After running the segmentation algorithm, you might wanna run the fixing artifacts once more. If you set the first threshold value as -1 and run it again. It will only run the fixing artifacts algorithm.

2)Load segments:- Load segments loads .seg file, which provides segments for different algorithm. These are files in the set of files provided by the mesh benchmark paper.


3)Refresh Colors:- After generating or loading the segments, you might not get ideal colors for viewing. Just click on refresh colors again and again, till you get better colors.


Mouse Actions:-

Button(s)            Description
Wheel                Zooms camera
Left                 Rotates camera
Left double click    Aligns camera
Right                Translates camera
Right double click   Centers scene
Middle               Zooms camera

Keyboard Actions:-


Key(s)               Description
Left                 Moves camera left
Up                   Moves camera up
Right                Moves camera right
Down                 Moves camera down



