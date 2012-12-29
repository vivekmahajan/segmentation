#ifndef VIEWERUI_H
#define VIEWERUI_H

#include"simpleViewer.h"
#include<QtGui>
#include<dataStructures.h>

class viewerUI : public QMainWindow
{
    Q_OBJECT

public:
    Viewer *viewer;

    viewerUI();
    void createPopup();
    void createPopup2();


private slots:
    void open();
    void save();
    void quit();
    void dummy();
    void wireFrameOn();
    void flatShadeOn();
    void smoothShadeOn();
    void wireShadeOn();
    void simplification();
    void segmentation();
    void loadSegments();
    void refreshColors();

    void buttonn();
    void segmentButton();
  //  void deletePopup();


private:
   // QTextEdit *textEdit;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *flatShadedAction;
    QAction *smoothShadedAction;
    QAction *wireFrameAction;
    QAction *catmullAction;
    QAction *butterflyAction;
    QAction *wireShadeAction;
    QAction *simplifyAction;

    QAction *refreshColorsAction;
    QAction *segmentAction;
    //QAction *okButtonAction;
    QAction *loadSegmentsAction;

    QMenu *fileMenu;
    QMenu *subdivisionMenu;
    QMenu *operationsMenu;

    QLabel *integerLabel1;
    QLabel *integerLabel2;
    QLabel *integerLabel3;
    QSpinBox *integerSpinBox1;
    QSpinBox *integerSpinBox2;
    QDoubleSpinBox *integerSpinBox3;
    QDoubleSpinBox *integerSpinBox4;
    QSpinBox *integerSpinBox5;
    QPushButton * okButton;
    QVBoxLayout *spinBoxLayout;
    QWidget* popupWidget;

};







#endif // VIEWERUI_H
