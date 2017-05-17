// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<SpeedController> RobotMap::drivingSystemSpeedControllerLeft;
std::shared_ptr<SpeedController> RobotMap::drivingSystemSpeedControllerRight;
std::shared_ptr<RobotDrive> RobotMap::drivingSystemRobotDrive2;
std::shared_ptr<ADXRS450_Gyro> RobotMap::drivingSystemAnalogGyro1;
std::shared_ptr<AnalogInput> RobotMap::drivingSystemUltrasonic;
std::shared_ptr<SpeedController> RobotMap::climberSpeedController;
std::shared_ptr<SpeedController> RobotMap::intakeSystemSpeedController;
std::shared_ptr<Encoder> RobotMap::shooterQuadratureEncoder;
std::shared_ptr<SpeedController> RobotMap::shooterSpeedControllerShooter;
std::shared_ptr<PIDController> RobotMap::shooterPIDController;
std::shared_ptr<SpeedController> RobotMap::shooterSpeedControllerLoader;
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    drivingSystemSpeedControllerLeft.reset(new Talon(0));
    lw->AddActuator("DrivingSystem", "Speed Controller Left", std::static_pointer_cast<Talon>(drivingSystemSpeedControllerLeft));
    
    drivingSystemSpeedControllerRight.reset(new Talon(1));
    lw->AddActuator("DrivingSystem", "Speed Controller Right", std::static_pointer_cast<Talon>(drivingSystemSpeedControllerRight));
    
    drivingSystemRobotDrive2.reset(new RobotDrive(drivingSystemSpeedControllerLeft, drivingSystemSpeedControllerRight));
    
    drivingSystemRobotDrive2->SetSafetyEnabled(true);
        drivingSystemRobotDrive2->SetExpiration(0.1);
        drivingSystemRobotDrive2->SetSensitivity(0.5);
        drivingSystemRobotDrive2->SetMaxOutput(1.0);
//        drivingSystemRobotDrive2->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
//        drivingSystemRobotDrive2->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
    drivingSystemAnalogGyro1.reset(new ADXRS450_Gyro());
    lw->AddSensor("DrivingSystem", "AnalogGyro 1", drivingSystemAnalogGyro1);
    drivingSystemUltrasonic.reset(new AnalogInput(0));
//    lw->AddSensor("DrivingSystem", "Ultrasonic", drivingSystemUltrasonic);

    climberSpeedController.reset(new Talon(2));
    climberSpeedController->SetInverted(true);
    lw->AddActuator("Climber", "Speed Controller", std::static_pointer_cast<Talon>(climberSpeedController));
    
    intakeSystemSpeedController.reset(new Talon(3));
    lw->AddActuator("IntakeSystem", "Speed Controller", std::static_pointer_cast<Talon>(intakeSystemSpeedController));
    
    shooterQuadratureEncoder.reset(new Encoder(0, 1, false, Encoder::k1X));
    lw->AddSensor("Shooter", "Quadrature Encoder", shooterQuadratureEncoder);
    shooterQuadratureEncoder->SetDistancePerPulse(1.0);
    shooterQuadratureEncoder->SetPIDSourceType(PIDSourceType::kRate);
    shooterSpeedControllerShooter.reset(new Talon(4));
    shooterSpeedControllerShooter->SetInverted(true);
    lw->AddActuator("Shooter", "Speed Controller Shooter", std::static_pointer_cast<Talon>(shooterSpeedControllerShooter));
    
    shooterPIDController.reset(new PIDController(6.0e-8, 0.0, 9.0e-5, shooterQuadratureEncoder.get(), shooterSpeedControllerShooter.get()));
    lw->AddActuator("Shooter", "PID Controller", shooterPIDController);
    shooterPIDController->SetContinuous(false); shooterPIDController->SetAbsoluteTolerance(1000);
        shooterPIDController->SetOutputRange(-1.0, 1.0);
    shooterSpeedControllerLoader.reset(new Talon(5));
    shooterSpeedControllerLoader->SetInverted(true);
    lw->AddActuator("Shooter", "Speed Controller Loader", std::static_pointer_cast<Talon>(shooterSpeedControllerLoader));
    

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
