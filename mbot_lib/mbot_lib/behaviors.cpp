/**
 * File: behaviors.cpp
 * 
 * Sources for high level functions that determine how the robot should move.
 */

#include <mbot_lib/behaviors.h>


std::vector<float> computeWallFollowerCommand(const std::vector<float>& ranges, const std::vector<float>& thetas)
{
    // *** Task: Implement this function according to the header file *** //
    float setpoint = 1.00f;
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
    float dx = goal[0]-pose[0];
    float dy = goal[1]-pose[1];
    float dt = normalizeAngle(goal[2]-pose[2]);
    float h = sqrt(pow(dx, 2) +pow(dy, 2));
    float vx = 0.5*dx/h;
    float vy = 0.5*dy/h;
float vt = 0.5*dt;
std::vector<float> vel = {vx, vy, vt};
transformVector2D(vel, pose[2]);
return vel;

    // *** End student code *** //
}

bool isGoalAngleObstructed(const std::vector<float>& goal, const std::vector<float>& pose,
                           const std::vector<float>& ranges, const std::vector<float>& thetas)
{
    // *** Task: Implement this function according to the header file *** //

    return false;

    // *** End student code *** //
}