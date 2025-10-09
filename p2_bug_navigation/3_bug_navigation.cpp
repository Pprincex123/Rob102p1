#include <cmath>
#include <iostream>
#include <signal.h>

#include <mbot_bridge/robot.h>

#include <mbot_lib/behaviors.h>
#include <mbot_lib/controllers.h>
#include <mbot_lib/utils.h>

using namespace std;
bool ctrl_c_pressed;
void ctrlc(int) {
    ctrl_c_pressed = true;
}


int main() {
    signal(SIGINT, ctrlc);
    signal(SIGTERM, ctrlc);

    // Initialize the robot.
    mbot_bridge::MBot robot;
    // Reset the robot odometry to zero.
    robot.resetOdometry();
  std::vector<float> ranges;
    std::vector<float> thetas;
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
    // *** End student code *** //

    // *** Task: Implement bug navigation finite state machine *** //
    
    // NOTE: You may want to change the condition in this loop.
    while (true) {
        robot.readLidarScan(ranges, thetas);
        if (isGoalAngleObstructed){
        float control =0.5;
    int min_idx = findMinNonzeroDist(ranges);
    float dist_to_wall = ranges[min_idx];
    float angle_to_wall = thetas[min_idx];
    std::vector<float> v_to_wall = {cos(angle_to_wall), sin(angle_to_wall), 0.0f};
    std::vector<float> v_up = {0.0f, 0.0f, 1.0f};
 std::vector<float> v_forward = crossProduct(v_up, v_to_wall);
    std::vector<float> correction = computeWallFollowerCommand(ranges, thetas);
    std::vector<float> finalDrive = vectorAdd(v_forward, correction);
    float vx = finalDrive[0]*correction;
    float vy = finalDrive[1]*correction;
    robot.drive(vx,, vy, finalDrive[2]);
robot.drive(DriveCommands[0], DriveCommands[1], DriveCommands[2]);
        }
vector<float> odemetry_pose =robot.readOdometry();
vector<float> drive = computeDriveToPoseCommand(goalPose, odemetry_pose);
robot.drive(drive[0], drive[1], drive[2]);
dx =goalPose[0]-odemetry_pose[0];
dy =goalPose[1]-odemetry_pose[1]
if (dx <0.1 && dy < 0.1){
    break;
}
        if(ctrl_c_pressed) break;
    }

    // *** End student code *** //

    // Stop the robot.
    robot.stop();

    // *** Task: Print out the robot's final odometry pose *** //
    cout << Final_odometry_pose[0] << ", ";
    cout << Final_odometry_pose[1] << ", ";
    cout << Final_odometry_pose[2];
    // *** End student code *** //
}
