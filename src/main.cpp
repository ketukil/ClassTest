/**
 * @file main.cpp
 * @author  ()
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <cstdio>
#include <iostream>

using namespace std;

#define log_construct(p) cout << "[" << p << "] Construct: " << __func__ << "@" << __LINE__ << endl;

const double GAIN1 = 327.68;	 // Integrator @ 5V
const double GAIN2 = 496.484848; // Integrator @ 3V3
const double GAIN3 = 13.5168e6;	 // Current source @ 5V
const double GAIN4 = 20.48e6;	 // Current source @ 3V3

class Driver
{
public:
	int DAC_VALUE;
	typedef enum
	{
		SUPPLY_5V,
		SUPPLY_3V3
	} supply_t;

	Driver()
	{
		log_construct(this);
	}
	void begin(void *arg)
	{
		printf("MPC::bus = %p\n", arg);
	}
	void setValue(int val)
	{
		printf("adc: %d\n", val);
	}
};

typedef enum MODE
{
	MODE_INVERTER,
	MODE_CHARGER
} power_block_mode_t;

class CurrentTrip : public Driver
{
	double gain = GAIN2;

public:
	CurrentTrip()
	{
		log_construct(this);
	}
};

class CurrentSource : public Driver
{
	double gain = GAIN4;

public:
	CurrentSource()
	{
		log_construct(this);
	}
};

// ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ POWER BLOCK CLASS                                                                                                    │
// └──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘

class PowerBlock : public CurrentSource, public CurrentTrip
{
	double gain = 327;

public:
	PowerBlock()
	{
		log_construct(this);
	}

	PowerBlock(power_block_mode_t mode)
	{
		log_construct(this);
		switch (mode)
		{
		case MODE_INVERTER:
			printf("INVERTER MODE\n");
			break;
		case MODE_CHARGER:
			printf("CHARGER MODE\n");
			break;

		default:
			break;
		}
	}

	void setOutputVoltage(double amps)
	{
	}

	void setCurrentLimit(double amps)
	{
	}
};

PowerBlock Charger(MODE_CHARGER);
PowerBlock Inverter(MODE_INVERTER);

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	Charger.setOutputVoltage(350);
	Charger.setCurrentLimit(8.5);

	Inverter.setOutputVoltage(230);
	Inverter.setCurrentLimit(12.5);

	return 0;
}
