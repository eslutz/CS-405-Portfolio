// questionable_code.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Eric Slutz
// SNHU - CS405 Secure Coding
// Module 5 Assignment 3
//

#include <cassert>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

// TODO: You are going to compare the warnings & errors between Visual Studio and CppCheck.
//  Make sure you are using CppCheck 2.1 or greater
//
//  1. Create a Visual Studio Console project with this file as the only file
//  2. Compile it and check the warning and errors
//  3. Create a CppCheck project to analyze a Visual Studio project with this file.
//  4. In CppCheck Edit / Preferences / General Tab: Set Display error id in column "Id", Enable inline suppressions, and Check for inconclusive errors also
//  5. In CppCheck View, Select Check All to ensure all types of checks are enabled
//  6. In CppCheck Analyze, set the C++ Standard to C++17, and Enforce C++
//  7. Make sure to run the analysis
//  8. Save the results to a file (XML format)
//  9. Take a screen shot of the Visual Studio Error list (all errors, warnings, and messages)
//  10. Identify all messages from CppCheck NOT identified in Visual Studio.
//      For each message not in both:
//        Identify the risk as: RISK or NOT RISK
//        Identify which system (Visual Studio or CppCheck) found the issue
//        Provide a couple of sentences describing the issue found

class C
{
    std::set<int> typedefs;
    bool is_type(int type) const
    {
        if (typedefs.find(type) != typedefs.end())
            return is_type(type); // BUG: endless recursion
        return false;
    }
};

class A
{
    int x;
    A(const A& other) {}
};

class MySpecialType
{
public:
    int MyVal = 1;

    void DontThrow() noexcept
    {
        throw "Ha! I threw anyway!";
    }
};

void foo(int** a)
{
    int b = 1;
    *a = &b;
}

void work_with_arrays(int count)
{
    int buf[10];
    if (count == 1000)
        buf[count] = 0; // <- ERROR
}

void do_something_useless()
{
    int sum = 0;
    for (auto i = 0; i < 1000; ++i)
    {
        sum += i;
    }

    std::cout << "I summed up " << sum << " as the answer." << std::endl;
}

void vector_test()
{
    std::vector<int> items;
    items.push_back(1);
    items.push_back(2);
    items.push_back(3);
    std::vector<int>::iterator iter;
    for (iter = items.begin(); iter != items.end(); ++iter) {
        if (*iter == 2) {
            items.erase(iter);
        }
    }
}

int a;
bool my_function()
{
    a = 1 + 2;
    return a;
}

struct Token
{
    Token* next() { return nullptr; }
};

int foo(Token* tok)
{
    while (tok);
    tok = tok->next();

    return 0;
}

int main()
{
    std::vector<int> counts { 1, 2, 3, 5 };
    int x = 0;
    int y = 0;
    int z = 0;

    std::cout << "Welcome to the Questionable Code Test!" << std::endl;

    //do_something_useless();

    work_with_arrays(10);

    assert(z = 2);

    assert(my_function() == 3);

    try
    {
        int x = 5;
        int y = 5;
        int z = 5;
        std::cout << "x + y + z = " << (x + y + z) << std::endl;
    }
    catch (...)
    {

    }

    int* c;
    foo(&c);

    vector_test();

    MySpecialType myobject;
    std::cout << "myobject.MyVal = " << myobject.MyVal << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
