#include "CalculatorHelper.h"
#define M_PI 3.14159265358979323846


double CalculatorHelper::EvaluateExpression(char* inputBuffer, unsigned int bufferSize)
{
    std::string input(inputBuffer);

    if (input.empty()) return 0;
    if (isOperator(input.back()) || input.back() == ' ') {
        snprintf(inputBuffer, bufferSize, "Invalid");
        return -1;
    }
    std::vector<std::string> tokens;
    std::string currentNumber;
    bool expectNumber = true;


    //parsing
    for (unsigned int i = 0; i < input.length(); i++) {
        char index = input[i];

        if (std::isspace(index)) continue;

        if (index == '-' && i + 3 < input.length()) {
            std::string possibleTrig = input.substr(i + 1, 3);
            if (possibleTrig == "sin" || possibleTrig == "cos" || possibleTrig == "tan") {
                if (!currentNumber.empty()) {
                    tokens.push_back(currentNumber);
                    currentNumber.clear();
                }
                tokens.push_back("-" + possibleTrig);
                i += 3; 
                expectNumber = true;
                continue;
            }
        }

        if (i + 2 < input.length()) {
            std::string possibleTrig = input.substr(i, 3);
            if (possibleTrig == "sin" || possibleTrig == "cos" || possibleTrig == "tan") {
                if (!currentNumber.empty()) {
                    tokens.push_back(currentNumber);
                    currentNumber.clear();
                }
                tokens.push_back(possibleTrig);
                i += 2;
                expectNumber = true;
                continue;
            }
        }

        if (index == '-') {
            if (expectNumber) {
                currentNumber += index;
                expectNumber = false;
            }
            else {
                if (!currentNumber.empty()) {
                    tokens.push_back(currentNumber);
                    currentNumber.clear();
                }
                tokens.push_back(std::string(1, index));
                expectNumber = true;
            }
        }
        else if (std::isdigit(index) || index == '.') {
            currentNumber += index;
            expectNumber = false;
        }
        else if (isOperator(index)) {
            if (!currentNumber.empty()) {
                tokens.push_back(currentNumber);
                currentNumber.clear();
            }
            tokens.push_back(std::string(1, index));
            expectNumber = true;
        }
    }

    if (!currentNumber.empty()) {
        tokens.push_back(currentNumber);
    }


    std::queue<std::string> output;
    std::stack<std::string> operators;

    for (const auto& token : tokens) {
        if (token.empty()) continue;

        if ((std::isdigit(token[0])) ||
            (token[0] == '-' && token.length() > 1 && std::isdigit(token[1]))) {
            output.push(token);
        }
        else if (IsUnaryOperator(token) ||
            (token.length() > 3 && token[0] == '-' && IsUnaryOperator(token.substr(1)))) {
            operators.push(token);
        }
        else if (token.length() == 1 && isOperator(token[0])) {
            while (!operators.empty() && (IsUnaryOperator(operators.top()) || GetOperatorPrio(operators.top()[0]) >= GetOperatorPrio(token[0]))) {
                output.push(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        output.push(operators.top());
        operators.pop();
    }

    std::stack<double> values;
    //evaluation
    while (!output.empty()) {
        std::string token = output.front();
        output.pop();
       
         if (IsUnaryOperator(token)) {
            if (values.empty()) {
                snprintf(inputBuffer, bufferSize, "Invalid");
                return -1;
            }
            double value = values.top();
            values.pop();
            double result = EvaluateUnaryOperation(token, value);
            values.push(result);
        }
        else if (token.length() == 1 && isOperator(token[0])) {
            if (values.size() < 2) {
                snprintf(inputBuffer, bufferSize, "Invalid");
                return -1;
            }
            double operand2 = values.top(); values.pop();
            double operand1 = values.top(); values.pop();

            double result;
            switch (token[0]) {
            case '+': result = operand1 + operand2; break;
            case '-': result = operand1 - operand2; break;
            case '*': result = operand1 * operand2; break;
            case '/':
                if (operand2 == 0) {
                    snprintf(inputBuffer, bufferSize, "Invalid");
                    return -1;
                }
                result = operand1 / operand2;
                break;
            case '%':
                if (operand2 == 0) {
                    snprintf(inputBuffer, bufferSize, "Invalid");
                    return -1;
                }
                result = fmod(operand1, operand2);
                break;
            default:
                snprintf(inputBuffer, bufferSize, "Invalid");
                return -1;
            }
            values.push(result);
        }
        else {
            values.push(std::stod(token));
        }
    }

    if (values.empty()) {
        return 0;
    }

    double result = values.top();
    FormatOutput(inputBuffer, bufferSize, result);
    return result;
}


void CalculatorHelper::Clear(char* inputBuffer)
{
    inputBuffer[0] = '\0';
}

void CalculatorHelper::Backspace(char* inputBuffer)
{
    size_t len = strlen(inputBuffer);

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
        snprintf(inputBuffer, bufferSize, "%s", current.c_str());

    }


}

bool CalculatorHelper::IsUnaryOperator(const std::string& op)
{
    return op == "sin" || op == "cos" || op == "tan"|| op == "-sin" || op == "-cos" || op == "-tan";
}
bool CalculatorHelper::isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}



int CalculatorHelper::GetOperatorPrio(char op)
{
    switch (op) {
    case '+': case '-': return 1;
    case '*': case '/': case '%': return 2;
    default: return -1;
    }
}

void CalculatorHelper::FormatOutput(char* buffer, unsigned int bufferSize, double value)
{
    if (value == static_cast<unsigned int>(value)) {
        snprintf(buffer, bufferSize, "%.0f", value);
    }
    else {
        snprintf(buffer, bufferSize, "%.4f", value);
    }

}


double CalculatorHelper::EvaluateUnaryOperation(const std::string& oper, double value)
{

    if (oper == "sin") return sin(value);
    if (oper == "cos") return cos(value);
    if (oper == "tan") return tan(value);


    return value;
}

