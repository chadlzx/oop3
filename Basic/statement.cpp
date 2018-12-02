/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
}
Statement::~Statement() {
}
StateLET::StateLET() {
}
StateLET::~StateLET() {
}
StatePRINT::StatePRINT() {
}
StatePRINT::~StatePRINT() {
}
StateINPUT::StateINPUT() {
}
StateINPUT::~StateINPUT() {
}
void StateLET::execute(EvalState& state){
	
}
void StatePRINT::execute(EvalState& state){
	
}
void StateINPUT::execute(EvalState& state){
	
}

