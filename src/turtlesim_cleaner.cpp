#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>

using namespace std;

ros::Publisher velocity_publisher;

void move(double speed, double distance, bool isForward);
void rotate (double angular_speed, double relative_angle, bool clockwise);
double degrees2radians(double angle_in_degrees);
const double PI = 3.14159265359;
int main(int argc, char **argv)
{
	// Initiate new ROS node named "talker"
	ros::init(argc, argv, "robot_cleaner");
	ros::NodeHandle n;
	velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);


	while(ros::ok()){
		
		/** test your code here **/
		move(1,3,1);
                rotate ( degrees2radians(30), degrees2radians(90),1);
                move(1,3,1);
                rotate ( degrees2radians(30), degrees2radians(90),1);
                move(1,3,1);
                rotate ( degrees2radians(30), degrees2radians(90),1);
                move(1,3,1);
               
		/** run the clean application afer you implement it*/
		double t0 = ros::Time::now().toSec(); //get current time before cleaning
		//clean();
		double t1 = ros::Time::now().toSec(); //get current time after cleaning
		ROS_INFO ("Cleaning execution time: %.2f", (t1-t0));
		return 0;

	}

	ros::spin();

   return 0;
}

/**
 *  makes the robot move with a certain linear velocity for a 
 *  certain distance in a forward or backward straight direction. 
 */
void move(double speed, double distance, bool isForward){
   geometry_msgs::Twist vel_msg;
   //set a random linear velocity in the x-axis
   if (isForward)
	   vel_msg.linear.x =abs(speed);
   else
	   vel_msg.linear.x =-abs(speed);
   vel_msg.linear.y =0;
   vel_msg.linear.z =0;
   //set a random angular velocity in the y-axis
   vel_msg.angular.x = 0;
   vel_msg.angular.y = 0;
   vel_msg.angular.z =0;

   double t0 = ros::Time::now().toSec();
   double current_distance = 0.0;
   ros::Rate loop_rate(100);
   do{
	   velocity_publisher.publish(vel_msg);
	   double t1 = ros::Time::now().toSec();
	   current_distance = speed * (t1-t0);
	   ros::spinOnce();
	   loop_rate.sleep();
	   //cout<<(t1-t0)<<", "<<current_distance <<", "<<distance<<endl;
   }while(current_distance<distance);
   vel_msg.linear.x =0;
   velocity_publisher.publish(vel_msg);

}
void rotate (double angular_speed, double relative_angle, bool clockwise){

	geometry_msgs::Twist vel_msg;
	   //set a random linear velocity in the x-axis
	   vel_msg.linear.x =0;
	   vel_msg.linear.y =0;
	   vel_msg.linear.z =0;
	   //set a random angular velocity in the y-axis
	   vel_msg.angular.x = 0;
	   vel_msg.angular.y = 0;
	   if (clockwise)
	   		   vel_msg.angular.z =-abs(angular_speed);
	   	   else
	   		   vel_msg.angular.z =abs(angular_speed);

	   double t0 = ros::Time::now().toSec();
	   double current_angle = 0.0;
	   ros::Rate loop_rate(1000);
	   do{
		   velocity_publisher.publish(vel_msg);
		   double t1 = ros::Time::now().toSec();
		   current_angle = angular_speed * (t1-t0);
		   ros::spinOnce();
		   loop_rate.sleep();
		   //cout<<(t1-t0)<<", "<<current_angle <<", "<<relative_angle<<endl;
	   }while(current_angle<relative_angle);
	   vel_msg.angular.z =0;
	   velocity_publisher.publish(vel_msg);
}
double degrees2radians(double angle_in_degrees){
	return angle_in_degrees *PI /180.0;
}
