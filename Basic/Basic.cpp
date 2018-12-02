/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);
void INPUT(string s,EvalState & state);
bool check(string now, string s);


void QUIT();

void CLEAR(Program& program,EvalState& state);

void LIST(Program& program);

void HELP();
void RUN(Program& program,EvalState& state);
int getVal(string line,EvalState& state){
	TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   Expression* exp=parseExp(scanner);
	int value;
	try{
		value=exp->eval(state);
	}
	catch(int k){
		if(exp!=nullptr)delete exp;exp=nullptr;
		throw k;
	}
	return value;
}
/* Main program */

int main() {
   EvalState state;//变量映射集
   Program program;//程序语句集
   while (true) {
      try {
         processLine(getLine(), program, state);//处理一行program
      } catch (ErrorException & ex) {//错误抛出
         cout << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */
string BasicString[20]={"","RUN","LIST","CLEAR","QUIT","HELP"};
string ProgramString[20]={"REM","LET","PRINT","INPUT","END","GOTO","IF","THEN"};
string keywords[20]={"RUN","LIST","CLEAR","QUIT","HELP","REM","LET","PRINT","INPUT","END","GOTO","IF","THEN"};

//判断BasicString 
bool check(string now, string s){
	int k=0;
	while(now[k]==' '&&k!=now.size())k++;
	bool flag=0;
	for(int j=0;j<s.size();j++){
		if(k+j>=now.size()){flag=1;break;}
		if(now[k+j]!=s[j]){flag=1;break;}
	}
	if(!flag){
		k=k+s.size();
		while(now[k]==' '&&k!=now.size())k++;
		if(k==now.size()){
			return 1;
		}
	}
	return 0;
}
void RUN(Program& program,EvalState& state){
	Expression* exp=nullptr;
	try{
		for(int it=program.getFirstLineNumber();it!=-1;){
			string line=program.getSourceLine(it);
			if(line=="")throw 3;
			TokenScanner scanner;
			scanner.ignoreWhitespace();
			scanner.scanNumbers();
			scanner.setInput(line);
			scanner.nextToken();
			string tmp=scanner.nextToken();
			
			if(check(tmp,"LET")){
			   exp=parseExp(scanner);
			   exp->eval(state);
			}
			else if(check(tmp,"PRINT")){
			   exp=parseExp(scanner);
				int value=exp->eval(state);
				cout<<value<<endl;
			}
		   else if(check(tmp,"INPUT")){
				INPUT(scanner.nextToken(),state);
		   }
		   else if(check(tmp,"REM")){
			   
		   }
		   else if(check(tmp,"END")){
			   break;
		   }
		   else if(check(tmp,"GOTO")){
			   exp=parseExp(scanner);
			   it=exp->eval(state);
			   continue;
		   }
		   else if(check(tmp,"IF")){
			   int then_pos=line.find("THEN");
			   int IF_pos=line.find("IF");
			   int l1=line.find('<'),l2=line.find('='),l3=line.find('>');
			   if(then_pos==line.npos)throw 1; 
			   int w=-1;if(l1==line.npos&&l2==line.npos&&l3==line.npos)throw 1;
			   if(l1!=line.npos)w=l1;else if(l2!=line.npos)w=l2;else w=l3;
			   
				string s1(line,IF_pos+2,w-IF_pos-3);
			   string s2(line,w+1,then_pos-w-1);
			   string s4(line,then_pos+4,line.size()-then_pos-4);
			   int v1=getVal(s1,state);
			   int v2=getVal(s2,state);
			   int v3=getVal(s4,state);
			   //printf("%d\n %d\n %d\n",v1,v2,v3);
			   if(l1!=line.npos){
				   if(v1<v2){
					   it=v3;if(exp!=nullptr)delete exp;exp=nullptr;
						continue;
				   }
			   }
			   else if(l2!=line.npos){
				   if(v1==v2){
					   it=v3;if(exp!=nullptr)delete exp;exp=nullptr;
						continue;
				   }
			   }
			   else if(l3!=line.npos){
				   if(v1>v2){
					   it=v3;if(exp!=nullptr)delete exp;exp=nullptr;
						continue;
				   }
			   }
		   }
			it=program.getNextLineNumber(it);
			if(exp!=nullptr)delete exp;exp=nullptr;
		}
	}
		catch(int i){
			if(i==1)printf("VARIABLE NOT DEFINED\n");
			else if(i==2)printf("DIVIDE BY ZERO\n");
			else if(i==3)printf("LINE NUMBER ERROR\n");
			else printf("SYNTAX ERROR\n");
			if(exp!=nullptr)delete exp;exp=nullptr;
		}
		catch(...){
			printf("SYNTAX ERROR\n");
			if(exp!=nullptr)delete exp;exp=nullptr;
		};
	if(exp!=nullptr)delete exp;exp=nullptr;
}
void LIST(Program& program){
	for(int it=program.getFirstLineNumber();it!=-1;it=program.getNextLineNumber(it))
		cout<<program.getSourceLine(it)<<endl;
}
void CLEAR(Program& program,EvalState& state){
	program.clear();
	state.clear();
}
void QUIT(){
	exit(0);
}
void HELP(){
	printf("This is a Basic Interpreter\n");
	printf("And so shit!\n");
	
}
void INPUT(string s,EvalState & state){
	cout<<" ? ";
	int a;a=stringToInteger(getLine());
	state.setValue(s,a);
}



// 			语句			程序语句集			变量映射集




bool check_exp(string a){
	TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(a);
   Expression *exp = parseExp(scanner);
   if(exp!=nullptr)delete exp;exp=nullptr;
   return 1;
}
bool check_con(string a){
	TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(a);
   Expression *exp = parseExp(scanner);
   if(exp->getType()!=CONSTANT){
	   if(exp!=nullptr)delete exp;exp=nullptr;
	   throw 1;
   }
   return 1;
}
bool check_keywords(string line,int g=0){
	TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
	scanner.nextToken();
	if(isdigit(line[0]))scanner.nextToken();
	while(true){
		string tmp=scanner.nextToken();
		if(tmp=="")break;
		for(int i=0;i<=12;i++){
			if(keywords[i]=="THEN"&&g==1){
				g=0;continue;
			}
			if(keywords[i]==tmp)throw "error";
		}
	}
	return 1;
}
void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   
   if(!isdigit(line[0])){
	//检查BasicString
		bool flag=0;
	    for(int i=1;i<=5;i++){
		   if(check(line,BasicString[i])){
			   if(i==1){RUN(program,state);flag=1;break;}
			   if(i==2){LIST(program);flag=1;break;}
			   if(i==3){CLEAR(program,state);flag=1;break;}
			   if(i==4){QUIT();flag=1;break;}
			   if(i==5){HELP();flag=1;break;}
		   }
	   }
	   if(flag)return;
	   string tmp;
	   Expression* exp=nullptr;
	   if(check(tmp=scanner.nextToken(),"PRINT")&&!flag){//PRINT
			try{
				check_keywords(line);
				flag=1;
				exp = parseExp(scanner);
				int value = exp->eval(state);
				cout<<value<<endl;
				if(exp!=nullptr)delete exp;exp=nullptr;
			}
			catch(int i){
			if(i==1)printf("VARIABLE NOT DEFINED\n");
			else if(i==2)printf("DIVIDE BY ZERO\n");
			else if(i==3)printf("LINE NUMBER ERROR\n");
			else printf("SYNTAX ERROR\n");
			if(exp!=nullptr)delete exp;exp=nullptr;
			}
			catch(...){
				printf("SYNTAX ERROR\n");
				if(exp!=nullptr)delete exp;exp=nullptr;
			}
			if(exp!=nullptr)delete exp;exp=nullptr;
			flag=1;
	   }
	   if(check(tmp,"LET")&&!flag){
		  try {
			   check_keywords(line);
			   flag=1;
			   exp=parseExp(scanner);
			   exp->eval(state);
			   if(exp!=nullptr)delete exp;exp=nullptr;
		   }
			catch(int i){
				if(i==1)printf("VARIABLE NOT DEFINED\n");
				else if(i==2)printf("DIVIDE BY ZERO\n");
				else if(i==3)printf("LINE NUMBER ERROR\n");
				else printf("SYNTAX ERROR\n");
				if(exp!=nullptr)delete exp;exp=nullptr;
			}
			catch(...){
				printf("SYNTAX ERROR\n");
				if(exp!=nullptr)delete exp;exp=nullptr;
			}
			if(exp!=nullptr)delete exp;exp=nullptr;
			flag=1;
	   }
	   if(check(tmp,"INPUT")&&!flag){
		   try {
				check_keywords(line);
				exp=parseExp(scanner);
			   if(exp->getType()!=IDENTIFIER)throw 1;
			   
			   TokenScanner sb;
			   sb.ignoreWhitespace();
			   sb.scanNumbers();
			   sb.setInput(line);
			   sb.nextToken();
			   INPUT(sb.nextToken(),state);
				if(exp!=nullptr)delete exp;exp=nullptr;
				flag=1;
		   }
			catch(...){
				printf("SYNTAX ERROR\n");
				if(exp!=nullptr)delete exp;exp=nullptr;
			}
	   }
	   
	   if(!flag){
		   printf("SYNTAX ERROR\n");
		}
		return;
   }
   else {
	   string tmp;
	   int LineNumber=stringToInteger(tmp=scanner.nextToken());
	   if(check(tmp,line)){//删除
		   program.removeSourceLine(LineNumber);
		   return;
	   }
	   tmp=scanner.nextToken();
	   Expression* exp=nullptr;
	   try{
		   if(check(tmp,"LET")){
			   check_keywords(line);
			   exp=parseExp(scanner);
			   program.addSourceLine(LineNumber,line);
		   }
		   else if(check(tmp,"PRINT")){
			   check_keywords(line);
			   exp=parseExp(scanner);
			   program.addSourceLine(LineNumber,line);
		   }
		   else if(check(tmp,"INPUT")){
			   check_keywords(line);
			   exp=parseExp(scanner);
				if(exp->getType()!=IDENTIFIER)throw 1;
			   program.addSourceLine(LineNumber,line);
		   }
		   else if(check(tmp,"REM")){
			   program.addSourceLine(LineNumber,line);
		   }
		   else if(check(tmp,"END")){
			   check_keywords(line);
			   if(scanner.nextToken()!="")throw 1;
			   program.addSourceLine(LineNumber,line);
		   }
		   else if(check(tmp,"GOTO")){
			   check_keywords(line);
			   exp=parseExp(scanner);
			   if(exp->getType()!=CONSTANT)throw 1;
			   program.addSourceLine(LineNumber,line);
		   }
		   else if(check(tmp,"IF")){
			   check_keywords(line,1);
			   
			   int then_pos=line.find("THEN");
			   int IF_pos=line.find("IF");
			   int l1=line.find('<'),l2=line.find('='),l3=line.find('>');
			   
			   
			   
			   if(then_pos==line.npos){
					throw 1;
			   }				   
			   int w=-1;
			   if(l1==line.npos&&l2==line.npos&&l3==line.npos){
				   throw 1;
			   }
			   if(l1!=line.npos)w=l1;else if(l2!=line.npos)w=l2;else w=l3;
			   
			   string s1(line,IF_pos+2,w-IF_pos-3);
			   string s2(line,w+1,then_pos-w-1);
			   string s4(line,then_pos+4,line.size()-then_pos-4);
			   
			   /*cout<<s1<<endl;
			   cout<<s2<<endl;
			   cout<<s4<<endl;*/
			   check_exp(s1);
			   check_exp(s2);
			   check_con(s4);
			   
			   program.addSourceLine(LineNumber,line);
		   }
		   else throw -1;
		}
	   catch(...){
		   printf("SYNTAX ERROR\n");
	   }
	   if(exp!=nullptr)delete exp;exp=nullptr;
   }
   
   return;
   
   /*
   Expression *exp = parseExp(scanner);
   int value = exp->eval(state);
   cout << value << endl;
   */
  
   //if(exp!=nullptr)delete exp;exp=nullptr;
}
