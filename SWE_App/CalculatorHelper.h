#pragma once
#include <string>
#include <stack>
#include <cstring>
#include <sstream>
#include <cmath>
#include <math.h>
#include <queue>
#include <iostream>
class CalculatorHelper
{
public:
	double EvaluateExpression(char* inputBuffer, unsigned int bufferSize);

	void Clear(char* inputBuffer);
	void Backspace(char* inputBuffer);
	void AddDecimal(char* inputBuffer, unsigned int bufferSize);
	void ToggleNegative(char* inputBuffer, unsigned int bufferSize);
	bool IsUnaryOperator(const std::string& op);
	bool isOperator(char c);
	int GetOperatorPrio(char op);
	void FormatOutput(char* buffer, unsigned int bufferSize, double value);
	double EvaluateUnaryOperation(const std::string& oper, double value);
};

