#include "Token.hpp"

namespace Calc
{
    Token::Token(TokenType type)
    : type(type)
    {
        // Set precedence levels, bigger number is higher precedence
        switch (type)
        {
            case TokenType::MINUS:
            case TokenType::PLUS:
                precedence = 0;
                break;
            case TokenType::STAR:
            case TokenType::SLASH:
                precedence = 1;
                break;
            case TokenType::CARET:
                precedence = 2;
                break;
        }
    }
    Token::Token(TokenType type, double num)
    : type(type), num(num)
    {}

    TokenType Token::getType() const
    {
        return type;
    }

    int Token::getPrecedence() const
    {
        return precedence;
    }

    std::string Token::toString() const
    {
        return std::to_string(static_cast<int>(type)) + ", literal: " + std::to_string(num);
    }

    std::string Token::stringify() const
    {
        switch (type)
        {
        case TokenType::M:
            return "M";
        case TokenType::MINUS:
            return "-";
        case TokenType::P:
            return "P";
        case TokenType::PLUS:
            return "+";
        case TokenType::STAR:
            return "*";
        case TokenType::SLASH:
            return "/";
        case TokenType::CARET:
            return "^";
        case TokenType::NUMBER:
            return std::to_string(num);
        default:
            return "";
            break;
        }
    }
} // namespace Calc