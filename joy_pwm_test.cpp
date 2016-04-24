//This a program for subscribing joy_msgs to give another point
//message type:sensor_msgs/joy
//Majunchong 2016.04.21
#include <ros/ros.h>
#include <stdlib.h>
#include <stdio.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Point.h>
//using namespace std;

class SubscribeAndPublish 
{
public: 
SubscribeAndPublish() 
{ 
    //Topic you want to publish
    joy_pwm_pub = nh.advertise<geometry_msgs::Point>("pwm",100);
    //Topic you want to subscribe
    joy_sub = nh.subscribe<sensor_msgs::Joy>("joy",100,&SubscribeAndPublish::Joy_Callback,this);
} 

void Joy_Callback(const sensor_msgs::Joy::ConstPtr& joy)
{
    float speed=0.0,base_speed = 75;

       geometry_msgs::Point pwm;
//.... do something with the input and generate the output... 

       if(joy->buttons[1])
    			ROS_INFO_STREAM("B!!");

    	    //速度档位调节,5 modes
    if(joy->buttons[6]==1)
       {
           if(speednum>=2)
              speednum--;         //速度减一档
           ROS_INFO_STREAM("Speed Mode:"
           	<<speednum);
       }
    if(joy->buttons[7]==1)
       {
           if(speednum<=4)     //速度加一档
              speednum++;
           ROS_INFO_STREAM("Speed Mode:"
           	<<speednum);
       }

       if (joy->axes[4]>=0.2)
       {
        speed = speednum*25+base_speed;
        ROS_INFO_STREAM("Left Axes Up!Speed:"
                        <<speed);
       }
       else if(abs(joy->axes[4]<0.2))
       {
       	speed = 0;
       }

       pwm.x = speed;
       pwm.y = pwm.x;
       pwm.z=0;

      joy_pwm_pub.publish(pwm);
}

private: 
float speednum;

ros::NodeHandle nh; 

ros::Publisher joy_pwm_pub; 

ros::Subscriber joy_sub;
};//End of class SubscribeAndPublish

int main(int argc,char ** argv)
{
	//initial a ros system and make a new node
	ros::init(argc,argv,"joy_sub_and_pub_pwm");
	
	SubscribeAndPublish SAPObject; 

	ros::spin();
}
