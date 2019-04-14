/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:16:48 by yyatsenk          #+#    #+#             */
/*   Updated: 2019/04/14 17:16:49 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstractvm.hpp"

MyException::MyException()
    {
    }
    MyException::MyException(const char *msge):msg(msge)
    {    
    }
    const char * MyException::what () {
      return msg;
   }
	MyException::~MyException(){}
