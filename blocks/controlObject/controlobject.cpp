#include "controlobject.h"

ControlObject::ControlObject(float initValue)
{
    m_integrator = new integrator(initValue);
}

float ControlObject::getOutput() const
{
    return m_integrator->state();
}

float ControlObject::update(float value, float dt)
{
    float tmp = m_integrator->state();
    m_integrator->update(value - tmp, dt);
    return tmp;
}
