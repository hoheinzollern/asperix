/* *************************************************************************
 * Copyright (C) 2009 Claire Lefèvre, Pascal Nicolas
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * claire.lefevre@univ-angers.fr       pascal.nicolas@univ-angers.fr
 ****************************************************************************/ 
#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <stdexcept>
#include <iostream>

class RuntimeExcept : public std::runtime_error{
	public :
		RuntimeExcept(const std::string& what):std::runtime_error("*** RunTime ERROR : " + what){}
};

class LogicExcept : public std::logic_error{
	public :
		LogicExcept(const std::string& what):std::logic_error("*** ERROR : " + what){  }
};

class OutOfRange : public LogicExcept{
	public :
		OutOfRange(const std::string& what=std::string("")):LogicExcept(what){}
};

class OutOfRangeNumConst : public OutOfRange{
	public :
		OutOfRangeNumConst(const std::string& what=std::string("")):OutOfRange(what){}
};

class OutOfRangeFuncTerm : public OutOfRange{
	public :
		OutOfRangeFuncTerm(const std::string& what=std::string("")):OutOfRange(what){}
};

class ContradictoryConclusion : public LogicExcept{
	public :
		ContradictoryConclusion(const std::string& what=std::string("")):LogicExcept(what){}
};

#endif // _EXCEPTIONS_H_


