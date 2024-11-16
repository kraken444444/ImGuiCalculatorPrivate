#include "CalculatorHelper.h"
#define M_PI 3.14159265358979323846

double CalculatorHelper::EvaluateExpression(char* inputBuffer, unsigned int bufferSize)
{

    //Spaghetti monster
    //converting input buffer to a string for handling
    std::string input(inputBuffer);

    //checks if its a unary operator
    std::stringstream ss(input);
    std::string firstToken;
    ss >> firstToken;
    int tokenLength = 1;
    if (IsUnaryOperator(firstToken)) {
        double value;
        ss >> value; //gets the number after sin/cos/tan
        double result = EvaluateUnaryOperation(firstToken, value);
        snprintf(inputBuffer, bufferSize, "%.9f", result);
        return result;
    }

    std::vector<std::string> tokens;
    std::string number;
    bool lastWasOperator = true; // true at start for first negative number

    for (unsigned int i = 0; i < input.length(); i++) {
        char c = input[i];

        if (std::isspace(c)) continue;  //skips white space in string

        //handles numbers, decimals, and negative numbers and builds up the number string
        if (std::isdigit(c) || c == '.' || (c == '-' && lastWasOperator && i + 1 < input.length() && std::isdigit(input[i + 1]))) {
            number += c;                
            lastWasOperator = false;
        }
        //handles the operators
        else if (isOperator(c)) {
            if (!number.empty()) {
                tokens.push_back(number); //saves accumulated number
                number.clear();
            }
            tokens.push_back(std::string(tokenLength, c)); //saves the operator
            lastWasOperator = true;
        }
    }
    //pushes back if not empty yet
    if (!number.empty()) {
        tokens.push_back(number);
    }

    std::queue<std::string> output;
    std::stack<char> operators;

    for (const auto& token : tokens) {
        if (token.empty()) continue;

        // checking if its a number(also negative)
        if (std::isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && std::isdigit(token[1]))) {
            output.push(token); // numbers go to output if it's a number
        }
        // if its an operator it goes to output
        else if (token.length() == 1 && isOperator(token[0])) {
            while (!operators.empty() && GetOperatorPrio(operators.top()) >= GetOperatorPrio(token[0])) {
                output.push(std::string(1, operators.top()));
                operators.pop();
            }
            operators.push(token[0]); 
        }
    }
    // remaining operators
    while (!operators.empty()) {
        output.push(std::string(1, operators.top()));
        operators.pop();
    }

    std::stack<double> values; //stack of doubles for holding numbers during calculation

    while (!output.empty()) {
        std::string token = output.front();
        output.pop();

        //if its an operator
        if (token.length() == 1 && isOperator(token[0])) {
            if (values.size() < 2) { // at least 2 numbers for an operation
                snprintf(inputBuffer, bufferSize, "Invalid");
                return 0;
            }
            double b = values.top(); values.pop();// numbers for operations
            double a = values.top(); values.pop();

            double result;
            switch (token[0]) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) { // no dividing by zero! what are you? crazy? 
                    snprintf(inputBuffer, bufferSize, "Invalid");
                    return 0;
                }
                result = a / b;
                break;
            case '%':
                if (b == 0) { //don't even think about it
                    snprintf(inputBuffer, bufferSize, "Invalid");
                    return 0;
                }
                result = fmod(a, b);
                break;
            default:
                snprintf(inputBuffer, bufferSize, "Invalid");
                return 0;
            }
            values.push(result); //result goes on the stack
        }
        else {
            
                values.push(std::stod(token)); //cast string to a double
        }
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
		snprintf(inputBuffer, bufferSize, "%s", current.c_str());

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

double CalculatorHelper::EvaluateUnaryOperation(const std::string& oper, double value)
{

	if (oper == "sin") return sin(value);
	if (oper == "cos") return cos(value);
	if (oper == "tan") return tan(value);
	

	return value;
}

