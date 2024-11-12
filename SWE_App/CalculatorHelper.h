#pragma once
#include <string>
#include <stack>
#include <cstring>
#include <sstream>
class CalculatorHelper
{
public:
	double EvaluateExpression(char* inputBuffer, unsigned int bufferSize);

	void Clear(char* inputBuffer);
};

