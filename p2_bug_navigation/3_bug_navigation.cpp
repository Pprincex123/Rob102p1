#include <iostream>
#include <cmath>
#include <mbot_bridge/robot.h>
#include <signal.h>
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
        vector<float> odometry_pose = robot.readOdometry();
        float control = 0.25;

        if (isGoalAngleObstructed(goalPose, odometry_pose, ranges, thetas)) {
           vector <float> v_forward =computeWallFollowerCommand(ranges, thetas);
            robot.drive(control*v_forward[0], control*v_forward[1], v_forward[2]);
        } else {
            vector<float> drive = computeDriveToPoseCommand(goalPose, odometry_pose);
            robot.drive(control*drive[0], control*drive[1], drive[2]);
        }

        float dx = goalPose[0] - odometry_pose[0];
        float dy = goalPose[1] - odometry_pose[1];
        float d = 0.1;
        cout << dx << "\n";
        cout << dy;
        if (dx < d && dy < d){
            break;
        }

        if(ctrl_c_pressed) break;
    }

    // *** End student code *** //
    robot.stop();
    // Stop the robot.

    // *** Task: Print out the robot's final odometry pose *** //
    cout << "final odemetry pose: ";
    vector<float> Final_odometry_pose = robot.readOdometry();
    cout << Final_odometry_pose[0] << ", ";
    cout << Final_odometry_pose[1] << ", ";
    cout << Final_odometry_pose[2];
    // *** End student code *** //

    return 0;
}
