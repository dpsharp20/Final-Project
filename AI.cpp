/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>
#include <string>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

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
        if (elevator.isServicing) {
            return "";
        }
    }
    
    //Check if a non-serviving elevator is at its target floor. If it is, and there are people on that floor, return a pickup -- return "eip"
    
    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        _Elevator elevator = buildingState.elevators[i];
        
        for (int j = 0; j < NUM_FLOORS; j++) {
        _Floor floor = buildingState.floors[j];
            if (!elevator.isServicing && elevator.currentFloor == elevator.targetFloor && floor.numPeople > 0) {
                return "eip";
            }
        }
    }
    // If there are no serviving elevators going to the floor with the angriest person, return a servicing move to go to that floor. -- return "eifj"
    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        _Elevator elevator = buildingState.elevators[i];
        
        for (int j = 0; j < NUM_FLOORS; j++) {
            _Floor floor = buildingState.floors[j];
            
            if (!elevator.isServicing && elevator.targetFloor != maxAngerFloor) {
                elevator.targetFloor = maxAngerFloor;
                return "eifj";
            }
            // If an elevator is already going to the floor with the angriest person, return a pass
            else if (!elevator.isServicing && elevator.targetFloor == maxAngerFloor) {
                return "";
            }
        }
    }

    return "";
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
   
    int maxAnger = 0;
    int maxAngerFloor = 0;
    bool goUp = false;
    // Check if the floor to pick up has both up and down requests
    for (int i = 0; i < NUM_FLOORS; ++i) {
      _Floor floor = buildingState.floors[i];
        if (floor.hasUpRequest == true && floor.hasDownRequest == true) {
            
            // Find the angriest person on that floor
            for (int j = 0; j < floor.numPeople; ++j) {
                _Person patron = floor.people[j];
                if (patron.angerLevel > maxAnger) {
                    maxAnger = patron.angerLevel;
                    maxAngerFloor = i;
                    
                    if (maxAnger && floor.hasUpRequest) {
                        bool goUp = true;
                        
                    }
                }
            }
        }
    }
    
  
    
    // If they want to go up, var goUp = true; if down, goUp = false;
    
    // If the floor only has people going up, goUp = true (if down, goUp = false;)
    // Determines the direction the elevator will travel in
    
    // FOr each person on the floor who wants to go in that direction, check to see if their target floor is full. If not -- add to pickup list
    
    //finally, return string representing pickuplist
    
    return "";
}
