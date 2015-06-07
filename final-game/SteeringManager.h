//
// Created by Matheus Pereira Junior on 6/7/15.
// Copyright (c) 2015 ___FULLUSERNAME___. All rights reserved.
//


#ifndef __SteeringManager_H_
#define __SteeringManager_H_

#include "Vector2d.h"
#include "IMovingEntity.h"

/* Class responsible for the steering behaviour functions
* Behaviours adapted from
*       http://gamedevelopment.tutsplus.com/series/understanding-steering-behaviors--gamedev-12732 */
class SteeringManager
{
private:
    /** holds forces applied to the host */
    Vector2d steeringForce;

    /** Reference to the moving entity */
    IMovingEntity *host;

public:
    SteeringManager(IMovingEntity *host) {
        this->host = host;
        this->steeringForce = Vector2d(0,0);
    }

    /* Public 'API' function calls.
    *  Used to change the steering force vector */
    void Seek(Vector2d target);

    void Flee(Vector2d target);

    void Arrive(Vector2d target);

    void Wander();

    void Pursuit(IMovingEntity &target);

    void Evade(IMovingEntity &target);

    /* Updates host velocity and position applying the calculated steering force.
    *  Resets x and y coordinates to 0 since forces must be new in each behaviour */
    void update();

private:
    /* The functions that actually do the hard work */

    /* Seek a target
    *  Returns a Vector2d holding the steering value force to be applied to host */
    Vector2d doSeek(Vector2d target);

    /* Flee from a target. Opposite behaviour of Seek
    *  Returns a Vector2d holding the steering value force to be applied to host */
    Vector2d doFlee(Vector2d target);

    /* Seek-like behaviour with smooth arrival when approaching the target
    *  Returns a Vector2d holding the steering value force to be applied to host *;
    Vector2d doArrive(Vector2d target);

    /* Wander on screen */
    // \todo Not working properly
    Vector2d doWander();

    /* Seek-based function that pursuits a target. Predict target's future position T times in the future
    *  Returns a Vector2d holding the steering value force to be applied to host */
    Vector2d doPursuit(IMovingEntity &target);

    /* Flee-based function that evades a target. Predict target's future position T times in the future *
    *  Returns a Vector2d holding the steering value force to be applied to host */
    Vector2d doEvade(IMovingEntity &target);
};


#endif //__SteeringManager_H_
