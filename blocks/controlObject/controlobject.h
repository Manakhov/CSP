#ifndef CONTROLOBJECT_H
#define CONTROLOBJECT_H

#include "blocks/integrator/integrator.h"

class ControlObject
{
public:
    ControlObject(float value);

    float getOutput() const;
    float update(float value, float dt);

public:
    integrator* m_integrator;
};

#endif // CONTROLOBJECT_H
