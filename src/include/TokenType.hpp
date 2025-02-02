#pragma once

// Possibly add functions ?
namespace Calc
{
    enum class TokenType
    {
        // Operators (P and M are unary plus and minus, respectively)
        MINUS, PLUS, SLASH, STAR, CARET, P, M, DOT, 

        // One character token
        LEFT_PAREN, RIGHT_PAREN, EQUAL,

        // literals
        NUMBER,

        TokenEOF
    };

} // namespace Calc