#ifndef ANSWERSOBJECTS
#define ANSWERSOBJECTS

#include <cstring>
#include <iostream>
#include <string>
#include <memory>
#include <functional>

namespace Teramind {

//======================================================================================================================
/// TODO: insert ScalarTypes class description here
struct ScalarTypes
{
public:
    ScalarTypes(char charMem, int intMem) :
        charMember_(charMem), intMember_(intMem)
    {}

private:
    char charMember_;
    int intMember_;

    ScalarTypes(const ScalarTypes& rhs);
    ScalarTypes& operator =(const ScalarTypes& rhs);
};

//======================================================================================================================
/// TODO: insert TreeItem class description here
class TreeItem
{
public:
    TreeItem(const TreeItem* p = 0)
        : parent_(p)
    {}
    virtual ~TreeItem() {}

    void setParent(const TreeItem& p) { parent_ = &p; }
    const TreeItem* parent() const { return parent_; }

protected:
    const TreeItem* parent_;

private:
    TreeItem(const TreeItem& rhs);
    TreeItem& operator =(const TreeItem& rhs);
};

//======================================================================================================================
void compareScalar()
{
    ScalarTypes obj1('A', 0);
    ScalarTypes obj2('A', 0);
    ScalarTypes obj3('A', 1);

    if ((sizeof(obj1) == sizeof(obj2))
            && (!std::memcmp(reinterpret_cast<void*>(&obj1), reinterpret_cast<void*>(&obj2), sizeof(obj1))))
        std::cerr << "Objects obj1 and obj2 seems to be equal" << std::endl;

    if ((sizeof(obj3) == sizeof(obj2))
            && !std::memcmp(reinterpret_cast<void*>(&obj3), reinterpret_cast<void*>(&obj2), sizeof(obj3)))
        std::cerr << "Objects obj2 and obj3 seems to be equal" << std::endl;

    std::cerr << "Even if the structure contains only scalar types, but with char you cannot compare objects of this type with memcmp function." << std::endl;
    std::cerr << "Because in pure C sizeof(char) == sizeof(int)" << std::endl;
    std::cerr << "The most reasonable way is to define the comparison operator" << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void stackOverflow()
{
    // Allocate on stack large enough local variable and that's it
    int array[uint(-1)/10];

    // Or we can simply turn this function into recursion
    // stackOverflow();
}

//----------------------------------------------------------------------------------------------------------------------
void segmentationFault()
{
    std::string* dummy = 0;
    dummy->size();
}

//----------------------------------------------------------------------------------------------------------------------
void memoryLeaks()
{
    typedef std::string T_Leaked;

    T_Leaked* leak = new T_Leaked("This is a leaked string");
    std::cerr << *leak << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void loopedLinkedList()
{
    TreeItem itemA;
    TreeItem itemB(&itemA);
    TreeItem itemC(&itemB);
    TreeItem itemD(&itemC);
    // TreeItem itemE;
    TreeItem itemE(&itemD);
    itemA.setParent(itemE);

    // Check if we have itemA loop
    const TreeItem* head = &itemA;
    for (const TreeItem* current = itemA.parent(); current && current->parent(); current = current->parent())
    {
        if (current == head)
        {
            std::cerr << "Loop detected in the list with itemA dependancy" << std::endl;
            break;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
uint fiboCalc(uint calcPos, uint currentPos = 0, uint prevFar = 0, uint prevNeighbour = 0)
{
    // These are the start values of Fibonacci serie
    static const uint first_ = 0;
    static const uint second_ = 1;

    if (0 == currentPos)
    {
        prevFar = first_;
        prevNeighbour = first_;
    }
    else if (1 == currentPos)
    {
        // HACK :)
        prevFar = second_;
        prevNeighbour = first_;
    }

    // Target position was reached
    if (calcPos == currentPos)
        return prevNeighbour + prevFar;

    // Next position Fibonacci values in temp objects
    return fiboCalc(calcPos, ++currentPos, prevNeighbour, prevNeighbour + prevFar);
}

//----------------------------------------------------------------------------------------------------------------------
void fiboPrint(uint calcPos)
{
    std::cerr << "Fibonacci series of first " << calcPos << " positions is: ";
    for (uint i = 0; i  < calcPos; ++i)
    {
        std::cerr << std::string((i == 0) ? "" : ", ") << Teramind::fiboCalc(i);
    }
    std::cerr << "." << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename T, typename T::iterator* = nullptr>
void reverse(const T& strIn, T& strOut,
             typename T::iterator* frontItPtr = nullptr, typename T::iterator* reverseItPtr = nullptr)
{
    typedef typename T::iterator T_Iter;

    // There is nothing to reverse
    if (1 >= strIn.size())
    {
        strOut = strIn;
        return;
    }

    T_Iter frontIt;
    T_Iter reverseIt;

    if (nullptr == frontItPtr)
    {
        // Starting point of the reverse
        strOut = strIn;
        frontIt = strOut.begin();
        reverseIt = --strOut.end();
    }
    else
    {
        // Continue reverse
        frontIt = *frontItPtr;
        reverseIt = *reverseItPtr;
    }

    // Swap values
    std::iter_swap(frontIt, reverseIt);

    // Move iterators
    frontIt++;
    reverseIt--;

    // Nothing to swap. We have finished with it
    if (1 >= std::distance(frontIt, reverseIt))
        return;

    return reverse(strIn, strOut, &frontIt, &reverseIt);
}

//----------------------------------------------------------------------------------------------------------------------
void reversePrint(const std::string& strIn)
{
    std::string reversed;
    Teramind::reverse(strIn, reversed);

    std::cerr << reversed << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void functionalStyle()
{
    // In C++11 we can write using instead of typedef
    // Declare a pointer to the function type.
    using T_Func = std::function<std::string()>;

    // We can use lambdas as anonymous functions passing pointer to the function as its argument
    auto lambda = [] (T_Func& func)
    {
        return func();
    };

    // We can evaluate a variable of our type with lambda
    T_Func varFunc = [] ()
    {
        return std::string("The most efficient functional style methods in C++11 to my oppinoin are:"
                           " auto, lambdas, std::function and decltype ");
    };

    // Just call lambda as an ordinary function
    auto theObj = lambda(varFunc);

    // And here we declare a variable of the type deduced from lambda. Very cool feature!
    decltype(theObj) printObj;

    // Now evalute it. We can easily do it.
    printObj = theObj;

    std::cerr << printObj << std::endl;
}

}


#endif // ANSWERSOBJECTS

