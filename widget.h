#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QDateTime>
#include "qcustomplot.h"
#include "blocks/gain/gain.h"
#include "blocks/integrator/integrator.h"
#include "blocks/controlObject/controlobject.h"
#include "blocks/DcontrolObject/dcontrolobject.h"
#include "blocks/Generator/generator.h"
#include "blocks/Dgenerator/dgenerator.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void update();

private:
    Ui::Widget *ui;
    QGridLayout *mainlayout;
    QCustomPlot *inputPlot;
    QCustomPlot *outputPlot;
	QPushButton* startButton;
	QPushButton* saveButton;

	qint64 startTime = 0;
	qint64 relativeTime = 0;
	qint64 dt;

    QTimer * timer;

    // --------------------------
    // Add pointer to the object here
    // --------------------------

    // for Constant
//    Generator *m_generator;
//    ControlObject *m_controlObject;

    // for Discrete
    Dgenerator *m_dgenerator;
    DcontrolObject *m_dcontrolObject;

    // Add pointer to the object here
    // --------------------------
};

#endif // WIDGET_H
