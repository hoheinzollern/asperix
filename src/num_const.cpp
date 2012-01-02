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
#include "num_const.h"

// static members
mapNumConst NumConst::_mapNumConst;
int NumConst::_maxInt = 1024;

NumConst* NumConst::new_NumConst(int n){
   if (n >= -NumConst::_maxInt && n <= NumConst::_maxInt){
       mapNumConst::iterator it = _mapNumConst.find(n);
       if (it!=_mapNumConst.end())
	       return (*it).second;
       else{
	       NumConst* nc = new NumConst(n);
	       return (*_mapNumConst.insert(std::make_pair(n,nc)).first).second;
       }
   }
   throw OutOfRangeNumConst();// exception
}

void NumConst::delete_all(){
	for (mapNumConst::iterator it = _mapNumConst.begin(); it != _mapNumConst.end(); it++)
		delete (*it).second;
}

//

NumConst::NumConst(){
}

NumConst::NumConst(int n): _val(n){
}

NumConst::~NumConst(){
}

