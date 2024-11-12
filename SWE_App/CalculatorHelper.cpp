#include "CalculatorHelper.h"
#define M_PI 3.14159265358979323846

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
	std::string current(inputBuffer);
	if (current.empty()) {
		snprintf(inputBuffer, bufferSize, "-");
	}
	else if (current[0] == '-') {
		current = current.substr(1);
		snprintf(inputBuffer, bufferSize, "%s", current.c_str());
	}
	else {
		std::string temp = "-" + current;
		snprintf(inputBuffer, bufferSize, "%s", temp.c_str());

	}


}

bool CalculatorHelper::IsUnaryOperator(const std::string& op)
{
	return op == "sin" || op == "cos" || op == "tan";
}
double CalculatorHelper::EvaluateUnaryOperation(const std::string& oper, double value)
{
	//double radian = value * M_PI / 180.0;

	if (oper == "sin") return sin(value);
	if (oper == "cos") return cos(value);
	if (oper == "tan") return tan(value);
	

	return value;
}

