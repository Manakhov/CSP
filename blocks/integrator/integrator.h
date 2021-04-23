#ifndef INTEGRATOR_H
#define INTEGRATOR_H


class integrator
{
public:
    integrator(float value);

    float update(float input, float dt);
    float state() const;

private:
    float m_prev_input = 0.0;
    float m_state = 0.0;
};

#endif // INTEGRATOR_H
