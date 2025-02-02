#pragma once

#include <string>
#include <exception>

// Make sure you save the expression when you hit an error
// Syntax errors are only thrown during parsing and only serves to halt further
// parsing (and the whole program breaking) and unwind all the way back, passing
// the error message back to the user
namespace Calc
{
    class SyntaxError : public std::exception 
    {
    public:
        SyntaxError(const char* msg) 
        : message(msg)
        { }
        const char* what() const throw()
        {
            return message.c_str();
        }
    private:
        std::string message;
    };
    // Basically the same thing, but allows for these errors to be caught and identified separately
    class RuntimeError : public std::exception 
    {
    public:
        RuntimeError(const char* msg)
        : message(msg)
        { }
        const char* what() const throw()
        {
            return message.c_str();
        }
    private:
        std::string message;

    };
    class RenderError : public std::exception 
    {
    public:
        RenderError(std::string msg)
        : message(msg)
        { }
        const char* what() const throw()
        {
            return message.c_str();
        }
    private:
        std::string message;

    };
} // namespace Calc