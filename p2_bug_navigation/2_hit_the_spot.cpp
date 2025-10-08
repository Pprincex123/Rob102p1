#include <iostream>
#include <cmath>

#include <mbot_bridge/robot.h>
#include <signal.h>
#include <mbot_lib/behaviors.h>
#include <mbot_lib/controllers.h>
#include <mbot_lib/utils.h>
using namespace std;

bool ctrl_c_pressed;
void ctrlc(int)
{
    ctrl_c_pressed = true;
}


int main(){
signal(SIGINT, ctrlc);
    // Initialize the robot.
    mbot_bridge::MBot robot;
    // Reset the robot odometry to zero at the beginning of the run.
    robot.resetOdometry();
    // *** Task: Get the goal pose (x, y, theta) from the user *** //
  vector<float> goalPose;
  float x;
  float y;
  float theta;
  cout << "What is your x? ";
  cin >> x;
  goalPose.push_back(x);
  cout << "What is your y? ";
  cin >> y;
goalPose.push_back(y);
  cout << "What is your theta? ";
  cin >> theta;
  goalPose.push_back(theta);
    while (true) {
        
        // *** Task: Implement hit the spot *** //
vector<float> odemetry_pose =robot.readOdometry();
vector<float> drive = computeDriveToPoseCommand(goalPose, odemetry_pose);
robot.drive(drive[0], drive[1], drive[2]);

        // *** End student code *** //
        
        if (ctrl_c_pressed) break;
    }

    // Stop the robot before exiting.
    robot.stop();

    // *** Task: Print out the robot's final odometry pose *** //
    vector<float>Final_odometry_pose = robot.readOdometry();
    cout << Final_odometry_pose[0] << ", ";
    cout << Final_odometry_pose[1] << ", ";
    cout << Final_odometry_pose[2];
    // *** End student code *** //

    return 0;
}
