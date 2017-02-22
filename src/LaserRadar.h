#ifndef SRC_LASERRADAR_H_
#define SRC_LASERRADAR_H_
#include <string>
#include "rplidar.h"
#include <opencv2/core/types.hpp>

using namespace std;
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

class LaserRadar {
private:
	static RPlidarDriver *drv;
	static bool Scanning;
	static string com_path;

public:
	bool debugInfo;
	rplidar_response_measurement_node_t nodes[360*2];	// raw result datum
	size_t   nodescount = _countof(nodes);
	rplidar_date_t datum[360*2];						// measurement result datum

private:
	bool checkRPLIDARHealth();
	RPlidarDriver* openLidar(int &errorCode, const char * opt_com_path, bool debugInfo);
	void closeLidar();
	void _Start(bool waitForStable = false);
	void _Stop();

public:
	static bool isValid();
	static bool isScanning();
	LaserRadar();
	LaserRadar(const string opt_com_path);
	virtual ~LaserRadar();
	bool Start();
	bool Stop();
	bool readData();
	bool getDistanceAt(int dirtheta, float* realtheta, float* distance, float delta);
	void drawrRadarDatum(cv::Mat& image, char* lastDistance, bool validDistance);
};

#endif /* SRC_LASERRADAR_H_ */
