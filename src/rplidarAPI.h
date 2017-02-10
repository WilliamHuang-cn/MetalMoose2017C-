#ifndef RPLIDARAPI_H_
#define RPLIDARAPI_H_

#include <iostream>
#include "rplidar.h"
#include <opencv2/core/types.hpp>

using namespace rp::standalone::rplidar;

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

typedef struct _rplidar_date_t {
	bool	sync;
    float   theta;
    float 	distance;
    int		quality;
} rplidar_date_t;

//opt_com_path = "/dev/tty.SLAB_USBtoUART";
RPlidarDriver * openLidar(int &errorCode, const char * opt_com_path, bool debugInfo);
void closeLidar(RPlidarDriver ** drv);
bool readData(RPlidarDriver * drv, bool debugInfo = false);
// call getDistanceAt after readData
bool getDistanceAt(int dirtheata, float* realtheata, float* distance, float delta);
void drawrpLidarDatum(cv::Mat& image, char* lastDistance, bool validDistance);

#endif /* RPLIDARAPI_H_ */
