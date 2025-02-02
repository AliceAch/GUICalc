#include "Interpreter.hpp"

#include <iostream>

namespace Calc
{
    Interpreter::Interpreter()
    {

    }

    Interpreter::~Interpreter() = default;

    double Interpreter::execute(std::queue<Token>& expressions)
    {
        while(!expressions.empty())
        {
            Token* tokenptr = &expressions.front();
            TokenType currType = tokenptr->getType();
            // Check if the token is a binary operator
            if(currType < TokenType::P)
            {
                if (operands.empty())
                {
                    throw RuntimeError("Incomplete number of operands for binary operator");
                }
                double operand1 = operands.top();
                operands.pop();
                if (operands.empty())
                {
                    throw RuntimeError("Incomplete number of operands for binary operator");
                }
                double operand2 = operands.top();
                operands.pop();
                switch (currType)
                {
                case TokenType::MINUS:
                    operands.push(operand2 - operand1);
                    #ifdef DEBUG
                     << operand2 << " - " << operand1 << std::endl;
                    #endif
                    break;
                case TokenType::PLUS:
                    operands.push(operand2 + operand1);
                    #ifdef DEBUG
                    std::cout << operand2 << " + " << operand1 << std::endl;
                    #endif
                    break;
                case TokenType::STAR:
                    operands.push(operand2 * operand1);
                    #ifdef DEBUG
                    std::cout << operand2 << " * " << operand1 << std::endl;
                    #endif
                    break;
                // Make sure you handle divide by zero error
                case TokenType::SLASH:
                    if (operand1 == 0)
                    {
                        throw RuntimeError("Divide by zero error");
                    }
                    operands.push(operand2 / operand1);
                    #ifdef DEBUG
                    std::cout << operand2 << " / " << operand1 << std::endl;
                    #endif
                    break;
                // Technically cheating that I didn't implement the power function
                case TokenType::CARET:
                    operands.push(pow(operand2, operand1));
                    #ifdef DEBUG
                    std::cout << operand2 << " ^ " << operand1 << std::endl;
                    #endif
                    break;
                }
            // Check if the token is a unary operator (P/M)
            } else if (currType < TokenType::DOT)
            {
                if (currType == TokenType::M)
                {
                    if (operands.empty())
                    {
                    throw RuntimeError("Incomplete number of operands for unary operator");
                    }
                    double operand = -operands.top();
                    operands.pop();
                    operands.push(operand);
                }
                
            } 
            else
            {
                // It's a number; push the value onto the stack
                operands.push(tokenptr->num);
            }
            expressions.pop();
        }
        if (operands.size() != 1)
        {
            return 0;
        }
        double output = operands.top();
        // Very hacky, 
        if (std::isinf(output))
        {
            throw RuntimeError("OVERFLOW");
        } 
        return operands.top();
    }
} // namespace Calc