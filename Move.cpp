/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Donovan Sharp, Emily Pytell, Kaitlyn Strukel, Madison Demski
 * donsharp, epytell, kstrukel, mdemski
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    if (commandString == "") {
        isPass = true;
        isPickup = false;
        isSave = false;
        isQuit = false;
    }
    else if (commandString == "S" || commandString == "s") {
        isPass = false;
        isPickup = false;
        isSave = true;
        isQuit = false;
    }
    else if (commandString == "Q" || commandString == "q") {
        isPass = false;
        isPickup = false;
        isSave = false;
        isQuit = true;
    }
    else {
        stringstream ss(commandString);
        char temp1;
        char temp2;
        ss >> temp1 >> elevatorId >> temp2;
        if (temp2 == 'f') {
            ss >> targetFloor;
        }
        else if (temp2 == 'p') {
            isPass = false;
            isPickup = true;
            isSave = false;
            isQuit = false;
        }
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    
    // if move is valid
    if (isPass == true || isQuit == true || isSave == true) {
        return true;
    }
    // if move is a pickup or service move
    else if (isPass == false || isQuit == false || isSave == false) {
        // checking to see if elevator is in service
        // for both pickup and service moves
        if ((elevatorId >= 0) && (elevatorId < NUM_ELEVATORS) && (!elevators[elevatorId].isServicing())) {
            if (isPickup == true) {
                return true;
            }
            // for service moves only
            if (isPickup == false) {
                if ((targetFloor >= 0) && (targetFloor < NUM_FLOORS) && (targetFloor != elevators[elevatorId].getCurrentFloor())) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    char i0;
    i0 = pickupList[0];
    int index0 = i0 - '0';
    
    targetFloor = pickupFloor.getPersonByIndex(index0).getTargetFloor();
    ++numPeopleToPickup;
    totalSatisfaction += (MAX_ANGER - pickupFloor.getPersonByIndex(index0).getAngerLevel());
    
    peopleToPickup[0] = index0;
    if (pickupList.size() > 1) {
        for (int i = 1; i < pickupList.size(); ++i) {
            char i1;
            i1 = pickupList[i];
            int index1 = i1 - '0';
            ++numPeopleToPickup;
            totalSatisfaction += (MAX_ANGER - pickupFloor.getPersonByIndex(index1).getAngerLevel());
            peopleToPickup[i] = index1;
            if ((abs(pickupFloor.getPersonByIndex(index1).getTargetFloor() - currentFloor)) > abs(targetFloor - currentFloor)) {
                targetFloor = pickupFloor.getPersonByIndex(index1).getTargetFloor();
            }
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
    return isPass;
}

bool Move::isSaveMove() const {
    return isSave;
}

bool Move::isQuitMove() const {
    return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
