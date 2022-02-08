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

     btnGoCircle = new QPushButton("Go Circle");
     connect(btnGoCircle, SIGNAL(clicked()), this, SLOT(on_btnGoCircle_clicked()));
     layout_menu->addWidget(btnGoCircle);

     btnStopCircle = new QPushButton("Stop Circle");
     connect(btnStopCircle, SIGNAL(clicked()), this, SLOT(on_btnStopCircle_clicked()));
     layout_menu->addWidget(btnStopCircle);
     btnStopCircle->hide();

     isAdditivMixing = new QRadioButton("Additiv");
     layout_menu->addWidget(isAdditivMixing);
     isAdditivMixing->setChecked(true);
     connect(isAdditivMixing, SIGNAL(clicked()), this, SLOT(on_isAdditivMixing_clicked()));

     isAverageMixing = new QRadioButton("Average");
     layout_menu->addWidget(isAverageMixing);
     connect(isAverageMixing, SIGNAL(clicked()), this, SLOT(on_isAverageMixing_clicked()));

     isGammaMixing = new QRadioButton("Gamma");
     layout_menu->addWidget(isGammaMixing);
     connect(isGammaMixing, SIGNAL(clicked()), this, SLOT(on_isGammaMixing_clicked()));

     sliderCollor = new QSlider(Qt::Horizontal,this);
     sliderCollor->setMaximum(4000);
     sliderCollor->setMinimum(250);
     sliderCollor->setValue(1000);
     layout_menu->addWidget(sliderCollor);

     label_slider = new QLabel();
     label_slider->setText(QString::number(sliderCollor->value()));
     layout_menu->addWidget(label_slider);

     sliderCollor->hide();
     label_slider->hide();

     connect(sliderCollor, &QSlider::valueChanged, label_slider,
       static_cast<void (QLabel::*)(double)>(&QLabel::setNum));

     connect(sliderCollor, SIGNAL(valueChanged(int)), this, SLOT(sliderCollor_valueChanged(int)));

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
     painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::FlatCap));
     painter.drawRect(50,50,1100,700);
     if(paintMode_ == 0)
     {
         paintMode_ = 1;
     }

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
         //vectorCircle_[i].setPlate(QPoint(50,50),QPoint(1100+50,700+50));
         vectorCircle_[i].paint(painter, paintMode_,double(sliderCollor->value())/1000);
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
    point.rx() = 350;
    point.ry() = 350;
    Circle circleRed(Qt::red, point, 300,qMakePair(QPoint(50,50),QPoint(1150,750)));
    vectorCircle_.push_back(circleRed);

    point.rx() = 760;
    point.ry() = 470;
    Circle circleGreen(Qt::green, point, 300, qMakePair(QPoint(50,50),QPoint(1150,750)));
    vectorCircle_.push_back(circleGreen);

    point.rx() = 550;
    point.ry() = 550;
    Circle circleBlue(Qt::blue, point, 300, qMakePair(QPoint(50,50),QPoint(1150,750)));
    vectorCircle_.push_back(circleBlue);

    point.rx() = 650;
    point.ry() = 550;
    Circle circlePurple(QColor(128,0,128), point, 300, qMakePair(QPoint(50,50),QPoint(1150,750)));
    vectorCircle_.push_back(circlePurple);

    repaint();
}

void MainWindow::on_btnMoveCircle_clicked()
{
    statusMode= statusModeView[1];
    label_status->setText(statusMode);
}

void MainWindow::sliderCollor_valueChanged(int)
{
    label_slider->setText(QString::number(double(sliderCollor->value())/1000,'f',2));
    repaint();
}

void MainWindow::on_btnGoCircle_clicked()
{
    timer_ = new QTimer(this);
    timer_->setInterval(40);
    connect(timer_, SIGNAL(timeout()), this, SLOT(updateRepaint()));

    statusMode= statusModeView[2];
    label_status->setText(statusMode);
    btnGoCircle->hide();
    btnStopCircle->show();
    timer_->start();
}

void MainWindow::updateRepaint()
{
    for(int i = 0; i < vectorCircle_.count();i++){
        vectorCircle_[i].move();
    }
    repaint();
}

void MainWindow::on_btnStopCircle_clicked()
{
    timer_->stop();
    delete timer_;
    statusMode= statusModeView[0];
    label_status->setText(statusMode);
    btnStopCircle->hide();
    btnGoCircle->show();
}

void MainWindow::on_isAdditivMixing_clicked()
{
    paintMode_ = 1;
    sliderCollor->hide();
    sliderCollor->hide();
    repaint();
}

void MainWindow::on_isAverageMixing_clicked()
{
    paintMode_ = 2;
    sliderCollor->hide();
    label_slider->hide();
    repaint();
}

void MainWindow::on_isGammaMixing_clicked()
{
    paintMode_ = 3;
    sliderCollor->show();
    label_slider->show();
    repaint();
}



