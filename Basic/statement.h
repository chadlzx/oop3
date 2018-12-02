/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
class Statement {

public:
   Statement();
   virtual ~Statement();
   virtual void execute(EvalState & state) = 0;
};
 
class StateLET : public Statement{
	public:
	StateLET();
	virtual ~StateLET();
	virtual void execute(EvalState& state);
	private:
	string s;
} ;
class StatePRINT : public Statement{
	public :
	StatePRINT();
	virtual ~StatePRINT();
	virtual void execute(EvalState& state);
	private:
	string s;
};
class StateINPUT : public Statement{
	public :
	StateINPUT();
	virtual ~StateINPUT();
	virtual void execute(EvalState& state);
	private:
	string s;
};
#endif
