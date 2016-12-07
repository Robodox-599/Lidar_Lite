#include <AHRS.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <RobotBase.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <SPI.h>
#include <iostream>
#include <string>

class Robot: public IterativeRobot
{
private:
  LiveWindow *lw = LiveWindow::GetInstance();
  SendableChooser *chooser;
  const std::string autoNameDefault = "Default";
  const std::string autoNameCustom = "My Auto";
  std::string autoSelected;

  SerialPort *serial;

  char sendValue = {1};
  uint16_t distance;
  char buffer[1] = {0};
  char toSend[1] = {0};

  void RobotInit()
  {
    serial = new SerialPort (9600, SerialPort::kMXP);
  }

  void AutonomousInit()
  {

  }

  void AutonomousPeriodic()
  {

  }

  void TeleopInit()
  {

  }

  void getDistance()
  {
    if (serial->Read(buffer, 2))
    distance = (buffer[0] << 8) | buffer[1];
  }

  void TeleopPeriodic()
  {
    getDistance();
    SmartDashboard::PutNumber("to send:", toSend[0]);
    SmartDashboard::PutNumber("Lidar lite distance:", distance);
  }

  void TestPeriodic()
  {
    lw->Run();
  }
};

START_ROBOT_CLASS(Robot)