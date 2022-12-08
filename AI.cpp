/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Kaitlyn Strukel,
 * kstrukel
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>
#include <string>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core
bool upOrDown(_Elevator currentFloor, _Elevator targetFloor,
              const BuildingState& buildingState) {
    bool goingUp = false;
    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        _Elevator elevator = buildingState.elevators[i];
        int floorDifference;
        floorDifference = elevator.targetFloor - elevator.currentFloor;
        if (floorDifference < 0) { //could be an error if target floor equals current floor
            goingUp = true;
        }
        else if (floorDifference > 0) {
            goingUp = false;
        }
        else {
            EXIT_FAILURE;
        }
    }
    return goingUp;
}


string getAIMoveString(const BuildingState& buildingState) {
  
    int maxAnger = 0;
    int maxAngerFloor = 0;
    string floorIndex = "";
    string elevatorIndex = "";
    
    // find floor with angriest person
    for (int i = 0; i < NUM_FLOORS; i++) {
        _Floor floor = buildingState.floors[i];
        
        for (int j = 0; j < floor.numPeople; j++) {
            _Person patron = floor.people[j];
            if (patron.angerLevel > maxAnger) {
                maxAnger = patron.angerLevel;
                maxAngerFloor = i;
            }
        }
    }
    
    // Check if all elevators are serviving.
    // If all elevators are serviving -- return a pass
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        _Elevator elevator = buildingState.elevators[i];
        if ((elevator.elevatorId == 0 && elevator.isServicing) && (elevator.elevatorId == 1 && elevator.isServicing) && (elevator.elevatorId == 2 && elevator.isServicing)) {
            return "";
        }
    }
    
    //Check if a non-serviving elevator has people on current floor, return a pickup -- return "eip"

    for (int i = 0; i < NUM_ELEVATORS; i++) {
        _Elevator elevator = buildingState.elevators[i];
        
        if (buildingState.floors[elevator.currentFloor].numPeople > 0 && !elevator.isServicing) {
            if (elevator.elevatorId == 0) {
                elevatorIndex = to_string(elevator.elevatorId);
                return "e" + elevatorIndex + "p";
            }
            else if (elevator.elevatorId == 1) {
                elevatorIndex = to_string(elevator.elevatorId);
                return "e" + elevatorIndex + "p";
            }
            else if (elevator.elevatorId == 2) {
                elevatorIndex = to_string(elevator.elevatorId);
                return "e" + elevatorIndex + "p";
            }
        }
    }
   
    // Send an elevator to maxAngerFloor
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        _Elevator elevator = buildingState.elevators[i];
        
        if ((elevator.elevatorId == 0 || elevator.elevatorId == 1 || elevator.elevatorId == 2) && elevator.currentFloor != maxAngerFloor) {
            if (!elevator.isServicing) {
                elevatorIndex = to_string(elevator.elevatorId);
                floorIndex = to_string(maxAngerFloor);
                
                return "e" + elevatorIndex + "f" + floorIndex;
            }
            
        }
    }
        
    
    for (int i = 0; i < NUM_FLOORS; i++) {
        _Floor floor = buildingState.floors[i];
        
        for (int j = 0; j < floor.numPeople; j++) {
            _Person patron = floor.people[j];
            if (patron.angerLevel > maxAnger) {
                maxAnger = patron.angerLevel;
                maxAngerFloor = i;
            }
        }
    }
    
    return "";
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
    
    string finalString;
    string str = "";
    int currentFloor = 0;
    int targetFloor = 0;
        
    if(floorToPickup.getHasDownRequest()) {
        for(int i = 0; i < floorToPickup.getNumPeople(); i++) {
            currentFloor = floorToPickup.getPersonByIndex(i).getCurrentFloor();
            targetFloor = floorToPickup.getPersonByIndex(i).getTargetFloor();
            if (targetFloor < currentFloor) {
                finalString += to_string(i);
            }
        }
        return finalString;
    }
        
    if(floorToPickup.getHasUpRequest()) {
        for(int i = 0; i < floorToPickup.getNumPeople(); i++) {
           currentFloor = floorToPickup.getPersonByIndex(i).getCurrentFloor();
           targetFloor = floorToPickup.getPersonByIndex(i).getTargetFloor();
            if (targetFloor > currentFloor) {
                finalString += to_string(i);
            }
        }
        return finalString;
    }

        
    return finalString;
}





// My idea for pickup (not 100%)
string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
    string finalString;
    
    if(floorToPickup.getHasDownRequest()) {
        for(int i = 0; i < floorToPickup.getNumPeople(); i++) {
            if(finalString.length() < ELEVATOR_CAPACITY) {
                if((floorToPickup.getPersonByIndex(i).getTargetFloor() < buildingState.elevators[move.getElevatorId()].currentFloor)){
                    if(floorToPickup.getPersonByIndex(i).getTargetFloor() < floorToPickup.getPersonByIndex(i).getCurrentFloor()){
                        finalString.append(to_string(i));
                    }
                }
            }
        }
        return finalString;
    }
    
    
    
    if(floorToPickup.getHasUpRequest()) {
        for(int i = 0; i < floorToPickup.getNumPeople(); i++) {
            if(finalString.length() < ELEVATOR_CAPACITY) {
                if((floorToPickup.getPersonByIndex(i).getTargetFloor() > buildingState.elevators[move.getElevatorId()].currentFloor)){
                    if(floorToPickup.getPersonByIndex(i).getTargetFloor() > floorToPickup.getPersonByIndex(i).getCurrentFloor()) {
                        finalString.append(to_string(i));
                    }
                    
                }
            }
            
        }
        return finalString;
    }
    
    return finalString;
}







