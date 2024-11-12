#include "CalculatorHelper.h"

double CalculatorHelper::EvaluateExpression(char* inputBuffer, unsigned int bufferSize)
{

	std::stringstream ss(inputBuffer);
	double num1 = 0;
	double num2 = 0;
	char operation = 0;

	ss >> num1 >> operation >> num2;
	double result = 0;

	switch (operation) {
	case '+': result = num1 + num2; break;
	case '-': result = num1 - num2; break;
	case '*': result = num1 * num2; break;
	case '/': result = (num2 != 0) ? num1 / num2 : 0; break;

	}
	snprintf(inputBuffer, bufferSize, "%.2f", result);
	return result;

}
