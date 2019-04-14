
#include "abstractvm.hpp"

int is_valid_command(std::string &mystr, std::list<std::string> &commands, int &end_found)
{
    std::regex re_command_no_args("^(pop|dump|add|sub|mul|div|mod|print)[ ]?(;.+)?");
    std::regex re_with_type("^(push |assert )(int(8|16|32)([(][-]?[0-9]+[)])|float[(][-]?[0-9]+.[0-9]+[)]|double[(][-]?[0-9]+.[0-9]+[)])[ ]?(;.+)?");
    std::regex re_end("^(exit|;;)$");
    std::regex re_comment("^;.+");

    try {
        if (std::regex_match(mystr, re_comment) || mystr == "")
            return (2);
        else if (std::regex_match(mystr, re_end))
        {
            end_found = 1;
            return (0);
        }
        else if (std::regex_match(mystr, re_command_no_args))
            return (1);
        else if (std::regex_match(mystr, re_with_type))
            return (1);
        throw MyException(MSG_UNKNOWN_INSTR);
    }
     catch (std::regex_error& e) {
         std::cout << "Regexp error\n";
    }
    return (0);
}


void parser(std::list<std::string> &commands, Stack<IOperand*> &mystack)
{
    std::string str;
    int end_found = 0;
    while(!end_found)
    {
        getline (std::cin, str); 
        if (is_valid_command(str, commands, end_found) == 1)
            commands.push_back(str);
    }
    for (auto &s : commands)
    {
        std::string str = s.substr(0, s.find(";", 0));
        std::cout << str << std::endl;
        if (std::regex_search(str, std::regex("^dump")))
            mystack.dump();
        else if (std::regex_search(str, std::regex("^print")))
            mystack.print();
        else if (std::regex_search(str, std::regex("^add")))
            mystack.add();
        else if (std::regex_search(str,std::regex("^sub")))
            mystack.sub();
        else if (std::regex_search(str, std::regex("^mul")))
            mystack.mul();
        else if (std::regex_search(str, std::regex("^div")))
            mystack.div();
        else if (std::regex_search(str, std::regex("^mod")))
            mystack.mod();
        else if (std::regex_search(str, std::regex("^print")))
            mystack.print();
        else if (std::regex_search(str, std::regex("^pop")))
        {
            if (mystack.size() == 0)
                throw MyException(MSG_POP_EMPTY);
            else
                mystack.pop_back();
        }
        else if (std::regex_search(str, std::regex("^push")))
        {
            IOperand *val;
            std::cout << "success\n";
            if (std::regex_search(str, std::regex("int8")))
            {
                std::string num = str.substr(str.find("(", 0) + 1, str.size() - 1);
                val = new Operand<int8_t>(atoi(num.c_str()));
                mystack.push_back(val);
            }
            else if (std::regex_search(str, std::regex("int16")))
            {
                std::string num = str.substr(str.find("(", 0) + 1, str.size() - 1);
                val = new Operand<int16_t>(atoi(num.c_str()));
                mystack.push_back(val);
            }
            else if (std::regex_search(str, std::regex("int32")))
            {
                std::string num = str.substr(str.find("(", 0) + 1, str.size() - 1);
                val = new Operand<int32_t>(atoi(num.c_str()));
                mystack.push_back(val);
            }
            else if (std::regex_search(str, std::regex("float")))
            {
                std::string num = str.substr(str.find("(", 0) + 1, str.size() - 1);
                val = new Operand<float>(atof(num.c_str()));
                mystack.push_back(val);
            }
            else if (std::regex_search(str, std::regex("double")))
            {
                std::string num = str.substr(str.find("(", 0) + 1, str.size() - 1);
                val = new Operand<double>(std::stod(num.c_str(), NULL));
                mystack.push_back(val);
            }
        }
        else if (std::regex_search(str, std::regex("^assert")))
        {
            IOperand *val;
            std::cout << "success\n";
            if (std::regex_search(str, std::regex("int8")))
            {
                std::string num = str.substr(str.find("(", 0) + 1, str.size() - 1);
                val = new Operand<int8_t>(atoi(num.c_str()));
                mystack.assert(*val);
            }
            else if (std::regex_search(str, std::regex("int16")))
            {
                std::string num = str.substr(str.find("(", 0) + 1, str.size() - 1);
                val = new Operand<int16_t>(atoi(num.c_str()));
                mystack.assert(*val);
            }
            else if (std::regex_search(str, std::regex("int32")))
            {
                std::string num = str.substr(str.find("(", 0) + 1, str.size() - 1);
                val = new Operand<int32_t>(atoi(num.c_str()));
                mystack.assert(*val);
            }
            else if (std::regex_search(str, std::regex("float")))
            {
                std::string num = str.substr(str.find("(", 0) + 1, str.size() - 1);
                val = new Operand<float>(atof(num.c_str()));
                mystack.assert(*val);
            }
            else if (std::regex_search(str, std::regex("double")))
            {
                std::string num = str.substr(str.find("(", 0) + 1, str.size() - 1);
                val = new Operand<double>(std::stod(num.c_str(), NULL));
                mystack.assert(*val);
            }
        }
    }
}


int main(int argv, char **argc)
{
    std::list<std::string> commands;
    try
    {
        Stack<IOperand*> b;
        parser(commands, b);
    }
    catch(MyException& e)
    {
       std::cerr << e.what() << '\n'; 
    }
    return (0);
}