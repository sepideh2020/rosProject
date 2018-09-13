#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include <sstream>



//turtlesim::Pose::ConstPtr message;
/*float x;
float y;
float theta;
float linear_velocity;
float angular_velocity;*/


turtlesim::Pose goal_pose;
turtlesim::Pose turtlesim_pose;

void chatterCallback(const turtlesim::Pose::ConstPtr& msg)
{
  ROS_INFO("I heard: [%f],[%f],[%f],[%f],[%f] \n", msg->x, msg->y, msg->theta, msg->linear_velocity, msg->angular_velocity);

  goal_pose.x=msg->x;
  goal_pose.y=msg->y; 
  goal_pose.theta=msg->theta;
  goal_pose.linear_velocity=msg->linear_velocity;
  goal_pose.angular_velocity=msg->angular_velocity;
  
}
void chatterCallback1(const turtlesim::Pose::ConstPtr& msg)
{
  ROS_INFO("I heard: [%f],[%f],[%f],[%f],[%f] \n", msg->x, msg->y, msg->theta, msg->linear_velocity, msg->angular_velocity);

  turtlesim_pose.x=msg->x;
  turtlesim_pose.y=msg->y; 
  turtlesim_pose.theta=msg->theta;
  turtlesim_pose.linear_velocity=msg->linear_velocity;
  turtlesim_pose.angular_velocity=msg->angular_velocity;
  
}


double getDistance(double x1, double y1, double x2, double y2){
	return sqrt(pow((x2-x1),2) + pow((y2-y1),2));
}



int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");

  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("turtle1/pose", 1000,chatterCallback);
  ros::Subscriber sub1 = n.subscribe("turtle2/pose", 1000,chatterCallback1);


//  ros::spin();


  //ros::init(argc, argv, "talker");

  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
  while (ros::ok())
  {
    geometry_msgs::Twist msg;
    msg.linear.x=1.5*getDistance(turtlesim_pose.x, turtlesim_pose.y, goal_pose.x, goal_pose.y);
    msg.linear.y=0; 
    msg.linear.z=0;
    ///angular velocity
    msg.angular.x = 0;
    msg.angular.y = 0;
    msg.angular.z = 4*(atan2(goal_pose.y - turtlesim_pose.y, goal_pose.x - turtlesim_pose.x)-turtlesim_pose.theta);
    
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
     ++count;
  }


  return 0;
}
