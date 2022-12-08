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
  // find floor with angriest person
    int maxAnger = 0;
    int maxAngerFloor = 0;
    for (int i = 0; i < NUM_FLOORS; ++i) {
        _Floor floor = buildingState.floors[i];
        
        for (int j = 0; j < floor.numPeople; ++j) {
            _Person patron = floor.people[j];
            if (patron.angerLevel > maxAnger) {
                maxAnger = patron.angerLevel;
                maxAngerFloor = i;
            }
        }
    }
    // Check if all elevators are serviving.
    // If all elevators are serviving -- return a pass
    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        _Elevator elevator = buildingState.elevators[i];
            if ((elevator.elevatorId == 0 && elevator.isServicing) && (elevator.elevatorId == 1 && elevator.isServicing) && (elevator.elevatorId == 2 && elevator.isServicing)) {
                return "";
            }
        
        
        for (int j = 0; j < NUM_FLOORS; ++j) {
            _Floor floor = buildingState.floors[j];
            string floorIndex = "";
            string elevatorIndex = "";
            
            
            // If there are no serviving elevators going to the floor with the angriest person, return a servicing move to go to that floor. -- return "eifj"
            
            if ((elevator.elevatorId == 0 || elevator.elevatorId == 1 || elevator.elevatorId == 2) && !elevator.isServicing && elevator.targetFloor != maxAngerFloor) {
                
                elevator.targetFloor = maxAngerFloor;
                floor.floorNum = maxAngerFloor;
                floorIndex = to_string(maxAngerFloor);
                elevatorIndex = to_string(elevator.elevatorId);
                return "e" + elevatorIndex + "f" + floorIndex;
            }
            // If an elevator is already going to the floor with the angriest person, return a pass
            else if ((elevator.elevatorId == 0 || elevator.elevatorId == 1 || elevator.elevatorId == 2) && elevator.isServicing && elevator.targetFloor == maxAngerFloor) {
                
                return "";
            }
            //Check if a non-serviving elevator is at its target floor. If it is, and there are people on that floor, return a pickup -- return "eip"
            
            else if ((elevator.elevatorId == 0 || elevator.elevatorId == 1 || elevator.elevatorId == 2) && !elevator.isServicing && elevator.currentFloor == elevator.targetFloor && floor.numPeople > 0) {
                
                elevatorIndex = to_string(elevator.elevatorId);
                return "e" + elevatorIndex + "p";
            }
        }
    }
    
    return "";
}


string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
   
    int maxAnger = 0;
    int maxAngerFloor = 0;
    bool goUp;
    string pickupList = "";
    string str = "";
    
    for (int i = 0; i < NUM_FLOORS; ++i) {
      _Floor floor = buildingState.floors[i];
        
            // Find the angriest person on that floor & add them to pickup list
            for (int j = 0; j < floor.numPeople; ++j) {
                _Person patron = floor.people[j];
                if (patron.angerLevel > maxAnger) {
                    maxAnger = patron.angerLevel;
                    maxAngerFloor = i;
                    pickupList += maxAnger;
                    
                    
                    // If they want to go up, var goUp = true;
                    if (maxAnger && floor.hasUpRequest) {
                         goUp = true;
            
                    }
                    // if down, goUp = false;
                    else if (maxAnger && floor.hasDownRequest) {
                        goUp = false;
                    }
                }
                // If the floor only has people going up, goUp = true (if down, goUp = false;)
                // Determines the direction the elevator will travel in
            }
        }

    //finally, return string representing pickuplist
    
    return pickupList;
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







