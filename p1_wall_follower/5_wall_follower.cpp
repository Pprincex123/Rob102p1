/**
 * File: wall_follower.cpp
 *
 * Controls robot to follow a wall. 
 */

#include <iostream>
#include <cmath>

#include <signal.h>

#include <mbot_bridge/robot.h>

#include <mbot_lib/behaviors.h>
#include <mbot_lib/controllers.h>
#include <mbot_lib/utils.h>


bool ctrl_c_pressed;
void ctrlc(int)
{
    ctrl_c_pressed = true;
}


int main(int argc, const char *argv[])
{
    signal(SIGINT, ctrlc);
    signal(SIGTERM, ctrlc);

    // Initialize the robot.
    mbot_bridge::MBot robot;
    // Create empty vectors to store the scan data.
    std::vector<float> ranges;
    std::vector<float> thetas;

   while (true) {
    // 1. Get nearest wall info
 robot.readLidarScan(ranges, thetas);
    int min_idx = findMinNonzeroDist(ranges);
    float dist_to_wall = ranges[min_idx];
    float angle_to_wall = thetas[min_idx];

    // 2. Build a vector pointing toward the wall

    std::vector<float> v_to_wall = {cos(angle_to_wall), sin(angle_to_wall), 0.0f};
    // 3. Build a vertical axis vector (z-axis)
    std::vector<float> v_up = {0.0f, 0.0f, 1.0f};

    // 4. Cross product: gives vector perpendicular to v_to_wall (forward along the wall)
    std::vector<float> v_forward = crossProduct(v_up, v_to_wall);

    // 5. Get correction from wall follower controller
    std::vector<float> correction = computeWallFollowerCommand(ranges, thetas);

    // 6. Combine forward motion with correction
    std::vector<float> finalDrive = vectorAdd(v_forward, correction);

    // 7. Send to robot
    robot.drive(finalDrive[0], finalDrive[1], finalDrive[2]);
     if (ctrl_c_pressed) break;
            // Stop the robot.
}

     
    robot.stop();
    return 0;
    }



