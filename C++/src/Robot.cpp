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

  AHRS* navX;

  SerialPort *serial;

  char sendValue = {1};
  uint16_t distance;
  char buffer[1] = {0};
  char toSend[1] = {0};
  /*IMAQdxSession session;
  Image *frame;
  IMAQdxError imaqError;*/

  void RobotInit()
  {
    /*chooser = new SendableChooser();
    chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
    chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
    SmartDashboard::PutData("Auto Modes", chooser);*/

    //navX = new AHRS(SPI::Port::kMXP); //NavX MXP
    navX = new AHRS(SerialPort::Port::kUSB); //NavX USB

    serial = new SerialPort (9600, SerialPort::kMXP);

    /*frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
    imaqError = IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
    if(imaqError != IMAQdxErrorSuccess)
    DriverStation::ReportError("IMAQdxOpenCamera error: " + std::to_string((long)imaqError) + "\n");
    imaqError = IMAQdxConfigureGrab(session);
    if(imaqError != IMAQdxErrorSuccess)
    DriverStation::ReportError("IMAQdxConfigureGrab error: " + std::to_string((long)imaqError) + "\n");*/
  }


  /**
   * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
   * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
   * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
   * below the Gyro
   *
   * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
   * If using the SendableChooser make sure to add them to the chooser code above as well.
   */
  void AutonomousInit()
  {
    /*autoSelected = *((std::string*)chooser->GetSelected());
    //std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
    std::cout << "Auto selected: " << autoSelected << std::endl;

    if(autoSelected == autoNameCustom){
      //Custom Auto goes here
    } else {
      //Default Auto goes here
    }*/
  }

  void AutonomousPeriodic()
  {
    /*if(autoSelected == autoNameCustom){
      //Custom Auto goes here
    } else {
      //Default Auto goes here
    }*/
  }

  void TeleopInit()
  {

  }

  void getDistance()
  {
    //toSend[0] = sendValue++;

    //serial->Write(toSend, 1);
    //Wait(0.25);
    if (serial->Read(buffer, 1))
    serial->Read(buffer, 1);

    distance = buffer[0];

    /*toSend[0] = sendValue; //code to test output of RoboRio values

    serial->Write(toSend, 1);
    while(!serial->Read(buffer, 1)){}

    distance = buffer[0];
    sendValue++;
    Wait(0.5);*/

    /*toSend[0] = 30;

    serial->Write(toSend, 8);
    serial->Read(buffer, 8);

    distance = (distance << 8) | buffer[0];*/
    /*toSend[0] = 3;
    serial->Write(toSend, 8);
    serial->Read(buffer, 8);*/
  }

  void TeleopPeriodic()
  {
    printSmartDashboard();
    //RunCamera();
    getDistance();
    SmartDashboard::PutNumber("to send:", toSend[0]);
    SmartDashboard::PutNumber("Lidar lite distance:", distance);
    //SmartDashboard::PutNumber("Returned value:", distance);
    //Wait(0.1);
  }

  /*void RunCamera()
      {
      IMAQdxStartAcquisition(session);
        {
          IMAQdxGrab(session, frame, true, NULL);
          if(imaqError != IMAQdxErrorSuccess)
          {
            DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
          }
          else
          {
            imaqDrawShapeOnImage(frame, frame, { 10, 10, 100, 100 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL, 0.0f);
            CameraServer::GetInstance()->SetImage(frame);
          }
        }
      }*/

  void printSmartDashboard()
  {
    SmartDashboard::PutNumber("Gyro Value", navX->GetAngle());
  }

  void TestPeriodic()
  {
    lw->Run();
  }
};

START_ROBOT_CLASS(Robot)
