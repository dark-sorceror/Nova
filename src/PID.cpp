/**
 * \file PID.cpp
 *
 * Updated - 1/2/2024
 * Last Successful Test - 1/2/2024
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
    
    futureError = (error - prevError);

    if (fabs(futureError) > fabs(acceleration + prevDeriv) && prevDeriv != 0) {
        futureError = acceleration + prevDeriv;
    }

    output = kP * error + kI * accumulatedError + kD * futureError;

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

/*
nova::PID::PID (
        float error,
        float kP, 
        float kI,
        float kD,
        float maxCumulativeError,
        float loopTime,
        bool holdIntegralAtEnd
    ):

    error(error),
    kP(kP),
    kI(kI),
    kD(kD),
    maxCumulativeError(maxCumulativeError),
    loopTime(loopTime),
    holdIntegralAtEnd(holdIntegralAtEnd)
{};

nova::PID::PID (
        float error,
        float kP,
        float kI,
        float kD,
        float maxCumulativeError,
        float minSettleError,
        float minSettleTime,
        float timeout,
        float loopTime,
        bool holdIntegralAtEnd
    ):

    error(error),
    kP(kP),
    kI(kI),
    kD(kD),
    maxCumulativeError(maxCumulativeError),
    minSettleError(minSettleError),
    minSettleTime(minSettleTime),
    timeout(timeout),
    loopTime(loopTime),
    holdIntegralAtEnd(holdIntegralAtEnd)
{};

float nova::PID::compute(float error) {
    

    
    if (fabs(error) < maxCumulativeError) {
        cumulativeError += error;
    }

    if (((error > 0 && prevError < 0) || (error < 0 && prevError > 0)) && !holdIntegralAtEnd) {
        cumulativeError = 0;
    }

    output = kP * error + kI * cumulativeError + kD * (error - prevError);
    prevError = error;

    if (fabs(error) < minSettleError) {
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

    if (timeSpentSettled > minSettleTime) {
        return true;
    }

    return false;
}

void nova::PID::resetSystem() {
    cumulativeError = 0;
    prevError = 0;
    output = 0;
    timeSpentSettled = 0;
    timeSpentRunning = 0;
}

*/