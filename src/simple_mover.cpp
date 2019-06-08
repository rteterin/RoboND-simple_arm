#include "ros/ros.h"
#include "std_msgs/Float64.h"

#include <iostream>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "arm_mover");

    ros::NodeHandle n;

    ros::Publisher joint1_pub = n.advertise<std_msgs::Float64>("/simple_arm/joint_1_position_controller/command", 10);
    ros::Publisher joint2_pub = n.advertise<std_msgs::Float64>("/simple_arm/joint_2_position_controller/command", 10);

    ros::Rate loop_rate(10);

    int start_time = 0;

    std::cout << "Waiting for non-zero time\n";

    while (!start_time)
    {
        start_time = ros::Time::now().toSec();
    }

    std::cout << "Starting main loop\n";

    while (ros::ok())
    {
        int elapsed_time = ros::Time::now().toSec() - start_time;

        std_msgs::Float64 joint1_angle, joint2_angle;

        joint1_angle.data = sin(2 * M_PI * 0.1 * elapsed_time) * (M_PI / 2);
        joint2_angle.data = sin(2 * M_PI * 0.1 * elapsed_time) * (M_PI / 2);

        joint1_pub.publish(joint1_angle);
        joint2_pub.publish(joint2_angle);

        loop_rate.sleep();
    }

    std::cout << "Finished\n";

    return 0;
}
