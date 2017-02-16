#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <LaserRadar.h>

RPlidarDriver* LaserRadar::drv = NULL;
bool LaserRadar::Scanning = false;
string LaserRadar::com_path = "/dev/ttyUSB0";

bool LaserRadar::isValid() {
	return (!(drv == NULL));
}

bool LaserRadar::isScanning() {
	return Scanning;
}

LaserRadar::LaserRadar() {
	debugInfo = false;
	int errorCode;

	drv = openLidar(errorCode,com_path.c_str(),debugInfo);
}

LaserRadar::LaserRadar(const string opt_com_path) {
	debugInfo = false;
	int errorCode;
	com_path = opt_com_path;

	drv = openLidar(errorCode,com_path.c_str(),debugInfo);
}

LaserRadar::~LaserRadar() {
	closeLidar();
}

void LaserRadar::Start() {
	int errorCode;

	if (!drv) drv = openLidar(errorCode,com_path.c_str(),debugInfo);
	if (!drv) return;
	_Start();
}

void LaserRadar::Stop() {
	_Stop();
}

bool LaserRadar::checkRPLIDARHealth()
{
    u_result     op_result;
    rplidar_response_device_health_t healthinfo;

	if (!drv) {
		if (debugInfo) printf("drv is Null, checkRPLIDARHealth return false\n");
		return false;
	}

    op_result = drv->getHealth(healthinfo);
    if (IS_OK(op_result)) { // the macro IS_OK is the preperred way to judge whether the operation is succeed.
    	if (debugInfo) printf("RPLidar health status : %d\n", healthinfo.status);
        if (healthinfo.status == RPLIDAR_STATUS_ERROR) {
        	if (debugInfo) fprintf(stderr, "Error, rplidar internal error detected. Please reboot the device to retry.\n");
            // enable the following code if you want rplidar to be reboot by software
            // drv->reset();
            return false;
        } else {
            return true;
        }

    } else {
    	if (debugInfo) fprintf(stderr, "Error, cannot retrieve the lidar health code: %x\n", op_result);
        return false;
    }
}

//opt_com_path = "/dev/tty.SLAB_USBtoUART";
RPlidarDriver* LaserRadar::openLidar(int &errorCode, const char * opt_com_path, bool debugInfo)
{
    _u32        opt_com_baudrate = 115200;
    u_result    op_result;

    // create the driver instance
    drv = RPlidarDriver::CreateDriver(RPlidarDriver::DRIVER_TYPE_SERIALPORT);

    if (!drv) {
        if (debugInfo) fprintf(stderr, "insufficent memory, exit\n");
        return NULL;
    }

    // make connection...
    if (IS_FAIL(drv->connect(opt_com_path, opt_com_baudrate))) {
    	if (debugInfo) fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n"
                , opt_com_path);
    	errorCode = -2;
        goto on_finished;
    }

    rplidar_response_device_info_t devinfo;

    // retrieving the device info
    ////////////////////////////////////////
    op_result = drv->getDeviceInfo(devinfo);

    if (IS_FAIL(op_result)) {
    	if (debugInfo) fprintf(stderr, "Error, cannot get device info.\n");
    	errorCode = -3;
        goto on_finished;

    }

    // print out the device serial number, firmware and hardware version number..
    if (debugInfo) {
    	printf("RPLIDAR S/N: ");
    	for (int pos = 0; pos < 16 ;++pos) {
    		printf("%02X", devinfo.serialnum[pos]);
    	}

    	printf("\n"
           "Firmware Ver: %d.%02d\n"
           "Hardware Rev: %d\n"
           , devinfo.firmware_version>>8
           , devinfo.firmware_version & 0xFF
           , (int)devinfo.hardware_version);
    }

    // check health...
    if (!checkRPLIDARHealth()) {
    	errorCode = -4;
        goto on_finished;
    }

    //_Start();

    if (debugInfo) printf("Success return drv\n");
    return drv;

on_finished:
	if (debugInfo) printf("Dispose and return drv=NULL\n");
	RPlidarDriver::DisposeDriver(drv);
	drv = NULL;
    return drv;
}

void LaserRadar::closeLidar()
{
	if (drv){
		_Stop();
		RPlidarDriver::DisposeDriver(drv);
		drv = NULL;
	}
}

void LaserRadar::_Start(bool waitForStable) {
	unsigned maxCount = 200;
	unsigned lastDatumSize, i;
	u_result op_result;

	if (!drv) return;

	if (!Scanning) {
		// start scan
		drv->startMotor();
		// start scan...
		drv->startScan();

		if (waitForStable) {
			if (debugInfo) printf("waitForStable... \n");
			lastDatumSize = 0;
			i = 0;
			maxCount = 10;
			// time out 2ms
			while ((lastDatumSize != nodescount) && (i < maxCount)) {
				op_result = drv->grabScanData(nodes, nodescount);
				if (IS_OK(op_result)) {
					lastDatumSize = nodescount;
					i ++;
				}
				if (debugInfo) printf("lastSize=%d, nodesCount=%d, i=%d\n",lastDatumSize,nodescount,i);
			}
		}
		else {
			if (debugInfo) printf("Don't waitForStable \n");
		}
		Scanning = true;
	}
}

void LaserRadar::_Stop() {
	if (!drv) return;
	if (Scanning) {
		drv->stop();
		drv->stopMotor();
		Scanning = false;
	}
}

bool LaserRadar::readData()
{
	u_result     op_result;

	if (!drv) return false;

    // time out 2ms
	op_result = drv->grabScanData(nodes, nodescount);

	if (IS_OK(op_result)) {
		drv->ascendScanData(nodes, nodescount);
		for (int pos = 0; pos < (int)nodescount ; ++pos) {
			datum[pos].sync = (nodes[pos].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT) ? true:false;
			datum[pos].theta = (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f;
			datum[pos].distance = nodes[pos].distance_q2/4.0f;
			datum[pos].quality = nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT;

			if (debugInfo) printf("%s theta: %03.2f Dist: %08.2f Q: %d \n",
					datum[pos].sync ?"S ":"  ",
					datum[pos].theta,
					datum[pos].distance,
					datum[pos].quality);
		}
	}
	return IS_OK(op_result);
}

bool LaserRadar::getDistanceAt(int dirtheta, float* realtheta, float* distance, float delta)
{
	bool result = false;
	bool closeRange, inRangeBoolExpr;
	unsigned i,low,high,validpoints;
	float theta,dirthetaL,dirthetaH, tmpdistance;
	const int maxdelta = 90;    // delta <= 90, search range -delta to delta along dirtheta
	const int mindelta = 0.5;

	// dirtheta example:
	// in:  45, -45, 370, -370
	// out: 45, 315, 10, 350

	if (dirtheta < 0) dirtheta = (int(- dirtheta) / 360 + 1) * 360 + dirtheta;
	dirtheta = dirtheta - (int(dirtheta) / 360) * 360;

	// delta example:
	// in:  0, 0.5 ,-0.5, 1, -1, 45, -45, 90, 95
	// out: 0.5, 0.5, 0.5, 1, 1, 45, 45, 90, 90
	delta = fabs(delta);
	delta = delta - (int(delta) / 360) * 360;
	if (delta >= maxdelta) delta = maxdelta;
	if (delta < mindelta) delta = mindelta;

	// example:
	// dirthetaL -- dirthetaH
	// 44.5 -- 45.5 : closeRange = true, dirtheta=45, delta = 0.5
	// 359.5 -- 0.5 : clsoeRange = false, dirtheta=0, delta = 0.5
	dirthetaL = dirtheta - delta;
	if (dirthetaL < 0) dirthetaL = dirthetaL + 360.0;
	dirthetaH = dirtheta + delta;
	if (dirthetaH < 0) dirthetaH = dirthetaH + 360.0;

	closeRange = (dirthetaH >= dirthetaL);

	// dirthetaL -- dirthetaH
	// 44.5 -- 45.5 : closeRange = true
	// 359.5 -- 0.5 : clsoeRange = false
	//
	// **rpLidar delta theta = 360 / nodescount
	// **search range in order datum (desc by theta)
	//
	// low -- high
	// 43 -- 46 : closeRange = true
	// 357 -- 363 : closeRange = false

	low = int(dirthetaL * nodescount / 360) - 1;
	if (low < 0) low = 0;
	high = int(dirthetaH * nodescount / 360) + 1;
	if (high >= nodescount) high = nodescount - 1;
	if (!closeRange) high = high + nodescount;

	validpoints = 0;
	*distance = 0;
	*realtheta = 0;
	// average theat and distance between low and high
	for (i = low; i <= high ; i++) {
		if (closeRange) {
			theta = datum[i].theta;
			tmpdistance = datum[i].distance;
			inRangeBoolExpr = ((theta <= dirthetaH) && (theta >= dirthetaL));
		}
		else {
			theta = datum[i % nodescount].theta;
			tmpdistance = datum[i % nodescount].distance;
			inRangeBoolExpr = ((theta <= dirthetaH) || (theta >= dirthetaL));
			if (theta <= dirthetaH) theta = theta + 360;
		}

		if (inRangeBoolExpr) {
			if (datum[i].quality > 0) {
				*distance = *distance + tmpdistance;
				*realtheta = *realtheta + theta;
				validpoints ++;
			}
		}
	}

	result = (validpoints > 0);
	if (result) {
		*distance = *distance / validpoints;
		*realtheta = *realtheta /validpoints;
		*realtheta = *realtheta - (int(*realtheta) / 360) * 360;
	}
	/* test */
//	result = true;
//	*distance = low * 1000;
//	*realtheta = high;

	return result;
}

void LaserRadar::drawrRadarDatum(cv::Mat& image, char* lastDistance, bool validDistance) {
	cv::Point beginPoint;
	cv::Point endPoint;
	unsigned i;
	float pi =3.1415926;
	float theta, distance;
	cv::Scalar lineColor;
	string tempString;

	if (image.empty()) return;

	cv::Scalar RedColor = cv::Scalar(0,0,255);
	cv::Scalar GreenColor = cv::Scalar(0,255,0);
	cv::Scalar BlueColor = cv::Scalar(255,0,0);
	cv::Scalar GreyColor = cv::Scalar(200,200,200);
	cv::Scalar ValidColor = BlueColor;
	cv::Scalar InValidColor = GreyColor;

	// scale for display mm * scale
	float scale = 0.04;
	// center of Image (default is 640 X 480)
	int center_x = 320;
	int center_y =240;
	// Center point
	beginPoint = cv::Point(center_x,center_y);

	for (i = 0; i < nodescount ; i++) {
		theta = datum[i].theta;
		if (datum[i].quality > 0) {
			lineColor = ValidColor;
			distance = datum[i].distance;
		}
		else {
			lineColor = InValidColor;
			distance = 500;
		}
		endPoint = cv::Point(distance*cos((theta - 90)*pi/180)*scale + center_x,
							distance*sin((theta - 90)*pi/180)*scale + center_y);
		cv::line(image,beginPoint,endPoint,lineColor,1);
	}

	// Distance value disaply
	if (validDistance) cv::putText(image, lastDistance, cv::Point(10,50), cv::FONT_HERSHEY_SIMPLEX, 1, GreenColor);
	else cv::putText(image, lastDistance, cv::Point(10,50), cv::FONT_HERSHEY_SIMPLEX, 1, RedColor);

	// Distances Mark 2m, 4m, 6m, 8m
	for (i = 1; i <= 4; i++) {
		distance = 2000*i ;
		endPoint = cv::Point(distance*cos(- 45*pi/180)*scale + center_x,
						distance*sin(-45*pi/180)*scale + center_y);

		// draw circle
		cv::circle(image,beginPoint,distance*scale,GreenColor,1);
		tempString = std::to_string(i*2) + "m";

		// draw scale
		cv::putText(image, tempString, endPoint, cv::FONT_HERSHEY_SIMPLEX, 0.4, GreenColor);

		// draw zero scale
		int segLine = 10;
		endPoint = cv::Point(distance*cos(- 90*pi/180)*scale + center_x,
									distance*sin(-90*pi/180)*scale + center_y);

		cv::line(image, cv::Point(endPoint.x, endPoint.y - segLine),
				cv::Point(endPoint.x, endPoint.y + segLine), RedColor, 2);
	}

	//cv::line(image,beginPoint,endPoint,lineColor,2);
}

