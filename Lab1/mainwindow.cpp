#include "mainwindow.h"

MainWindow::MainWindow(QMainWindow* parent) :QMainWindow(parent)
{
    resize(1280,800);

    layout_main = new QVBoxLayout;
    layout_menu = new QHBoxLayout;
    layout_graph = new QHBoxLayout;

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout_main);

    statusBar = new QStatusBar();
    label_status = new QLabel(statusModeView[0]);
    statusMode = statusModeView[0];
    statusBar->addPermanentWidget(label_status);

    btnCreateFigure = new QPushButton("Create figure");
    connect(btnCreateFigure, SIGNAL(clicked()), this, SLOT(on_btnCreateFigure_clicked()));
    layout_menu->addWidget(btnCreateFigure);

    btnMoveFigure = new QPushButton("Move figure");
    connect(btnMoveFigure, SIGNAL(clicked()), this, SLOT(on_btnMoveFigure_clicked()));
    layout_menu->addWidget(btnMoveFigure);

    btnRotateFigure = new QPushButton("Rotate figure");
    connect(btnRotateFigure, SIGNAL(clicked()), this, SLOT(on_btnRotateFigure_clicked()));
    layout_menu->addWidget(btnRotateFigure);

    btnScaleFigure = new QPushButton("Scale figure");
    connect(btnScaleFigure, SIGNAL(clicked()), this, SLOT(on_btnScaleFigure_clicked()));
    layout_menu->addWidget(btnScaleFigure);

    btnTabulationFigure = new QPushButton("Tabulation figure");
    connect(btnTabulationFigure, SIGNAL(clicked()), this, SLOT(on_btnTabulationFigure_clicked()));
    layout_menu->addWidget(btnTabulationFigure);
    layout_menu->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding));

    layout_main->addLayout(layout_menu);
    layout_main->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout_main->addLayout(layout_graph);
    layout_main->addWidget(statusBar);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}

bool MainWindow::isFigureOnCoordinates(int x, int y)
{
    for(int i = 0; i < vectorFigure_.length();i++)
    {
        if(vectorFigure_[i].isFigureOnCoordinates(x, y))
            return true;
    }
    return false;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QVector<Figure> triangles;

    for(int i = 0; i < vectorFigure_.length(); i++)
    {
        vectorFigure_[i].paint(painter, triangles);
        if(vectorFigure_[i].getCountPoint()>2)
            triangles += vectorFigure_[i].triangulate();
        //vectorFigure_[i].paintTriangles(painter);
    }
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(statusMode == statusModeView[1]) //create
    {
        if(event->button() & Qt::LeftButton)
        {
             vectorFigure_.back().add_point(event->pos().x(), event->pos().y());
        }
        if(event->button() & Qt::RightButton)
        {
             if(vectorFigure_.back().getCountPoint() > 2)
             {
                vectorFigure_.back().closeShape();
                statusMode= statusModeView[0];
                label_status->setText(statusMode);
             }

        }
    }
    if(statusMode == statusModeView[2]) //move
    {
        if(event->button() & Qt::LeftButton) {
                for(int i = 0; i < vectorFigure_.count();i++)
                {
                    if(vectorFigure_[i].isFigureOnCoordinates(event->pos().x(), event->pos().y()))
                    {
                        isSelection_=true;
                        selectFugure_ = &vectorFigure_[i];
                        selectPoint_ = event->pos();
                    }
                }
        }
    }
    if(statusMode == statusModeView[3]) //Rotate
    {
        for(int i = 0; i < vectorFigure_.count();i++)
        {
            if(event->button() & Qt::LeftButton) {
               isSelection_=true;
               selectFugure_ = &vectorFigure_[i];
               selectPoint_ = event->pos();
            }
        }
    }
    if(statusMode == statusModeView[4]) //Scale
    {
        for(int i = 0; i < vectorFigure_.count();i++)
        {
            if(event->button() & Qt::LeftButton) {
               isSelection_=true;
               selectFugure_ = &vectorFigure_[i];
               selectPoint_ = event->pos();
            }
        }
    }
    if(statusMode == statusModeView[5]) //Tabulation
    {
        if(event->button() & Qt::LeftButton)
        {
            for(int i = 0; i < vectorFigure_.count();i++)
            {
                if(vectorFigure_[i].isFigureOnCoordinates(event->pos().x(),event->pos().y()))
                {
                    Figure temp = vectorFigure_[i];
                    vectorFigure_.remove(i);
                    vectorFigure_.push_front(temp);
                }
            }
        }
        if(event->button() & Qt::RightButton)
        {
            statusMode = statusModeView[0];
            label_status->setText(statusMode);
        }
    }
    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
     if(statusMode == statusModeView[2]) //move
     {
         if(event->button() == Qt::LeftButton && isSelection_){
            selectFugure_->move(event->pos().x()-selectPoint_.x(), event->pos().y()-selectPoint_.y());
            selectPoint_ = event->pos();
            statusMode = statusModeView[0];
            label_status->setText(statusMode);
            isSelection_ = false;
        }
     }
     if(statusMode == statusModeView[3]) //Rotate
     {
         if(event->button() == Qt::LeftButton && isSelection_){
            selectFugure_->setAngle(selectPoint_, event->pos());
            selectFugure_->rotate();
            statusMode = statusModeView[0];
            label_status->setText(statusMode);
            isSelection_ = false;
        }
     }
     if(statusMode == statusModeView[4]) //Scale
     {
         if(event->button() == Qt::LeftButton && isSelection_){
            selectFugure_->setScale(event->pos().x(), event->pos().y(), selectPoint_);
            selectFugure_->scale();
            statusMode = statusModeView[0];
            label_status->setText(statusMode);
            isSelection_ = false;
        }
     }
     repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(statusMode == statusModeView[2]) //move
    {
        if((event->buttons() & Qt::LeftButton) && isSelection_) {
                       selectFugure_->move(event->pos().x()-selectPoint_.x(), event->pos().y()-selectPoint_.y());
                       selectPoint_ = event->pos();
        }
    }
    if(statusMode == statusModeView[3]) //Rotate
    {
        if(((event->buttons() & Qt::LeftButton) && isSelection_))
        {
            selectFugure_->setAngle(selectPoint_, event->pos());
            selectFugure_->rotate();
        }
    }
    if(statusMode == statusModeView[4]) //Scale
    {
        if(((event->buttons() & Qt::LeftButton) && isSelection_))
        {
            selectFugure_->setScale(event->pos().x(), event->pos().y(), selectPoint_);
            selectFugure_->scale();
        }
    }
    repaint();
}

void MainWindow::on_btnCreateFigure_clicked()
{
    createFigure();
}

void MainWindow::on_btnMoveFigure_clicked()
{
    statusMode= statusModeView[2];
    label_status->setText(statusMode);
}

void MainWindow::on_btnRotateFigure_clicked()
{
    statusMode= statusModeView[3];
    label_status->setText(statusMode);
}

void MainWindow::on_btnScaleFigure_clicked()
{
    statusMode= statusModeView[4];
    label_status->setText(statusMode);
}

void MainWindow::on_btnTabulationFigure_clicked()
{
    statusMode= statusModeView[5];
    label_status->setText(statusMode);
}

void MainWindow::createFigure()
{
    Figure newFigure(QColor(QRandomGenerator::global()->generate()%255, QRandomGenerator::global()->generate()%255, QRandomGenerator::global()->generate()%255));
    vectorFigure_.push_back(newFigure);
    statusMode= statusModeView[1];
    label_status->setText(statusMode);
}
