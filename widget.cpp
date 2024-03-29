#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <math.h>

// --------------------------
// Set stop time here
// --------------------------
#define ENDOFTIME 40
//#define SAMPLINGTIMEMSEC 10 // 100 Hz
//#define SAMPLINGTIMEMSEC 40 // 25 Hz
#define SAMPLINGTIMEMSEC 200 // 5 Hz
// --------------------------
// Set stop time here
// --------------------------

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

	// Create dir for logs
	if (!QDir("logs").exists()) {
		QDir().mkdir("logs");
	}

    // Set window size
	this->setMinimumSize(640, 480);

    // Add main layout with two plots
    mainlayout = new QGridLayout(this);
    inputPlot = new QCustomPlot(this);
    outputPlot = new QCustomPlot(this);
	mainlayout->addWidget(inputPlot, 0, 0);
	mainlayout->addWidget(outputPlot, 0, 1);
	inputPlot->addGraph();
	outputPlot->addGraph();

	startButton = new QPushButton("Start");
	connect(startButton, &QPushButton::clicked, this, [=](){
		startTime = 0;
		relativeTime = 0;
		inputPlot->graph(0)->data()->clear();
		outputPlot->graph(0)->data()->clear();
		timer->start();
	});
	mainlayout->addWidget(startButton, 1, 0);

	saveButton = new QPushButton("Save");
	connect(saveButton, &QPushButton::clicked, this, [=](){
		QString timestamp = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
		inputPlot->savePng(QString("./logs/%1_input.png").arg(timestamp));
		outputPlot->savePng(QString("./logs/%1_output.png").arg(timestamp));
	});
	mainlayout->addWidget(saveButton, 1, 1);

    // Give the axes some labels:
    inputPlot->xAxis->setLabel("t");
    inputPlot->yAxis->setLabel("input");
    outputPlot->xAxis->setLabel("t");
    outputPlot->yAxis->setLabel("output");

    // --------------------------
    // Change ranges if you need
    // --------------------------
    // Set axes ranges so see all data:
    inputPlot->xAxis->setRange(0, ENDOFTIME);
    inputPlot->yAxis->setRange(-2, 3); // (-7, 9);
    outputPlot->xAxis->setRange(0, ENDOFTIME);
    outputPlot->yAxis->setRange(-2, 3); // (-7, 9);

    // --------------------------
    // Create the object here
    // --------------------------

    // for Constant
//    m_generator = new Generator(0, 1, 0, -0.25, 0, 0, 0, 0, -0.5, 1, 0, 1, 1.0, 0.0, 1.0);
//    m_controlObject = new ControlObject(0, 1, 0, 0, 0, 1, -1, -4, -4, 0, 0, 1, 2, 4, 4, 0, 0.0, 0.0, 0.0);

    // for Discrete 100 Hz
//    m_dgenerator = new Dgenerator(1.0000, 0.0100, 0, -0.0025, 1.0000, 0, 0, 0, 0.9950, 1, 0, 1, 1.0, 0.0, 1.0);
//    m_dcontrolObject = new DcontrolObject(1.0000, 0.0100, 0.0000, -0.0000, 0.9998, 0.0098, -0.0098, -0.0393, 0.9606,
//                                          0.0000, 0.0000, 0.0098, 2, 4, 4, 0, 0.0, 0.0, 0.0);

    // for Discrete 25 Hz
//    m_dgenerator = new Dgenerator(0.9998, 0.0400, 0, -0.0100, 0.9998, 0, 0, 0, 0.9802, 1, 0, 1, 1.0, 0.0, 1.0);
//    m_dcontrolObject = new DcontrolObject(1.0000, 0.0400, 0.0008, -0.0008, 0.9970, 0.0369, -0.0369, -0.1485, 0.8493,
//                                          0.0000, 0.0008, 0.0369, 2, 4, 4, 0, 0.0, 0.0, 0.0);

    // for Discrete 5 Hz
    m_dgenerator = new Dgenerator(0.9950, 0.1997, 0, -0.0499, 0.9950, 0, 0, 0, 0.9048, 1, 0, 1, 1.0, 0.0, 1.0);
    m_dcontrolObject = new DcontrolObject(0.9989, 0.1956, 0.0154, -0.0154, 0.9374, 0.1340, -0.1340, -0.5514, 0.4013,
                                          0.0011, 0.0154, 0.1340, 2, 4, 4, 0, 0.0, 0.0, 0.0);

    // --------------------------
    // Create the object here
    // --------------------------

    timer = new QTimer(this);
    timer->setTimerType(Qt::TimerType::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // --------------------------
    // Set sampling time here
    // --------------------------
	timer->setInterval(SAMPLINGTIMEMSEC);
    // --------------------------
    // Set sampling time here
    // --------------------------
}

Widget::~Widget()
{
    delete ui;
    delete inputPlot;
    delete outputPlot;
    delete timer;
    delete mainlayout;

    // --------------------------
    // Delete the object here
    // --------------------------

    // for Constant
//    delete m_generator;
//    delete m_controlObject;

    // for Discrete
    delete m_dgenerator;
    delete m_dcontrolObject;

    // --------------------------
    // Delete the object here
    // --------------------------
}

void Widget::update() {

	// --------------------------
	// Replace input signal with ours
	// --------------------------

    // for Constant
//    double signal = m_generator->getOutput();

    // for Discrete
    double signal = m_dgenerator->getOutput();

	// --------------------------
	// Replace input signal with ours
	// --------------------------

	// --------------------------
	// Plot initial values here
	// --------------------------
	if (startTime == 0) {
		// First step only plot initial values
		startTime = QDateTime::currentMSecsSinceEpoch();

		inputPlot->graph(0)->addData(0.0, 0);
		outputPlot->graph(0)->addData(0.0, 0);
		return;
	} else {
		dt = relativeTime;
		relativeTime = QDateTime::currentMSecsSinceEpoch() - startTime;
		dt = relativeTime - dt;
	}

    inputPlot->graph(0)->addData(relativeTime / 1000.0, signal);
//    outputPlot->graph(0)->addData(relativeTime / 1000.0, m_controlObject->getOutput()); // for Constant
    outputPlot->graph(0)->addData(relativeTime / 1000.0, m_dcontrolObject->getOutput()); // for Discrete

    inputPlot->replot();
    outputPlot->replot();

    // --------------------------
    // Update the object here
    // --------------------------

    // for Constant
//    signal = m_generator->update(dt / 1000.0);
//    m_controlObject->update(signal, dt / 1000.0);

    // for Discrete
    signal = m_dgenerator->update();
    m_dcontrolObject->update(signal);

    // --------------------------
    // Update the object here
    // --------------------------

	if (relativeTime / 1000.0 > ENDOFTIME) {
		timer->blockSignals(true);
		timer->stop();
		timer->blockSignals(false);
	}
}
