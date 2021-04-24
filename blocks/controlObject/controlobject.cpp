#include "controlobject.h"

ControlObject::ControlObject(float x1, float x2, float x3)
{
    m_integrator_X1 = new integrator(x1);
    m_integrator_X2 = new integrator(x2);
    m_integrator_X3 = new integrator(x3);
}

ControlObject::~ControlObject()
{
    delete m_integrator_X1;
    delete m_integrator_X2;
    delete m_integrator_X3;
}

float ControlObject::getOutput() const
{
    return 2*m_integrator_X1->state() + 4*m_integrator_X2->state() + 4*m_integrator_X3->state();
}

float ControlObject::update(float input, float dt)
{
    float tmp_x1 = m_integrator_X1->state();
    float tmp_x2 = m_integrator_X2->state();
    float tmp_x3 = m_integrator_X3->state();
    float output = getOutput();
    m_integrator_X1->update(tmp_x2, dt);
    m_integrator_X2->update(tmp_x3, dt);
    m_integrator_X3->update(-1*tmp_x1 - 4*tmp_x2 - 4*tmp_x3 + input, dt);
    m_prev_input = input;
    return output;
}
