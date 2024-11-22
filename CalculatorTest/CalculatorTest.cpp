#include "pch.h"
#include "CppUnitTest.h"
#include "../SWE_App/CalculatorHelper.cpp"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTest
{
	TEST_CLASS(CalculatorTest)
	{
	private: 
		CalculatorHelper* calculateHelper;
		char inputBuffer[512];
	public:
		//I wanted to add button tests but you have to render a new window just to test the buttons
		
		TEST_METHOD(SanityTest)
		{
			Assert::IsTrue(true);
		}
		TEST_METHOD(BasicAddition) {
			strcpy_s(inputBuffer, "2+3");
			double result = calculateHelper->EvaluateExpression(inputBuffer, sizeof(inputBuffer));
			Assert::AreEqual(5.0, result);
		}
		TEST_METHOD(BasicSubtraction) {
			strcpy_s(inputBuffer, "6-2");
			double result = calculateHelper->EvaluateExpression(inputBuffer, sizeof(inputBuffer));
			Assert::AreEqual(4.0, result);
		}
		TEST_METHOD(Multiplication) {
			strcpy_s(inputBuffer, "4*6");
			double result = calculateHelper->EvaluateExpression(inputBuffer, sizeof(inputBuffer));
			Assert::AreEqual(24.0, result);
		}
		TEST_METHOD(Division) {
			strcpy_s(inputBuffer, "10/2");
			double result = calculateHelper->EvaluateExpression(inputBuffer, sizeof(inputBuffer));
			Assert::AreEqual(5.0, result);
		}
		TEST_METHOD(Modulus) {
			strcpy_s(inputBuffer, "17%5");
			double result = calculateHelper->EvaluateExpression(inputBuffer, sizeof(inputBuffer));
			Assert::AreEqual(2.0, result);
		}
		TEST_METHOD(Sin) {
			strcpy_s(inputBuffer, "sin 1");
			double result = calculateHelper->EvaluateExpression(inputBuffer, sizeof(inputBuffer));
			Assert::AreEqual(sin(1), result, 0.0001);
		}
		TEST_METHOD(Cos) {
			strcpy_s(inputBuffer, "cos 1");
			double result = calculateHelper->EvaluateExpression(inputBuffer, sizeof(inputBuffer));
			Assert::AreEqual(cos(1), result, 0.0001);
		}
		TEST_METHOD(Tan) {
			strcpy_s(inputBuffer, "tan 1");
			double result = calculateHelper->EvaluateExpression(inputBuffer, sizeof(inputBuffer));
			Assert::AreEqual(tan(1), result, 0.0001);
		}
		TEST_METHOD(NegativeTrig) {
			strcpy_s(inputBuffer, "-tan 1");
			double result = calculateHelper->EvaluateExpression(inputBuffer, sizeof(inputBuffer));
			Assert::AreEqual(-tan(1), result);
		}
		TEST_METHOD(InvalidInput) {
			strcpy_s(inputBuffer, "5++2+");
			double result = calculateHelper->EvaluateExpression(inputBuffer, sizeof(inputBuffer));
			Assert::AreEqual(std::string("Invalid"), std::string(inputBuffer));
		}
		TEST_METHOD(Clear) {
			calculateHelper->Clear(inputBuffer);
			Assert::AreEqual('\0', inputBuffer[0]);
		}
		
	};
}
