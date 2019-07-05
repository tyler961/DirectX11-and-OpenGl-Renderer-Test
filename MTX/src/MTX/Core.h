#pragma once


// Currently only Windows is supported my MTX
#ifdef MTX_PLATFORM_WINDOWS
	
#else
	#error MTX only supports windows!
#endif

// Used to stop running the program if a critical error occurs to assist with debugging only
#ifdef MTX_ENABLE_ASSERTS
	#define MTX_ASSERT(x, ...) { if(!(x)) { MTX_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MTX_CORE_ASSERT(x, ...) { if(!(x)) { MTX_CORE_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MTX_ASSERT(x, ...)
	#define MTX_CORE_ASSERT(x, ...)
#endif

// For ease of use with event.h
#define BIT(x) (1 << x)

// Binding event functions

// std::function:
// Basically it's a variable to hold a function.

// placeholders let you reorder variables in std::function
// example you have a function show that prints the variables
// using namespace std::placeholders;
// void show(const string& a, const string& b, const string& c) { cout << a << "," << b << "," << c << endl; }
// function<void (string, string, string)> x = bind(show, _1, _3, _2); then do x("one, "two", "three")
// Output: one, three, two
// std::bind is a template function like before but it lets you bind a set of arugments to a function
#define MTX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// Microsoft::WRL::ComPtr<x>
// Reduce messy code
#define COMPTR(x) Microsoft::WRL::ComPtr<x>

