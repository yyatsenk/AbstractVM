#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include <typeinfo>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <regex>
#include <memory>
#include <stdlib.h>
#include <limits>
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
    
    public:
    virtual int getPrecision(void)const= 0;
    virtual OperandType  getType(void)const= 0;
    virtual IOperand const *operator+( IOperand const& rhs )const= 0;
    virtual IOperand const *operator-( IOperand const& rhs )const= 0;
    virtual IOperand const *operator*( IOperand const& rhs )const= 0;
    virtual IOperand const *operator/( IOperand const& rhs )const= 0;
    virtual IOperand const *operator%( IOperand const& rhs )const= 0;
    virtual std::string const& toString(void)const= 0;
    IOperand(){}
    virtual ~IOperand(void) {}
};

template <typename T>
class Operand : public IOperand
{
    private:
    IOperand const * createInt8( std::string const & value ) const
    {
        int32_t val;
        int8_t res;

        val = atoi(value.c_str());
        if (val > 127 || val < -128)
            throw MyException();
        else
            res = static_cast<int8_t>(val);
        return (new Operand<int8_t>(res));
    }
    IOperand const * createInt16( std::string const & value ) const
    {
        int32_t val;
        int16_t res;

        val = atoi(value.c_str());
        if (val > 32767 || val < -32768)
            throw MyException();
        else
            res = static_cast<int16_t>(val);
        return (new Operand<int16_t>(res));
    }
    IOperand const * createInt32( std::string const & value ) const
    {
        int64_t val;
        int32_t res;

        val = atoll(value.c_str());
        if (val > 2147483647 || val < -2147483648)
            throw MyException();
        else
            res = static_cast<int32_t>(val);
        return (new Operand<int32_t>(res));
    }
    IOperand const * createFloat( std::string const & value ) const
    {
        float res;

        res = atof(value.c_str());
        //std::cout <<res << "\n";
        return (new Operand<float>(res));
    }
    IOperand const * createDouble( std::string const & value ) const
    {
        double res;
        std::size_t offset = 0; 
        res = std::stod(value, &offset);
        //std::cout <<res << "\n";
        return (new Operand<double>(res));
    }
    public:
    T operand;
    OperandType type;
    int getPrecision(void)const;
    OperandType  getType(void)const;
    void set_Type(T val);

    template <typename T_2>
    IOperand const *add_temp(IOperand  const &rhs, std::string const &sign) const
    {
        Operand<T_2> *op;
        op = dynamic_cast<Operand<T_2> *>(const_cast<IOperand *>(&rhs));
        int32_t over_test;
             //if ()
            if (sign == "+")
            {
                over_test = this->operand + op->operand;
                if (this->type == OperandType::Float
                || this->type == OperandType::Double || op->type == OperandType::Float
                || op->type == OperandType::Double)
                {    
                    if (this->type < op->type)
                        return this->createOperand(op->type, std::to_string(this->operand + op->operand));
                    return this->createOperand(this->type, std::to_string(this->operand + op->operand));
                }
                else
                {
                    if (this->type < op->type)
                        return this->createOperand(op->type, std::to_string(over_test));
                    return this->createOperand(this->type, std::to_string(over_test));
                }
            }
            else if (sign == "-")
            {
                if (this->type < op->type)
                    return this->createOperand(op->type, std::to_string(this->operand - op->operand));
                return this->createOperand(this->type, std::to_string(this->operand - op->operand));
            }
            else if (sign == "*")
            {
                if (this->type < op->type)
                    return this->createOperand(op->type, std::to_string(this->operand * op->operand));
                return this->createOperand(this->type, std::to_string(this->operand * op->operand));
            }
            else if (sign == "/")
            {
                if (!op->operand)
                    throw MyException();
                if (this->type < op->type)
                    return this->createOperand(op->type, std::to_string(this->operand / op->operand));
                return this->createOperand(this->type, std::to_string(this->operand / op->operand));
            }
            else if (sign == "%")
            {
                if (!op->operand || this->type == OperandType::Float
                || this->type == OperandType::Double || op->type == OperandType::Float
                || op->type == OperandType::Double)
                    throw MyException();
                if (this->type < op->type)
                    return this->createOperand(op->type, std::to_string(static_cast<int>(this->operand) % static_cast<int>(op->operand)));
                return this->createOperand(this->type, std::to_string(static_cast<int>(this->operand) % static_cast<int>(op->operand)));
            }
        return (0);
    }

    IOperand const *operator+( IOperand const& rhs )const
    {
        OperandType t;
        t = rhs.getType();
        if (t == OperandType::Int8)
            return (add_temp<int8_t>(rhs, "+"));
        else if (t == OperandType::Int16)
            return (add_temp<int16_t>(rhs, "+"));
        else if (t == OperandType::Int32)
            return (add_temp<int32_t>(rhs, "+"));
        else if (t == OperandType::Float)   
            return (add_temp<float>(rhs, "+"));
        else   
            return (add_temp<double>(rhs, "+"));
        return (0);    
    }
    IOperand const *operator-( IOperand const& rhs )const
    {
        OperandType t;
        t = rhs.getType();
        if (t == OperandType::Int8)
            return (add_temp<int8_t>(rhs, "-"));
        else if (t == OperandType::Int16)
            return (add_temp<int16_t>(rhs, "-"));
        else if (t == OperandType::Int32)
            return (add_temp<int32_t>(rhs, "-"));
        else if (t == OperandType::Float)   
            return (add_temp<float>(rhs, "-"));
        else   
            return (add_temp<double>(rhs, "-"));
        return (0);
    }
    IOperand const *operator*( IOperand const& rhs )const
    {
        OperandType t;
        t = rhs.getType();
        if (t == OperandType::Int8)
            return (add_temp<int8_t>(rhs, "-"));
        else if (t == OperandType::Int16)
            return (add_temp<int16_t>(rhs, "-"));
        else if (t == OperandType::Int32)
            return (add_temp<int32_t>(rhs, "-"));
        else if (t == OperandType::Float)   
            return (add_temp<float>(rhs, "-"));
        else   
            return (add_temp<double>(rhs, "-"));
        return (0);
    }
    IOperand const *operator/( IOperand const& rhs )const
    {
        OperandType t;
        t = rhs.getType();
        if (t == OperandType::Int8)
            return (add_temp<int8_t>(rhs, "/"));
        else if (t == OperandType::Int16)
            return (add_temp<int16_t>(rhs, "/"));
        else if (t == OperandType::Int32)
            return (add_temp<int32_t>(rhs, "/"));
        else if (t == OperandType::Float)   
            return (add_temp<float>(rhs, "/"));
        else   
            return (add_temp<double>(rhs, "/"));
        return (0);
    }
    IOperand const *operator%( IOperand const& rhs )const
    {
        OperandType t;
        t = rhs.getType();
        if (t == OperandType::Int8)
            return (add_temp<int8_t>(rhs, "%"));
        else if (t == OperandType::Int16)
            return (add_temp<int16_t>(rhs, "%"));
        else if (t == OperandType::Int32)
            return (add_temp<int32_t>(rhs, "%"));
        else if (t == OperandType::Float)
            return (add_temp<float>(rhs, "%"));
        else if (t == OperandType::Double)
            return (add_temp<double>(rhs, "%"));
        return (0);
    }
    std::string const& toString(void)const;
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
    Operand(const Operand &) = default;
    
    ~Operand(){}
    IOperand &operator=(const IOperand &a)
    {
        IOperand *this_one = this;
        if (&a == this_one)
            return (*this_one);
        else
        {
            OperandType t;
            t = a.getType();
    if (t == OperandType::Int8)
    {   
        Operand<int8_t> *op;
        op = dynamic_cast<Operand<int8_t> *>(const_cast<IOperand *>(&a));
        this->operand = op->operand;
        this->type = op->type;
    }
    else if (t == OperandType::Int16)
    {   
        Operand<int16_t> *op;
        op = dynamic_cast<Operand<int16_t> *>(const_cast<IOperand *>(&a));
        this->operand = op->operand;
        this->type = op->type;
    }
    else if (t == OperandType::Int32)
    {   
        Operand<int32_t> *op;
        op = dynamic_cast<Operand<int32_t> *>(const_cast<IOperand *>(&a));
        this->operand = op->operand;
        this->type = op->type;
    }
    else if (t == OperandType::Float)
    {   
        Operand<float> *op;
        op = dynamic_cast<Operand<float> *>(const_cast<IOperand *>(&a));
        this->operand = op->operand;
        this->type = op->type;
    }
    else //if (t == OperandType::Double)
    {   
        Operand<double> *op;
        op = dynamic_cast<Operand<double> *>(const_cast<IOperand *>(&a));
        this->operand = op->operand;
        this->type = op->type;
    }
        }
    }
    
    IOperand const * createOperand( OperandType type, std::string const & value ) const
    {
        try
        {
            switch(type)
            {
                case OperandType::Int8 :
                   return createInt8(value);
                case OperandType::Int16:
                    return createInt16(value);
                case OperandType::Int32:
                    return createInt32(value);
                case OperandType::Float:
                    return createFloat(value);
                case OperandType::Double:
                   return createDouble(value);
                default :
                   return (0);
            }
        }
        catch(MyException& e)
        {
            std::cout << e.what() << '\n';
        }
    return (0);
    }
    
};


template <typename T>
class Stack : public std::vector<T>
{
    public:

    template <typename T_2>
    void assert_temp(IOperand const& rhs)
    {
        Operand<T_2> *op;
        Operand<T_2> *op_2;
        op = dynamic_cast<Operand<T_2> *>(const_cast<IOperand *>(&rhs));
        op_2 = dynamic_cast<Operand<T_2> *>(const_cast<IOperand *>(this->back()));
        if (!op_2)
            throw MyException();
        else if (op->operand != op_2->operand)
            throw MyException();
    }

    template <typename T_3>
    void dump_temp(IOperand  *rhs)
    {
        Operand<T_3> *op;
        op = dynamic_cast<Operand<T_3> *>(const_cast<IOperand *>(rhs));
        std::cout << op->operand << std::endl;
    }

    void dump()
    {
        for(auto v: *this)
        {
            OperandType t;
            if (v == 0) //!!!!!!!!!!!!!Possible debug
                continue ;
            t = v->getType();
            
            if (t == OperandType::Int8)
                dump_temp<int8_t>(v);
            else if (t == OperandType::Int16)
                dump_temp<int16_t>(v);
            else if (t == OperandType::Int32)
                dump_temp<int32_t>(v);
            else if (t == OperandType::Float)
                dump_temp<float>(v);
            else
                dump_temp<double>(v);
        }
    }
    void assert(IOperand const& rhs)
    {
        try
        {  
            OperandType t;
            t = rhs.getType();
            
            if (t == OperandType::Int8)  
                assert_temp<int8_t>(rhs);
            else if (t == OperandType::Int16)
                assert_temp<int16_t>(rhs);
            else if (t == OperandType::Int32)
                assert_temp<int32_t>(rhs);
            else if (t == OperandType::Float) 
                assert_temp<float>(rhs);
            else
                assert_temp<double>(rhs);
        }
        catch(MyException& e)
        {
            std::cout << e.what() << '\n';
        }
    }

    void add()
    {
        try
        {
            if (this->size() < 2)
                throw MyException();
            
            const IOperand *res;
            const IOperand *res_2;
            const IOperand *res_3;

            res = (*this).at(this->size() - 1);
            res_2 = (*this).at(this->size() - 2);
            res_3 = *res + *res_2;
            this->pop_back();
            this->pop_back();
            this->push_back(const_cast<IOperand *>(res_3));
        }
        catch(MyException& e)
        {
            std::cerr << e.what() << '\n';
            //~Stack();
            exit(1);
        }
    }
    void sub()
    {
        try
        {
            if (this->size() < 2)
                throw MyException();
            const IOperand *res;
            const IOperand *res_2;
            const IOperand *res_3;

            res = (*this).at(this->size() - 1);
            res_2 = (*this).at(this->size() - 2);
            res_3 = *res - *res_2;
            this->pop_back();
            this->pop_back();
            this->push_back(const_cast<IOperand *>(res_3));
        }
        catch(MyException& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void mul()
    {
        try
        {
            if (this->size() < 2)
                throw MyException();
            const IOperand *res;
            const IOperand *res_2;
            const IOperand *res_3;

            res = (*this).at(this->size() - 1);
            res_2 = (*this).at(this->size() - 2);
            res_3 = *res * *res_2;
            this->pop_back();
            this->pop_back();
            this->push_back(const_cast<IOperand *>(res_3));
        }
        catch(MyException& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void div()
    {
        try
        {
            if (this->size() < 2)
                throw MyException();
            const IOperand *res;
            const IOperand *res_2;
            const IOperand *res_3;

            res = (*this).at(this->size() - 1);
            res_2 = (*this).at(this->size() - 2);
            res_3 = *res / *res_2;
            this->pop_back();
            this->pop_back();
            this->push_back(const_cast<IOperand *>(res_3));
        }
        catch(MyException& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void mod()
    {
        try
        {
            if (this->size() < 2)
                throw MyException();
            const IOperand *res;
            const IOperand *res_2;
            const IOperand *res_3;

            res = (*this).at(this->size() - 1);
            res_2 = (*this).at(this->size() - 2);
            res_3 = *res % *res_2;
            this->pop_back();
            this->pop_back();
            this->push_back(const_cast<IOperand *>(res_3));
        }
        catch(MyException& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void print()
    {
        try
        {  
            OperandType t;
            t = this->back()->getType();
            
            if (t != OperandType::Int8)
                throw MyException();
            Operand<int8_t> *to_output;
            to_output = dynamic_cast<Operand<int8_t> *>(const_cast<IOperand*>(this->back()));
            if (to_output)
                std::cout << static_cast<char>(to_output->operand) << std::endl;
        }
        catch(MyException& e)
        {
            std::cout << e.what() << '\n';
        }
    }
    Stack(T val)
    {
    }
    Stack()
    {
        
    }
    ~Stack()
    {}
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
    if (!strcmp(typeid(val).name(),"a"))
        type = OperandType::Int8;
    else if (!strcmp(typeid(val).name(),"s"))
        type = OperandType::Int16;
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
    return (type);
}
/*template <typename T>
IOperand const *Operand<T>::operator+( IOperand const& rhs )const
{
    OperandType t;
    t = rhs.getType();
    if (t == OperandType::Int8)
    {   
        Operand<int8_t> *op;
        op = dynamic_cast<Operand<int8_t> *>(const_cast<IOperand *>(&rhs));
        if (op->type != this->type)
        {
            if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(this->operand + op->operand)); 
            return this->createOperand(this->type, std::to_string(this->operand + op->operand));
        }
    }
    else if (t == OperandType::Int16)
    {   
        Operand<int16_t> *op;
        op = dynamic_cast<Operand<int16_t> *>(const_cast<IOperand *>(&rhs));
        if (op->type != this->type)
        {
            if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(this->operand + op->operand)); 
            return this->createOperand(this->type, std::to_string(this->operand + op->operand));
        }
    }
    else if (t == OperandType::Int32)
    {   
        Operand<int32_t> *op;
        op = dynamic_cast<Operand<int32_t> *>(const_cast<IOperand *>(&rhs));
        if (op->type != this->type)
        {
            if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(this->operand + op->operand)); 
            return this->createOperand(this->type, std::to_string(this->operand + op->operand));
        }
    }
    else if (t == OperandType::Float)
    {   
        Operand<float> *op;
        op = dynamic_cast<Operand<float> *>(const_cast<IOperand *>(&rhs));
        if (op->type != this->type)
        {
            if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(this->operand + op->operand)); 
            return this->createOperand(this->type, std::to_string(this->operand + op->operand));
        }
    }
    else //if (t == OperandType::Double)
    {   
        Operand<double> *op;
        op = dynamic_cast<Operand<double> *>(const_cast<IOperand *>(&rhs));
        if (op->type != this->type)
        {
            if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(this->operand + op->operand)); 
            return this->createOperand(this->type, std::to_string(this->operand + op->operand));
        }
    }
    return (0);
}*/
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
