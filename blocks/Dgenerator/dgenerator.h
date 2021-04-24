#ifndef DGENERATOR_H
#define DGENERATOR_H


class Dgenerator
{
public:
    Dgenerator(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33,
               float c1, float c2, float c3, float x1, float x2, float x3);

    float getOutput() const;
    float update();

private:
    float m_a11;
    float m_a12;
    float m_a13;
    float m_a21;
    float m_a22;
    float m_a23;
    float m_a31;
    float m_a32;
    float m_a33;
    float m_c1;
    float m_c2;
    float m_c3;
    float m_x1;
    float m_x2;
    float m_x3;
};

#endif // DGENERATOR_H
