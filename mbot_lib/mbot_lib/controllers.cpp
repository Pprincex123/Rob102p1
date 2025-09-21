/**
 * File: controllers.cpp
 *
 * Sources for feedback controllers.
 */

#include <mbot_lib/controllers.h>


float bangBangControl(float current, float setpoint, float scaling, float tolerance)
{
    // *** Task: Implement this function according to the header file *** //
float error = setpoint - current;
if (error > tolerance){
    return scaling;
}
else if (error < -tolerance) {
return -scaling;
}
else {
    return -1;
}
}

    // *** End student code *** //


float pControl(float current, float setpoint, float kp)
{
    // *** Task: Implement this function according to the header file *** //
float error = setpoint - current;
float Control_Velocity = kp*error;
    return Control_Velocity;
    // *** End student code *** //
}