/* ************************************************************************
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
#ifndef _RANGE_TERM_H_
#define _RANGE_TERM_H_

#include "definition.h"
#include "arguments.h"
#include <vector>

/* RangeTerm is an interval left_term..right_term 
 * it represents all terms (NumConst) in this interval
 * it can appear only in the head of a rule (in a RangeLiteral)
 * */
class RangeTerm : public Term 
{
  public:
	typedef std::vector<RangeTerm*> Vector;
	  
	RangeTerm(Term* lt, Term* rt); // constructor
	virtual ~RangeTerm();
	inline Term::Vector& getExpansion();
	inline void addVariables(variableSet&);// adds its own vars to vs
	inline bool match(Term* t); // only used for terms that appear in body
				    // no sense here
	inline Term* applySubstitution();
	inline Term* getClone(MapVariables&);

	static RangeTerm* new_RangeTerm(Term* lt, Term* rt);
	static void delete_all();
       
  private:
       inline std::ostream& put(std::ostream&) const;
       
  protected:
       static mapRangeTerm _mapRangeTerm;
       
       Term* _left_bound;
       Term* _right_bound;
       Term::Vector _expansion; // set of NumCont represented by RangeTerm
};

inline Term::Vector& RangeTerm::getExpansion(){
	return _expansion;
}

inline void RangeTerm::addVariables(variableSet& vs){
	_left_bound->addVariables(vs);
	_right_bound->addVariables(vs);
}

inline bool RangeTerm::match(Term*){ // t is a ground term
// erreur match with a range term
	throw RuntimeExcept("Request match for a range term");
}

inline Term* RangeTerm::applySubstitution(){
	return RangeTerm::new_RangeTerm(_left_bound->applySubstitution(), _right_bound->applySubstitution());
}
inline Term* RangeTerm::getClone(MapVariables& mapVar){
	Term* lb = _left_bound->getClone(mapVar);
	Term* rb =  _right_bound->getClone(mapVar);
	return RangeTerm::new_RangeTerm(lb, rb);
}

inline std::ostream& RangeTerm::put(std::ostream& os) const {
	return os << *_left_bound << ".." << *_right_bound;
}

#endif // _RANGE_TERM_H_


