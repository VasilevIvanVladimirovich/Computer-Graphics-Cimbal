#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
     resize(1280,800);

     layout_main = new QVBoxLayout;
     layout_menu = new QHBoxLayout;
     layout_graph = new QHBoxLayout;

     btnCreateCircle = new QPushButton("Create Circle");
     connect(btnCreateCircle, SIGNAL(clicked()), this, SLOT(on_btnCreateCircle_clicked()));
     layout_menu->addWidget(btnCreateCircle);

     btnMoveCircle = new QPushButton("Move Circle");
     connect(btnMoveCircle, SIGNAL(clicked()), this, SLOT(on_btnMoveCircle_clicked()));
     layout_menu->addWidget(btnMoveCircle);

     layout_menu->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding));

     QWidget *centralWidget = new QWidget;
     centralWidget->setLayout(layout_main);

     statusBar = new QStatusBar();
     label_status = new QLabel(statusModeView[0]);
     statusMode = statusModeView[0];
     statusBar->addPermanentWidget(label_status);


     layout_main->addLayout(layout_menu);
     layout_main->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
     layout_main->addLayout(layout_graph);
     layout_main->addWidget(statusBar);
     setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
     Q_UNUSED(event);
     QPainter painter(this);

     for(int i = 0; i < vectorCircle_.count();i++)
     {
         for(int j = 0; j < vectorCircle_.count();j++)
         {
            if(j == i)
            {
                continue;
            }
          vectorCircle_[i].setOtherCircle(vectorCircle_[j].getCenter(),
                                          vectorCircle_[j].getDiametr(),
                                          vectorCircle_[j].getCollor());
         }
     }
     for(int i = 0; i < vectorCircle_.count(); i++)
     {
         vectorCircle_[i].paint(painter);
         vectorCircle_[i].clearOtherCircle();
     }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(statusMode == statusModeView[1]) //move
    {
        if(event->button() & Qt::LeftButton)
        {
            for(int i = 0; i < vectorCircle_.count();i++)
            {
                if(vectorCircle_[i].isFigureOnCoordinates(event->pos().x(), event->pos().y()))
                {
                    isSelection_=true;
                    selectCircle_ = &vectorCircle_[i];
                    selectPoint_ = event->pos();
                }
            }
         }
    }
    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(statusMode == statusModeView[1]) //move
    {
        if(event->button() == Qt::LeftButton && isSelection_){
           selectCircle_->move(event->pos().x()-selectPoint_.x(), event->pos().y()-selectPoint_.y());
           selectPoint_ = event->pos();
           isSelection_ = false;
       }
    }
    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(statusMode == statusModeView[1]) //move
    {
        if((event->buttons() & Qt::LeftButton) && isSelection_) {
            selectCircle_->move(event->pos().x()-selectPoint_.x(), event->pos().y()-selectPoint_.y());
            selectPoint_ = event->pos();
        }
    }
    repaint();
}

bool MainWindow::isFigureOnCoordinates(int x, int y)
{
    for(int i = 0; i < vectorCircle_.length();i++)
    {
        if(vectorCircle_[i].isFigureOnCoordinates(x, y))
            return true;
    }
    return false;
}

void MainWindow::on_btnCreateCircle_clicked()
{
    QPoint point;
    point.rx() = 150;
    point.ry() = 150;
    Circle circleRed(Qt::red, point, 250);
    vectorCircle_.push_back(circleRed);

    point.rx() = 450;
    point.ry() = 350;
    Circle circleGreen(Qt::green, point, 250);
    vectorCircle_.push_back(circleGreen);

    point.rx() = 200;
    point.ry() = 500;
    Circle circleBlue(Qt::blue, point, 250);
    vectorCircle_.push_back(circleBlue);

    repaint();
}

void MainWindow::on_btnMoveCircle_clicked()
{
    statusMode= statusModeView[1];
    label_status->setText(statusMode);
}

