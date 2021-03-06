// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "DrivingSystem.h"
#include "../RobotMap.h"
#include "../Commands/Drive.h"

#include "SmartDashboard/SmartDashboard.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

DrivingSystem::DrivingSystem() : Subsystem("DrivingSystem") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    speedControllerLeft = RobotMap::drivingSystemSpeedControllerLeft;
    speedControllerRight = RobotMap::drivingSystemSpeedControllerRight;
    robotDrive2 = RobotMap::drivingSystemRobotDrive2;
    gyro = RobotMap::drivingSystemAnalogGyro1;
    ultrasonic = RobotMap::drivingSystemUltrasonic;
    vision = new grip::GripPipeline();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

}

void DrivingSystem::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

	SetDefaultCommand(new Drive());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void DrivingSystem::operate()
{
	robotDrive2->TankDrive(-Robot::oi->getxboxController()->GetRawAxis(1),
							-Robot::oi->getxboxController()->GetRawAxis(5),
							true);
}

void DrivingSystem::rotate(double degree)
{

	double c =	gyro->GetAngle();
	double e;
	Timer t;
	t.Start();

	e=c+degree;
	SmartDashboard::PutNumber("c", c);
	SmartDashboard::PutNumber("e", e);
	if (degree>=0)
		while(gyro->GetAngle() < e)
		{
			robotDrive2->TankDrive(0.4, -0.4);
			SmartDashboard::PutNumber("gyro read", gyro->GetAngle());
			if (t.Get() > 5)
				break;
		}
	else
		while(gyro->GetAngle() > e)
		{
			robotDrive2->TankDrive(-0.5, 0.5);
			SmartDashboard::PutNumber("gyro read", gyro->GetAngle());
			if (t.Get() > 5)
				break;
		}

	this->stop();

}

void DrivingSystem::rotate_left(double degree)
{
	double c= gyro->GetAngle();
	double e = c + degree;
	if (degree>=0)
	{
		while (gyro->GetAngle() < e)
		{
			robotDrive2->TankDrive(0.5,0);
		}
	}
	else
	{
		while (gyro->GetAngle() > e)
		{
			robotDrive2->TankDrive(-0.5, 0);
		}
	}

	this->stop();
}

void DrivingSystem::stop()
{
	robotDrive2->TankDrive(0.0,0.0,true);
}

double DrivingSystem::aim_goal()
{

//	CameraServer::GetInstance()->StartAutomaticCapture("AimingCamera",0).SetExposureManual(100);
	cs::CvSink sink =CameraServer::GetInstance()->GetVideo("AimingCamera");
	cv::Mat frame;
	sink.GrabFrameNoTimeout(frame);
	vision->Process(frame);
	std::vector<std::vector<cv::Point> >*  results = vision->GetFilterContoursOutput();


	double centerX, centerY;
	std::vector<cv::Point> centers;
	if (results->empty())
		return 0;
	else
	{
		for (int i = 0; i < results->size(); i++) {
			  cv::Rect r = cv::boundingRect((*results)[i]);
			  centerX = r.x + r.width / 2;
			  centerY = r.y + r.height / 2;
			  centers.push_back(cv::Point(centerX, centerY));
			}
	}

	SmartDashboard::PutNumber("goal_center", centers[0].x);

	centerX=centerY=0;
	for (int i=0; i < centers.size(); i++)
	{
		centerX+=centers[i].x;
		centerY+=centers[i].y;
	}
	centerX/=centers.size();
	centerY/=centers.size();


	double angle;
	if (centerX <= 320)
	{
		angle = atan((320-centerX)/320*tan(3.1415926/6))/3.1415926*180;
		return -angle;
	}
	else
	{
		angle = atan((centerX-320)/320*tan(3.1415926/6))/3.1415926*180;
		angle +=1.5;
		return angle;
	}

}

double DrivingSystem::aim_gear()
{
//	 	CameraServer::GetInstance()->StartAutomaticCapture("GearCamera", 1).SetExposureManual(50);
		cs::CvSink sink = CameraServer::GetInstance()->GetVideo("GearCamera");

		cv::Mat frame;
		sink.GrabFrameNoTimeout(frame);
		vision->Process(frame);
		std::vector<std::vector<cv::Point> >*  results = vision->GetFilterContoursOutput();

		double centerX, centerY;
			std::vector<cv::Point> centers;
			std::vector<cv::Rect> r;
			if (results->empty())
				return 0;
			else
			{
				for (int i = 0; i < results->size(); i++)
					r.push_back(cv::boundingRect((*results)[i]));
				SmartDashboard::PutNumber("r1",r[0].x);
				SmartDashboard::PutNumber("r2", r[1].x);
				for (int i = 0; i < results->size(); i++) {
					  centerX = r[i].x + r[i].width / 2;
					  centerY = r[i].y + r[i].height / 2;
					  centers.push_back(cv::Point(centerX, centerY));
					}
			}
			SmartDashboard::PutNumber("center1", centers[0].x);
			SmartDashboard::PutNumber("center2", centers[1].x);

			double mid=0;
			double arv_width=0;
			for (int i=0; i < centers.size();i++)
			{
				mid+=centers[i].x;
				arv_width+=r[i].width;
			}
			mid/=centers.size();
			arv_width/=centers.size();
			SmartDashboard::PutNumber("size", centers.size());
			SmartDashboard::PutNumber("mid", mid);
			SmartDashboard::PutNumber("arv_width", arv_width);

			double target = mid+arv_width*5/2;
			double angle;
				if (target <= 80)
				{
					angle = atan((80-target)/80*tan(3.1415926/6))/3.1415926*180;
					SmartDashboard::PutNumber("angle", -angle);
					return -angle;
				}
				else
				{
					angle = atan((target-80)/80*tan(3.1415926/6))/3.1415926*180;
					SmartDashboard::PutNumber("angle", angle);
					return angle;
				}





}

double DrivingSystem::dis_goal()
{
	SmartDashboard::PutBoolean("enters dis_goal", true);
//		CameraServer::GetInstance()->StartAutomaticCapture("GearCamera", 1).SetExposureManual(50);
	cs::CvSink sink =CameraServer::GetInstance()->GetVideo("GearCamera");
			cv::Mat frame;
			sink.GrabFrameNoTimeout(frame);
			vision->Process(frame);
			std::vector<std::vector<cv::Point> >*  results = vision->GetFilterContoursOutput();
			double centerX, centerY;
				std::vector<cv::Point> centers;
				std::vector<cv::Rect> r;
				if (results->empty())
					return 0;
				else
				{
					for (int i = 0; i < results->size(); i++)
						r.push_back(cv::boundingRect((*results)[i]));
					for (int i = 0; i < results->size(); i++)
					{
						centerX = r[i].x + r[i].width / 2;
						centerY = r[i].y + r[i].height / 2;
						centers.push_back(cv::Point(centerX, centerY));
					}
				}
				double h_max=120;
				for (int i=0; i<r.size(); i++)
				{
					if (r[i].y < h_max)
						h_max = r[i].y;
				}
				SmartDashboard::PutNumber("h_max", h_max);

				double angle;

				angle = atan((60-h_max)/60*tan(3.1415926/8))/3.1415926*180;
				angle+=25.59;
				SmartDashboard::PutNumber("get_dis angle", angle);
				//double dist = 64.5*2.54/100/tan(angle);
				double dist = 64.5/tan(angle/180*3.1415926);
				SmartDashboard::PutNumber("distance in in'", dist );
				return dist;

}

void DrivingSystem::drive_straight(double t, double speed)
{
	double c = gyro->GetAngle();
	const double k=0.01;
	double d;
	Timer t_1;
	t_1.Start();
	SmartDashboard::PutBoolean("t<0", false);
	SmartDashboard::PutBoolean("t>=0", false);
	if (t >= 0)
	{
		while (t_1.Get()<t)
		{
			d = gyro->GetAngle()-c;
			robotDrive2->TankDrive(speed-k*d,speed+k*d);
			SmartDashboard::PutBoolean("t>=0", true);
		}
	}
	else
	{
		t = -t;
		while(t_1.Get() < t)
		{
			d = gyro->GetAngle()-c;
			robotDrive2->TankDrive(-speed-k*d, -speed+k*d);
			SmartDashboard::PutBoolean("t<0", true);
		}
	}
	stop();

}

double DrivingSystem::get_range()
{
	double v = ultrasonic->GetVoltage();
	double dist_mm = v/0.977*1000;
	double dist_in = dist_mm/25.4;
	return dist_in;
}

void DrivingSystem::drive_dist(double dist)
{
	double e = get_range() + dist;
	Timer t;
	double c = gyro->GetAngle();
	const double k=0.01;
	double d;
	t.Start();
	if (dist >= 0)
	{
		while (get_range() < e)
		{
			d = gyro->GetAngle()-c;
			robotDrive2->TankDrive(0.5-k*d,0.5+k*d);
			if (t.Get()>7)
				break;
		}
	}
	else
	{
		while (get_range() > e)
		{
			d = gyro->GetAngle()-c;
			robotDrive2->TankDrive(-0.5-k*d, -0.5+k*d);
			if (t.Get() > 7)
				break;
		}
	}
	stop();
}

double DrivingSystem::back_aim_goal()
{
	cs::CvSink sink =CameraServer::GetInstance()->GetVideo("GearCamera");
		cv::Mat frame;
		sink.GrabFrameNoTimeout(frame);
		vision->Process(frame);
		std::vector<std::vector<cv::Point> >*  results = vision->GetFilterContoursOutput();


		double centerX, centerY;
		std::vector<cv::Point> centers;
		if (results->empty())
			return 0;
		else
		{
			for (int i = 0; i < results->size(); i++) {
				  cv::Rect r = cv::boundingRect((*results)[i]);
				  centerX = r.x + r.width / 2;
				  centerY = r.y + r.height / 2;
				  centers.push_back(cv::Point(centerX, centerY));
				}
		}

		SmartDashboard::PutNumber("goal_center", centers[0].x);

		centerX=centerY=0;
		for (int i=0; i < centers.size(); i++)
		{
			centerX+=centers[i].x;
			centerY+=centers[i].y;
		}
		centerX/=centers.size();
		centerY/=centers.size();


		double angle;
		if (centerX <= 80)
		{
			angle = atan((80-centerX)/80*tan(3.1415926/6))/3.1415926*180;
			angle +=1.5;
			return -angle;
		}
		else
		{
			angle = atan((centerX-80)/80*tan(3.1415926/6))/3.1415926*180;
			angle +=1.5;
			return angle;
		}
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

