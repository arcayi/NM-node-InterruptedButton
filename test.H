/**
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * DESCRIPTION
 *
 * Interrupt driven binary switch example with dual interrupts
 * Author: Patrick 'Anticimex' Fallberg
 * Connect one button or door/window reed switch between
 * digitial I/O pin 3 (BUTTON_PIN below) and GND and the other
 * one in similar fashion on digital I/O pin 2.
 * This example is designed to fit Arduino Nano/Pro Mini
 *
 */


#include <MySensorS.h>
#include <SPI.h>

#define SKETCH_NAME "Binary Sensor"
#define SKETCH_MAJOR_VER "1"
#define SKETCH_MINOR_VER "0"

#define PRIMARY_CHILD_ID 1
#define SECONDARY_CHILD_ID 2

#define PRIMARY_BUTTON_PIN 2   // Arduino Digital I/O pin for button/reed switch
#define SECONDARY_BUTTON_PIN 3 // Arduino Digital I/O pin for button/reed switch

int value = 0;
int value2 = 0;

MySensor sensor_node;

// Change to V_LIGHT if you use S_LIGHT in presentation below
MyMessage msg(PRIMARY_CHILD_ID, V_VAR1);
MyMessage msg2(SECONDARY_CHILD_ID, V_VAR1);

void setup()
{
	Serial.println("Hopp");
	sensor_node.begin(NULL, 5, false);

	// Setup the buttons
	pinMode(PRIMARY_BUTTON_PIN, INPUT);
	pinMode(SECONDARY_BUTTON_PIN, INPUT);

	// Activate internal pull-ups
	digitalWrite(PRIMARY_BUTTON_PIN, HIGH);
	digitalWrite(SECONDARY_BUTTON_PIN, HIGH);

	// Send the sketch version information to the gateway and Controller
	sensor_node.sendSketchInfo(SKETCH_NAME, SKETCH_MAJOR_VER "." SKETCH_MINOR_VER);

	// Register binary input sensor to sensor_node (they will be created as child devices)
	sensor_node.present(PRIMARY_CHILD_ID, S_CUSTOM);
	sensor_node.present(SECONDARY_CHILD_ID, S_CUSTOM);
}

// Loop will iterate on changes on the BUTTON_PINs
void loop()
{

	// // Short delay to allow buttons to properly settle
	// sensor_node.sleep(30);

	value = digitalRead(PRIMARY_BUTTON_PIN);
	if (value == LOW)
	{
		sensor_node.send(msg.set("On"));
	}

	value2 = digitalRead(SECONDARY_BUTTON_PIN);
	if (value2 == LOW)
	{
		sensor_node.send(msg2.set("On"));
	}
	
	// Sleep until something happens with the sensor
	// sensor_node.sleep(PRIMARY_BUTTON_PIN - 2, CHANGE, SECONDARY_BUTTON_PIN - 2, CHANGE, 0);
}