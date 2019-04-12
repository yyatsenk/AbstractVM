
#include "abstractvm.hpp"

int main(int argv, char **argc)
{
    int a = 100;
    Stack<IOperand*> b;
    Operand<int> m((int)100);
    Operand<uint16_t> c((uint16_t)12);
    Operand<uint32_t> d((uint32_t)300);
    Operand<float> e((float)1.1);
    Operand<double> f((double)1.1);
    b.push_back(&m);
    b.push_back(&c);
    b.push_back(&d);
    b.push_back(&e);
    b.push_back(&f);
    b.add();
    
    /*for(auto v: b)
    {
        //Operand *res;
        OperandType type;
        type = v->getType();
        int a = static_cast<int>(type);
        //res = dynamic_cast<Operand *>(v)
        std::cout << a << std::endl;
    }*/
   std::cout << "int is: " << typeid(int).name() << '\n';
    return (0);
}