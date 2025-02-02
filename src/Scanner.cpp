#include "Scanner.hpp"

// Extremely simple scanner, not much to do
namespace Calc
{
    Scanner::Scanner(std::string expression)
    : expression(expression)
    {}

    std::vector<Token> Scanner::scanTokens()
    {
        while(!isAtEnd())
        {
            start = current;
            scanToken();
        }
        tokens.emplace_back(TokenType::TokenEOF);
        return tokens;
    }

    void Scanner::scanToken()
    {
        auto c = advance();
        switch (c) 
        {
            // Add a case for just decimal numbers (like .45)
            case '.': dot(); break;
            case '-': addToken(TokenType::MINUS); break;
            case '+': addToken(TokenType::PLUS); break;
            case '*': addToken(TokenType::STAR); break;
            case '/': addToken(TokenType::SLASH); break;
            case '^': addToken(TokenType::CARET); break;
            case '(': addToken(TokenType::LEFT_PAREN); break;
            case ')': addToken(TokenType::RIGHT_PAREN); break;
            default:
                number();
                break;
        }
    }
    void Scanner::number()
    {
        while(std::isdigit(peek())) advance();
        // Look for the fractional part
        if (peek() == '.' && std::isdigit(peekNext()))
        {
            // Consume the dot
            advance();

            while (std::isdigit(peek())) 
                advance();
            if (peek() == '.')
            {
                //ERROR
                throw SyntaxError("Unexpected character '.'");
            }
        }
        addToken(TokenType::NUMBER, std::stod(expression.substr(start, current - start)));
    }
    // basically the same, except no extra dots
    void Scanner::dot()
    {
        while(std::isdigit(peek())) advance();
            if (peek() == '.')
                throw SyntaxError("Unexpected character '.'");
        addToken(TokenType::NUMBER, std::stod(expression.substr(start, current - start)));

    }
    char Scanner::peek() const
    {
        if (isAtEnd())
            return '\0';
        return expression.at(current);
    }
    char Scanner::peekNext() const
    {
        if (current + 1 >= static_cast<int>(expression.size())) return '\0';
        return expression.at(current + 1);
    }
    char Scanner::advance()
    {
        current++;
        return expression.at(current-1);
    }
    bool Scanner::isAtEnd() const
    {
        return current >= static_cast<int>(expression.size());
    }
    void Scanner::addToken(TokenType type)
    {
        tokens.emplace_back(type);
    }
    void Scanner::addToken(TokenType type, double num)
    {
        tokens.emplace_back(type, num);
    }
} // namespace Calc 
