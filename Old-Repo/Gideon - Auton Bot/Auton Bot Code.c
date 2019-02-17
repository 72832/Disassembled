#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  ,               sensorSONAR_inch)
#pragma config(Sensor, dgtl3,  ,               sensorSONAR_inch)
#pragma config(Sensor, dgtl5,  ,               sensorSONAR_inch)
#pragma config(Sensor, dgtl7,  ,               sensorSONAR_inch)
#pragma config(Sensor, dgtl9,  ,               sensorSONAR_inch)
#pragma config(Sensor, dgtl11, ,               sensorSONAR_inch)
#pragma config(Sensor, I2C_1,  rightDrive,     sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  leftDrive,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,            ,             tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,            ,             tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Declaring variables
int rDiffRight;
int rDiffLeft;

// Declaring functions
// Generating a random number
void getRNum(r)
{
	int r = random[srand(nSeedValue)];
}

void stopDrive()
{
	motor(port1) = 0;
	motor(port2) = 0;
	motor(port3) = 0;
	motor(port4) = 0;
}

void moveForward()
{
	motor(port1) = 127;
	motor(port2) = 127;
	motor(port3) = 127;
	motor(port4) = 127;
}

void moveBack()
{
	motor(port1) = -127;
	motor(port2) = -127;
	motor(port3) = -127;
	motor(port4) = -127;
}

void turnRight()
{
	while (SensorValue(rightDrive) > -90)
	{
		motor(port1) = -127;
		motor(port2) = -127;
		motor(port3) = 127;
		motor(port4) = 127;
	}
}

void turnLeft()
{
	while (SensorValue(leftDrive) > -90)
	{
		motor(port1) = 127;
		motor(port2) = 127;
		motor(port3) = -127;
		motor(port4) = -127;
	}
}

void turn180()
{
	while (SensorValue(rightDrive) > -180)
	{
		motor(port1) = -127;
		motor(port2) = -127;
		motor(port3) = 127;
		motor(port4) = 127;
	}
}

// Calculating differences between encoders and random number
void rDiffs()
{
	// Right encoder
	if (SensorValue(rightDrive) > r)
	{
		rDiffRight = SensorValue(rightDrive) - r;
	}
	else
	{
		rDiffRight = r - SensorValue(rightDrive);
	}

	// Left encoder
	if (SensorValue(leftDrive) > r)
	{
		rDiffLeft = SensorValue(leftDrive) - r;
	}
	else
	{
		rDiffLeft = r - SensorValue(leftDrive);
	}
}

task main()
{
	// Resetting encoders
	SensorValue(I2C_1) = 0;
	SensorValue(I2C_2) = 0;

	// Auton logic
	while (true)
	{
		if (SensorValue(dgtl1) > 12 && SensorValue(dgtl3) > 12)
		{
			moveForward();
		}
		else if (SensorValue(dgtl1) < 12 && SensorValue(dgtl3) < 12)
		{
			moveBack();

			if (SensorValue(dgtl9) < SensorValue(dgtl11))
			{
				turnRight();
			}
			else if (SensorValue(dgtl9) > SensorValue(dgtl11))
			{
				turnLeft();
			}
			else if (SensorValue(dgtl9) == SensorValue(dgtl11) && SensorValue(dgtl5) && SensorValue(dgtl7) > SensorValue(dgtl9) && SensorValue(dgtl11))
			{
				turn180();
			}
			else
			{
				getRNum(r);
				rDiffs();
				if (rDiffLeft > rDiffRight)
				{
					while(SensorValue(rightDrive) != r)
					{
						motor[port1] = -127;
						motor[port1] = -127;
						motor[port1] = 127;
						motor[port1] = 127;
					}
				}
				else
				{
					while(SensorValue(leftDrive) != r)
					{
						motor[port1] = 127;
						motor[port1] = 127;
						motor[port1] = -127;
						motor[port1] = -127;
					}
				}
			}
		}
	}
}