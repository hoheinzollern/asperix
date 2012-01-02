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
#include "symb_const.h"

// static members
mapSymbConst SymbConst::_mapSymbConst;

SymbConst* SymbConst::new_SymbConst(std::string* name){ //WARNING : name is deleted if it already exists
       mapSymbConst::iterator it = _mapSymbConst.find(*name);
       if (it!=_mapSymbConst.end()){
	       delete name;
	       return (*it).second;
       }
       else{
	       SymbConst* sc = new SymbConst(name);
	       return (*_mapSymbConst.insert(std::make_pair(*name,sc)).first).second;
       }
}

void SymbConst::delete_all(){
	for (mapSymbConst::iterator it = _mapSymbConst.begin(); it != _mapSymbConst.end(); it++)
		delete (*it).second;
}


//
//
SymbConst::SymbConst(){
}

SymbConst::SymbConst(const std::string* s): _name(s) {	
}

SymbConst::~SymbConst(){
	delete _name;
}
	       

