#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include <typeinfo>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <regex>
#include <stdlib.h>
#include <functional>

#define MSG_OVER_UNDER_FLOW "Over or under flow happened!\n"
#define MSG_DIV_0 "Div/Mod by 0!\n"
#define MSG_ASSERS_NOT_TRUE "Assertion failed!\n"
#define MSG_LESS_2_VAL "Error! Less that two values when an arithmetic instruction is executed!\n"
#define MSG_POP_EMPTY "Error! Pop empty stack!\n"
#define MSG_UNKNOWN_INSTR "Error! Unknown command!\n"
#define MSG_END_ABSENT "Error! Exit or ;; is absent!\n"
#define MSG_PRINT_FAILED "Error! Print failed!\n"
#define MSG_BIT_OPERATION_FLOAT "Error! No bit operations for floats!\n"

class MyException : public std::exception
{
    const char *msg;
    public:
    MyException();
    MyException(const char *msge);
    const char * what ();
	~MyException();
};

enum class OperandType
{
    Int8 = 0,
    Int16 = 1,
    Int32 = 2,
    Float = 3,
    Double = 4
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

    /*BONUS*/
    virtual IOperand const *operator&( IOperand const& rhs )const= 0;
    virtual IOperand const *operator|( IOperand const& rhs )const= 0;
    virtual IOperand const *operator^( IOperand const& rhs )const= 0;
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
            throw MyException(MSG_OVER_UNDER_FLOW);
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
            throw MyException(MSG_OVER_UNDER_FLOW);
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
            throw MyException(MSG_OVER_UNDER_FLOW);
        else
            res = static_cast<int32_t>(val);
        return (new Operand<int32_t>(res));
    }
    IOperand const * createFloat( std::string const & value ) const
    {
        float res;

        res = atof(value.c_str());
        return (new Operand<float>(res));
    }
    IOperand const * createDouble( std::string const & value ) const
    {
        double res;
        std::size_t offset = 0; 
        res = std::stod(value, &offset);
        return (new Operand<double>(res));
    }
    IOperand const* (Operand::*createType[5])(std::string const & value )const = {
        &Operand<T>::createInt8,
        &Operand<T>::createInt16,
        &Operand<T>::createInt32,
        &Operand<T>::createFloat,
        &Operand<T>::createDouble
    };
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
        int64_t over_test = 0;
        if (sign == "+")
        {
            over_test = static_cast<int64_t>(this->operand) + op->operand;
            if (this->type == OperandType::Float
            || this->type == OperandType::Double || op->type == OperandType::Float
            || op->type == OperandType::Double)
            {    
                if (this->type < op->type)
                    return this->createOperand(op->type, std::to_string(this->operand + op->operand));
                return this->createOperand(this->type, std::to_string(this->operand + op->operand));
            }
            else if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(over_test));
            return this->createOperand(this->type, std::to_string(over_test));
        }
        else if (sign == "-")
        {
            over_test = static_cast<int64_t>(this->operand) - op->operand;
            if (this->type == OperandType::Float
            || this->type == OperandType::Double || op->type == OperandType::Float
            || op->type == OperandType::Double)
            {    
                if (this->type < op->type)
                    return this->createOperand(op->type, std::to_string(this->operand - op->operand));
                return this->createOperand(this->type, std::to_string(this->operand - op->operand));
            }
            else if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(over_test));
            return this->createOperand(this->type, std::to_string(over_test));
        }
        else if (sign == "*")
        {
            over_test = static_cast<int64_t>(this->operand) * op->operand;
            if (this->type == OperandType::Float
            || this->type == OperandType::Double || op->type == OperandType::Float
            || op->type == OperandType::Double)
            {    
                if (this->type < op->type)
                    return this->createOperand(op->type, std::to_string(this->operand * op->operand));
                return this->createOperand(this->type, std::to_string(this->operand * op->operand));
            }
            else if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(over_test));
            return this->createOperand(this->type, std::to_string(over_test));
        }
        else if (sign == "/")
        {
            if (!op->operand)
                throw MyException(MSG_DIV_0);
            over_test = static_cast<int64_t>(this->operand) / op->operand;
            if (this->type == OperandType::Float
            || this->type == OperandType::Double || op->type == OperandType::Float
            || op->type == OperandType::Double)
            {    
                if (this->type < op->type)
                    return this->createOperand(op->type, std::to_string(this->operand / op->operand));
                return this->createOperand(this->type, std::to_string(this->operand / op->operand));
            }
                else if (this->type < op->type)
                    return this->createOperand(op->type, std::to_string(over_test));
                return this->createOperand(this->type, std::to_string(over_test));
            }
        else if (sign == "%")
        {
            if (!op->operand || this->type == OperandType::Float
            || this->type == OperandType::Double || op->type == OperandType::Float
            || op->type == OperandType::Double)
                throw MyException(MSG_DIV_0);
            over_test = static_cast<int64_t>(this->operand) % static_cast<int64_t>(op->operand);
            if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(static_cast<int64_t>(over_test)));
            return this->createOperand(this->type, std::to_string(static_cast<int64_t>(over_test)));
        }
        else if (sign == "&")
        {
            if (!op->operand || this->type == OperandType::Float
            || this->type == OperandType::Double || op->type == OperandType::Float
            || op->type == OperandType::Double)
                throw MyException(MSG_BIT_OPERATION_FLOAT);
            over_test = static_cast<int64_t>(this->operand) & static_cast<int64_t>(op->operand);
            if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(static_cast<int64_t>(over_test)));
            return this->createOperand(this->type, std::to_string(static_cast<int64_t>(over_test)));
        }
        else if (sign == "|")
        {
            if (!op->operand || this->type == OperandType::Float
            || this->type == OperandType::Double || op->type == OperandType::Float
            || op->type == OperandType::Double)
                throw MyException(MSG_BIT_OPERATION_FLOAT);
            over_test = static_cast<int64_t>(this->operand) | static_cast<int64_t>(op->operand);
            if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(static_cast<int64_t>(over_test)));
            return this->createOperand(this->type, std::to_string(static_cast<int64_t>(over_test)));
        }
        else if (sign == "^")
        {
            if (!op->operand || this->type == OperandType::Float
            || this->type == OperandType::Double || op->type == OperandType::Float
            || op->type == OperandType::Double)
                throw MyException(MSG_BIT_OPERATION_FLOAT);
            over_test = static_cast<int64_t>(this->operand) ^ static_cast<int64_t>(op->operand);
            if (this->type < op->type)
                return this->createOperand(op->type, std::to_string(static_cast<int64_t>(over_test)));
            return this->createOperand(this->type, std::to_string(static_cast<int64_t>(over_test)));
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
            return (add_temp<int8_t>(rhs, "*"));
        else if (t == OperandType::Int16)
            return (add_temp<int16_t>(rhs, "*"));
        else if (t == OperandType::Int32)
            return (add_temp<int32_t>(rhs, "*"));
        else if (t == OperandType::Float)   
            return (add_temp<float>(rhs, "*"));
        else   
            return (add_temp<double>(rhs, "*"));
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
    IOperand const *operator&( IOperand const& rhs )const
    {
        OperandType t;
        t = rhs.getType();
        if (t == OperandType::Int8)
            return (add_temp<int8_t>(rhs, "&"));
        else if (t == OperandType::Int16)
            return (add_temp<int16_t>(rhs, "&"));
        else if (t == OperandType::Int32)
            return (add_temp<int32_t>(rhs, "&"));
        else if (t == OperandType::Float)
            return (add_temp<float>(rhs, "&"));
        else if (t == OperandType::Double)
            return (add_temp<double>(rhs, "&"));
        return (0);
    }
    IOperand const *operator|( IOperand const& rhs )const
    {
        OperandType t;
        t = rhs.getType();
        if (t == OperandType::Int8)
            return (add_temp<int8_t>(rhs, "|"));
        else if (t == OperandType::Int16)
            return (add_temp<int16_t>(rhs, "|"));
        else if (t == OperandType::Int32)
            return (add_temp<int32_t>(rhs, "|"));
        else if (t == OperandType::Float)
            return (add_temp<float>(rhs, "|"));
        else if (t == OperandType::Double)
            return (add_temp<double>(rhs, "|"));
        return (0);
    }
    IOperand const *operator^( IOperand const& rhs )const
    {
        OperandType t;
        t = rhs.getType();
        if (t == OperandType::Int8)
            return (add_temp<int8_t>(rhs, "^"));
        else if (t == OperandType::Int16)
            return (add_temp<int16_t>(rhs, "^"));
        else if (t == OperandType::Int32)
            return (add_temp<int32_t>(rhs, "^"));
        else if (t == OperandType::Float)
            return (add_temp<float>(rhs, "^"));
        else if (t == OperandType::Double)
            return (add_temp<double>(rhs, "^"));
        return (0);
    }
    std::string const& toString(void)const;
    Operand()
    {
    }
    Operand(T value)
    {
        operand = value;
        this->set_Type(value);
    }
    template <typename T_4>
    void copy_temp(const IOperand &a)
    {
        Operand<T_4> *op;
        op = dynamic_cast<Operand<T_4> *>(const_cast<IOperand *>(&a));
        this->operand = op->operand;
        this->set_Type(this->operand);
    }
    Operand(const IOperand &a)
    {
        OperandType t;
        t = a.getType();
        if (t == OperandType::Int8)
            copy_temp<int8_t>(a);
        else if (t == OperandType::Int16) 
            copy_temp<int16_t>(a);
        else if (t == OperandType::Int32) 
            copy_temp<int32_t>(a);
        else if (t == OperandType::Float) 
            copy_temp<float>(a);
        else
            copy_temp<double>(a);
    }
    template <typename T_3>
    void assign_temp(const IOperand &a)
    {
        Operand<T_3> *op;
        op = dynamic_cast<Operand<T_3> *>(const_cast<IOperand *>(&a));
        this->operand = op->operand;
    }

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
                assign_temp<int8_t>(a);
            else if (t == OperandType::Int16) 
                assign_temp<int16_t>(a);
            else if (t == OperandType::Int32) 
                assign_temp<int32_t>(a);
            else if (t == OperandType::Float) 
                assign_temp<float>(a);
            else
                assign_temp<double>(a);
        }
        return (*this);
    }
    
    IOperand const * createOperand( OperandType type, std::string const & value ) const
    {
        unsigned int t = static_cast<int>(type);
        if (t >= 0 && t <= 4)
            return (this->*createType[t])(value);
        return (0);
    }
    
};

template <typename T>
class Stack : public std::vector<T>
{
    public:
    std::function<void(char)> command = [this](char sign) mutable -> void
    {
        if (this->size() < 2)
            throw MyException(MSG_LESS_2_VAL);
        const IOperand *res;
        const IOperand *res_2;
        const IOperand *res_3;

        res = (*this).at(this->size() - 1);
        res_2 = (*this).at(this->size() - 2);
        if (sign == '+')
            res_3 = *res + *res_2;
        else if (sign == '-')
            res_3 = *res - *res_2;
        else if (sign == '*')
            res_3 = *res * *res_2;
        else if (sign == '/')
            res_3 = *res_2 - *res;
        else if (sign == '%')
            res_3 = *res_2 % *res;
        else if (sign == '&')
            res_3 = *res & *res_2;
        else if (sign == '|')
            res_3 = *res | *res_2;
        else if (sign == '^')
            res_3 = *res ^ *res_2;
        this->pop_back();
        this->pop_back();
        this->push_back(const_cast<IOperand *>(res_3));
    };

    template <typename T_2>
    void assert_temp(IOperand const& rhs)
    {
        Operand<T_2> *op;
        Operand<T_2> *op_2;
        if (this->size() == 0)
            throw MyException(MSG_ASSERS_NOT_TRUE);
        op = dynamic_cast<Operand<T_2> *>(const_cast<IOperand *>(&rhs));
        op_2 = dynamic_cast<Operand<T_2> *>(const_cast<IOperand *>(this->back()));
        if (!op_2)
            throw MyException(MSG_ASSERS_NOT_TRUE);
        else if (op->operand != op_2->operand)
            throw MyException(MSG_ASSERS_NOT_TRUE);
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
        for(auto v = this->rbegin(); v != this->rend(); ++v)
        {
            OperandType t;
            if (*v == 0)
                break ;
            t = (*v)->getType();
            
            if (t == OperandType::Int8)
                dump_temp<int8_t>(*v);
            else if (t == OperandType::Int16)
                dump_temp<int16_t>(*v);
            else if (t == OperandType::Int32)
                dump_temp<int32_t>(*v);
            else if (t == OperandType::Float)
                dump_temp<float>(*v);
            else
                dump_temp<double>(*v);
        }
    }
    void assert(IOperand const& rhs)
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

    void add()
    {
        command('+');
    }
    void sub()
    {
        command('-');
    }
    void mul()
    {
        command('*');
    }
    void div()
    {
        command('/');
    }
    void mod()
    {
        command('%');
    }
    void b_and()
    {
        command('&');
    }
    void b_or()
    {
        command('|');
    }
    void b_xor()
    {
        command('^');
    }
    void print()
    {
        OperandType t;
        if (this->size() == 0)
            throw MyException(MSG_PRINT_FAILED);
        t = this->back()->getType();
   
        if (t != OperandType::Int8)
            throw MyException(MSG_PRINT_FAILED);
        Operand<int8_t> *to_output;
        to_output = dynamic_cast<Operand<int8_t> *>(const_cast<IOperand*>(this->back()));
        if (to_output)
            std::cout << static_cast<char>(to_output->operand) << std::endl;
    }
    Stack(T val)
    {
    }
    Stack()
    {
        
    }
    Stack(const Stack<T> &var) = default;
    Stack<T>& operator=(const Stack<T> &var ) = default;
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

template <typename T>
std::string const& Operand<T>::toString(void)const
{
    std::string *str = new std::string(std::to_string(operand));
    return (*str);
}


#endif
