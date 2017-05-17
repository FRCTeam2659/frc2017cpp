/*
 * Rotate30.cpp
 *
 *  Created on: Mar 18, 2017
 *      Author: Mark
 */

// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Rotate30.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

Rotate30::Rotate30(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::drivingSystem.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void Rotate30::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Rotate30::Execute() {
	Robot::drivingSystem->drive_dist(40-Robot::drivingSystem->get_range());
}

// Make this return true when this Command no longer needs to run execute()
bool Rotate30::IsFinished() {
    return true;
}

// Called once after isFinished returns true
void Rotate30::End() {
	Robot::drivingSystem->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Rotate30::Interrupted() {
	Robot::drivingSystem->stop();
}



