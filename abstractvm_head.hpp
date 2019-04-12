#ifndef ABSTRACTVM_HEAD_HPP
#define ABSTRACTVM_HEAD_HPP



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
    if (typeid(val).name() == "h")
        type = OperandType::Int8;
    else if (typeid(val).name() == "t")
        type = OperandType::Int16;
    else if (typeid(val).name() == "i" ||typeid(val).name() == "j")
        type = OperandType::Int32;
    else if (typeid(val).name() == "f")
        type = OperandType::Float;
    else if (typeid(val).name() == "d")
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
    Operand op;
    op.val += rhs.val;
    return (&op);
}

template <typename T>
IOperand const *Operand<T>::operator-( IOperand const& rhs )const
{
    Operand op;
    op.val -= rhs.val;
    return (&op);
}

template <typename T>
IOperand const *Operand<T>::operator*( IOperand const& rhs )const
{
    Operand op;
    op.val *= rhs.val;
    return (&op);
}

template <typename T>
IOperand const *Operand<T>::operator/( IOperand const& rhs )const
{
    Operand op;
    if (rhs.val == 0)
        throw MyException();
    op.val /= rhs.val;
    return (&op);
}
template <typename T>
IOperand const *Operand<T>::operator%( IOperand const& rhs )const
{
    Operand op;
    //int a = 
    if (rhs.val == 0)
        throw MyException();
    op.val = 0 ;
    return (&op);
}

template <typename T>
std::string const& Operand<T>::toString(void)const
{
    //double res;
    //OperandType op_type;

    //op_type = this->get_type();
    std::string str = std::to_string(val);
    return (str);
}

#endif