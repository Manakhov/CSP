#ifndef CONTROLOBJECT_H
#define CONTROLOBJECT_H

#include "blocks/integrator/integrator.h"

class ControlObject
{
public:
    ControlObject(float x1, float x2, float x3);
    ~ControlObject();

    float getOutput() const;
    float update(float input, float dt);

public:
    integrator* m_integrator_X1;
    integrator* m_integrator_X2;
    integrator* m_integrator_X3;
    float m_prev_input;
};

#endif // CONTROLOBJECT_H
