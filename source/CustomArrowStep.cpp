#include "CustomArrowStep.h"

CustomArrowStep::CustomArrowStep (const char *pName) : LiveActor(pName) {
    OSReport("Helo\n");
    mSpeed = 5.0f;
    mArrowAmount = 4;
}
CustomArrowStep::~CustomArrowStep () {

}

void CustomArrowStep::init (const JMapInfoIter &rIter) {
    OSReport("We are ze custom\n");
    MR::initDefaultPos(this, rIter);
    MR::processInitFunction(this, rIter, false);
    MR::connectToSceneMapObj(this);
    
    MR::getJMapInfoArg0NoInit(rIter, &mSpeed);
    MR::getJMapInfoArg1NoInit(rIter, &mArrowAmount);
    initArrows();

    MR::addHitSensorMapObj(this, "Body", 1, 600.0f, TVec3f(0));
    initBinder(600.0f, 0.0f, 0);
    MR::initCollisionParts(this, "CustomArrowStep", getSensor("Body"), NULL);
    
    initNerve(&NrvCustomArrowStep::NrvInactive::sInstance, 0);
    MR::validateCollisionParts(this);
    MR::validateClipping(this);
    makeActorAppeared();
}

void CustomArrowStep::initArrows () {
    mVelocity = TVec3f(0);
    mCurrentArrowName = "";
    initHitSensor(mArrowAmount + 1);
    mArrows = new ArrowStep*[mArrowAmount];
    for (s32 i = 1; i <= mArrowAmount; i++) {
        char arrowName[9];
        sprintf(arrowName, "Arrow_%d", i);
        mArrows[i - 1] = (ArrowStep *)MR::createPartsModelMapObj(this, "ArrowStep", "ArrowStep", MR::getJointMtx(this, arrowName));
        strcpy(mArrows[i - 1]->mLinkedJointName, arrowName);
        MR::addHitSensorAtJointMapObj(this, mArrows[i - 1]->mLinkedJointName, arrowName, 8, 50.0f, TVec3f(0.0f));
        mArrows[i - 1]->initSound(1, "ArrowStep", 0, TVec3f(0));
    }
}

void CustomArrowStep::attackSensor (HitSensor *pReceiver, HitSensor *pSender) {
    if (MR::isBinded(this) || isNerve(&NrvCustomArrowStep::NrvDisabled::sInstance)) 
        return;
    if (MR::isEqualSensor(pReceiver, this, "Body") && MR::isSensorPlayerOrYoshiOrRide(pSender)) 
        setNerve(&NrvCustomArrowStep::NrvActive::sInstance);
    else if (MR::isSensorPlayerOrYoshiOrRide(pSender) && MR::isOnGroundPlayer()) {
        if (!MR::isEqualSensor(pReceiver, this, mCurrentArrowName)) 
            setDirection(pReceiver);
    }
}

void CustomArrowStep::control () {
    if (MR::isValidSwitchA(this) && !MR::isOnSwitchA(this)) 
        setNerve(&NrvCustomArrowStep::NrvDisabled::sInstance);
    else 
        setNerve(&NrvCustomArrowStep::NrvInactive::sInstance);
}

void CustomArrowStep::setDirection (HitSensor *pDirectionSensor) {
    if (!pDirectionSensor) {
        setDirection(TVec3f(0));
        mCurrentArrowName = "";
        for (s32 i = 0; i < mArrowAmount; i++) 
            MR::startAction(mArrows[i], "Inactive");
        return;
    }
    
    for (s32 i = 0; i < mArrowAmount; i++) {
        if (MR::isEqualSensor(pDirectionSensor, this, mArrows[i]->mLinkedJointName)) {
            MR::startAction(mArrows[i], "Active");
            TVec3f frontVec;
            MR::calcFrontVec(&frontVec, mArrows[i]);
            setDirection(frontVec);
            mCurrentArrowName = mArrows[i]->mLinkedJointName;
            OSReport("Interacting with %s\n", mCurrentArrowName);
        } else 
            MR::startAction(mArrows[i], "Inactive");
    }
}

void CustomArrowStep::setDirection (const TVec3f &direction) {
    mVelocity = direction * mSpeed;
}

void CustomArrowStep::stopMove () {
    setDirection(NULL);
}

void CustomArrowStep::exeDisabled () {
    if (MR::isFirstStep(this)) 
        for (s32 i = 0; i < mArrowAmount; i++) {
            OSReport("%x\n", mArrows[i]);
            MR::startAction(mArrows[i], "Disabled");
        }
}

namespace NrvCustomArrowStep {
    void NrvActive::execute (Spine *pSpine) const {
        
    }
    void NrvInactive::execute (Spine *pSpine) const {
        CustomArrowStep *pActor = (CustomArrowStep *)pSpine->mExecutor;
        pActor->stopMove();
    }
    void NrvDisabled::execute (Spine *pSpine) const {
        CustomArrowStep *pActor = (CustomArrowStep *)pSpine->mExecutor;
        pActor->exeDisabled();
    }

    NrvActive(NrvActive::sInstance);
    NrvInactive(NrvInactive::sInstance);
    NrvDisabled(NrvDisabled::sInstance);
}