/**
 * File: drive_star.cpp
 *
 * Code to drive in a five-pointed star shape without turning. 
 */

#include <iostream>
#include <cmath>

#include <signal.h>

#include <mbot_bridge/robot.h>
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

    // *** Task: Drive in a five pointed star *** //
double degree1 = 0.0;
double radian1 = degree1 *(M_PI/180);
double degree2 = -144.0;
double radian2 = degree2 *(M_PI/180);
double degree3 = 72.0;
double radian3 = degree3 *(M_PI/180);
double degree4 = -72.0;
double radian4 = degree4 *(M_PI/180);
double degree5 = 144.0;
double radian5 = degree5 *(M_PI/180);

std::vector<double> radians = {radian1, radian2, radian3, radian4, radian5};
for (int i = 0; i < radians.size(); i++) {
    std::vector<double> ray = rayConversionVector(radians[i]); 
    robot.drive(ray[0], ray[1], ray[2]);
    sleepfor(2); // time to move before the next ray
}

    // *** End student code *** //

    // Stop the robot.
    robot.stop();
    return 0;
}