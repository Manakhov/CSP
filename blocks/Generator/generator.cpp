#include "generator.h"


Generator::Generator(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33,
                     float c1, float c2, float c3, float x1, float x2, float x3):
    m_a11(a11), m_a12(a12), m_a13(a13), m_a21(a21), m_a22(a22), m_a23(a23), m_a31(a31), m_a32(a32), m_a33(a33),
    m_c1(c1), m_c2(c2), m_c3(c3)
{
    m_integrator_X1 = new integrator(x1);
    m_integrator_X2 = new integrator(x2);
    m_integrator_X3 = new integrator(x3);
}

Generator::~Generator()
{
    delete m_integrator_X1;
    delete m_integrator_X2;
    delete m_integrator_X3;
}

float Generator::getOutput() const
{
    return m_c1*m_integrator_X1->state() + m_c2*m_integrator_X2->state() + m_c3*m_integrator_X3->state();
}

float Generator::update(float dt)
{
    float tmp_x1 = m_integrator_X1->state();
    float tmp_x2 = m_integrator_X2->state();
    float tmp_x3 = m_integrator_X3->state();
    m_integrator_X1->update(m_a11*tmp_x1 + m_a12*tmp_x2 + m_a13*tmp_x3, dt);
    m_integrator_X2->update(m_a21*tmp_x1 + m_a22*tmp_x2 + m_a23*tmp_x3, dt);
    m_integrator_X3->update(m_a31*tmp_x1 + m_a32*tmp_x2 + m_a33*tmp_x3, dt);
    float output = getOutput();
    return output;
}
