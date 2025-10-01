/**
 * File: behaviors.cpp
 * 
 * Sources for high level functions that determine how the robot should move.
 */

#include <mbot_lib/behaviors.h>


std::vector<float> computeWallFollowerCommand(const std::vector<float>& ranges, const std::vector<float>& thetas)
{
    // *** Task: Implement this function according to the header file *** //
    float setpoint = 0.5f;
int MinIndex = findMinNonzeroDist(ranges);
float MinDist = ranges[MinIndex];
float Angle = thetas[MinIndex];
float correction = pControl(MinDist, setpoint, -0.5);
std::vector<float>direction = rayConversionVector(Angle);
float vx = correction * direction[0];
float vy = correction * direction[1];
float wtheta = 0;
return {vx, vy, wtheta};

    // *** End student code *** //
}

std::vector<float> computeDriveToPoseCommand(const std::vector<float>& goal, const std::vector<float>& pose)
{   
    // *** Task: Implement this function according to the header file *** //

    return std::vector<float>();

    // *** End student code *** //
}

bool isGoalAngleObstructed(const std::vector<float>& goal, const std::vector<float>& pose,
                           const std::vector<float>& ranges, const std::vector<float>& thetas)
{
    // *** Task: Implement this function according to the header file *** //

    return false;

    // *** End student code *** //
}