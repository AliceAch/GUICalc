#pragma once

#include <string>

#include <TokenType.hpp>

namespace Calc
{
    class Token
    {
    public:
        // for number literals
        Token(TokenType type, double num);
        // for operators
        Token(TokenType type);
        double num = 0;
        TokenType getType() const;
        int getPrecedence() const;
        // for debugging
        std::string toString() const;
        std::string stringify() const;
        TokenType type;
    private:
        // Shoddy solution, but eh it's fine
        // bigger number is a higher precedence
        // Precedence of -1 means an operand/literal
        int precedence = -1;
    };
} // namespace Calc