CXX = g++
CXXFLAGS = -O3 
LFLAGS = 
SRCS = num_const.cpp symb_const.cpp variable.cpp operator.cpp arith_expr.cpp range_term.cpp func_term.cpp arguments.cpp functor.cpp term.cpp predicate.cpp negated_predicate.cpp literal.cpp basic_literal.cpp positive_literal.cpp negative_literal.cpp relational_literal.cpp affect_literal.cpp range_literal.cpp program.cpp fact_rule.cpp constraint_rule.cpp normal_rule.cpp rule.cpp changes.cpp graph.cpp main.cpp 
OBJS = $(SRCS:.cpp=.o)


all: parser ASPeRiX 

ASPeRiX: $(OBJS)
	$(CXX) $(LFLAGS) -o "../asperix" $(OBJS)  -lfl
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< 

parser: parser.l parser.y
	flex -oparser.lex.cpp parser.l
	bison -oparser.cpp parser.y
clean:
	rm -f $(OBJS) asperix.o "../asperix"

distclean: clean
	rm -f parser.lex.cpp parser.o parser.cpp
	


