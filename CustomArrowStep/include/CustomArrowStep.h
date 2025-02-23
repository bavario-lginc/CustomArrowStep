#pragma once

#include "syati.h"
#include "ArrowStep.h"

class CustomArrowStep : public LiveActor {
public:
    CustomArrowStep(const char *);
    ~CustomArrowStep();
    virtual void init(const JMapInfoIter &);
    virtual void attackSensor(HitSensor *, HitSensor *);
    virtual void control();
    void initArrows();
    void setDirection(HitSensor *);
    void setDirection(const TVec3f &);
    void stopMove();
    void exeDisabled();
    
    f32 mSpeed;
    s32 mArrowAmount;
    ArrowStep **mArrows;
    const char *mCurrentArrowName;
};

namespace NrvCustomArrowStep {
    NERVE(NrvActive);
    NERVE(NrvInactive);
    NERVE(NrvDisabled);
};