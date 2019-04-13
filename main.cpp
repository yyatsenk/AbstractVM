
#include "abstractvm.hpp"

int main(int argv, char **argc)
{
    int a = 100;
    Stack<IOperand*> b;
    Operand<int8_t> m(8);
    Operand<int8_t> z((int8_t)120);
    /*Operand<int> g((int)100);
    Operand<int16_t> c((int16_t)12);
    Operand<int16_t> c2((int16_t)22);
    Operand<int32_t> i((int16_t)32);
    Operand<int32_t> d((int32_t)500);
    Operand<float> e((float)1.1);
    Operand<double> f((double)2.11233);
    b.push_back(&m);
    b.push_back(&c);
    b.push_back(&d);
    b.push_back(&e);
    b.push_back(&m);*/
    b.push_back(&m);
    b.push_back(&z);
    

    //b.pop_back();
    b.add();

        //f-;
    b.dump();
    //b.print();
    //b.assert(*(b.createOperand(OperandType::Int8, "55")));

    return (0);
}