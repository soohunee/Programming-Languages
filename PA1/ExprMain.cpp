#include <iostream>

#include "antlr4-cpp/ExprBaseListener.h"
#include "antlr4-cpp/ExprLexer.h"
#include "antlr4-cpp/ExprParser.h"
#include <queue>


using namespace std;
using namespace antlr4;
using namespace antlr4::tree;

class EvalListener : public ExprBaseListener {

	map<char, double> vars; //ex)  a = 100
	stack<double> intStack;
	stack<double> evalS;
    stack<char> opS;
    queue<double> outQ;
    stack<char> eqS;
    
    void calculate(){
        if (evalS.top() == '+'){
            evalS.pop();
            double x = (double)evalS.top();
            evalS.pop();
            double y = (double)evalS.top();
            evalS.pop();
            double z = x + y;
            evalS.push(z);


        }
        else if (evalS.top() == '-'){
            evalS.pop();
            double x = (double)evalS.top();
            evalS.pop();
            double y = (double)evalS.top();
            evalS.pop();
            double z = y - x;
            evalS.push(z);

        }
        else if (evalS.top() == '*'){
            evalS.pop();
            double x = (double)evalS.top();
            evalS.pop();
            double y = (double)evalS.top();
            evalS.pop();
            double z = x * y;

            evalS.push(z);

        }
        else if (evalS.top() == '/'){
            evalS.pop();
            double x = (double)evalS.top();
            evalS.pop();
            double y = (double)evalS.top();
            evalS.pop();
            double z = y / x;
            evalS.push(z);

        }


    }
    int p(char a){
        if (a == '*' || a== '/')
            return 3;
        if (a == '+' || a == '-')
            return 2;
		if (a == '(')
			return 1;
    }

public:
	virtual void enterProg(ExprParser::ProgContext *ctx){
		//cout << "enterProg: \n" << endl;
	}
    virtual void enterEveryRule(antlr4::ParserRuleContext *ctx){
        //cout<< "entereveryrule : \n" << endl;
    }
    virtual void enterAssn(ExprParser::AssnContext *ctx){
		//cout << "enterAssn: \n" << endl;
	}
	virtual void enterExpr(ExprParser::ExprContext *ctx){
		//cout << "enterExpr: \n" << endl;
	}
    virtual void enterTerm(ExprParser::TermContext *ctx){
        //cout << "enterTerm: \n" << endl;
    }
    virtual void enterFactor(ExprParser::FactorContext *ctx){
        //cout << "enterFactor: \n" << endl;
    }
    virtual void enterNum(ExprParser::NumContext *ctx){
       //cout << "enterNum: \n" << endl;
    }

    virtual void visitTerminal(tree::TerminalNode *node) {
        //cout << "\t\tTerminal: " << node->getText() << "\n";
        if (node->getSymbol()->getType() == ExprLexer::PLUS)
            if(opS.empty())
                opS.push('+');
            else{
                while(p(opS.top())>2){

                    outQ.push(opS.top());
					opS.pop();
                }
                opS.push('+');
            }
		else if (node->getSymbol()->getType() == ExprLexer::MINUS)
            if(opS.empty())
                opS.push('-');
            else{
                while(p(opS.top())>2){
                    outQ.push(opS.top());
                    opS.pop();
                }
                opS.push('-');
            }
		else if (node->getSymbol()->getType() == ExprLexer::MULT)
            opS.push('*');
		else if (node->getSymbol()->getType() == ExprLexer::DIV)
            opS.push('/');
		else if (node->getSymbol()->getType() == ExprLexer::LBRACKET)
            opS.push('(');
		else if (node->getSymbol()->getType() == ExprLexer::EQ)
            eqS.push('=');
		else if (node->getSymbol()->getType() == ExprLexer::RBRACKET){
			while(opS.top() != '('){
				outQ.push(opS.top());
                opS.pop();
            }
            opS.pop();
        }
		else if (node->getSymbol() -> getType() == ExprLexer::SCOLON){
			while(!opS.empty()){
				outQ.push(opS.top());
				opS.pop();
			}
			while(!outQ.empty()){
				evalS.push(outQ.front());
				calculate();
				outQ.pop();
			}
			if (!evalS.empty()){
				cout.setf(ios::fixed);
				cout.precision(1);
				cout << evalS.top() << '\n';
			}
			while (!evalS.empty())
				evalS.pop();
		}

    }
    virtual void exitAssn(ExprParser::AssnContext *ctx){
        //cout << "exitAssn: \n" << endl;
		std:string a = (string)ctx->getText();
		const char *c = a.c_str();
        double num = (double)intStack.top();
		vars[c[0]] = num;
        intStack.pop();
		eqS.pop();

    }
    virtual void exitNum(ExprParser::NumContext *ctx){
        //cout << "exitNum: \n" << endl;
		std:string s = ctx->getText();
		const char* x= s.c_str();
        if(!eqS.empty()){ // assn
            double d = stod(s);
            intStack.push(d);
        }
        else {
            if (vars.find(x[0]) == vars.end()){ // not found -> number -> operator
				double d = stod(s);
                outQ.push(d);

            }
            else{ // found -> variable
                double d = (vars.find(x[0])->second);
                outQ.push(d);
				
            }
        }
    }
    virtual void exitFactor(ExprParser::FactorContext *ctx){
        //cout << "exitFactor: \n" << endl;
    }
    virtual void exitTerm(ExprParser::TermContext *ctx){
        //cout << "exitTerm: \n" << endl;
    }
    virtual void exitExpr(ExprParser::ExprContext *ctx){
        //cout << "exitExpr: \n" << endl;
    }
    virtual void exitEveryRule(antlr4::ParserRuleContext *ctx){
        //cout << "exitEveryrule : \n" << endl;
    }
	virtual void exitProg(ExprParser::ProgContext *ctx){
		//cout << "exitProg : \n" << endl;
	}

	virtual void visitErrorNode(antlr4::tree::ErrorNode *node){
		//cout << "visiterrornode : \n";
	}
};

int main(int argc, const char* argv[]) {
	if (argc < 2) {
		cerr << "[Usage] " << argv[0] << "  <input-file>\n";
		exit(0);
	}
	std::ifstream stream;
	stream.open(argv[1]);
	if (stream.fail()) {
		cerr << argv[1] << " : file open fail\n";
		exit(0);
	}

	//cout << "---Expression Evaluation with ANTLR listener---\n";
	ANTLRInputStream input(stream);
	ExprLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	ExprParser parser(&tokens);
	ParseTree *tree = parser.prog();

	//cout << tree-> toStringTree(&parser) << endl;

	ParseTreeWalker walker;
	EvalListener listener;	

	walker.walk(&listener, tree);
}
