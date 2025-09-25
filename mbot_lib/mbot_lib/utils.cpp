/**
 * File: utils.cpp
 * 
 * Sources for functions for handling common tasks like working with geometry and interpreting lidar data.
 */

#include <mbot_lib/utils.h>


std::vector<float> rayConversionCartesian(float dist, float angle) 
{
    // *** Task: Implement this function according to the header file *** //
float x = dist * std::cos(angle);
float y = dist * std::sin(angle);
std::vector<float> result;
result.push_back(x);
result.push_back(y);
return result;
    // *** End student code *** //
}

std::vector<float> rayConversionVector(float angle) 
{
float x = std::cos(angle);
float y = std::sin(angle);
float z = 0.0f;
std::vector<float> result;
result.push_back(x);
result.push_back(y);
result.push_back(z);
return result;
}

int findMinDist(const std::vector<float>& ranges)
{
    // *** Task: Implement this function according to the header file *** //
    if (ranges.empty()) return -1;
    float minVal = ranges[0];
    int minIndex = 0;
    for (int i = 1; i < ranges.size(); i++) {
        float val = ranges[i];
        if (val < minVal) {
            minVal = val;
            minIndex = i;
        }
    }
    return minIndex;
    // *** End student code *** //
}

int findMinNonzeroDist(const std::vector<float>& ranges)
{
    // *** Task: Implement this function according to the header file *** //
if (ranges.empty()) return -1;
    float minVal = 100000;
    int minIndex = -1;
    for (int i = 0; i < ranges.size(); i++) {
        float val = ranges[i];
        if (val < minVal && val > 0.00f) {
            minVal = val;
            minIndex = i;
        }
    }
    return minIndex;
    }

    
    // *** End student code *** //

std::vector<float> vectorAdd(const std::vector<float>& v1, const std::vector<float>& v2) 
{
    // *** Task: Implement this function according to the header file *** //
{
  std::vector<float> result(v1.size());
    for (int i = 0; i < v1.size(); i++) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

    return std::vector<float>();

    // *** End student code *** //
}

std::vector<float> crossProduct(const std::vector<float>& v1, const std::vector<float>& v2) {

    // *** Task: Implement this function according to the header file *** //
std::vector<float>result(3);
result[0] = v1[1]*v2[2]-v1[2]*v2[1];
result[1] = v1[2]*v2[0]-v1[0]*v2[2];
result[2] = v1[0]*v2[1]-v1[1]*v2[0];
    return result;

    // *** End student code *** //
}

void transformVector2D(std::vector<float>& xy, float theta) 
{
    // *** Task: Implement this function according to the header file *** //

    // *** End student code *** //
}
