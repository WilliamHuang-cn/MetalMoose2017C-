#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

constexpr int leftFA = 4;
constexpr int leftFB = 5;
constexpr int leftBA = 6;
constexpr int leftBB = 7;
constexpr int rightFA = 0;
constexpr int rightFB = 1;
constexpr int rightBA = 2;
constexpr int rightBB = 3;

constexpr int shooterMotor = 4;

constexpr int encoderLeftF[] = { 0, 1 };

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int RANGE_FINDER_PORT = 1;
// constexpr int RANGE_FINDER_MODULE = 1;

#endif  // ROBOTMAP_H
