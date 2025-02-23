#pragma once

#include "syati.h"

class ArrowStep : public PartsModel {
public:
    ArrowStep (LiveActor *pHost, const char *pName, const char *pModelName, MtxPtr pMtx, int drawBufferType, bool unk) : PartsModel(pHost, pName, pModelName, pMtx, drawBufferType, unk) {};
    ~ArrowStep () {}
    char mLinkedJointName[9];
};