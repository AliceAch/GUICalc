#pragma once

#include <vector>
#include <string>

#include "Token.hpp"
#include "Errors.hpp"

namespace Calc
{
    class Scanner
    {
    public:
        Scanner(std::string expression);
        std::vector<Token> scanTokens();
    private:
        bool isAtEnd() const;
        char advance();
        void addToken(TokenType type);
        void addToken(TokenType type, double num);
        void scanToken();
        void number();
        void dot();
        char peek() const;
        char peekNext() const;
        std::string expression;
        std::vector<Token> tokens;

        int start = 0;
        int current = 0;
    };
} // namespace Calc