//
// Created by Matheus Pereira Junior on 6/7/15.
// Copyright (c) 2015 ___FULLUSERNAME___. All rights reserved.
//


#ifndef __SteeringManager_H_
#define __SteeringManager_H_


#include "Vector2d.h"
#include "IMovingEntity.h"

class SteeringManager
{
private:
    Vector2d steeringForce;

public:
    IMovingEntity *host;

    SteeringManager() {
        // \FIXME steering not initialized, not safe
        this->steeringForce = Vector2d(0,0);
    }

    SteeringManager(IMovingEntity *host) {
        this->host = host;
        this->steeringForce = Vector2d(0,0);
    }

    void Seek(Vector2d target);

    void Flee(Vector2d target);

    void Arrive(Vector2d target);

//    void Wander();
//
    void Pursuit(IMovingEntity &target);

    void Evade(IMovingEntity &target);

    void update();

private:
    Vector2d doSeek(Vector2d target);

    Vector2d doFlee(Vector2d target);

    Vector2d doArrive(Vector2d target);

//    Vector2d doWander();

    Vector2d doPursuit(IMovingEntity &target);

    Vector2d doEvade(IMovingEntity &target);
};


#endif //__SteeringManager_H_
