//
// Created by Matheus Pereira Junior on 6/7/15.
// Copyright (c) 2015 ___FULLUSERNAME___. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "SteeringManager.h"
#include "Util.h"

void SteeringManager::Seek(Vector2d target)
{
    // \FIXME must be added to itself to allow multiple behaviour combination, reset in update
    steeringForce += doSeek(target);
}

void SteeringManager::Flee(Vector2d target)
{
    steeringForce += doFlee(target);
}

void SteeringManager::Arrive(Vector2d target)
{
    steeringForce += doArrive(target);
}

//void SteeringManager::Wander()
//{
//    steeringForce += doWander();
//}

void SteeringManager::Pursuit(IMovingEntity &target)
{
    steeringForce += doPursuit(target);
}

void SteeringManager::Evade(IMovingEntity &target)
{
    steeringForce += doEvade(target);
}

Vector2d SteeringManager::doSeek(Vector2d target)
{
    Vector2d desiredVelocity;

    desiredVelocity = Vector2d::Normalize(target - host->getPos());
    desiredVelocity.x *= MAX_VELOCITY.x;
    desiredVelocity.y *= MAX_VELOCITY.y;

    return desiredVelocity - host->getVelocity();
}

Vector2d SteeringManager::doFlee(Vector2d target)
{
    Vector2d desiredVelocity;
    const double SAFE_ZONE = 100 * 100;

    // check if the enemy is far enough to keep calm
    if (host->getPos().getSequentialDistance(target) > SAFE_ZONE) {
        return Vector2d(0, 0);
    }
    desiredVelocity = Vector2d::Normalize(host->getPos() - target);
    desiredVelocity.x *= MAX_VELOCITY.x;
    desiredVelocity.y *= MAX_VELOCITY.y;

    return desiredVelocity - host->getVelocity();
}

Vector2d SteeringManager::doArrive(Vector2d target)
{
    Vector2d desiredVelocity;
    const float slowingRadius = 100;
    float distance;

    desiredVelocity = target - host->getPos();
    // Line orders cannot be inverted
    distance = desiredVelocity.getLength();
    desiredVelocity.Normalize();
    desiredVelocity.x *= MAX_VELOCITY.x;
    desiredVelocity.y *= MAX_VELOCITY.y;

    if (distance < slowingRadius) {
        desiredVelocity.x *= (distance / slowingRadius);
        desiredVelocity.y *= (distance / slowingRadius);
    }

    return desiredVelocity - host->getVelocity();
}

Vector2d SteeringManager::doEvade(IMovingEntity &target)
{
    Vector2d distance = target.getPos() - host->getPos();
    int T = distance.getLength() / MAX_VELOCITY.x;
    Vector2d futurePosition = target.getPos() + target.getVelocity() * T;
    return doFlee(futurePosition);
}

void SteeringManager::update()
{
    host->setVelocity(host->getVelocity() + steeringForce);
    host->setPos(host->getPos() + host->getVelocity());

    // \FIXME Must be reset since each force caulcalition does not depend on the previous one
    steeringForce.x = 0;
    steeringForce.y = 0;
}

//Vector2d SteeringManager::doWander()
//{
//    Vector2d circle;
//    Vector2d wanderForce;
//    Vector2d displacement(0, -1);
//
//    circle = host->getVelocity();
//    // Find the circle's center position
//    circle.Normalize();
//    circle.x *= CIRCLE_DISTANCE;
//    circle.y *= CIRCLE_DISTANCE;
//
//    // rotation matrix
//    displacement.x = cos(wanderAngle) * displacement.x + -sin(wanderAngle) * displacement.y;
//    displacement.y = sin(wanderAngle) * displacement.x + cos(wanderAngle) * displacement.y;
//
//    displacement.x *= CIRCLE_RADIUS;
//    displacement.y *= CIRCLE_RADIUS;
//
//    wanderAngle += Util::GenerateRandom(0, 10) * ANGLE_CHANGE - ANGLE_CHANGE * 0.1;
////    if (wanderAngle > INT_MAX/2) wanderAngle = 0;
//
//    return circle + displacement;
//}
Vector2d SteeringManager::doPursuit(IMovingEntity &target)
{
    Vector2d distance = target.getPos() - host->getPos();
    int T = distance.getLength() / MAX_VELOCITY.x;
    Vector2d futurePosition = target.getPos() + target.getVelocity() * T;
    return doSeek(futurePosition);
}
