

#include"viewerUI.h"
#include <qapplication.h>

int main(int argc, char** argv)
{
  // Read command lines arguments.
  QApplication application(argc,argv);


  viewerUI *viewerUI2=new viewerUI;



  viewerUI2->show();



  // Run main loop.
  return application.exec();
}
