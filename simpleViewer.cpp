
#define SAME_CLOCKNESS 1
#define DIFF_CLOCKNESS 0


#include "simpleViewer.h"
#include <iostream>
#include <QtGui>
#include <math.h>
#include <time.h>
using namespace std;
using namespace qglviewer;

// Draws a spiral
void Viewer::draw()
{
    //std::cout<<"aaaaaaaaaaaaaaaaaaa"<<std::endl;
    if(heFaceList.size()!=0)
    {
        //glEnable(GL_LIGHT0);
        if(wireFlag==1)
        {

           glEnable(GL_DEPTH_TEST);
           glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
           //set_color(BLUE);
         //  glColor3f(1.0,1.0,1.0);
            glColor3f(0.0,0.0,0.0);
           glTranslatef(medianObject.x,medianObject.y,medianObject.z);
           drawObject(shadingFlag);

           QColor back=this->backgroundColor();
           float r=back.red();
           float g=back.green();
           float b=back.blue();
           r=r/255.0;
           g=g/255.0;
           b=b/255.0;

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_POLYGON_OFFSET_FILL);
            //glPolygonOffset(100000.0, 1000.0);
            glPolygonOffset(100.0,1.0);
            //set_color(BLACK);
            //glColor3f(0.15,0.15,0.15);
            glColor3f(r,g,b);
            //glColor3f(0.0,0.3,0.3);
            glDisable(GL_LIGHTING);
            drawObject(shadingFlag);
            glEnable(GL_LIGHTING);

            glDisable(GL_POLYGON_OFFSET_FILL);

        }else if(wireShadeFlag==1)
        {
           glEnable(GL_DEPTH_TEST);
           glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
           glColor3f(0.0,0.0,0.0);
           glTranslatef(medianObject.x,medianObject.y,medianObject.z);

           drawObject(shadingFlag);



            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1.0, 1.0);
            glColor3f(0.0,0.3,0.3);

            drawObject(shadingFlag);

            glDisable(GL_POLYGON_OFFSET_FILL);

        }else
        {
            glPolygonMode(GL_FRONT,GL_FILL);
            glPolygonMode(GL_BACK,GL_FILL);
          //  glColor3f(0.0,0.3,0.3);
            glTranslatef(medianObject.x,medianObject.y,medianObject.z);
            drawObject(shadingFlag);
        }



     }

     glFlush();

}

void Viewer::refreshColorsSeg()
{
    if(colorList.size()==0)
        return;
    srand(time(NULL));
    //filling the color
    colorList.clear();
    for(unsigned int i=0;i<this->numberCommunities;i++)
    {
          Point3 color;
          color.x=(float)(rand()%this->numberCommunities)/(float)this->numberCommunities;
          color.y=(float)(rand()%this->numberCommunities)/(float)this->numberCommunities;
          color.z=(float)(rand()%this->numberCommunities)/(float)this->numberCommunities;
          this->colorList.push_back(color);

       //   std::cout<<"hohohohoh "<<std::endl;
    }


}

void Viewer::drawObject(int flag)
{
      glBegin(GL_TRIANGLES);
      if(flag==1)
      {
          std::list<heFace*>::iterator it;
          for(it=heFaceList.begin();it!=heFaceList.end();it++)
          {
              heEdge* edge = (*it)->edge;
              do {
                   // do something with edge, edge->pair or edge->face
                  glNormal3f(edge->vert->normals[0],edge->vert->normals[1],edge->vert->normals[2]);
                  glVertex3f(edge->vert->x,edge->vert->y,edge->vert->z);
                  edge = edge->next;
              } while (edge != (*it)->edge);
          }
     }else
      {
         std::list<heFace*>::iterator it;
         for(it=heFaceList.begin();it!=heFaceList.end();it++)
         {
     //        glIndexs((*it)->clusterNo+100);
          //  glColor3f(0.0,0.3,(float)(*it)->clusterNo/7);
             if(colorList.size()!=0)
             {
                glColor3f(this->colorList[(*it)->clusterNo].x,this->colorList[(*it)->clusterNo].y,this->colorList[(*it)->clusterNo].z);
             }else
             {
                 glColor3f(0.0,0.3,0.3);

             }

             glNormal3f((*it)->normals[0],(*it)->normals[1],(*it)->normals[2]);
             heEdge* edge = (*it)->edge;
             do {
                  // do something with edge, edge->pair or edge->face
                 glVertex3f(edge->vert->x,edge->vert->y,edge->vert->z);
                  edge = edge->next;


             } while (edge != (*it)->edge);
         }
     }


  glEnd();




/*

    glBegin(GL_TRIANGLES);
    //glColor3f(0.0,0.0,0.3);
    unsigned int numberTriangles=faceArray.size();
    //1 means flat 0 means smooth
    if(flag==1)
    {
        for(unsigned int i=0;i<numberTriangles;i++)
        {
            glNormal3f(normalVertexArray[faceArray[i].p1].x,normalVertexArray[faceArray[i].p1].y,normalVertexArray[faceArray[i].p1].z);
            glVertex3f(vertexArray[faceArray[i].p1].x,vertexArray[faceArray[i].p1].y,vertexArray[faceArray[i].p1].z);
            glNormal3f(normalVertexArray[faceArray[i].p2].x,normalVertexArray[faceArray[i].p2].y,normalVertexArray[faceArray[i].p2].z);
            glVertex3f(vertexArray[faceArray[i].p2].x,vertexArray[faceArray[i].p2].y,vertexArray[faceArray[i].p2].z);
            glNormal3f(normalVertexArray[faceArray[i].p3].x,normalVertexArray[faceArray[i].p3].y,normalVertexArray[faceArray[i].p3].z);
            glVertex3f(vertexArray[faceArray[i].p3].x,vertexArray[faceArray[i].p3].y,vertexArray[faceArray[i].p3].z);
        }

   }else
    {


       for(unsigned int i=0;i<numberTriangles;i++)
       {
           glNormal3f(normalFaceArray[i].x,normalFaceArray[i].y,normalFaceArray[i].z);
           glVertex3f(vertexArray[faceArray[i].p1].x,vertexArray[faceArray[i].p1].y,vertexArray[faceArray[i].p1].z);
           glVertex3f(vertexArray[faceArray[i].p2].x,vertexArray[faceArray[i].p2].y,vertexArray[faceArray[i].p2].z);
           glVertex3f(vertexArray[faceArray[i].p3].x,vertexArray[faceArray[i].p3].y,vertexArray[faceArray[i].p3].z);
       }


   }

glEnd();
*/
}

void Viewer::init()
{

  //  std::cout<<"firsttttttttttttttt "<<std::endl;

    // Restore previous viewer state.
  restoreStateFromFile();

  // Opens help window
  //help();
}

QString Viewer::helpString() const
{
  QString text("<h2>S i m p l e V i e w e r</h2>");
  text += "Use the mouse to move the camera around the object. ";
  text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
  text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
  text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
  text += "Simply press the function key again to restore it. Several keyFrames define a ";
  text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
  text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
  text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
  text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
  text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
  text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
  text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
  text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
  text += "Press <b>Escape</b> to exit the viewer.";
  return text;
}

void Viewer::insertPoint(Point3 p)
{
    vertexArray.push_back(p);

}
void Viewer::insertFace(Face3 f)
{


    f.p1=f.p1-1;
    f.p2=f.p2-1;
    f.p3=f.p3-1;
    faceArray.push_back(f);






}
void Viewer::printAll()
{
  /*  for(unsigned int i=0;i<vertexArray.size();i++)
    {
        std::cout<<"**** "<<vertexArray[i].x<<" "<<vertexArray[i].y<<" "<<vertexArray[i].z<<std::endl;
    }

    std::cout<<"size of vertexArray "<<vertexArray.size()<<std::endl;*/
    for(unsigned int i=0;i<5;i++)
    {
        std::cout<<this->heFaceArr[i]->no<<std::endl;


    }
}
void Viewer::calculateMedian()
{
    medianObject.x=0.0;
    medianObject.y=0.0;
    medianObject.z=0.0;
  /*  unsigned int sizee=faceArray.size();
    for(unsigned int i=0;i<sizee;i++)
    {
        medianObject.x=medianObject.x+(vertexArray[faceArray[i].p1].x+vertexArray[faceArray[i].p2].x+vertexArray[faceArray[i].p3].x)/sizee;
        medianObject.y=medianObject.y+(vertexArray[faceArray[i].p1].y+vertexArray[faceArray[i].p2].y+vertexArray[faceArray[i].p3].y)/sizee;
        medianObject.z=medianObject.z+(vertexArray[faceArray[i].p1].z+vertexArray[faceArray[i].p2].z+vertexArray[faceArray[i].p3].z)/sizee;

    }*/

    unsigned int sizee=vertexArray.size();
    for(unsigned int i=0;i<sizee;i++)
    {
        medianObject.x=medianObject.x+vertexArray[i].x/sizee;
        medianObject.y=medianObject.y+vertexArray[i].y/sizee;
        medianObject.z=medianObject.z+vertexArray[i].z/sizee;

    }



    medianObject.x=-1.0*medianObject.x;
    medianObject.y=-1.0*medianObject.y;
    medianObject.z=-1.0*medianObject.z;


}
void Viewer::clearAll()
{
    vertexArray.clear();
    faceArray.clear();
    normalFaceArray.clear();
    normalVertexArray.clear();
    normalBuffer.clear();
    heFaceArr.clear();
    heVertArr.clear();
    heFaceList.clear();
    dualGraph.clear();
    adjanceyGraph.clear();
    colorList.clear();
}
void Viewer::setWireFlag(int val)
{
    wireFlag=val;
}
void Viewer::setShadingFlag(int val)
{
    shadingFlag=val;
}

void Viewer::setWireShadeFlag(int val)
{
     wireShadeFlag=val;
}

void Viewer::calculateFaceNormal()
{
    //for vertex normals
    std::vector<Point3> temp;
    for(unsigned int i=0;i<vertexArray.size();i++)
        normalBuffer.push_back(temp);



    unsigned int numberTriangles=faceArray.size();
    for(unsigned int i=0;i<numberTriangles;i++)
    {
        Point3 U,V,normal;
        U=subtractPoints(vertexArray[faceArray[i].p1],vertexArray[faceArray[i].p2]);
        V=subtractPoints(vertexArray[faceArray[i].p1],vertexArray[faceArray[i].p3]);


      //  U=subtractPoints(vertexArray[faceArray[i].p2],vertexArray[faceArray[i].p1]);
      //  V=subtractPoints(vertexArray[faceArray[i].p3],vertexArray[faceArray[i].p1]);


        normal.x=(U.y*V.z)-(U.z*V.y);
        normal.y=(U.z*V.x)-(U.x*V.z);
        normal.z=(U.x*V.y)-(U.y*V.x);
        float temp1=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
        normal.x=normal.x/temp1;
        normal.y=normal.y/temp1;
        normal.z=normal.z/temp1;
        normalFaceArray.push_back(normal);

        //for vertex normals

        normalBuffer[faceArray[i].p1].push_back(normal);
        normalBuffer[faceArray[i].p2].push_back(normal);
        normalBuffer[faceArray[i].p3].push_back(normal);

    }
}
void Viewer::calculateVertexNormal()
{
   for(unsigned int i=0;i<normalBuffer.size();i++)
    {
        Point3 temp;
        normalVertexArray.push_back(temp);
        normalVertexArray[i].x=0.0;
        normalVertexArray[i].y=0.0;
        normalVertexArray[i].z=0.0;
        for(unsigned int j=0;j<normalBuffer[i].size();j++)
        {
            normalVertexArray[i].x=normalVertexArray[i].x+(normalBuffer[i][j].x/normalBuffer[i].size());
            normalVertexArray[i].y=normalVertexArray[i].y+(normalBuffer[i][j].y/normalBuffer[i].size());
            normalVertexArray[i].z=normalVertexArray[i].z+(normalBuffer[i][j].z/normalBuffer[i].size());
        }
    }
}


Point3 Viewer::subtractPoints(Point3 first,Point3 second)
{
    Point3 temp;
    temp.x=first.x-second.x;
    temp.y=first.y-second.y;
    temp.z=first.z-second.z;
    return temp;

}

void Viewer::createHalfEdgeStructure()
{
    //create face arr
    for(unsigned int i=0;i<faceArray.size();i++)
    {
        heFace* temp=new heFace;
        temp->edge=NULL;
        temp->no=i+1;
        //normal insertions
        temp->normals[0]=normalFaceArray[i].x;
        temp->normals[1]=normalFaceArray[i].y;
        temp->normals[2]=normalFaceArray[i].z;
        temp->updateFlag=0;
        heFaceArr.push_back(temp);

    }
    //create vert Array
    for(unsigned int i=0;i<vertexArray.size();i++)
    {
        heVertex* temp=new heVertex;
        temp->no=i+1;
        temp->edge=NULL;
        temp->x=vertexArray[i].x;
        temp->y=vertexArray[i].y;
        temp->z=vertexArray[i].z;
        temp->degree=0;
        temp->updatedFlag=0;
        heVertArr.push_back(temp);
    }

    map<pair<int, int>, heEdge *> myMap;
    for(unsigned int i=0;i<faceArray.size();i++)
    {
            heEdge * edge1=new heEdge;
            heEdge * edge2=new heEdge;
            heEdge * edge3=new heEdge;

            edge1->face=heFaceArr[i];
            edge2->face=heFaceArr[i];
            edge3->face=heFaceArr[i];

            edge1->vert=heVertArr[faceArray[i].p2];
            edge2->vert=heVertArr[faceArray[i].p3];
            edge3->vert=heVertArr[faceArray[i].p1];

            edge1->next=edge2;
            edge2->next=edge3;
            edge3->next=edge1;

            heFaceArr[i]->edge=edge2;

            heVertArr[faceArray[i].p1]->edge=edge1;
            heVertArr[faceArray[i].p2]->edge=edge2;
            heVertArr[faceArray[i].p3]->edge=edge3;

            //creating pair of half edges

            //for edge1
            map<pair<int, int>, heEdge *>::iterator it;

            it=myMap.find(std::make_pair(faceArray[i].p2,faceArray[i].p1));
            if(it!=myMap.end())//it means it exists
            {
                it->second->pair=edge1;
                edge1->pair=it->second;

            }else //it doesn't exist..insert it
            {
                myMap.insert(std::make_pair(std::make_pair(faceArray[i].p1,faceArray[i].p2), edge1));
                edgeArray.push_back(std::pair<int,int>(faceArray[i].p1,faceArray[i].p2));//creating edge list
            }


            //for edge2
            it=myMap.find(std::make_pair(faceArray[i].p3,faceArray[i].p2));
            if(it!=myMap.end())//it means it exists
            {
                it->second->pair=edge2;
                edge2->pair=it->second;

            }else //it doesn't exist..insert it
            {
                myMap.insert(std::make_pair(std::make_pair(faceArray[i].p2,faceArray[i].p3), edge2));
                edgeArray.push_back(std::pair<int,int>(faceArray[i].p2,faceArray[i].p3));//creating edge list

            }


            //for edge3
            it=myMap.find(std::make_pair(faceArray[i].p1,faceArray[i].p3));
            if(it!=myMap.end())//it means it exists
            {
                it->second->pair=edge3;
                edge3->pair=it->second;

            }else //it doesn't exist..insert it
            {
                myMap.insert(std::make_pair(std::make_pair(faceArray[i].p3,faceArray[i].p1), edge3));
                edgeArray.push_back(std::pair<int,int>(faceArray[i].p3,faceArray[i].p1));//creating edge list
            }
    }

    myMap.clear();edgeArray.clear();

    for(unsigned int i=0;i<heFaceArr.size();i++)
    {
        heFaceList.push_back(heFaceArr[i]);
    }
    for(unsigned int i=0;i<normalVertexArray.size();i++)
    {
       heVertArr[i]->normals[0]=normalVertexArray[i].x;
       heVertArr[i]->normals[1]=normalVertexArray[i].y;
       heVertArr[i]->normals[2]=normalVertexArray[i].z;
    }

    for(unsigned int i=0;i<heVertArr.size();i++)
    {
       heEdge* edge=heVertArr[i]->edge;
       int j=0;
       do
       {
           j++;
           edge=edge->pair->next;

       }while(edge!=heVertArr[i]->edge);

       heVertArr[i]->degree=j;
    }
}
float Viewer::angleBtwVec(heFace * h1, heFace *h2)
{
    float mag1=sqrt(pow(h1->normals[0],2)+pow(h1->normals[1],2)+pow(h1->normals[2],2));
    float mag2=sqrt(pow(h2->normals[0],2)+pow(h2->normals[1],2)+pow(h2->normals[2],2));
    float cosd=(h1->normals[0]*h2->normals[0]+h1->normals[1]*h2->normals[1]+h1->normals[2]*h2->normals[2])/(mag1*mag2);
    //std::cout<<h1->normals[0]<<" "<<h1->normals[1]<<" "<<h1->normals[2]<<" ** "<<h2->normals[0]<<" "<<h2->normals[1]<<" "<<h2->normals[2]<<" mag1 "<<mag1<<" mag2 "<<mag2<<std::endl;

    float angle;

    if(cosd>=1)
    {
        angle=0.0;
    }
    else
    {
        angle=acos(cosd);
    }
    //std::cout<<"cosd "<<cosd<<"Angle "<<angle<<std::endl;


    return angle;

}

float Viewer::edgeLength(heEdge * edge)
{
    float dist=sqrt(pow(edge->vert->x-edge->pair->vert->x,2)+pow(edge->vert->y-edge->pair->vert->y,2)+pow(edge->vert->z-edge->pair->vert->z,2));
    return dist;
}
float Viewer::triangleDist(heFace *h1, heFace *h2)
{
    Point3 cent1,cent2;
    cent1.x=0.0;
    cent1.y=0.0;
    cent1.z=0.0;
    cent2.x=0.0;
    cent2.y=0.0;
    cent2.z=0.0;

    heEdge* edge=h1->edge;
    do{
        cent1.x=cent1.x+edge->vert->x;
        cent1.y=cent1.y+edge->vert->y;
        cent1.z=cent1.z+edge->vert->z;
        edge=edge->next;
    }while(edge!=h1->edge);
    cent1.x=cent1.x/3;
    cent1.y=cent1.y/3;
    cent1.z=cent1.z/3;

    edge=h2->edge;
    do{
        cent2.x=cent2.x+edge->vert->x;
        cent2.y=cent2.y+edge->vert->y;
        cent2.z=cent2.z+edge->vert->z;
        edge=edge->next;
    }while(edge!=h2->edge);
    cent2.x=cent2.x/3;
    cent2.y=cent2.y/3;
    cent2.z=cent2.z/3;

    float dist=sqrt(pow(cent1.x-cent2.x,2)+pow(cent1.y-cent2.y,2)+pow(cent1.z-cent2.z,2));
    return dist;

}

void Viewer::calculateCentroids()
{
    std::list<heFace*>::iterator it;
    for(it=heFaceList.begin();it!=heFaceList.end();it++)
    {
        heEdge* edge=(*it)->edge;
        (*it)->centroid[0]=0.0;
        (*it)->centroid[1]=0.0;
        (*it)->centroid[2]=0.0;
        do
        {
            (*it)->centroid[0]=(*it)->centroid[0]+edge->vert->x;
            (*it)->centroid[1]=(*it)->centroid[1]+edge->vert->y;
            (*it)->centroid[2]=(*it)->centroid[2]+edge->vert->z;
            edge=edge->next;
        }while(edge!=(*it)->edge);

        (*it)->centroid[0]=(*it)->centroid[0]/3;
        (*it)->centroid[1]=(*it)->centroid[1]/3;
        (*it)->centroid[2]=(*it)->centroid[2]/3;
      //  std::cout<<"( "<<(*it)->centroid[0]<<","<<(*it)->centroid[1]<<","<<(*it)->centroid[2]<<")"<<std::endl;
    }
}
int Viewer::convexCheck(heFace *h1, heFace *h2)
{
     //calcuate the vector
    float vec[3];
    for(int i=0;i<3;i++)
    {
        vec[i]=h1->centroid[i]-h2->centroid[i];
    }

    //find dot product with one of the normals
    float dotProduct=0.0;
    for(int i=0;i<3;i++)
    {
       dotProduct=dotProduct+vec[i]*h2->normals[i];
    }

    if(dotProduct<=0)
    {
        return 1;
    }else
    {
        return 0;
    }





}

void Viewer::calculateAvgWtheta()
{
    dualNode* temp=new dualNode;
    temp->avgWtheta=0.0;
    this->dualNodes.push_back(temp);
    for(unsigned int i=1;i<this->dualGraph.size();i++)
    {
        dualNode* temp2=new dualNode;
        temp2->avgWtheta=0.0;
        for(unsigned int j=0;j<dualGraph[i].size();j++)
        {
            temp2->avgWtheta=temp2->avgWtheta+dualGraph[i][j]->wtheta;
        }
        temp2->avgWtheta=temp2->avgWtheta/3.0;
        dualNodes.push_back(temp2);
    }
}

void Viewer::makeDualGraph()
{
    for(unsigned int i=0;i<=this->heFaceArr.size();i++)//first entry will be kept vacant
    {
        std::vector<dualEdge *> tempVec;
        std::vector<int> tempvecc;
        this->adjanceyGraph.push_back(tempvecc);
        this->dualGraph.push_back(tempVec);

    }
    for(unsigned int i=1;i<=this->heFaceArr.size();i++)
    {

        heFace* tempFace=heFaceArr[i-1];
        assert(tempFace->no==i);
        heEdge* edge=tempFace->edge;
        do
        {
            int alpha=10;
            float pie=3.1419;
            int con=convexCheck(tempFace,edge->pair->face);
            float angle=angleBtwVec(tempFace,edge->pair->face);
            float edgeLen=edgeLength(edge);
            float triDist=triangleDist(tempFace,edge->pair->face);
            float wtheta=0.0;


            if(con==1)//convex edge
            {
                angle=angle+pie;

            }else
            {
                angle=pie-angle;

            }

            float val=pow((angle/pie),alpha);

            if(val>1)
            {
                wtheta=1;
            }else
            {
                wtheta=val;
            }

           // std::cout<<" wtheta "<<wtheta<<" angle "<<angle<<std::endl;
            dualEdge* tempEdge=new dualEdge;
            tempEdge->node=edge->pair->face->no;

            tempEdge->cutCost=wtheta*edgeLen;
            tempEdge->traversalCost=wtheta*triDist;
            tempEdge->wtheta=wtheta;
            dualGraph[i].push_back(tempEdge);
            adjanceyGraph[i].push_back(tempEdge->node);
            edge=edge->next;
        }while(edge!=tempFace->edge);
    }
    //Checking the validity of the dual graph..
    for(unsigned int i=1;i<dualGraph.size();i++)
    {
        //std::cout<<dualGraph[i].size();
        assert(dualGraph[i].size()==3);
        assert(adjanceyGraph[i].size()==3);
    }

   // this->printAll();
}



int check_same_clock_dir(Point3 pt1, Point3 pt2, Point3 pt3, Point3 norm)
{
   float testi, testj, testk;
   float dotprod;
   // normal of trinagle
   testi = (((pt2.y - pt1.y)*(pt3.z - pt1.z)) - ((pt3.y - pt1.y)*(pt2.z - pt1.z)));
   testj = (((pt2.z - pt1.z)*(pt3.x - pt1.x)) - ((pt3.z - pt1.z)*(pt2.x - pt1.x)));
   testk = (((pt2.x - pt1.x)*(pt3.y - pt1.y)) - ((pt3.x - pt1.x)*(pt2.y - pt1.y)));

   // Dot product with triangle normal
   dotprod = testi*norm.x + testj*norm.y + testk*norm.z;


   //answer
   if(dotprod < 0)
   {
       return DIFF_CLOCKNESS;
   }else
   {
       return SAME_CLOCKNESS;
   }
}

int check_intersect_tri(Point3 pt1, Point3 pt2, Point3 pt3, Point3 linept, Point3 vect,Point3* pt_int,Point3 norm)
{

   float dotprod;
   float t;


   // dot product of normal and line's vector if zero line is parallel to triangle
   dotprod = norm.x*vect.x + norm.y*vect.y + norm.z*vect.z;

   if(dotprod > 0)//the normal hitting from backside of the triangle
   {
      //Find point of intersect to triangle plane.
      //find t to intersect point
      t = -(norm.x*(linept.x-pt1.x)+norm.y*(linept.y-pt1.y)+norm.z*(linept.z-pt1.z))/(norm.x*vect.x+norm.y*vect.y+norm.z*vect.z);

      // if ds is neg line started past triangle so can't hit triangle.
      if(t < 0) return 0;

      pt_int->x = linept.x + vect.x*t;
      pt_int->y = linept.y + vect.y*t;
      pt_int->z = linept.z + vect.z*t;


      if(check_same_clock_dir(pt1, pt2, *pt_int, norm)==SAME_CLOCKNESS)
      {
         if(check_same_clock_dir(pt2, pt3, *pt_int, norm) == SAME_CLOCKNESS)
         {
            if(check_same_clock_dir(pt3, pt1, *pt_int, norm) == SAME_CLOCKNESS)
            {
               // answer in pt_int is insde triangle
               return 1;
            }
         }
      }
   }
   return 0;
}



int Viewer::normalIntersect(heFace *h1, heFace *h2,Point3 *ptInt)
{

Point3 p[3];
heEdge* edge=h2->edge;
int j=0;
do
{
   // std::cout<<"j "<<j<<std::endl;
    p[j].x=edge->vert->x;
    p[j].y=edge->vert->y;
    p[j].z=edge->vert->z;

    j++;
    edge=edge->next;
}while(edge!=h2->edge);

//finding the line point..i.e centroid of the triangle
Point3 linept;
linept.x=0.0;
linept.y=0.0;
linept.z=0.0;
edge=h1->edge;
do
{
    linept.x=linept.x+edge->vert->x;
    linept.y=linept.y+edge->vert->y;
    linept.z=linept.z+edge->vert->z;
    edge=edge->next;
}while(edge!=h1->edge);
linept.x=linept.x/3;
linept.y=linept.y/3;
linept.z=linept.z/3;

Point3 vect;
vect.x=-1.0*h1->normals[0];
vect.y=-1.0*h1->normals[1];
vect.z=-1.0*h1->normals[2];

Point3 norm;
norm.x=h2->normals[0];
norm.y=h2->normals[1];
norm.z=h2->normals[2];
return(check_intersect_tri(p[0],p[1],p[2],linept,vect,ptInt,norm));

}

void Viewer::addRemoveEdges(float threshAdd,float threshRem)
{

/*
    long int sumEdge=0;
    for(unsigned int i=1;i<adjanceyGraph.size();i++)
    {
        sumEdge=sumEdge+adjanceyGraph[i].size();

    }


    //now I have the adjancey graph without duplicated
    igraph_t g;
    igraph_vector_t v1, v2;
    //assert(sumEdge%2==0);//even number of edges
    igraph_vector_init(&v1,sumEdge*2);
    //directed graph
    int k=0;
    for(unsigned int i=1;i<this->adjanceyGraph.size();i++)
    {

        for(unsigned int j=0;j<this->adjanceyGraph[i].size();j++)
        {
            VECTOR(v1)[k]=i-1;
            k++;
            VECTOR(v1)[k]=adjanceyGraph[i][j]-1;
            k++;
        }

    }
    igraph_create(&g,&v1,0,0);
    igraph_vector_t modularity, weights;
    igraph_matrix_t merges;
    igraph_vector_init(&modularity,0);
     igraph_matrix_init(&merges,0,0);
     igraph_vector_init(&weights,0);
     igraph_simplify(&g,1,0);

     igraph_community_fastgreedy(&g, 0, &merges, &modularity);
     std::cout<<"hahahahahhahaha"<<std::endl;

*/
    //find the intersected triangle and decide whether to add edges or not
    for(unsigned int i=0;i<this->heFaceArr.size();i++)
    {
        std::vector<intersectedNode> pointSet;
        for(unsigned int j=0;j<this->heFaceArr.size();j++)
        {
                //std::cout<<i<<" "<<j<<std::endl;

               if(i!=j)
               {
                   Point3 ptInt;
                   intersectedNode node;

                   node.node=j+1;
                   if(normalIntersect(heFaceArr[i],heFaceArr[j],&ptInt))//we have found the intersecting triangle
                   {
                       node.pt=ptInt;
                       //collect all the point which are contendors
                       pointSet.push_back(node);
                   }

               }

        }
        assert(pointSet.size()>0);
        //if(pointSet.size()>1);
            //std::cout<<"Point size "<<pointSet.size()<<std::endl;

       // std::cout<<"Node 1 = "<<heFaceArr[i]->no<<" Node 2 = "<<pointSet[0].node<<std::endl;
        //std::cout<<pointSet.size()<<std::endl;

        Point3 cent;
        cent.x=0.0;
        cent.y=0.0;
        cent.z=0.0;
        heEdge* edge=heFaceArr[i]->edge;
        do
        {
            cent.x=cent.x+edge->vert->x;
            cent.y=cent.y+edge->vert->y;
            cent.z=cent.z+edge->vert->z;
            edge=edge->next;
        }while(edge!=heFaceArr[i]->edge);
        cent.x=cent.x/3;
        cent.y=cent.y/3;
        cent.z=cent.z/3;


        float min;
        int nodeId;
        //select the point with the closest euclidean distance
        for(unsigned int j=0;j<pointSet.size();j++)
        {
            float dist=sqrt(pow(pointSet[j].pt.x-cent.x,2)+pow(pointSet[j].pt.y-cent.y,2)+pow(pointSet[j].pt.z-cent.z,2));
            if(j==0)
            {
                nodeId=pointSet[j].node;
                min=dist;
            }else if(dist<min)
            {
                nodeId=pointSet[j].node;
                min=dist;
            }
        }
    /*    //now we have the node..decide whether we have to add or remove the edges..this is crucial
        float average1=0.0;
        for(unsigned int k=0;k<3;k++)
        {
          //  average1=average1+this->dualGraph[i+1][k]->traversalCost; //it can cutCost as well...we will see
             average1=average1+this->dualGraph[i+1][k]->wtheta; //it can cutCost as well...we will see
        }
        float average2=0.0;
        for(unsigned int k=0;k<3;k++)
        {
            //average2=average2+this->dualGraph[nodeId][k]->traversalCost; //it can cutCost as well...we will see
            average2=average2+this->dualGraph[nodeId][k]->wtheta; //it can cutCost as well...we will see
        }
        average2=average2/3;
        average1=average1/3;*/

        float average1,average2;
       average1=dualNodes[i+1]->avgWtheta;
       average2=dualNodes[nodeId]->avgWtheta;
     //  std::cout<<"ThreshAdd = "<<threshAdd<<" ThreshRem = "<<threshRem<<" Average1 = "<<average1<<" Average2 = "<<average2<<" avg1= "<<dualNodes[i+1]->avgWtheta<<" avg2 = "<<dualNodes[nodeId]->avgWtheta<<std::endl;

       if(average1>threshAdd&&average2>threshAdd)//add edges
        {
            //find the neighborhood of the intersected triangle and add
        /*    heEdge* edge=heFaceArr[nodeId-1]->edge;
            do
            {

                int flagg=0;
                for(unsigned int u=0;u<adjanceyGraph[edge->pair->face->no].size();u++)
                {
                    if(adjanceyGraph[edge->pair->face->no][u]==(i+1))
                    {
                        flagg=1;
                        break;
                    }

                }
                for(unsigned int u=0;u<adjanceyGraph[i+1].size();u++)
                {
                    if(adjanceyGraph[i+1][u]==edge->pair->face->no)
                    {
                        flagg=1;
                        break;
                    }

                }
                if(flagg==0&&(i+1)!=edge->pair->face->no)
                {
                    this->adjanceyGraph[i+1].push_back(edge->pair->face->no);
                    this->adjanceyGraph[edge->pair->face->no].push_back(i+1);

                }
                edge=edge->next;
            }while(edge!=heFaceArr[nodeId-1]->edge);*/

            heEdge* edge=heFaceArr[i]->edge;
            do
            {

                int flagg=0;
               /* for(unsigned int u=0;u<adjanceyGraph[edge->pair->face->no].size();u++)
                {
                    if(adjanceyGraph[edge->pair->face->no][u]==(i+1))
                    {
                        flagg=1;
                        break;
                    }

                }
                for(unsigned int u=0;u<adjanceyGraph[i+1].size();u++)
                {
                    if(adjanceyGraph[i+1][u]==edge->pair->face->no)
                    {
                        flagg=1;
                        break;
                    }

                }*/
                if(flagg==0&&(nodeId)!=edge->pair->face->no)
                {
                    if(dualNodes[edge->pair->face->no]->avgWtheta>threshAdd)
                    {
                        this->adjanceyGraph[nodeId].push_back(edge->pair->face->no);
                        this->adjanceyGraph[edge->pair->face->no].push_back(nodeId);
                    }

                }
                edge=edge->next;
            }while(edge!=heFaceArr[i]->edge);






        }
      /*  if(average1<threshRem)//remove edges
        {
            std::cout<<"***************************************** "<<std::endl;
            srand(time(NULL));
            int size=this->adjanceyGraph[i+1].size();
            for(int j=0;j<(size/2);j++)
            {
                int no=rand()%this->adjanceyGraph[i+1].size();
                this->adjanceyGraph[i+1].erase(this->adjanceyGraph[i+1].begin()+no);
            }

        }
*/

        pointSet.clear();

    }

    //now time to delete the edges
    for(unsigned int i=0;i<heFaceList.size();i++)
    {
        float average1=0.0;
        for(unsigned int k=0;k<3;k++)
        {
             average1=average1+this->dualGraph[i+1][k]->wtheta; //it can cutCost as well...we will see
        }
        if(average1<threshRem)//if it is less than the threshold then delete half of the edges
        {
            srand(time(NULL));
            int size=this->adjanceyGraph[i+1].size();
            for(int j=0;j<2*(size/3);j++)
            {
                int no=rand()%this->adjanceyGraph[i+1].size();
                int edgeTo=adjanceyGraph[i+1][no];
                this->adjanceyGraph[i+1].erase(this->adjanceyGraph[i+1].begin()+no);
                for(unsigned int k=0;k<adjanceyGraph[edgeTo].size();k++)
                {
                    if(adjanceyGraph[edgeTo][k]==(i+1))
                    {
                        this->adjanceyGraph[edgeTo].erase(this->adjanceyGraph[edgeTo].begin()+k);
                        k--;
                    }
                }
            }


        }
    }






    for(unsigned int i=1;i<5;i++)
    {
        std::cout<<adjanceyGraph[i].size()<<std::endl;
    }
    std::cout<<"Finished "<<std::endl;
    std::cout<<adjanceyGraph.size()<<std::endl;
    //removing the duplicates from the graph
    for(unsigned int i=1;i<this->adjanceyGraph.size();i++)
    {
        sort(adjanceyGraph[i].begin(),adjanceyGraph[i].end());
        adjanceyGraph[i].erase(unique(adjanceyGraph[i].begin(),adjanceyGraph[i].end()),adjanceyGraph[i].end());
    }

    for(unsigned int i=1;i<5;i++)
    {
        std::cout<<adjanceyGraph[i].size()<<std::endl;
    }

    //count the number of edges
    long int sumEdge=0;
    for(unsigned int i=1;i<adjanceyGraph.size();i++)
    {
        sumEdge=sumEdge+adjanceyGraph[i].size();

    }
    std::cout<<"Total number of edges "<<sumEdge<<std::endl;

    //now I have the adjancey graph without duplicated
    igraph_t g;
    igraph_vector_t v1, v2;
    //assert(sumEdge%2==0);//even number of edges
    igraph_vector_init(&v1,sumEdge*2);
    //directed graph
    int k=0;
    for(unsigned int i=1;i<this->adjanceyGraph.size();i++)
    {

        for(unsigned int j=0;j<this->adjanceyGraph[i].size();j++)
        {
            VECTOR(v1)[k]=i-1;
            k++;
            VECTOR(v1)[k]=adjanceyGraph[i][j]-1;
            k++;
        }

    }
    igraph_create(&g,&v1,0,0);
    igraph_vector_t modularity, weights;
    igraph_matrix_t merges;
    igraph_vector_init(&modularity,0);
     igraph_matrix_init(&merges,0,0);
     igraph_vector_init(&weights,0);
     igraph_simplify(&g,1,0);

     igraph_community_fastgreedy(&g, 0, &merges, &modularity);
     show_results(&g, &modularity, &merges);

     srand(time(NULL));
     //filling the color
     colorList.clear();
     for(unsigned int i=0;i<this->numberCommunities;i++)
     {
           Point3 color;
           color.x=(float)(rand()%this->numberCommunities)/(float)this->numberCommunities;
           color.y=(float)(rand()%this->numberCommunities)/(float)this->numberCommunities;
           color.z=(float)(rand()%this->numberCommunities)/(float)this->numberCommunities;
           this->colorList.push_back(color);

          // std::cout<<"hohohohoh "<<std::endl;
     }

     std::cout<<"ThreshAdd = "<<threshAdd<<" ThreshRemove "<<threshRem<<std::endl;


}
void Viewer::fixingArtifacts(int k)
{
    /*for(int i=0;i<k;i++)
    {
        //visiting each face and fixing its segment
        std::list<heFace*>::iterator it;
        for(it=heFaceList.begin();it!=heFaceList.end();it++)
        {
            std::vector<int> tempv;
            heEdge* edge=(*it)->edge;
            do
            {
                tempv.push_back(edge->pair->face->clusterNo);
                edge=edge->next;

            }while(edge!=(*it)->edge);
            assert(tempv.size()==3);
            std::sort(tempv.begin(),tempv.end());
            if(tempv[0]==tempv[1])
            {
                (*it)->clusterNo=tempv[0];
            }else if(tempv[1]==tempv[2])
            {
                (*it)->clusterNo=tempv[1];
            }

        }
    }*/

    for(int i=0;i<k;i++)
    {

        std::list<heFace *>::iterator it;

        //for each face..
        int counter=0;
        for(it=heFaceList.begin();it!=heFaceList.end();it++)
        {
            counter++;
            //std::cout<<counter<<" ";
            std::vector<int> hashMap;
            for(unsigned int j=0;j<heFaceArr.size();j++)
            {
                hashMap.push_back(0);

            }
            std::vector<int> tempv;
        //    tempv.push_back((*it)->clusterNo);

            heEdge* edge=(*it)->edge;
            do{
                if(hashMap[edge->pair->face->no]!=1)
                {
                    tempv.push_back(edge->pair->face->clusterNo);
                    hashMap[edge->pair->face->no]=1;
                }

                heEdge* edge1=edge->pair;
                do{

                    if(hashMap[edge1->pair->face->no]!=1)
                    {
                        tempv.push_back(edge1->pair->face->clusterNo);
                        hashMap[edge1->pair->face->no]=1;
                    }
                    edge1=edge1->next;
                }while(edge1!=edge->pair);
                edge=edge->next;

            }while(edge!=(*it)->edge);
            hashMap.clear();
            //now tempv vector has the information of the clusters around a face
            //pick the majority one
            std::sort(tempv.begin(),tempv.end());
            int size=tempv.size();
            int middle=size/2;
            int triple=size/3;

            if(tempv[0]==tempv[middle])
            {
                (*it)->clusterNo=tempv[middle];
            }else if(tempv[middle]==tempv[size-1])
            {
                (*it)->clusterNo=tempv[middle];
            }

        /*    //finding the majority cluster
            int previous=tempv[0];
            int currentColCount=1;
            int maxCol=tempv[0];
            int maxColCount=1;
            int currentCol=tempv[0];
            for(unsigned int l=1;l<tempv.size();l++)
            {
                if(tempv[l]==previous)
                {
                    currentColCount++;
                    currentCol=tempv[l];
                }else
                {
                    if(currentColCount>maxColCount)
                    {
                        //std::cout<<"Hhahhahah "<<std::endl;

                        maxColCount=currentColCount;
                        maxCol=previous;
                    }
                    currentColCount=1;
                    currentCol=tempv[l];
                }
                previous=tempv[l];

            }
            if(maxColCount>=middle)
            {
              //  std::cout<<"Hhahhahah "<<std::endl;
                (*it)->clusterNo=maxCol;
            }

        //    std::cout<<"triple "<<triple<<"Max count = "<<maxColCount<<std::endl;

*/
           tempv.clear();


        }

    }


}

void Viewer::show_results(igraph_t *g, igraph_vector_t *mod, igraph_matrix_t *merges) {
  long int i;
  igraph_vector_t membership;

  igraph_vector_init(&membership, 0);

  i=igraph_vector_which_max(mod);
 // std::cout<<"Modularity:"<<VECTOR(*mod)[i];

  igraph_community_to_membership(merges, igraph_vcount(g), i, &membership, 0);
//  std::cout<<"Membership: ";
  long int max=(long int)VECTOR(membership)[0];
  std::list<heFace*>::iterator it;
  it=heFaceList.begin();
  for (i=0; i<igraph_vector_size(&membership); i++) {
      (*it)->clusterNo=(long int)VECTOR(membership)[i];
      it++;
      long int temp=(long int)VECTOR(membership)[i];
      if(temp>max)
      {
          max=temp;
      }

  //  printf("%li ", (long int)VECTOR(membership)[i]);
  }

 // printf("\n");

  std::cout<<"Membership size "<<igraph_vector_size(&membership)<<std::endl;
  std::cout<<"Number of clusters = "<<max+1<<std::endl;
  this->numberCommunities=max+1;

  igraph_vector_destroy(&membership);
}


void Viewer::testingHalfEdge()
{
    std::list<heFace*>::iterator it;
    int i=0;
    for(it=heFaceList.begin();it!=heFaceList.end();it++)
    {
        i=0;
        heEdge* edge = (*it)->edge;
        do {

            int h=0;
            heEdge* edgel=edge->vert->edge;
            do
            {
                edgel=edgel->pair->next;
                h++;
                if(h>1000)
                {
                    std::cout<<"infinite loop "<<std::endl;
                    exit(0);
                }
            }while(edgel!=edge->vert->edge);


             // do something with edge, edge->pair or edge->face
            edge = edge->next;
            i++;
        } while (edge != (*it)->edge);
        assert(i=3);

    }

}

void Viewer::traversingFaces(heVertex* vert)
{

    heEdge* edge=vert->edge;

    do {

              // do something with edge, edge->pair or edge->face
              edge = edge->pair->next;


       } while (edge != vert->edge);


}
//calculating plane equation for each faces --i.e essentially calculating a,b,c,d variable values
void Viewer::calculatingPlaneEq()
{
    //traverse all the faces
    for(unsigned int i=0;i<heFaceArr.size();i++)
    {
        //Now traverse all the points on the face
        heEdge* edge=heFaceArr[i]->edge;
        Point3 arr[3];
        int j=0;
        do{
            //do something with the edge

            arr[j].x=edge->vert->x;
            arr[j].y=edge->vert->y;
            arr[j].z=edge->vert->z;
            j++;
            edge=edge->next;

        }while(edge!=heFaceArr[i]->edge);
        assert(j==3);
        heFaceArr[i]->varr[0]=arr[0].y*(arr[1].z-arr[2].z)+arr[1].y*(arr[2].z-arr[0].z)+arr[2].y*(arr[0].z-arr[1].z);
        heFaceArr[i]->varr[1]=arr[0].z*(arr[1].x-arr[2].x)+arr[1].z*(arr[2].x-arr[0].x)+arr[2].z*(arr[0].x-arr[1].x);
        heFaceArr[i]->varr[2]=arr[0].x*(arr[1].y-arr[2].y)+arr[1].x*(arr[2].y-arr[0].y)+arr[2].x*(arr[0].y-arr[1].y);
        heFaceArr[i]->varr[3]=arr[0].x*(arr[1].y*arr[2].z-arr[2].y*arr[1].z)+arr[1].x*(arr[2].y*arr[0].z-arr[0].y*arr[2].z)+arr[2].x*(arr[0].y*arr[1].z-arr[1].y*arr[0].z);
        float sum=sqrt(pow(heFaceArr[i]->varr[0],2)+pow(heFaceArr[i]->varr[1],2)+pow(heFaceArr[i]->varr[2],2));
        heFaceArr[i]->varr[0]=heFaceArr[i]->varr[0]/sum;
        heFaceArr[i]->varr[1]=heFaceArr[i]->varr[1]/sum;
        heFaceArr[i]->varr[2]=heFaceArr[i]->varr[2]/sum;
        heFaceArr[i]->varr[3]=-1.0*(heFaceArr[i]->varr[3]/sum);



    }
}

void Viewer::initiatingQuadrics()
{
    for(unsigned int k=0;k<heVertArr.size();k++)
    {


        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                heVertArr[k]->quadrics[i][j]=0.0;
            }
        }

        heEdge* edge=heVertArr[k]->edge;

        do {

                  // do something with edge, edge->pair or edge->face

                  for(int i=0;i<4;i++)
                  {
                      for(int j=0;j<4;j++)
                      {
                          heVertArr[k]->quadrics[i][j]=heVertArr[k]->quadrics[i][j]+edge->face->varr[i]*edge->face->varr[j];
                      }
                  }

                  edge = edge->pair->next;


           } while (edge != heVertArr[k]->edge);




    }
}

float Viewer::calculatingError(heVertex* v1,heVertex* v2)
{
    float p1[4];
    p1[0]=v1->x;
    p1[1]=v1->y;
    p1[2]=v1->z;
    p1[3]=1.0;
  /* p2[0]=v2->x;
    p2[1]=v2->y;
    p2[2]=v2->z;
    p2[3]=1.0;
*/
    heVertex v3;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            v3.quadrics[i][j]=v1->quadrics[i][j]+v2->quadrics[i][j];
        }
    }

    float temp1=errorMatrix(p1,&v3);
  //  float temp2=errorMatrix(p2,&v3);
   // float temp3=errorMatrix(p3,&v3);

    return temp1;
    /*if(temp1>temp2)
        return temp2;
    else
        return temp1;*/
   /* if(temp1>temp2)
    {
        if(temp1>temp3)
        {
            return temp1;
        }else
        {
            return temp3;
        }
    }else if(temp2>temp3)
    {
        return temp2;
    }else
    {
        return temp3;
    }*/

}

float Viewer::errorMatrix(float arr[],heVertex *v)
{
    float temp[4];
    for(int i=0;i<4;i++)
    {
            temp[i]=0.0;
            for(int k=0;k<4;k++)
            {
                temp[i]=temp[i]+arr[k]*v->quadrics[k][i];
            }

    }
    float res=0.0;
    for(int i=0;i<4;i++)
    {
        res=res+temp[i]*arr[i];
    }

    return res;
}


void Viewer::simplifyMesh(int k,unsigned int nTriangles)
{
    std::vector<edgeError*> myVec;

    srand(time(NULL));

    while(heFaceList.size()>nTriangles)
    {


        heEdge* batman;
        unsigned int numberTrials=0;
        for(int i=0;i<k;)
        {

            numberTrials++;
             int randFace=(rand()%heFaceList.size()+1);//selecting a random triangle
            int randEdge=rand()%3+1;//selectin a random edge
            std::list<heFace*>::iterator it1;
            int j=1;
            //getting to the face
            for(it1=heFaceList.begin();it1!=heFaceList.end();it1++)
            {
                if(j==randFace)
                    break;
                j++;
            }
            heEdge* edge = (*it1)->edge;
            j=1;
            //getting the edge to be collapsed
            do {
                 // do something with edge, edge->pair or edge->face

                 if(j==randEdge)
                 {
                     break;
                 }

                 edge = edge->next;

                 j++;

            } while (edge != (*it1)->edge);

            batman=edge;
            //detecting fins
            vector<int> va;
            vector<int> vb;
            vector<int> vc;
            heEdge* superman=edge;
            do{
                va.push_back(superman->vert->no);
                superman=superman->pair->next;
            }while(superman!=edge);

            superman=edge->pair;
            do{
                vb.push_back(superman->vert->no);
                superman=superman->pair->next;
            }while(superman!=edge->pair);

            sort(va.begin(),va.end());
            sort(vb.begin(),vb.end());
            //vector<int>::iterator it;
            std::set_intersection(va.begin(),va.end(),vb.begin(),vb.end(),std::inserter(vc,vc.begin()));
            if(vc.size()>=3)
            {

                if(numberTrials>heFaceList.size())
                {

                    QMessageBox msgBox;
                    msgBox.setText("Can't avoid fin formations! Please try again!");
                    msgBox.exec();
                    std::cout<<"Can't avoid fin formations "<<std::endl;
                    return;
                }
                continue;
            }

            edgeError* temp=new edgeError;
            temp->p2.x=edge->vert->x;
            temp->p2.y=edge->vert->y;
            temp->p2.z=edge->vert->z;

            temp->p1.x=edge->pair->vert->x;
            temp->p1.y=edge->pair->vert->y;
            temp->p1.z=edge->pair->vert->z;
            temp->edge=edge;
            temp->error=0.0;
            temp->faceNo=randFace;

            //search in the vector p2->p1 edge
            unsigned int l;
            for(l=0;l<myVec.size();l++)
            {
                if(temp->p2.x==myVec[l]->p1.x && temp->p2.y==myVec[l]->p1.y && temp->p2.z==myVec[l]->p1.z && temp->p1.x==myVec[l]->p2.x && temp->p1.y==myVec[l]->p2.y && temp->p1.z==myVec[l]->p2.z)
                {
                    break;
                }

            }

            if(l!=myVec.size())//it means it exists
            {
                continue;
            }else
            {
                i++;
                myVec.push_back(temp);
            }
            i++;
            myVec.push_back(temp);

        }
        //now find the edge collapse which produces the least error

        float min=calculatingError(myVec[0]->edge->vert,myVec[0]->edge->pair->vert);
        int z=0;
        for(unsigned int i=0;i<myVec.size();i++)
        {
            float temp;
         /*   //edges points to a vertex...so the another vertex will collapse into that
            float temp1=calculatingError(myVec[i]->edge->vert,myVec[i]->edge->pair->vert);
            float temp2=calculatingError(myVec[i]->edge->pair->vert,myVec[i]->edge->vert);

            if(temp1<0)
            {
                temp1=temp1*(-1.0);
                 temp1=temp1*(-1.0);
            }
            if(temp2<0)
            {
                temp2=temp2*(-1.0);
                temp2=temp2*(-1.0);
            }
            if(temp2<temp1)
            {
                myVec[i]->edge=myVec[i]->edge->pair;
                temp=temp2;
            }else
            {
                temp=temp1;
            }
            //std::cout<<"temp = "<<temp<<std::endl;*/
             temp=calculatingError(myVec[i]->edge->vert,myVec[i]->edge->pair->vert);

            if(temp<min)
            {
                min=temp;
                z=i;
            }

        }



             halfEdgeCollapse(myVec[z]->edge);
        myVec.clear();


    }

}

void Viewer::updatingPlaneEq(heVertex* vert)
{
    heEdge* edge=vert->edge;
    do
    {

        heEdge* edge2=edge;
        Point3 arr[3];
        int j=0;
        do{


            arr[j].x=edge2->vert->x;
            arr[j].y=edge2->vert->y;
            arr[j].z=edge2->vert->z;
            j++;

            edge2=edge2->next;
        }while(edge2!=edge);

        edge->face->varr[0]=arr[0].y*(arr[1].z-arr[2].z)+arr[1].y*(arr[2].z-arr[0].z)+arr[2].y*(arr[0].z-arr[1].z);
        edge->face->varr[1]=arr[0].z*(arr[1].x-arr[2].x)+arr[1].z*(arr[2].x-arr[0].x)+arr[2].z*(arr[0].x-arr[1].x);
        edge->face->varr[2]=arr[0].x*(arr[1].y-arr[2].y)+arr[1].x*(arr[2].y-arr[0].y)+arr[2].x*(arr[0].y-arr[1].y);
        edge->face->varr[3]=arr[0].x*(arr[1].y*arr[2].z-arr[2].y*arr[1].z)+arr[1].x*(arr[2].y*arr[0].z-arr[0].y*arr[2].z)+arr[2].x*(arr[0].y*arr[1].z-arr[1].y*arr[0].z);
        float sum=sqrt(pow(edge->face->varr[0],2)+pow(edge->face->varr[1],2)+pow(edge->face->varr[2],2));
        edge->face->varr[0]=edge->face->varr[0]/sum;
        edge->face->varr[1]=edge->face->varr[1]/sum;
        edge->face->varr[2]=edge->face->varr[2]/sum;
        edge->face->varr[3]=-1.0*(edge->face->varr[3]/sum);


        edge=edge->pair->next;
    }while(edge!=vert->edge);
}

void Viewer::updatingStuff(heVertex* vert)
{


    assert(vert->edge->vert->edge!=NULL);


    for(int i=0;i<3;i++)
    {
        vert->normals[i]=0.0;
        assert(vert->edge->vert->edge!=NULL);

    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            vert->quadrics[i][j]=0.0;
        }
    }

    assert(vert->edge->vert->edge!=NULL);
    heEdge* edge=vert->edge;
    float avgOutside=0.0;

    do{

        avgOutside++;
        for(int i=0;i<3;i++)
        {
            vert->normals[i]=vert->normals[i]+edge->face->normals[i];
            edge->vert->normals[i]=0.0;
        }
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {

                vert->quadrics[i][j]=vert->quadrics[i][j]+edge->face->varr[i]*edge->face->varr[j];
                edge->vert->quadrics[i][j]=0.0;
            }
        }

        heVertex* neighborVert=edge->vert;

        float avgInside=0.0;
        heEdge* edge2=neighborVert->edge;
        do{

            avgInside++;
            for(int j=0;j<3;j++)
            {
                neighborVert->normals[j]=neighborVert->normals[j]+edge2->face->normals[j];
            }

            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    neighborVert->quadrics[i][j]=neighborVert->quadrics[i][j]+edge2->face->varr[i]*edge2->face->varr[j];
                }
            }

            edge2=edge2->pair->next;


        }while(edge2!=neighborVert->edge);

        for(int i=0;i<3;i++)
        {
            edge->vert->normals[i]=edge->vert->normals[i]/avgInside;

        }



        edge=edge->pair->next;
    }while(edge!=vert->edge);
    for(int i=0;i<3;i++)
    {
        vert->normals[i]=vert->normals[i]/avgOutside;

    }


}

void Viewer::halfEdgeCollapse(heEdge * remEdge)
{

    heVertex* spiderman=remEdge->vert;

    heEdge* edge11 = remEdge;
    heEdge* edge22 = remEdge->pair;
    heEdge* termEdge1=remEdge;
    heEdge* termEdge2=remEdge->pair;

    //testingHalfEdge();

    remEdge->vert->edge=remEdge->next->pair->next;
    remEdge->next->vert->edge=remEdge->next->pair;
    remEdge->pair->next->vert->edge=remEdge->pair->next->pair;



    //preparing for the later things
    heVertex* vertee=remEdge->vert;

    heEdge* edge1=remEdge->next->next->pair;
    heEdge* edge2=remEdge->next->pair;
    heEdge* edge3=remEdge->pair->next->next->pair;
    heEdge* edge4=remEdge->pair->next->pair;
    assert(edge1!=edge1->pair);
    assert(edge2!=edge2->pair);
    assert(edge3!=edge3->pair);
    assert(edge4!=edge4->pair);

    //update the degrees
    remEdge->vert->degree=remEdge->vert->degree+remEdge->pair->vert->degree-4;
    remEdge->next->vert->degree=remEdge->next->vert->degree-1;
    remEdge->pair->next->vert->degree=remEdge->next->vert->degree-1;


    heVertex* removedVert=remEdge->pair->vert;//store the address to remove it later- very important
    heEdge* tempEdge = remEdge;
    int h=1;
    do {
         // do something with edge, edge->pair or edge->face
        assert(tempEdge->pair->vert->no!=-12);
        tempEdge->pair->vert=remEdge->vert;
        tempEdge = tempEdge->pair->next;
        h++;
        if(h>100000)
        {
            std::cout<<"infinite loooooop :: deletion in progress testing "<<std::endl;
            std::cout<<"FaceSize "<<heFaceList.size()<<std::endl;
            return;

        }
    }while(tempEdge!=remEdge);
    edge1->pair=edge2;
    edge2->pair=edge1;
    edge3->pair=edge4;
    edge4->pair=edge3;

    assert(edge1->vert==edge1->pair->pair->vert);
    assert(edge2->vert==edge2->pair->pair->vert);
    assert(edge3->vert==edge3->pair->pair->vert);
    assert(edge4->vert==edge4->pair->pair->vert);


    //deleting faces from face list
    heFaceList.remove(remEdge->face);
    heFaceList.remove(remEdge->pair->face);


    //delete the vertex
  //  std::cout<<"Deleted Vert "<<removedVert->no<<std::endl;
    delete(removedVert);

    int d=0;
    do {
        d++;

       // do something with edge
       heEdge* temp=edge11;
       edge11 = edge11->next;

     // temp->vert->no=-12;
       if(edge1==temp)
       {

           std::cout<<"d === "<<d<<std::endl;
       }
       if(edge2==temp)
       {
            std::cout<<"d === "<<d<<std::endl;
       }
       if(edge3==temp)
       {
            std::cout<<"d === "<<d<<std::endl;
       }
       if(edge4==temp)
       {
             std::cout<<"d === "<<d<<std::endl;
       }
       assert(edge1!=temp);
       assert(edge2!=temp);
       assert(edge3!=temp);
       assert(edge4!=temp);
       delete(temp);

    } while (edge11 != termEdge1);
    assert(d==3);

    d=0;
    do {

               d++;
       // do something with edge
       heEdge* temp=edge22;
       edge22 = edge22->next;
       if(edge1==temp)
       {
            std::cout<<"d === "<<d<<std::endl;
       }
       if(edge2==temp)
       {
           std::cout<<"d === "<<d<<std::endl;

       }
       if(edge3==temp)
       {
           std::cout<<"d === "<<d<<std::endl;

       }
       if(edge4==temp)
       {
           std::cout<<"d === "<<d<<std::endl;

       }





      // temp->vert->no=-12;
       assert(edge1!=temp);
       assert(edge2!=temp);
       assert(edge3!=temp);
       assert(edge4!=temp);
       delete(temp);
       //delete(temp);


    } while (edge22 != termEdge2);
    assert(d==3);

   heEdge* ledge=vertee->edge;
   //std::cout<<"faces traversed ";
    h=0;
   do
   {
      // std::cout<<ledge->face->no<<" ";
       int q=0;
       heEdge* edge22=ledge;
       do{
           edge22=edge22->next;
           q++;
       }while(edge22!=ledge);

     //  std::cout<<"Value of q = "<<q;
       assert(q==3);




       ledge=ledge->pair->next;
       h++;
       if(h>10000)
       {
           std::cout<<"Infinite loop :- after deletion testing "<<std::endl;
           std::cout<<"FaceSize "<<heFaceList.size()<<std::endl;
           return;
       }

   }while(ledge!=vertee->edge);
   //std::cout<<std::endl;

   //updating the face normals
   ledge=vertee->edge;
    h=0;
   do
   {
       assert(ledge->vert->no!=-12);
       assert(ledge->pair->vert->no!=-12);

       heEdge* temEdge=ledge;
       int n=0;
       Point3 arr[3];
       do{
           arr[n].x=temEdge->vert->x;
           arr[n].y=temEdge->vert->y;
           arr[n].z=temEdge->vert->z;
           temEdge=temEdge->next;
           n++;
       }while(temEdge!=ledge);


       assert(n==3);
       Point3 U,V,normal;
       U=subtractPoints(arr[0],arr[1]);
       V=subtractPoints(arr[0],arr[2]);
       normal.x=(U.y*V.z)-(U.z*V.y);
       normal.y=(U.z*V.x)-(U.x*V.z);
       normal.z=(U.x*V.y)-(U.y*V.x);
       float temp1=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
       normal.x=normal.x/temp1;
       normal.y=normal.y/temp1;
       normal.z=normal.z/temp1;
       ledge->face->normals[0]=normal.x;
       ledge->face->normals[1]=normal.y;
       ledge->face->normals[2]=normal.z;
       ledge=ledge->pair->next;

       h++;
       if(h>100000)
       {
           std::cout<<"Infinite loop :- after deletion testing "<<std::endl;
           std::cout<<"FaceSize "<<heFaceList.size()<<std::endl;
           return;
       }

   }while(ledge!=vertee->edge);

   assert(spiderman->edge->vert->edge!=NULL);
   updatingPlaneEq(spiderman);
   updatingStuff(spiderman);


}

unsigned int Viewer::getFaceListSize()
{
    return heFaceList.size();
}

void Viewer::startSavingArr()
{
   faceArray.clear();
   vertexArray.clear();

   std::list<heFace*>::iterator it;

   for(it=heFaceList.begin();it!=heFaceList.end();it++)
   {
       heEdge* edge=(*it)->edge;
       Face3* face=new Face3;
           int flag=0;
           unsigned int i;
           for(i=0;i<vertexArray.size();i++)
           {
               if(vertexArray[i].x==edge->vert->x&&vertexArray[i].y==edge->vert->y&&vertexArray[i].z==edge->vert->z)
               {
                   flag=1;
                   break;
               }
           }
           if(flag==1)
           {
               face->p1=i;
               assert(face->p1>=0);

           }else
           {
               Point3* point=new Point3;
               point->x=edge->vert->x;
               point->y=edge->vert->y;
               point->z=edge->vert->z;
               vertexArray.push_back(*point);

               face->p1=vertexArray.size()-1;
               assert(face->p1>=0);

           }
           edge=edge->next;


           flag=0;
           for( i=0;i<vertexArray.size();i++)
           {
               if(vertexArray[i].x==edge->vert->x&&vertexArray[i].y==edge->vert->y&&vertexArray[i].z==edge->vert->z)
               {
                   flag=1;
                   break;
               }
           }
           if(flag==1)
           {
               face->p2=i;
               assert(face->p2>=0);


           }else
           {
               Point3* point=new Point3;
               point->x=edge->vert->x;
               point->y=edge->vert->y;
               point->z=edge->vert->z;
               vertexArray.push_back(*point);
               face->p2=vertexArray.size()-1;
               assert(face->p2>=0);


           }
           edge=edge->next;

           flag=0;
           for( i=0;i<vertexArray.size();i++)
           {
               if(vertexArray[i].x==edge->vert->x&&vertexArray[i].y==edge->vert->y&&vertexArray[i].z==edge->vert->z)
               {
                   flag=1;
                   break;
               }
           }
           if(flag==1)
           {
               face->p3=i;
               assert(face->p3>=0);

           }else
           {
               Point3* point=new Point3;
               point->x=edge->vert->x;
               point->y=edge->vert->y;
               point->z=edge->vert->z;
               vertexArray.push_back(*point);
               face->p3=vertexArray.size()-1;
               assert(face->p3>=0);

           }
           assert(face->p1>=0);
           assert(face->p2>=0);
           assert(face->p3>=0);


           faceArray.push_back(*face);
           assert((*it)->edge==edge->next);
   }



}
Point3 Viewer::getPoint(int i)
{
    return vertexArray[i];
}

Face3 Viewer::getFace(int i)
{
    return faceArray[i];
}

int Viewer::getVertexArrSize()
{
    return vertexArray.size();
}

int Viewer::getFaceArrSize()
{
    return faceArray.size();
}

void Viewer::copyObject(Viewer *cop)
{

    std::list<heFace*>::iterator it;
    for(it=cop->heFaceList.begin();it!=cop->heFaceList.end();it++)
    {
        heFace* temp=new heFace;
        temp->edge=(*it)->edge;
        temp->no=(*it)->no;
        temp->updateFlag=(*it)->updateFlag;
        for(int i=0;i<3;i++)
        {
            temp->normals[i]=(*it)->normals[i];
        }
        for(int i=0;i<4;i++)
        {
            temp->varr[i]=(*it)->varr[i];
        }
        heFaceList.push_back(temp);

    }

}

void Viewer::addingSegments(std::vector<int> tempVec)
{
    std::list<heFace* >::iterator it;
    int max=tempVec[0];
    int i=0;
    for(it=heFaceList.begin();it!=heFaceList.end();it++)
    {
        if(tempVec[i]>max)
        {
            max=tempVec[i];
        }
        (*it)->clusterNo=tempVec[i];
        i++;
    }
    this->numberCommunities=max+1;
    this->colorList.clear();

    srand(time(NULL));
    //filling the color
    for(unsigned int i=0;i<this->numberCommunities;i++)
    {
          Point3 color;
          color.x=(float)(rand()%this->numberCommunities)/(float)this->numberCommunities;
          color.y=(float)(rand()%this->numberCommunities)/(float)this->numberCommunities;
          color.z=(float)(rand()%this->numberCommunities)/(float)this->numberCommunities;
          this->colorList.push_back(color);

    }


}
