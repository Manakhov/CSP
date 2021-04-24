#include "dcontrolobject.h"

DcontrolObject::DcontrolObject(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33,
                               float b1, float b2, float b3, float c1, float c2, float c3, float d, float x1, float x2, float x3):
    m_a11(a11), m_a12(a12), m_a13(a13), m_a21(a21), m_a22(a22), m_a23(a23), m_a31(a31), m_a32(a32), m_a33(a33),
    m_b1(b1), m_b2(b2), m_b3(b3),m_c1(c1), m_c2(c2), m_c3(c3), m_d(d), m_x1(x1), m_x2(x2), m_x3(x3), m_prev_input(0.0)
{

}

float DcontrolObject::getOutput()
{
    return m_x1*m_c1 + m_x2*m_c2 + m_x3*m_c3 + m_d*m_prev_input;
}

float DcontrolObject::update(float input)
{
    float output = getOutput();
    float tmp_x1 = m_x1;
    float tmp_x2 = m_x2;
    float tmp_x3 = m_x3;
    m_x1 = m_a11*tmp_x1 + m_a12*tmp_x2 + m_a13*tmp_x3 + m_b1*input;
    m_x2 = m_a21*tmp_x1 + m_a22*tmp_x2 + m_a23*tmp_x3 + m_b2*input;
    m_x3 = m_a31*tmp_x1 + m_a32*tmp_x2 + m_a33*tmp_x3 + m_b3*input;
    m_prev_input = input;
    return output;
}
