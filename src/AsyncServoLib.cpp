/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#include "AsyncServoLib.h"

AsyncServo::AsyncServo()
{
	_inputLow = 0;
	_inputMid = 900;
	_inputHigh = 1800;
	_outputLow = 600;
	_outputMid = 1500;
	_outputHigh = 2400;

	_currentPosition = 900;
}

uint8_t AsyncServo::Attach(int pin)
{
	_servo.attach(pin);
	write(_currentPosition);
}

void AsyncServo::Detach()
{
	_servo.detach();
}

int AsyncServo::Read()
{
	return _servo.read();
}

void AsyncServo::SetInput(int low, int mid, int high)
{
	_inputLow = low;
	_inputMid = mid;
	_inputHigh = high;
}

void AsyncServo::SetOutput(int low, int mid, int high)
{
	_outputLow = low;
	_outputMid = mid;
	_outputHigh = high;
}

void AsyncServo::write(int value)
{
	_currentPosition = value;

	int valueMs;
	if (value<_inputMid)
	{
		valueMs = map(value, _inputLow, _inputMid, _outputLow, _outputMid);
	}
	else
	{
		valueMs = map(value, _inputMid, _inputHigh, _outputMid, _outputHigh);
	}
	_servo.writeMicroseconds(valueMs);
}

void AsyncServo::WriteDegree(int value)
{
	write(value * 10);
}

void AsyncServo::WriteMicroseconds(int value)
{
	_servo.writeMicroseconds(value);
}

void AsyncServo::Move(int dec, int timeMs)
{
	Move(dec, timeMs, nullptr);
}

void AsyncServo::Move(int dec, int timeMs, ServoAction finish)
{
	_startPosition = _currentPosition;
	_endPosition = dec;
	_startTime = micros();
	_endTime = _startTime + 1000 * static_cast<unsigned long>(timeMs);
	_isMoving = true;
	Finish = finish;
}

void AsyncServo::MoveDegrees(int deg, int timeMs)
{
	Move(deg * 10, timeMs);
}

void AsyncServo::MoveDegrees(int deg, int timeMs, ServoAction finish)
{
	Move(deg * 10, timeMs, finish);
}

void AsyncServo::Stop()
{
	_isMoving = false;
}

void AsyncServo::Update()
{
	if (_isMoving == false) return;

	unsigned long _currentTime = micros();
	if (_endTime < _currentTime)
	{
		_isMoving = false;
		write(_endPosition);
		if (Finish != nullptr) Finish();
	}

	float position = static_cast<float>(_endPosition - _startPosition) * (_currentTime - _startTime) / (_endTime - _startTime);

	write(static_cast<int>(position) + _startPosition);
}

int16_t AsyncServo::GetCurrentPosition() const
{
	return _currentPosition;
}
