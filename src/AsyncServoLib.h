/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _AsyncServoLib_h
#define _AsyncServoLib_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a se

#include <Servo.h>

class AsyncServo
{
	typedef  void(*ServoAction)();

public:
	AsyncServo();

	uint8_t Attach(int pin);
	void Detach();
	int Read();

	void SetInput(int low, int mid, int high);
	void SetOutput(int low, int mid, int high);

	void write(int dec);
	void WriteDegree(int deg);
	void WriteMicroseconds(int uS);

	void Move(int dec, int timeMs);
	void Move(int dec, int timeMs, ServoAction finish);
	void MoveDegrees(int deg, int timeMs);
	void MoveDegrees(int deg, int timeMs, ServoAction finish);
	void Stop();

	void Update();
	int16_t GetCurrentPosition() const;

	ServoAction Finish;


private:
	Servo _servo;
	bool _isMoving;
	int16_t _currentPosition;

	int16_t _startPosition;
	int16_t _endPosition;
	unsigned long _startTime;
	unsigned long _endTime;

	int16_t _inputLow;
	int16_t _inputMid;
	int16_t _inputHigh;
	int16_t _outputLow;
	int16_t _outputMid;
	int16_t _outputHigh;
};

#endif

