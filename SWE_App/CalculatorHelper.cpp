#include "CalculatorHelper.h"
#define M_PI 3.14159265358979323846

double CalculatorHelper::EvaluateExpression(char* inputBuffer, unsigned int bufferSize)
{
    std::string input(inputBuffer);

    std::stringstream ss(input);
    std::string firstToken;
    ss >> firstToken;
    if (IsUnaryOperator(firstToken)) {
        double value;
        ss >> value;
        double result = EvaluateUnaryOperation(firstToken, value);
        snprintf(inputBuffer, bufferSize, "%.9f", result);
        return result;
    }

    // Tokenize input
    std::vector<std::string> tokens = TokenizeInput(input);

    std::queue<std::string> output;
    std::stack<char> operators;

    for (const std::string& token : tokens) {
        if (token.empty()) continue;

        char firstChar = token[0];

        // If token is a number
        if (std::isdigit(firstChar) || (firstChar == '-' && token.length() > 1)) {
            output.push(token);
        }
        else if (isOperator(firstChar)) {
            while (!operators.empty() &&
                GetOperatorPrio(operators.top()) >= GetOperatorPrio(firstChar)) {
                output.push(std::string(1, operators.top()));
                operators.pop();
            }
            operators.push(firstChar);
        }
    }

    while (!operators.empty()) {
        if (operators.top() != '(') {
            output.push(std::string(1, operators.top()));
        }
        operators.pop();
    }

    std::stack<double> values;
    while (!output.empty()) {
        std::string token = output.front();
        output.pop();

        if (!token.empty() && isOperator(token[0])) {
            if (values.size() < 2) {
                snprintf(inputBuffer, bufferSize, "Invalid");
                return 0;
            }
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            values.push(ApplyOperation(b, a, token[0]));
        }
        else {
            try {
                values.push(std::stod(token));
            }
            catch (const std::exception& e) {
                snprintf(inputBuffer, bufferSize, "Invalid");
                return 0;
            }
        }
    }

    if (values.empty()) {
        snprintf(inputBuffer, bufferSize, "Invalid");
        return 0;
    }

    double result = values.top();
    snprintf(inputBuffer, bufferSize, "%.4f", result);
    return result;
}



void CalculatorHelper::Clear(char* inputBuffer)
{
	inputBuffer[0] = '\0';
}

void CalculatorHelper::Backspace(char* inputBuffer)
{
	size_t len = strlen(inputBuffer);

	if (len == 0) {return;};

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
bool CalculatorHelper::isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

double CalculatorHelper::ApplyOperation(double a, double b, char op)
{

	
	switch (op) {
	case '+': return a + b; 
	case '-':return a - b; 
	case '*': return a * b; 
	case '/': return (b != NULL) ? a / b : NULL; 
	case '%': return fmod(a, b); 
	default: return NULL;
	}
	
}

int CalculatorHelper::GetOperatorPrio(char op)
{
	switch (op) {
	case '+': case '-': return 1;
	case '*': case '/': case '%': return 2;
	default: return -1;
	}
}

std::vector<std::string> CalculatorHelper::TokenizeInput(const std::string& input)
{

	char space = ' ';

	std::vector<std::string> tokens;
	std::string currentNumber;
	int strLength = 1;
	for (unsigned int i = 0; i < input.length(); i++) {
		char c = input[i];

		if (c == space) {
			if (!currentNumber.empty()) {
				tokens.push_back(currentNumber);
				currentNumber.clear();
			}
			continue;
		}

		if (c == '-') {
			if (i == 0 || (i > 0 && isOperator(input[i - 1]))) {
				currentNumber += c;
			}
			else {
				if (!currentNumber.empty()) {
					tokens.push_back(currentNumber);
					currentNumber.clear();
				}
				tokens.push_back(std::string(strLength, c));
			}
		}

		else if (std::isdigit(c) || c == '.') {
			currentNumber += c;
		}
		else if (isOperator(c)) {
			if (!currentNumber.empty()) {
				tokens.push_back(currentNumber);
				currentNumber.clear();
			}
			tokens.push_back(std::string(strLength, c));
		}
	}
	if (!currentNumber.empty()) {
		tokens.push_back(currentNumber);
	}
	return tokens;
}



double CalculatorHelper::EvaluateUnaryOperation(const std::string& oper, double value)
{

	if (oper == "sin") return sin(value);
	if (oper == "cos") return cos(value);
	if (oper == "tan") return tan(value);
	

	return value;
}

