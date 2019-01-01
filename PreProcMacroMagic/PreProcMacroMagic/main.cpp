#include <iostream>
#include <chrono>

// Object-like Macros (Simple text substitution macro)
#define VERSION 123
#define CONCATENATED 123 << "hello"

// Function-like Macros
#define MULTIPLY(a, b) ((a) * (b))

// Variadic macro
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)

// If statement - pattern matching
#define IF_ELSE(condition) _IF_ ## condition
#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE
#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

// If statement - cast to bool / negation
// It doesn't seem to work in VS. Reason can not be __VA_ARGS__ , because that works just fine in the DEBUG() macro
// Related links:
// https://stackoverflow.com/questions/5588855/standard-alternative-to-gccs-va-args-trick
#define SECOND(a, b, ...) b
#define CAT(a,b) a ## b
#define IS_PROBE(...) SECOND(__VA_ARGS__, 0) 
#define PROBE() 999, 1
#define NOT(x) IS_PROBE(CAT(_NOT_, x))
#define _NOT_0 PROBE()
#define BOOL(x) NOT(NOT(x))

// Iterators - recursive macros are explicitly bloacked, but we can force CPP to make multiple passes
// e.g.: A EMPTY() (123) will be evaluated as A(123) only when embedded into another macro:
// EVAL1(...) __VA_ARGS__
#define EMPTY() 
#define A(n) I like the number n
#define EVAL1(...) __VA_ARGS__

using namespace std;

// OFFTOPIC - generate current time in milliseconds converted to long long
chrono::system_clock::time_point now = chrono::system_clock::now();
auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>( now );
auto epoch = now_ms.time_since_epoch();
auto value = std::chrono::duration_cast<std::chrono::milliseconds>( epoch );
long long timeAtStart = value.count();

int main( int argc, char** argv )
{
    cout << "Version: " << VERSION << endl;
    cout << "Rubbish: " << CONCATENATED << endl;
    cout << "Multiply (2+5) * (26-7): " << MULTIPLY(2+5, 26-7) << endl;
    DEBUG( "John was born in %s, %s. Her mothers name is %s.\n", "London", "1980.02.11", "Joanna" );
    DEBUG( "Negate 1: %d, negate 0: %d, negate 158: %d\n", NOT(1), NOT(0), NOT(158) );
    DEBUG( "1 to BOOL: %d, 0 to BOOL: %d, 158 to BOOL: %d\n", BOOL(1), BOOL(0), BOOL(158) );

    return 0;
}