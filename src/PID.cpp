/**
 * \file PID.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/10/2024
 */ 

#include "main.h"

nova::PID::PID (
        float error,
        float kP, 
        float kI,
        float kD,
        float maxCumulativeError,
        float loopTime
    ):

    error(error),
    kP(kP),
    kI(kI),
    kD(kD),
    maxCumulativeError(maxCumulativeError),
    loopTime(loopTime)
{};

nova::PID::PID (
        float error,
        float kP,
        float kI,
        float kD,
        float maxCumulativeError,
        float settleError,
        float settleTime,
        float timeout,
        float loopTime
    ):

    error(error),
    kP(kP),
    kI(kI),
    kD(kD),
    maxCumulativeError(maxCumulativeError),
    settleError(settleError),
    settleTime(settleTime),
    timeout(timeout),
    loopTime(loopTime)
{};

float nova::PID::compute(float error) {
    if (fabs(error) < maxCumulativeError) {
        accumulatedError += error;
    }

    if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0)) {
        accumulatedError = 0;
    }

    /*
    futureError = (error - prevError);

    if (fabs(futureError) > fabs(acceleration + prevDeriv) && prevDeriv != 0) {
        futureError = acceleration + prevDeriv;
    }
    */

    output = kP * error + kI * accumulatedError + kD * (error - prevError);

    prevError = error;
    acceleration = futureError - prevDeriv;
    prevDeriv = futureError;
    
    if (fabs(error) < settleError) {
        timeSpentSettled += loopTime;
    } else {
        timeSpentSettled = 0;
    }

    timeSpentRunning += loopTime;

    return output;
}

bool nova::PID::isSettled() {
    if (timeSpentRunning > timeout && timeout != 0) {
        return true;
    }

    if (timeSpentSettled > settleTime) {
        return true;
    }

    return false;
}

void nova::PID::reset() {
    accumulatedError = 0;
    futureError = 0;
    prevError = 0;

    acceleration = 0;
    prevDeriv = 0;
    error = 0;
    output = 0;

    timeSpentSettled = 0;
    timeSpentRunning = 0;
}

void nova::PID::setkConstants (
        float kP, 
        float kI, 
        float kD, 
        float maxCumulativeError
    ) {

    this -> kP = kP;
    this -> kI = kI;
    this -> kD = kD;
    this -> maxCumulativeError = maxCumulativeError;
} 

void nova::PID::setExitConditionConstants (
        float settleError, 
        float settleTime, 
        float timeout
    ) {

    this -> settleError = settleError;
    this -> settleTime = settleTime;
    this -> timeout = timeout;
}