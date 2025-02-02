#pragma once

#include <vector>
#include <stack>
#include <queue>
// Will have to get rid of this later
#include <iostream>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Errors.hpp"

namespace Calc
{
    // implemented using the Shunting Yard Algorithm in Reverse Polish Notation
    class Parser
    {
    public:
        // Maybe pass tokens along using smart pointers?
        Parser(std::vector<Token> tokens);
        std::queue<Token> parse();

    private:
        
        Token& advance();
        Token& previous();
        bool isAtEnd() const;
        bool checkOperatorType(TokenType type) const;
        bool isLeftAssociative(TokenType type) const;
        bool isRightAssociative(TokenType type) const;
        bool isOperator(TokenType type) const;

        std::vector<Token> tokens;

        std::stack<Token> operators;
        std::queue<Token> output;
        // Keeps track of parenthesis encapsulation ex. 2(3(2))
        std::stack<bool> multStack;
        int current{0};
    };
} // namespace Calc