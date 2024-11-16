#pragma once
#include <string>
#include <stack>
#include <cstring>
#include <sstream>
#include <cmath>
#include <math.h>
#include <queue>
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
	double ApplyOperation(double a, double b, char op);
	int GetOperatorPrio(char op);
	std::vector<std::string> TokenizeInput(const std::string& input);
	

	double EvaluateUnaryOperation(const std::string& oper, double value);
};

