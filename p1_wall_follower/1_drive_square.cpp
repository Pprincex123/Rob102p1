/**
 * File: drive_square.cpp
 *
 * Code to drive in a square N times.
 */

#include <iostream>
#include <cmath>

#include <mbot_bridge/robot.h>

#include <mbot_lib/utils.h>


int main(int argc, const char *argv[])
{
    // Initialize the robot.
    mbot_bridge::MBot robot;

    // Variables to be tuned.
    float vel = 0.5;
    float dt = 1.0;


    // *** Task: Write code to drive in a square three times *** //
    for (int num_square =0; num_square <=3; num_square++) {
    robot.drive(0.5, 0, 0);
    sleepFor(2);
    robot.drive(0, 0.5, 0);
    sleepFor(2);
    robot.drive(-0.5, 0, 0);
    sleepFor(2);
    robot.drive(0, -0.5, 0);
    sleepFor(2);
    }

    // *** End student code *** //

    // Stop the robot.
    std::cout << "Stopping the robot!!" << std::endl;
    robot.stop();
    return 0;
}
