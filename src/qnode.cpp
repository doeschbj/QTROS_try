/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/qtros/qnode.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtros {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}
//hoiöo
static void QNode::scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
  ROS_INFO("I heard scans");

  for(int i=0; i<360; i++){
      scan[i] = (int)((msg->ranges)[i]);
  }
  Q_EMIT update_Scans();
}

bool QNode::init() {
	ros::init(init_argc,init_argv,"qtros");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
        //chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
        sub = n.subscribe("/robot3/scan",1000,scanCallback);
	start();
	return true;
}

void QNode::run() {
	ros::Rate loop_rate(1);
        int count = 0;
	while ( ros::ok() ) {

                /*std_msgs::String msg;
		std::stringstream ss;
		ss << "hello world " << count;
		msg.data = ss.str();
		chatter_publisher.publish(msg);
                log(Info,std::string("I sdvent: ")+msg.data);*/



                ros::spinOnce();
                loop_rate.sleep();
		++count;
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

}  // namespace qtros
