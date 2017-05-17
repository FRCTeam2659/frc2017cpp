// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutonomousCommand.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutonomousCommand::AutonomousCommand(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutonomousCommand::Initialize() {

	Timer t;
	t.Start();
	while (t.Get() < 10)
	{
		Robot::shooter->shoot(60000);
		Robot::shooter->load();
	}
	Robot::shooter->stop_shoot();
	Robot::shooter->stop_load();

	Robot::drivingSystem->drive_straight(-0.7,0.9);
	Robot::drivingSystem->rotate(30);
	Robot::drivingSystem->drive_straight(-3.5,0.9);




	/*Robot::drivingSystem->drive_straight(-5);
	Robot::drivingSystem->drive_straight(3.5);
	Robot::drivingSystem->rotate(-45);

	Robot::drivingSystem->rotate(Robot::drivingSystem->aim_gear());
	Wait(0.5);
	Robot::drivingSystem->drive_straight(-7);

	CameraServer::GetInstance()->StartAutomaticCapture("GearCamera",1).SetExposureAuto();
	*/
	/*
	Robot::drivingSystem->drive_straight(2);
	Robot::drivingSystem->rotate(120);

	Robot::drivingSystem->rotate(Robot::drivingSystem->aim_goal());
	Wait(0.5);
	Robot::drivingSystem->rotate(Robot::drivingSystem->aim_goal());
	Wait(0.5);
	Robot::drivingSystem->rotate(Robot::drivingSystem->aim_goal());
	Wait(0.5);
	*/
}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {



}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousCommand::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void AutonomousCommand::End() {
	Robot::shooter->stop_shoot();
	Robot::shooter->stop_load();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousCommand::Interrupted() {
	Robot::shooter->stop_shoot();
	Robot::shooter->stop_load();
}