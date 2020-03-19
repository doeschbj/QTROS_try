/**
 * @file /include/qtros/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qtros_QNODE_HPP_
#define qtros_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>

#include "sensor_msgs/LaserScan.h"
#include <QStringListModel>


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtros {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	void run();
        static int scan [360];


Q_SIGNALS:
        void update_Scans();
        void rosShutdown();

private:
        static void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
	int init_argc;
	char** init_argv;
        ros::Subscriber sub;

};

}  // namespace qtros

#endif /* qtros_QNODE_HPP_ */
