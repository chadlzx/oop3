/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
	program.clear();
}

Program::~Program() {
}

void Program::clear() {
   program.clear();
   pos.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
	program[lineNumber]=line;
}

void Program::removeSourceLine(int lineNumber) {
   program.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
	if(program.count(lineNumber))return program[lineNumber];
	else return "";    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   
}

Statement *Program::getParsedStatement(int lineNumber) {
   return NULL;  
}

int Program::getFirstLineNumber() {
	if(program.end()==program.begin())return -1;
   return program.begin()->first;     // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
	auto it=program.find(lineNumber);
	if(it==program.end())return -1;
	it++;
	if(it==program.end())return -1;
	return it->first;     // Replace this stub with your own code
}
