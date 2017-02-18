#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

static constexpr int leftFAChannel = 4;
static constexpr int leftFBChannel = 5;
static constexpr int leftBAChannel = 6;
static constexpr int leftBBChannel = 7;
static constexpr int rightFAChannel = 0;
static constexpr int rightFBChannel = 1;
static constexpr int rightBAChannel = 2;
static constexpr int rightBBChannel = 3;

static constexpr int shooterMotor = 8;

static constexpr int encoderLeftF[] = { 0, 1 };

static constexpr int gearGate = 9;

static constexpr int solRightFChannels[] = { 0, 1 };
static constexpr int solRightBChannels[] = { 2, 3 };
static constexpr int solLeftFChannels[] = { 4, 5 };
static constexpr int solLeftBChannels[] = { 6, 7 };

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int RANGE_FINDER_PORT = 1;
// constexpr int RANGE_FINDER_MODULE = 1;

#endif  // ROBOTMAP_H
