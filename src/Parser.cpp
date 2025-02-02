#include "Parser.hpp"

// Credit to MacTee on github whose c# implementation of the 
// shunting yard algorithm added unary operators...
namespace Calc
{
    Parser::Parser(std::vector<Token> tokens)
    : tokens(std::move(tokens))
    { }

    // Not a very pretty implementation, but it is really simple
    std::queue<Token> Parser::parse()
    {
        bool first = true;
        bool afterParen = false;
        TokenType lastTokenType;
        // Read all tokens except for EOF
        while (!isAtEnd())
        {
            // Just so I don't have to copy the token in the stack to access it 
            // Dunno if it has any effect on performance
            Token* tokenptr = &tokens.at(current);
            TokenType currType = tokenptr->getType();
            if (currType == TokenType::NUMBER)
            {
                // Need to decide how to store tokens
                output.push((*tokenptr));
            }
            // Get ready for some uncommented code 
            else if (isOperator(currType))
            {
                Token* currentOpptr = tokenptr;
                TokenType currentOp = currentOpptr->getType();
                if (first && currentOp == TokenType::MINUS)
                {
                    currentOpptr->type = currentOp = TokenType::M;
                }
                else if (first && currentOp == TokenType::PLUS)
                {
                    currentOpptr->type = currentOp = TokenType::P;
                }
                else if (operators.size() > 0)
                {
                    Token* lastOpptr = &operators.top();
                    TokenType lastOp = lastOpptr->getType();
                    if (!afterParen)
                    {
                        // Check for a negation after an open parenthesis or another operator
                        if ((isOperator(lastOp) || lastOp == TokenType::LEFT_PAREN) &&
                            currentOp == TokenType::MINUS && lastOp != TokenType::P && 
                            lastOp != TokenType::M && lastTokenType != TokenType::NUMBER)
                        {
                            currentOpptr->type = currentOp = TokenType::M;
                        }
                        // Check of a positation(?) after an open parenthesis or another operator
                        if ((isOperator(lastOp) || lastOp == TokenType::LEFT_PAREN) 
                            && currentOp == TokenType::PLUS && lastOp != TokenType::P && lastOp != TokenType::M && lastTokenType != TokenType::NUMBER)
                        {
                            currentOpptr->type = currentOp =  TokenType::P;
                        }
                    }
                    while (isOperator(lastOp))
                    {
                        if (isLeftAssociative(currentOp) && operators.top().getPrecedence() >= tokenptr->getPrecedence() ||
                            isRightAssociative(currentOp) && operators.top().getPrecedence() > tokenptr->getPrecedence())
                        {
                            output.push(operators.top());
                            operators.pop();
                        
                            if (operators.size() == 0)
                            {
                                break;
                            } else
                            {
                                lastOp = operators.top().getType();
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                operators.push(*currentOpptr);

                afterParen = false;
            }
            else if (currType == TokenType::LEFT_PAREN)
            {
                if (!isOperator(lastTokenType))
                {
                    multStack.push(1);
                }
                operators.push((*tokenptr));
            }
            else if (currType == TokenType::RIGHT_PAREN)
            {
                if (operators.empty())
                {
                    throw SyntaxError("Mismatched parenthesis, missing '('");
                }
                TokenType lastOp  = operators.top().getType();
                while (lastOp != TokenType::LEFT_PAREN)
                {
                    output.push(operators.top());
                    operators.pop();
                    if (operators.size() == 0)
                    {
                        throw SyntaxError("Mismatched parenthesis, missing '('");
                    }
                    lastOp = operators.top().getType();
                }
                if (operators.size() == 0)
                {
                    throw SyntaxError("Mismatched parenthesis, missing '('");
                }
                // Discard left parenthesis (or change it in to a multiplication)
                if (!multStack.empty())
                {
                    operators.top().type = TokenType::STAR;
                    output.push(operators.top());
                    multStack.pop();
                }   
                operators.pop();
                afterParen = true;
            }
            else
            {
                // Will hopefully never run
                throw SyntaxError("Unknown symbol");
            }
            ++current;
            lastTokenType = tokenptr->getType();
            first = false;
        }
        // Pop entire stack to output
        while (operators.size() > 0)
        {
            if (checkOperatorType(TokenType::LEFT_PAREN) || checkOperatorType(TokenType::RIGHT_PAREN))
            {
                // Yet Another Error!!
                throw SyntaxError("Mismatched parenthesis, missing ')'");
            } else
            {
                output.push(operators.top());
                operators.pop();
            }
        }
        return output;
    }

    Token& Parser::previous()
    {
        return tokens.at(current - 1);
    }

    Token& Parser::advance() 
    {
        return tokens.at(current++);
    }

    bool Parser::isAtEnd() const 
    {
        return tokens.at(current).getType() == TokenType::TokenEOF;
    }

    bool Parser::checkOperatorType(TokenType type) const
    {
        return operators.top().getType() == type;
    }

    // Makes me sad :(
    bool Parser::isLeftAssociative(TokenType type) const
    {
        switch (type)
        {
        case TokenType::PLUS:
        case TokenType::MINUS:
        case TokenType::STAR:
        case TokenType::SLASH:
            return true;
        }
        return false;
    }

    bool Parser::isRightAssociative(TokenType type) const
    {
        return isLeftAssociative(type);
    }

    bool Parser::isOperator(TokenType type) const
    {
        if (type < TokenType::DOT)
        {
            return true;
        }
        return false;
    }

} // namespace Calc