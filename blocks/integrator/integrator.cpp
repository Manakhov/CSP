#include "integrator.h"

integrator::integrator(float value)
{
    m_state = value;
}

float integrator::update(float input, float dt)
{
    m_state = m_state + (m_prev_input + input) * dt / 2;
    m_prev_input = input;
    return m_state;
}

float integrator::state() const
{
    return m_state;
}
