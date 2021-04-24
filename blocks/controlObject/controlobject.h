#ifndef CONTROLOBJECT_H
#define CONTROLOBJECT_H

#include "blocks/integrator/integrator.h"

class ControlObject
{
public:
    ControlObject(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33,
                  float b1, float b2, float b3, float c1, float c2, float c3, float d, float x1, float x2, float x3);
    ~ControlObject();

    float getOutput() const;
    float update(float input, float dt);

private:
    integrator* m_integrator_X1;
    integrator* m_integrator_X2;
    integrator* m_integrator_X3;
    float m_a11;
    float m_a12;
    float m_a13;
    float m_a21;
    float m_a22;
    float m_a23;
    float m_a31;
    float m_a32;
    float m_a33;
    float m_b1;
    float m_b2;
    float m_b3;
    float m_c1;
    float m_c2;
    float m_c3;
    float m_d;
    float m_prev_input;
};

#endif // CONTROLOBJECT_H
