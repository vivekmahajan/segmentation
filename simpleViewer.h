
#include <QtGui>
#include<QApplication>
#include <QGLViewer/qglviewer.h>
#include <fstream>
#include <vector>
#include <dataStructures.h>
#include <assert.h>
#include <list>
#include <time.h>
#include<algorithm>
#include <set>
#include <igraph/igraph.h>



class Viewer : public QGLViewer
{
private:
   //various datastructures for creating the half edge datastructure
    std::vector<Point3> vertexArray;
    std::vector<Face3> faceArray;
    std::vector<Point3> normalFaceArray;
    std::vector<std::pair<int,int> >edgeArray;
    std::vector<Point3> normalVertexArray;
    std::vector< std::vector<Point3> >normalBuffer;
    std::vector<heFace *> heFaceArr;
    std::vector<heVertex * > heVertArr;
    std::vector<int> deletedVert;
    std::vector< std::vector<dualEdge*> >dualGraph; //adjancey list
    std::vector< std::vector<int> > adjanceyGraph;
    std::vector<Point3> colorList;
    std::vector<dualNode*> dualNodes;

    Point3 medianObject;
    int wireFlag;
    int shadingFlag;//1=>flat 0=>smooth
    int wireShadeFlag;
    int numberCommunities;
    //data members will have datastructure to store meshes
protected :
  virtual void init();
  virtual QString helpString() const;
public:

  virtual void draw();


  std::list<heFace *> heFaceList;

  void drawObject(int);//drawing the final object

  void copyObject(Viewer*);


  //These set of functions changes the UI
  void setWireFlag(int); //for wire mesh
  void setShadingFlag(int); //for shading
  void setWireShadeFlag(int);//fore wire+shading

  //Functions called imidiately after loading the mesh(mainly populates the datastructure
  void createHalfEdgeStructure();//creating the half edge datastructure
  void calculateFaceNormal();//calculating the face normals
  void calculateVertexNormal();//calculating vertex normals
  void calculateMedian(); //calculating the median to center the object in the screen
  void calculatingPlaneEq();//calculating the plane equation for quadric error
  void initiatingQuadrics();//initiating quadric matrix


  //These functions are used during simplication process
  void simplifyMesh(int,unsigned int);//this routine is called when decimate button is pressed
  float calculatingError(heVertex* ,heVertex* );//calculating the error when second vertex is collapsed into one
  float errorMatrix(float[],heVertex*);//getting the error- helper function for calculatingError() function
  void halfEdgeCollapse(heEdge*);//collapsing the passed half edge
  void updatingStuff(heVertex*);//updating quadric and vertex normals
  void updatingPlaneEq(heVertex*);//updating the plane equations


  //helper functions(functions used by various functions)
  unsigned int getFaceListSize();//getting the face list size
  void startSavingArr();
  Point3 getPoint(int);
  Face3 getFace(int);
  int getVertexArrSize();
  int getFaceArrSize();
  void testingHalfEdge();//testing half edge datastructure
  void traversingFaces(heVertex*);//traversing the faces-helper function for testing
  Point3 subtractPoints(Point3,Point3); //subtracting two points and getting new points e.g p1=p2-p3;
  void insertPoint(Point3); //inserting a point in the datastructure
  void insertFace(Face3); //inserting face in the datastructure
  void printAll();//helper function to print all


  //clear all created datastrucutres
  void clearAll(); //clearing all the datastructures before loading another mesh


  //Segmentation supporting functions
  void makeDualGraph();
  float angleBtwVec(heFace*,heFace*);
  float edgeLength(heEdge*);
  float triangleDist(heFace*,heFace*);
  void addRemoveEdges(float,float);
  int normalIntersect(heFace*,heFace*,Point3*);
  void refreshColorsSeg();
  int convexCheck(heFace*,heFace*);

  void calculateCentroids();

  void calculateAvgWtheta();

  void addingSegments(std::vector<int>);
  void fixingArtifacts(int); //fixing artifacts after generating the segements

  void show_results(igraph_t *, igraph_vector_t *, igraph_matrix_t *);





};
