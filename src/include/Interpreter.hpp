#pragma once

#include <queue>
#include <stack>
#include <cmath>

#include "Token.hpp"
#include "Errors.hpp"

namespace Calc
{
    class Interpreter
    {
    public:
        Interpreter();
        ~Interpreter();
        double execute(std::queue<Token>& expression);

    private:
        std::stack<double> operands;
    };
} // namespace Calc