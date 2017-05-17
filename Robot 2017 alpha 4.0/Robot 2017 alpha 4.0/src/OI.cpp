// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include <Commands/AimGoal.h>
#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/Clear.h"
#include "Commands/Climb.h"
#include "Commands/Drive.h"
#include "Commands/Intake.h"
#include "Commands/Load.h"
#include "Commands/Outlet.h"
#include "Commands/Release.h"
#include "Commands/Shoot.h"
#include "Commands/Rotate30.h"
#include "Commands/AimGear.h"
#include "Commands/DistGoal.h"
#include "Commands/GotoShoot.h"

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    logitechController.reset(new Joystick(1));
    
    g7.reset(new JoystickButton(logitechController.get(), 7));
    g7->WhileHeld(new Clear());
    g6.reset(new JoystickButton(logitechController.get(), 6));
    g6->WhileHeld(new Climb());
    g5.reset(new JoystickButton(logitechController.get(), 5));
    g5->WhileHeld(new Shoot());
    g4.reset(new JoystickButton(logitechController.get(), 4));
    g4->WhileHeld(new Release());
    g3.reset(new JoystickButton(logitechController.get(), 3));
    g3->WhileHeld(new Load());
    g2.reset(new JoystickButton(logitechController.get(), 2));
    g2->WhileHeld(new Outlet());
    g1.reset(new JoystickButton(logitechController.get(), 1));
    g1->WhileHeld(new Intake());
    xboxController.reset(new Joystick(0));
    
    rB.reset(new JoystickButton(xboxController.get(), 6));
    rB->WhileHeld(new Climb());
    lB.reset(new JoystickButton(xboxController.get(), 5));
    lB->WhileHeld(new Intake());
    a.reset(new JoystickButton(xboxController.get(), 1));
    a->WhenPressed(new Aim);

    // SmartDashboard Buttons
    SmartDashboard::PutData("Shoot", new Shoot());
    SmartDashboard::PutData("Clear", new Clear());
    SmartDashboard::PutData("Load", new Load());
    SmartDashboard::PutData("Release", new Release());
    SmartDashboard::PutData("Climb", new Climb());
    SmartDashboard::PutData("Outlet", new Outlet());
    SmartDashboard::PutData("Intake", new Intake());
    SmartDashboard::PutData("Drive", new Drive());
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
    SmartDashboard::PutData("AimGoal", new Aim());
    SmartDashboard::PutData("TestRotation",new Rotate30());
    SmartDashboard::PutData("AimGear", new AimGear());
    SmartDashboard::PutData("Distance to Goal", new DistGoal());
    SmartDashboard::PutData("GotoShoot", new GotoShoot());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getxboxController() {
   return xboxController;
}

std::shared_ptr<Joystick> OI::getlogitechController() {
   return logitechController;
}

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
