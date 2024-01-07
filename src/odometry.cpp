/**
 * \file odometry.cpp
 *
 * Updated - 1/1/2024
 * Last Successful Test - /
 */ 

#include "main.h"

float nova::Odometry::getAvgLeftEncoderValue() {
    return (nova::frontLeft.get_position() + nova::backBottomLeft.get_position() + nova::backTopLeft.get_position());
}

float nova::Odometry::getAvgRightEncoderValue() {
    return (nova::frontRight.get_position() + nova::backBottomRight.get_position() + nova::backTopRight.get_position());
}

float nova::Odometry::getTrackingEncoderValue() {
    return (nova::backTracking.get_position());
}

void nova::Odometry::trackPosition(int left, int right, int back, sPos& position) {
    float leftDist = (left - position.leftLst);
    float rightDist = (right - position.rightLst);
    float backDist = (back - position.backLst);

    position.leftLst = left;
    position.rightLst = right;
    position.backLst = back;

    float y;
    float x;
    float angle = (leftDist - rightDist) / (LEFT_SIDE_RADIUS + RIGHT_SIDE_RADIUS);

    if (angle) {
        y = 2 * (((rightDist) / angle) + RIGHT_SIDE_RADIUS) * (sin((angle / 2)));
        x = 2 * (((backDist) / angle) + BACK_SIDE_RADIUS) * (sin((angle / 2)));
    } else {
        y = rightDist;
        x = backDist;
    }

    float currentAngle = (angle / 2) + position.angle;
    
    position.y += y * cos(currentAngle) + x * -sin(currentAngle);
    position.x += y * sin(currentAngle) + x * cos(currentAngle);
    position.angle += angle;
}

void nova::Odometry::resetPosition(sPos& position) {
    position.leftLst = position.rightLst = position.backLst = position.x = position.y = position.angle = 0;
}

pros::Task nova::Odometry::updateTrackPosition() {
    while (true) {
        this -> trackPosition(this -> getAvgLeftEncoderValue(), this -> getAvgRightEncoderValue(), this -> getTrackingEncoderValue(), this -> botPosition);
    }
}