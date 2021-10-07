// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/livewindow/LiveWindow.h>
#include <ctre/Phoenix.h>

#define LEFT_VICTOR_MOTOR_CAN_ID 1
#define RIGHT_VICTOR_MOTOR_CAN_ID 2
#define LEFT_TALON_MOTOR_CAN_ID 3
#define RIGHT_TALON_MOTOR_CAN_ID 4


class Robot : public frc::TimedRobot {

 
 public:
  Robot() {
    m_VICTORLeftMotor = new WPI_VictorSPX(LEFT_VICTOR_MOTOR_CAN_ID);
    m_TALONLeftMotor = new WPI_TalonSRX(LEFT_TALON_MOTOR_CAN_ID);
    m_VICTORRightMotor = new WPI_VictorSPX(RIGHT_VICTOR_MOTOR_CAN_ID);
    m_TALONRightMotor = new WPI_TalonSRX(RIGHT_TALON_MOTOR_CAN_ID);

  m_VICTORLeftMotor->ConfigFactoryDefault();
    m_TALONLeftMotor->ConfigFactoryDefault();
    m_VICTORRightMotor->ConfigFactoryDefault();
    m_TALONRightMotor->ConfigFactoryDefault();

m_VICTORLeftMotor->Follow(*m_TALONLeftMotor);
 m_VICTORRightMotor->Follow(*m_TALONRightMotor);

    m_DifferentialDrive = new frc::DifferentialDrive(*m_TALONLeftMotor,*m_TALONRightMotor);
    
    
   // m_robotDrive.SetExpiration(0.1);
    m_timer.Start();
  }

  void AutonomousInit() override {
    m_timer.Reset();
    m_timer.Start();
  }

  void AutonomousPeriodic() override {
    
    // Drive for 2 seconds
    // if (m_timer.Get() < 2.0) {
    //   // Drive forwards half speed
    //   m_robotDrive.ArcadeDrive(0.5, 0.0);
    // } else {
    //   // Stop robot
    //   m_robotDrive.ArcadeDrive(0.0, 0.0);
    // }
  }

  void TeleopInit() override {}

  void TeleopPeriodic() override {
    // Drive with arcade style (use right stick)
    m_DifferentialDrive->ArcadeDrive(m_stick.GetY() * SensitivityY, m_stick.GetX() * SensitivityX);
  }

  void TestInit() override {}

  void TestPeriodic() override {}

 private:
  float SensitivityX = 0.8f, SensitivityY = 0.8f;
  // Robot drive system
 
 
 
  WPI_VictorSPX *m_VICTORLeftMotor;
  WPI_TalonSRX *m_TALONLeftMotor ;
  WPI_VictorSPX *m_VICTORRightMotor;
  WPI_TalonSRX *m_TALONRightMotor ;


 
  // frc::PWMVictorSPX m_left{0};
  // frc::PWMVictorSPX m_right{1};

  frc::DifferentialDrive *m_DifferentialDrive;

  frc::Joystick m_stick{0};
  frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
  frc::Timer m_timer;
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
