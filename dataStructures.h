#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
//holds the definitins of various datastructures
struct HE_vert;
struct HE_edge;
struct HE_face;



typedef struct Point
{
    float x,y,z;
}Point3;

typedef struct intersectedNode
{
    struct Point pt;
    int node;
}intersectedNode;


typedef struct Face
{
    int p1,p2,p3;
}Face3;



typedef struct HE_vert
{

    int no;
    float x;
    float y;
    float z;

    float quadrics[4][4];

    float normals[3];

    struct HE_edge* edge;  // one of the half-edges emantating from the vertex
    int degree;
    int updatedFlag;
}heVertex;

typedef struct HE_edge
{

    HE_vert *vert;   // vertex at the end of the half-edge
    HE_edge* pair;   // oppositely oriented adjacent half-edge
    HE_face* face;   // face the half-edge borders
    HE_edge* next;   // next half-edge around the face

}heEdge;




typedef struct HE_face
{

    int no;
    HE_edge* edge;  // one of the half-edges bordering the face
    //float a,b,c,d; //for planes
    float varr[4];
    float normals[3];
    int updateFlag;
    long int clusterNo;
    float centroid[3];

}heFace;

typedef struct eError
{
    Point3 p1,p2;
    HE_edge* edge;
    float error;
    int faceNo;
}edgeError;

typedef struct dualEdge
{
    int node;
    float traversalCost;
    float cutCost;
    float wtheta;

}dualEdge;

typedef struct dualNode
{
    float avgWtheta;
};

#endif // DATASTRUCTURES_H
