
#include "abstractvm.hpp"

int main(int argv, char **argc)
{
    std::list<std::string> commands;
    std::string mystr;
    std::cout << "What's your name? ";
    getline (std::cin, mystr); 
    std::cout << "Hello " << mystr << ".\n";
    //if_match("pattern")
    //commans.push_back(mystr);
    //else 
    //throw MyExeption();
    try
    {

    int a = 100;
    Stack<IOperand*> b;
    Operand<int8_t> m(7);
    Operand<int8_t> z((int8_t)120);
    Operand<int> g((int)100);
    Operand<int16_t> c((int16_t)12);
    Operand<int16_t> c2((int16_t)22);
    Operand<int32_t> i((int32_t)-1);
    Operand<int32_t> d((int32_t)-2147483647);
    Operand<float> e((float)1.1);
    Operand<double> f((double)2.11233);
    b.push_back(&c);
    //b.push_back(&d);
    b.push_back(&e);
    b.push_back(&i);
    b.push_back(&d);
    

    //b.pop_back();
    b.add();

        //f-;
    b.dump();
    //b.print();
    //b.assert(*(b.createOperand(OperandType::Int8, "55")));
    }
    catch(MyException& e)
    {
       std::cerr << e.what() << '\n'; 
    }
    return (0);
}