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
        odometry_pose = robot.readOdometry();

        if (isGoalAngleObstructed(goalPose, odometry_pose, ranges, thetas)) {
            int min_idx = findMinNonzeroDist(ranges);
            float angle_to_wall = thetas[min_idx];
            vector<float> v_to_wall = {cos(angle_to_wall), sin(angle_to_wall), 0.0f};
            vector<float> v_up = {0.0f, 0.0f, 1.0f};
            vector<float> v_forward = crossProduct(v_up, v_to_wall);

            vector<float> correction = computeWallFollowerCommand(ranges, thetas);
            vector<float> finalDrive = vectorAdd(v_forward, correction);

            robot.drive(finalDrive[0], finalDrive[1], finalDrive[2]);
        } else {
            vector<float> drive = computeDriveToPoseCommand(goalPose, odometry_pose);
            robot.drive(drive[0], drive[1], drive[2]);
        }

        float dx = goalPose[0] - odometry_pose[0];
        float dy = goalPose[1] - odometry_pose[1];
        float d = 0.05;
        }
dx =goalPose[0]-odemetry_pose[0];
dy =goalPose[1]-odemetry_pose[1]
float d = 0.005;
if (dx < d && dy < d){
    break;
}
        if(ctrl_c_pressed) break;
    }

    // *** End student code *** //

    // Stop the robot.
    robot.stop();

    // *** Task: Print out the robot's final odometry pose *** //
    cout << "final odemetry pose: "
    cout << Final_odometry_pose[0] << ", ";
    cout << Final_odometry_pose[1] << ", ";
    cout << Final_odometry_pose[2];
    // *** End student code *** //

