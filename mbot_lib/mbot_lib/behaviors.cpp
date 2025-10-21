/**
 * File: behaviors.cpp
 * 
 * Sources for high level functions that determine how the robot should move.
 */

#include <mbot_lib/behaviors.h>
#include <vector>
#include <iostream>

std::vector<float> computeWallFollowerCommand(const std::vector<float>& ranges, const std::vector<float>& thetas)
{
    // --- Parameters ---
    float setpoint = 0.5f;   // Desired distance from wall
    // --- Step 1: Find the nearest wall direction ---
    int MinIndex = findMinNonzeroDist(ranges);
    float MinDist = ranges[MinIndex];
    float Angle = thetas[MinIndex];
    // --- Step 2: Compute distance correction using P-control ---
    float correction_mag = pControl(MinDist, setpoint, -0.5f);
    // --- Step 3: Compute direction vector toward the wall ---
    std::vector<float> dir_to_wall = rayConversionVector(Angle); // unit vector toward wall
    // --- Step 4: Turn that into a correction vector ---
    std::vector<float> correction = { correction_mag * dir_to_wall[0], correction_mag * dir_to_wall[1], 0.0f };
    // --- Step 5: Compute forward direction along wall ---
    std::vector<float> v_to_wall = {cos(Angle), sin(Angle), 0.0f};
    std::vector<float> v_up = {0.0f, 0.0f, 1.0f};
    std::vector<float> v_forward = crossProduct(v_up, v_to_wall);
    // --- Step 6: Combine forward drive and wall correction ---
    std::vector<float> finalDrive = vectorAdd(v_forward, correction);

    return finalDrive;
}


std::vector<float> computeDriveToPoseCommand(const std::vector<float>& goal, const std::vector<float>& pose)
{   
    // *** Task: Implement this function according to the header file *** //
    float dx = goal[0]-pose[0];
    float dy = goal[1]-pose[1];
    float dt = normalizeAngle(goal[2]-pose[2]);

    // std::cout << "angle: " << dt << "\n";

    float h = sqrt(dx*dx + dy*dy);

    float vx = 0.4 * dx/h;
    float vy = 0.4 * dy/h;
    float vt = 1.5 * dt;

    if(sqrt(dt*dt) < M_PI/22) dt = 0;

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
    float setpoint = 0.25;
    float dx = goal[0]-pose[0];
    float dy = goal[1]-pose[1];

    float TanAngle = atan(dy/dx);
    float target_angle = normalizeAngle(TanAngle-pose[2]);
    float slice_size = M_PI/2;

    int minIndex = findMinNonzeroDistInSlice(ranges, thetas, target_angle, slice_size);
    return ranges[minIndex] < setpoint;

    // *** End student code *** //
}