// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVINGSYSTEM_H
#define DRIVINGSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../GripPipeline.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class DrivingSystem: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<SpeedController> speedControllerLeft;
	std::shared_ptr<SpeedController> speedControllerRight;
	std::shared_ptr<RobotDrive> robotDrive2;
	std::shared_ptr<ADXRS450_Gyro> gyro;
	std::shared_ptr<AnalogInput> ultrasonic;
	grip::GripPipeline *vision;

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	DrivingSystem();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	void operate();
	void rotate(double degree);
	void rotate_left(double degree);
	void drive_straight(double t, double speed = 0.6);
	void drive_dist(double dist);
	double aim_goal();
	double back_aim_goal();
	double aim_gear();
	double dis_goal();
	double get_range();
	void stop();
};

#endif
