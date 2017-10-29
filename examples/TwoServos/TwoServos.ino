/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#include "AsyncServoLib.h"

AsyncServo asyncServo09;
AsyncServo asyncServo10;

void setup()
{
	Serial.begin(115200);
	Serial.println("Restart");
	
	asyncServo09.Attach(9);
	asyncServo10.Attach(10);

	asyncServo09.SetOutput(500, 1500, 2500);
	asyncServo10.SetOutput(500, 1500, 2500);
	delay(1000);
	asyncServo10.write(450);
	delay(1000);
	asyncServo10.write(1350);
	delay(1000);
	asyncServo10.write(900);
	delay(1000);

	step1();
	step4();
}

void step1()
{
	asyncServo10.Move(1350, 2000, step2);
}

void step2()
{
	asyncServo10.Move(450, 2000, step1);
}


void step4()
{
	asyncServo09.Move(1350, 4000, step5);
}

void step5()
{
	asyncServo09.Move(450, 4000, step4);
}


void loop()
{
	delay(10);
	asyncServo09.Update();
	asyncServo10.Update();
}