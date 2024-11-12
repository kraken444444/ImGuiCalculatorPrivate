#pragma once
#include <string>
#include <stack>
#include <cstring>
#include <sstream>
#include <cmath>
class CalculatorHelper
{
public:
	double EvaluateExpression(char* inputBuffer, unsigned int bufferSize);

	void Clear(char* inputBuffer);
	void Backspace(char* inputBuffer);
	void AddDecimal(char* inputBuffer, unsigned int bufferSize);
	void ToggleNegative(char* inputBuffer, unsigned int bufferSize);
	bool IsUnaryOperator(const std::string& op);
};

