//
// Created by Matheus Pereira Junior on 6/7/15.
// Copyright (c) 2015 ___FULLUSERNAME___. All rights reserved.
//


#ifndef __IMovingEntity_H_
#define __IMovingEntity_H_

#include "Vector2d.h"

/* Interface for allowing different game entities to use steering behaviours */
class IMovingEntity
{
public:
    // do-nothing constructor to allow call to delete
    ~IMovingEntity() {};
    virtual void setVelocity(Vector2d vel) = 0;
    virtual Vector2d getVelocity() = 0;
    virtual void setPos(Vector2d pos) = 0;
    virtual Vector2d getPos() = 0;
};


#endif //__IMovingEntity_H_
