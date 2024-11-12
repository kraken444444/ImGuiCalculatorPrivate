#include "CalculatorHelper.h"
#define M_PI   3.14159265358979323846264338327950288

double CalculatorHelper::EvaluateExpression(char* inputBuffer, unsigned int bufferSize)
{
	std::string input(inputBuffer);
	std::stringstream ss(input);
	std::string Token;
	ss >> Token;



	if (IsUnaryOperator(Token)) {
		double value;
		ss >> value;
		double result = EvaluateUnaryOperation(Token, value);
		snprintf(inputBuffer, bufferSize, "%.2f", result);
		return result;
	}

	double num1 = std::stod(Token);
	double num2 = 0;
	char operation = 0;
	

	ss >> operation >> num2;
	double result = 0;

	switch (operation) {
	case '+': result = num1 + num2; break;
	case '-': result = num1 - num2; break;
	case '*': result = num1 * num2; break;
	case '/': result = (num2 != 0) ? num1 / num2 : 0; break;
	case '%': result = fmod(num1, num2); break;

	}
	snprintf(inputBuffer, bufferSize, "%.2f", result);
	return result;

}

void CalculatorHelper::Clear(char* inputBuffer)
{
	inputBuffer[0] = '\0';
}

void CalculatorHelper::Backspace(char* inputBuffer)
{
	unsigned int len = strlen(inputBuffer);

	if (len == 0) { return; };

	if (len >= 4) {
		std::string endOfInput = std::string(inputBuffer + len - 4);
		if (endOfInput == "sin " || endOfInput == "cos " || endOfInput == "tan ") {
			inputBuffer[len - 4] = '\0';
		}

	}
	

		inputBuffer[len - 1] = '\0';
	
}

void CalculatorHelper::AddDecimal(char* inputBuffer, unsigned int bufferSize)
{
	std::string current(inputBuffer);
	if (current.find('.')) {
		if (strlen(inputBuffer) == 0) {
			snprintf(inputBuffer, bufferSize, "0.");
		}
		else {
			strncat_s(inputBuffer, bufferSize, ".", 1);
		}
	}
}

void CalculatorHelper::ToggleNegative(char* inputBuffer, unsigned int bufferSize)
{
}

bool CalculatorHelper::IsUnaryOperator(const std::string& op)
{
	return op == "sin" || op == "cos" || op == "tan";
}
double CalculatorHelper::EvaluateUnaryOperation(const std::string& oper, double value)
{
	double radian = value * M_PI / 180.0;

	if (oper == "sin") return sin(radian);
	if (oper == "cos") return cos(radian);
	if (oper == "tan") return tan(radian);
	

	return value;
}

