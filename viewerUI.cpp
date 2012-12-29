#include"viewerUI.h"
//#include"simpleViewer.h"
#include<iostream>
using namespace std;

viewerUI::viewerUI()
{
            openAction = new QAction(tr("&Open"), this);
            saveAction = new QAction(tr("&Save"), this);
            exitAction = new QAction(tr("E&xit"), this);
            flatShadedAction = new QAction(tr("&FlatShaded"),this);
            smoothShadedAction = new QAction(tr("&SmoothShaded"),this);
            wireFrameAction = new QAction(tr("&WireFrame"),this);
            catmullAction = new QAction(tr("&Catmull"),this);
            butterflyAction = new QAction(tr("&Butterfly"),this);
            wireShadeAction= new QAction(tr("Wi&reFrameShading"),this);
            simplifyAction=new QAction(tr("S&implification"),this);
            segmentAction=new QAction(tr("Se&gmentation"),this);
            loadSegmentsAction=new QAction(tr("&Load Segments"),this);
            refreshColorsAction=new QAction(tr("Refresh &Colors"),this);
            //okButtonAction=new QAction(this);

          //  connect(okButtonAction, SIGNAL(QPushButton::clicked()),this,SLOT(buttonn()));

            connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
            connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
            connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));
            connect(flatShadedAction,SIGNAL(triggered()),this,SLOT(flatShadeOn()));
            connect(smoothShadedAction,SIGNAL(triggered()),this,SLOT(smoothShadeOn()));
            connect(wireFrameAction,SIGNAL(triggered()),this,SLOT(wireFrameOn()));
            connect(catmullAction,SIGNAL(triggered()),this,SLOT(dummy()));
            connect(butterflyAction,SIGNAL(triggered()),this,SLOT(dummy()));
            connect(wireShadeAction,SIGNAL(triggered()),this,SLOT(wireShadeOn()));
            connect(simplifyAction,SIGNAL(triggered()),this,SLOT(simplification()));
            connect(segmentAction,SIGNAL(triggered()),this,SLOT(segmentation()));
            connect(loadSegmentsAction,SIGNAL(triggered()),this,SLOT(loadSegments()));
            connect(refreshColorsAction,SIGNAL(triggered()),this,SLOT(refreshColors()));


            fileMenu = menuBar()->addMenu(tr("&File"));
            fileMenu->addAction(openAction);
            fileMenu->addAction(saveAction);
            fileMenu->addSeparator();
            fileMenu->addAction(exitAction);

            operationsMenu = menuBar()->addMenu(tr("&Operations"));
            operationsMenu->addAction(flatShadedAction);
            operationsMenu->addAction(smoothShadedAction);

            //operationsMenu->addSeparator();
            operationsMenu->addAction(wireFrameAction);
            operationsMenu->addAction(wireShadeAction);
            operationsMenu->addAction(simplifyAction);
            operationsMenu->addAction(segmentAction);
            operationsMenu->addAction(loadSegmentsAction);
            operationsMenu->addAction(refreshColorsAction);

            subdivisionMenu=operationsMenu->addMenu(tr("Sub&division"));
            subdivisionMenu->addAction(catmullAction);
            subdivisionMenu->addAction(butterflyAction);


           // textEdit = new QTextEdit;
           // setCentralWidget(textEdit);
           viewer = new Viewer;
           setCentralWidget(viewer);
           setWindowTitle(tr("mesh"));
        }

void viewerUI::refreshColors()
{
    viewer->refreshColorsSeg();
}

void viewerUI::loadSegments()
{
//    std::cout<<"Load segments "<<std::endl;

    cout<<"Open Segment File"<<endl;

    std::vector<int> tempVec;

     QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
     tr("seg files (*.seg)"));


    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
       QTextStream in(&file);
        while (!in.atEnd()) {
            QStringList list;
            QString line = in.readLine();
            list=line.split(" ");
            //std::cout<<list.size()<<std::endl;
            tempVec.push_back(list[0].toInt());
        }
        //assert(tempVec.size()==viewer->getFaceListSize());
        if(tempVec.size()!=viewer->getFaceListSize())
        {
            std::cout<<"Match not found "<<std::endl;
            return;
        }
        std::cout<<"hahhaha "<<std::endl;
        viewer->addingSegments(tempVec);



    }





}

      void viewerUI::open()
      {
           cout<<"Open"<<endl;
//            QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
  //          tr("smf files (*.smf)"));

            QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
            tr("off files (*.off)"));


           if (fileName != "") {
               QFile file(fileName);
               if (!file.open(QIODevice::ReadOnly)) {
                   QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                   return;
               }
               viewer->clearAll();

              QTextStream in(&file);

              /***********************************/
              QString line1 = in.readLine();
              QString line2 = in.readLine();
              QStringList list2;
              list2=line2.split(" ");
              int noVertices=list2[0].toInt();
              int noTriangles=list2[1].toInt();
              int i=1;
              int j=1;
               while (!in.atEnd()) {
                   QStringList list;
                   QString line = in.readLine();
                   list=line.split(" ");
                 //  std::cout<<list.size()<<std::endl;

                   if(i<=noVertices)
                   {
                       Point3 point;
                       point.x=list[0].toFloat();
                       point.y=list[1].toFloat();
                       point.z=list[2].toFloat();

                       viewer->insertPoint(point);
                       i++;
                   }else if(j<=noTriangles)
                   {
                       assert(list[0].toInt()==3);
                       Face3 face;
                       face.p1=list[1].toInt()+1;
                       face.p2=list[2].toInt()+1;
                       face.p3=list[3].toInt()+1;
                       viewer->insertFace(face);

                       j++;
                   }


                   /*
                   if(list.size()>=4 && list[0][0]!='#')
                   {
                       //qDebug()<<list;

                   if(list.contains(QString('v')))
                   {
                       Point3 point;
                       point.x=list[1].toFloat();
                       point.y=list[2].toFloat();
                       point.z=list[3].toFloat();

                       viewer->insertPoint(point);
                   }else{
                       Face3 face;
                       face.p1=list[1].toInt();
                       face.p2=list[2].toInt();
                       face.p3=list[3].toInt();

                       viewer->insertFace(face);
                    }
                   }*/

               }

               viewer->calculateMedian();
               viewer->calculateFaceNormal();
               viewer->calculateVertexNormal();
               viewer->createHalfEdgeStructure();
               viewer->makeDualGraph();
               viewer->calculateCentroids();
               viewer->calculateAvgWtheta();
             //  viewer->testingHalfEdge();
               viewer->calculatingPlaneEq();//for quadrics
               viewer->initiatingQuadrics();

           }
           //viewer->printAll();


      }


    void viewerUI::save()
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
        tr("smf files (*.smf)"));

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                return;
            } else {

                viewer->startSavingArr();

                QTextStream out(&file);
                out << "# " << viewer->getVertexArrSize() << " " << viewer->getFaceArrSize() << "\n";

                for(int i=0;i<viewer->getVertexArrSize();i++)
                {
                    Point3 temp=viewer->getPoint(i);
                    out << "v " << temp.x << " " << temp.y << " " << temp.z << "\n";
                }
                for(int i=0;i<viewer->getFaceArrSize();i++)
                {
                    Face3 temp2=viewer->getFace(i);
                    out << "f " << temp2.p1+1 << " " << temp2.p2+1<< " " << temp2.p3+1 << "\n";
                }
                 //    out << "The magic number is: " << 49 << "\n";
                file.close();

            }
        }
    }


        void viewerUI::quit()
          {
              QMessageBox messageBox;
              messageBox.setWindowTitle(tr("mesh"));
              messageBox.setText(tr("Do you really want to quit?"));
              messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
              messageBox.setDefaultButton(QMessageBox::No);
              if (messageBox.exec() == QMessageBox::Yes)
              {
                  this->close();
                  //qApp->quit();
              }

          }

        void viewerUI::dummy()
        {
              cout<<"Doesn't work!"<<endl;
        }
        void viewerUI::wireFrameOn()
        {
            viewer->setWireFlag(1);
            viewer->setWireShadeFlag(0);

        }
        void viewerUI::flatShadeOn()
        {
            viewer->setWireFlag(0);
            viewer->setWireShadeFlag(0);
            viewer->setShadingFlag(0);
        }
        void viewerUI::smoothShadeOn()
        {
            viewer->setWireFlag(0);
            viewer->setWireShadeFlag(0);
            viewer->setShadingFlag(1);
        }


        void viewerUI::wireShadeOn()
        {
            viewer->setWireShadeFlag(1);
            viewer->setWireFlag(0);
        }






        void viewerUI::simplification()
        {
            createPopup();
            popupWidget->show();
        }

        void viewerUI::createPopup2()
        {

            integerLabel2 = new QLabel(tr("Enter the threshold for adding edges"));
            integerLabel1 = new QLabel(tr("Enter the threshold for removing edges"));
            integerLabel3 = new QLabel(tr("Enter the number of iterations for fixing segments"));
            integerSpinBox3 = new QDoubleSpinBox;
            integerSpinBox4 = new QDoubleSpinBox;
            integerSpinBox5 = new QSpinBox;
            okButton = new QPushButton;
            spinBoxLayout = new QVBoxLayout;
            popupWidget = new QWidget;

            integerSpinBox3->setRange(-1.0, 1.05);
            integerSpinBox3->setSingleStep(0.05);
            integerSpinBox3->setValue(-1.0);

            integerSpinBox4->setRange(0.0,1.05);
            integerSpinBox4->setSingleStep(0.05);
            integerSpinBox4->setValue(0.2);

            integerSpinBox5->setRange(0,100);
            integerSpinBox5->setSingleStep(1);
            integerSpinBox5->setValue(1);

            okButton->setText("Start");
            connect(okButton, SIGNAL(clicked()),this, SLOT(segmentButton()));
             //okButton->addAction(okButtonAction);


            spinBoxLayout->addWidget(integerLabel2);
            spinBoxLayout->addWidget(integerSpinBox3);
            spinBoxLayout->addWidget(integerLabel1);
            spinBoxLayout->addWidget(integerSpinBox4);
            spinBoxLayout->addWidget(integerLabel3);
            spinBoxLayout->addWidget(integerSpinBox5);
            spinBoxLayout->addWidget(okButton);


            popupWidget->setWindowFlags(Qt::Popup);
            popupWidget->setWindowFlags(Qt::Dialog);
            popupWidget->setWindowFlags(Qt::Window);
            popupWidget->setWindowTitle("Inputs for Segmentation Algorithm");
            popupWidget->setLayout(spinBoxLayout);
            popupWidget->move(300,300);



        }

        void viewerUI::createPopup()
        {
            unsigned int faceSize=viewer->getFaceListSize();
            integerLabel1 = new QLabel(tr("Enter number of triangles desired(between "
                  "%1 and %2)").arg(3).arg(faceSize));
            integerLabel2 = new QLabel(tr("Enter the value for K"));
            integerSpinBox1 = new QSpinBox;
            integerSpinBox2 = new QSpinBox;
            okButton = new QPushButton;
            spinBoxLayout = new QVBoxLayout;
            popupWidget = new QWidget;



            integerSpinBox1->setRange(3, faceSize);
            integerSpinBox1->setSingleStep(5);
            integerSpinBox1->setValue(faceSize-1);


            integerSpinBox2->setRange(1, faceSize);
            integerSpinBox2->setSingleStep(1);
            integerSpinBox2->setValue(10);

            //integerSpinBox1->setWindowTitle("Number of Triangles");

            okButton->setText("Decimate");
            connect(okButton, SIGNAL(clicked()),this, SLOT(buttonn()));
             //okButton->addAction(okButtonAction);


            spinBoxLayout->addWidget(integerLabel2);
            spinBoxLayout->addWidget(integerSpinBox2);
            spinBoxLayout->addWidget(integerLabel1);
            spinBoxLayout->addWidget(integerSpinBox1);
            spinBoxLayout->addWidget(okButton);


            popupWidget->setWindowFlags(Qt::Popup);
            popupWidget->setWindowFlags(Qt::Dialog);
            popupWidget->setWindowFlags(Qt::Window);
            popupWidget->setWindowTitle("Inputs for Simplification Algorithm");
            popupWidget->setLayout(spinBoxLayout);
            popupWidget->move(300,300);

        }

        void viewerUI::buttonn()
        {
            std::cout<<"Number of triangles selected "<<integerSpinBox1->value()<<std::endl;
            int no=integerSpinBox1->value();
            std::cout<<"Value of K "<<integerSpinBox2->value()<<std::endl;
            int k=integerSpinBox2->value();
            popupWidget->close();
            viewer->simplifyMesh(k,no);

        }

        void viewerUI::segmentButton()
        {
           /* std::cout<<"segment button is pressed "<<std::endl;
            int k=integerSpinBox2->value();
            for(int i=0;i<k;i++)
            {
                viewerUI *viewerUI2=new viewerUI;

                viewerUI2->show();
                viewerUI2->viewer->copyObject(this->viewer);
              //  viewerUI2->viewer->draw();

            }
         */
            float thresh1=integerSpinBox3->value();
            float thresh2=integerSpinBox4->value();
            float k=integerSpinBox5->value();
            popupWidget->close();
            if(thresh1!=-1.0)
            {
                viewer->addRemoveEdges(thresh1,thresh2);
            }
            viewer->fixingArtifacts(k);
        }

        void viewerUI::segmentation()
        {
         //   viewer->addRemoveEdges();



            //Building the dual graph(Adjancey list)
            //viewer->makeDualGraph();

            createPopup2();
            popupWidget->show();
        }
