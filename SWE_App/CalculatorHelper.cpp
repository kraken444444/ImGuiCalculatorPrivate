#include "CalculatorHelper.h"
CalculatorHelper* CalculatorHelper::instance = nullptr;

double CalculatorHelper::EvaluateExpression(char* inputBuffer, unsigned int bufferSize)
{
    std::string input(inputBuffer);

    if (input.empty()) return 0;
    if (isOperator(input.back()) || input.back() == ' ') {
        snprintf(inputBuffer, bufferSize, "Invalid"); //input validation
        return -1;
    }
    std::vector<std::string> tokens;
    std::string currentNumber;
    bool expectNumber = true;


    //parsing
    for (unsigned int i = 0; i < input.length(); i++) {
        char index = input[i];

        if (std::isspace(index)) continue; // skips blank space 

        if (index == '-' && i + 3 < input.length()) { //checking for trig function
            std::string possibleTrig = input.substr(i + 1, 3); //checking for possible negative trig function
            if (possibleTrig == "sin" || possibleTrig == "cos" || possibleTrig == "tan") {
                if (!currentNumber.empty()) {
                    tokens.push_back(currentNumber);
                    currentNumber.clear();
                }
                tokens.push_back("-" + possibleTrig);
                i += 3; //skips if negative trig function
                expectNumber = true;
            }
        }

        if (i + 2 < input.length()) {
            std::string possibleTrig = input.substr(i, 3); //checking for regular trig function
            if (possibleTrig == "sin" || possibleTrig == "cos" || possibleTrig == "tan") {
                if (!currentNumber.empty()) {
                    tokens.push_back(currentNumber);
                    currentNumber.clear();
                }
                tokens.push_back(possibleTrig);
                i += 2; //skips if its a trig function to keep our loop correct
                expectNumber = true;
            }
        }

        if (index == '-') {
            if (expectNumber) {
                currentNumber += index; //this is how im handling multiple - signs in the input, if user inputs -sin6 --sin6 this should work
                expectNumber = false;
            }
            else {
                if (!currentNumber.empty()) {
                    tokens.push_back(currentNumber);
                    currentNumber.clear();
                }
                tokens.push_back(std::string(sizeof(index), index));
                expectNumber = true;
            }
        }
        else if (std::isdigit(index) || index == '.') {
            currentNumber += index; //could have used my own class to check if something is a number but std::isdigit works great for what i'm trying to do
            expectNumber = false;
        }
        else if (isOperator(index)) {
            if (!currentNumber.empty()) { //checks if its an operator
                tokens.push_back(currentNumber);
                currentNumber.clear();
            }
            tokens.push_back(std::string(sizeof(index), index)); //make this more clear with sizeof(index)
            expectNumber = true; //this essentially just pushes back a 'string' with the size of the index instead of magic numbers
        }
    }
    
    if (!currentNumber.empty()) {
        tokens.push_back(currentNumber);
    }
    


    std::queue<std::string> output; // queue for output could have just used a vector for both but wanted to try something different
    std::stack<std::string> operators;// operators

    for (const auto& token : tokens) {
        if (token.empty()) continue; 
        //separates numbers and operators into their own queue and stack. I probably could use a stack or queue for both but this just works
        //so im not messing with it anymore
        
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
                return -1; //if user enters a unary operator with no numbers
            }
                double value = values.top();
                values.pop();
                double result = EvaluateUnaryOperation(token, value);
                values.push(result); //evaluates unary operation with the unary operator and value
            
        }
        else if (token.length() == 1 && isOperator(token[0])) {
            if (values.size() < 2) {
                snprintf(inputBuffer, bufferSize, "Invalid");
                return -1;
            }
            double operand2 = values.top(); values.pop(); // sets the value then removes it from top of stack
            double operand1 = values.top(); values.pop();

            double result;
            //calcuations
            switch (token[0]) {
            case '+': result = operand1 + operand2; break;
            case '-': result = operand1 - operand2; break;
            case '*': result = operand1 * operand2; break;
            case '/':
                if (operand2 == 0) {
                    snprintf(inputBuffer, bufferSize, "Invalid");
                    return -1; // no dividing by 0 or % by 0
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
        return 0; // does nothing if value is empty
    }

    double result = values.top(); // returns value at the top of the stack
    FormatOutput(inputBuffer, bufferSize, result);
    return result;
}


void CalculatorHelper::Clear(char* inputBuffer)
{
    inputBuffer[0] = '\0'; // first index null terminator

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
//adds decimal
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
// unary operator check
bool CalculatorHelper::IsUnaryOperator(const std::string& op)
{
    return op == "sin" || op == "cos" || op == "tan"|| op == "-sin" || op == "-cos" || op == "-tan";
}
bool CalculatorHelper::isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}


//operator priority
int CalculatorHelper::GetOperatorPrio(char op)
{
    switch (op) {
    case '+': case '-': return 1;
    case '*': case '/': case '%': return 2;
    default: return -1;
    }
}

//formatting input if value is not a double
void CalculatorHelper::FormatOutput(char* buffer, unsigned int bufferSize, double value)
{
    if (value == static_cast<int>(value)) {
        snprintf(buffer, bufferSize, "%.0f", value);
    }
    else {
        snprintf(buffer, bufferSize, "%.4f", value);
    }

}

//unary evaluation 
double CalculatorHelper::EvaluateUnaryOperation(const std::string& oper, double value)
{

    if (oper == "sin") return sin(value);
    if (oper == "cos") return cos(value);
    if (oper == "tan") return tan(value);
    if (oper == "-tan") return -tan(value);
    if (oper == "-cos") return -cos(value);
    if (oper == "-sin") return -sin(value);


    return value;
}



