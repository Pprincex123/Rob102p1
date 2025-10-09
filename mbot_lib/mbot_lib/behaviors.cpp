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
/**
 * Checks if the straight line path to a goal pose is obstructed such that another method of navigation must be used.
 * @param  goal The goal pose of the robot in world frame.
 * @param  pose The current pose of the robot in world frame, according to odometry. 
 * @param  ranges Vector of ray ranges.
 * @param  thetas Vector of ray angles.
 * @return  True if the straight line path to the goal pose is obstructed, false otherwise.
 *
 * NOTE: This function is not unit tested, it is simply meant to help you structure your code.
 */
bool isGoalAngleObstructed(const std::vector<float>& goal, const std::vector<float>& pose,
                           const std::vector<float>& ranges, const std::vector<float>& thetas)
{
    // *** Task: Implement this function according to the header file *** //
float setpoint = 0.5;
float dx = goal[0]-pose[0];
 float dy = goal[1]-pose[1];
float target_angle = atan(dy/dx);
float slice_size = M_PI/2;
int minIndex = findMinNonzeroDistInSlice(ranges, thetas, target_angle, slice_size);
if (ranges[minIndex] < setpoint){
    return true;
}

    // *** End student code *** //
}