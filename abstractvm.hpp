#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include <typeinfo>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <regex>
#include <memory>
//#include "abstractvm_head.hpp"

class MyException : public std::exception
{
    public:
    const char * what () {
      return "C++ Exception";
   }
	~MyException(){}
};

enum class OperandType
{
    Int8 = 1,
    Int16 = 2,
    Int32 = 4,
    Float = 5,
    Double = 8
};

class IOperand
{   
    //protected:
    //double val;
    public:
    virtual int getPrecision(void)const= 0;// Precision of the type of the instancevirtuale
    virtual OperandType  getType(void)const= 0;// Type of the instancevirtual
    virtual IOperand const *operator+( IOperand const& rhs )const= 0;// Sumvirtual
    /*virtual IOperand const *operator-( IOperand const& rhs )const= 0;// Differencevirtual
    virtual IOperand const *operator*( IOperand const& rhs )const= 0;// Productvirtual
    virtual IOperand const *operator/( IOperand const& rhs )const= 0;// Quotientvirtual
    virtual IOperand const *operator%( IOperand const& rhs )const= 0;// Modulovirtual
    */virtual std::string const& toString(void)const= 0;// String representation of the instance
    IOperand(){}
    virtual ~IOperand(void) {}
};

template <typename T>
class Operand : public IOperand
{
    public:
    T operand;
    OperandType type;
    int getPrecision(void)const;
    OperandType  getType(void)const;
    void set_Type(T val);
    IOperand const *operator+( IOperand const& rhs )const;// Sumvirtual
    /*IOperand const *operator-( IOperand const& rhs )const;// Differencevirtual
    IOperand const *operator*( IOperand const& rhs )const;// Productvirtual
    IOperand const *operator/( IOperand const& rhs )const;// Quotientvirtual
    IOperand const *operator%( IOperand const& rhs )const;// Modulovirtual
    */std::string const& toString(void)const;
    /*T get_val()const{
        return operand;
    }
    void set_val(T value){
        operand = value;
    }
    OperandType get_type()const{
        return type;
    }*/
    Operand()
    {
        std::cout << typeid(operand).name() << std::endl;    //Your answer
        std::cout << sizeof(operand) << std::endl;
    }
    Operand(T value)
    {
        operand = value;
        this->set_Type(value);
    }
    ~Operand(){}
    /*Operand &operator=(const Operand &a)
    {
        if (&a == this)
            return (*this);
        else
        {
            this->operand = a.get_val();
            this->type = a.get_type();
            return (*this);
        }
    }*/
};

template <typename T>
class Stack : public std::vector<T>
{
    public:
    //std::list<T> mystack;
    void add()
    {
        IOperand* res;
        IOperand* res_2;
        const IOperand* res_3;

        res = this->at(0);
        res_2 = this->at(1);
        res_3 = *res + *res_2;
        // auto it = this->begin();
        // this->push_back(*(*this)[0] + *(*this)[1]);


    }
    Stack(T val)
    {
        //mystack.push_back(val);
    }
    Stack()
    {
        
    }
};

template <typename T>
int Operand<T>::getPrecision(void)const
{
    switch(type)
    {
        case OperandType::Int8:
            return 1;
        case OperandType::Int16:
            return 2;
        case OperandType::Int32:
            return 4;
        case OperandType::Float:
            return 5;
        case OperandType::Double:
            return 8;
    }
    return (0);
}

template <typename T>
void Operand<T>::set_Type(T val)
{
    std::cout << typeid(val).name() << std::endl;
    //std::cout << typeid(val).name() << std::endl;
    if (!strcmp(typeid(val).name(),"h"))
        type = OperandType::Int8;
    else if (!strcmp(typeid(val).name(),"t"))
    {
        type = OperandType::Int16;
        //std::cout << "test" << std::endl;
    }
    else if (!strcmp(typeid(val).name(),"i") ||!strcmp(typeid(val).name(),"j"))
        type = OperandType::Int32;
    else if (!strcmp(typeid(val).name(),"f"))
        type = OperandType::Float;
    else if (!strcmp(typeid(val).name(),"d"))
        type = OperandType::Double;
}

template <typename T>
OperandType  Operand<T>::getType(void)const
{
   /* OperandType op_type;

    if (typeid(operand).name() == "h")
        op_type = Int8;
    else if (typeid(operand).name() == "t")
        op_type = Int16;
    else if (typeid(operand).name() == "i" ||typeid(operand).name() == "j")
        op_type = Int32;
    else if (typeid(operand).name() == "f")
        op_type = Float;
    else if (typeid(operand).name() == "d")
        op_type = Double;*/
    return (type);
}
template <typename T>
IOperand const *Operand<T>::operator+( IOperand const& rhs )const
{
    OperandType t;
    t = this->type;
    if (t == OperandType::Int8)
    {   Operand<int8_t> *op;
        op = dynamic_cast<Operand<int8_t> *>(const_cast<IOperand *>(&rhs));
        //if (op->type > this->type)
            return (new Operand<int8_t>(this->operand+op->operand));
    }
    else if (t == OperandType::Int16)
    {   Operand<int16_t> *op;
        op = dynamic_cast<Operand<int16_t> *>(const_cast<IOperand *>(&rhs));
        //if (op->type > this->type)
            return (new Operand<int16_t>(this->operand+op->operand));
    }
    else if (t == OperandType::Int32)
    {   Operand<int32_t> *op;
        op = dynamic_cast<Operand<int32_t> *>(const_cast<IOperand *>(&rhs));
        //if (op->type > this->type)
            return (new Operand<int32_t>(this->operand+op->operand));
    }
    else if (t == OperandType::Float)
    {   Operand<float> *op;
        op = dynamic_cast<Operand<float> *>(const_cast<IOperand *>(&rhs));
        //if (op->type > this->type)
            return (new Operand<float>(this->operand+op->operand));
    }
    else //if (t == OperandType::Double)
    {   Operand<double> *op;
        op = dynamic_cast<Operand<double> *>(const_cast<IOperand *>(&rhs));
        //if (op->type > this->type)
            return (new Operand<double>(this->operand+op->operand));
    }

    /*int priority_1 = this->getPrecision();
    int priority_2 = op->getPrecision();

    if (priority_2 > priority_1)
        this->set_Type(priority_2)*/
    //std::cout << op << std::endl;
    //op->set_val(this->operand + op->get_val());
    //return op;
}
/*
template <typename T>
IOperand const *Operand<T>::operator-( IOperand const& rhs )const
{
    Operand op;
    op.get_val() -= rhs.get_val();
    return (&op);
}

template <typename T>
IOperand const *Operand<T>::operator*( IOperand const& rhs )const
{
    Operand op;
    op.get_val() *= rhs.get_val();
    return (&op);
}

template <typename T>
IOperand const *Operand<T>::operator/( IOperand const& rhs )const
{
    Operand op;
    if (rhs.get_val() == 0)
        throw MyException();
    op.get_val() /= rhs.get_val();
    return (&op);
}
template <typename T>
IOperand const *Operand<T>::operator%( IOperand const& rhs )const
{
    Operand op;
    //int a = 
    if (rhs.get_val() == 0)
        throw MyException();
    op.get_val() = 0 ;
    return (&op);
}
*/
template <typename T>
std::string const& Operand<T>::toString(void)const
{
    //double res;
    //OperandType op_type;

    //op_type = this->get_type();
    std::string *str = new std::string(std::to_string(operand));
    return (*str);
}


/*class mystack : public Operand
{

};*/

#endif
