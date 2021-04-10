#include <iostream>
#include <fstream>

#include "antlr4-cpp/KotlinBaseVisitor.h"
#include "antlr4-cpp/KotlinLexer.h"
#include "antlr4-cpp/KotlinParser.h"

using namespace std;
using namespace antlr4;
using namespace antlr4::tree;

class Kotlin2Java : public KotlinBaseVisitor {
	string a;
    public:
		antlrcpp::Any visitProg(KotlinParser::ProgContext *ctx) override{
			return visitChildren(ctx);
		}
        antlrcpp::Any visitPackageList(KotlinParser::PackageListContext *ctx) override{ 
			string a;
			a = ctx->getText() + ";\n";
			return a;
        }
        antlrcpp::Any visitImportList(KotlinParser::ImportListContext *ctx) override {
            string a;
			a = "import java.util.*" + ctx->getText() + ";\n";
			return a;
        }
        antlrcpp::Any visitIdentifier(KotlinParser::IdentifierContext *ctx) override {
            return visitChildren(ctx);
        }
        antlrcpp::Any visitNumber(KotlinParser::NumberContext *ctx) override {
            return visitChildren(ctx);
        }
        antlrcpp::Any visitPlusNum(KotlinParser::PlusNumContext *ctx) override {
            return visitChildren(ctx);
        }
        antlrcpp::Any visitMinusNum(KotlinParser::MinusNumContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitStatement(KotlinParser::StatementContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitStatementContent(KotlinParser::StatementContentContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitAssignment(KotlinParser::AssignmentContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitType(KotlinParser::TypeContext *ctx) override {
            return visitChildren(ctx);
        }
        antlrcpp::Any visitListType(KotlinParser::ListTypeContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitAssignmentExpression(KotlinParser::AssignmentExpressionContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitFunctionDeclare(KotlinParser::FunctionDeclareContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitFunctionDeclareArgument(KotlinParser::FunctionDeclareArgumentContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitFunctionCall(KotlinParser::FunctionCallContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitFunctionCallArgument(KotlinParser::FunctionCallArgumentContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitClassDeclare(KotlinParser::ClassDeclareContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitClassDeclareArgument(KotlinParser::ClassDeclareArgumentContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitClassInheritance(KotlinParser::ClassInheritanceContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitInterfaceDeclare(KotlinParser::InterfaceDeclareContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitStatementBody(KotlinParser::StatementBodyContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitParenthesizedBody(KotlinParser::ParenthesizedBodyContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitBody(KotlinParser::BodyContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitBodyContent(KotlinParser::BodyContentContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitIfExpression(KotlinParser::IfExpressionContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitForStatement(KotlinParser::ForStatementContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitWhileStatement(KotlinParser::WhileStatementContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitReturnStatement(KotlinParser::ReturnStatementContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitExpression(KotlinParser::ExpressionContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitStringLiteral(KotlinParser::StringLiteralContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitAdditiveExpression(KotlinParser::AdditiveExpressionContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitMultiplicativeExpression(KotlinParser::MultiplicativeExpressionContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitFixExpression(KotlinParser::FixExpressionContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitPrefix(KotlinParser::PrefixContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitPostfix(KotlinParser::PostfixContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitOperatorFixExpression(KotlinParser::OperatorFixExpressionContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitOperatorAssignment(KotlinParser::OperatorAssignmentContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitCondition(KotlinParser::ConditionContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitLogicalOperator(KotlinParser::LogicalOperatorContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitConditionOperator(KotlinParser::ConditionOperatorContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitNotConditionOperator(KotlinParser::NotConditionOperatorContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitConditionExpression(KotlinParser::ConditionExpressionContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitRange(KotlinParser::RangeContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitVariableName(KotlinParser::VariableNameContext *ctx) override {
            return visitChildren(ctx);
        }

        antlrcpp::Any visitRangeExpression(KotlinParser::RangeExpressionContext *ctx) override {
            return visitChildren(ctx);
        }
};

int main(int argc, const char* args[]) {
    ifstream stream;
    ofstream outstream;
    
	stream.open(args[1]);
    
    ANTLRInputStream input(stream);
    KotlinLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    KotlinParser parser(&tokens);
	tree::ParseTree *tree = parser.prog();
	//printing parsetree
	cout << "Parse tree: " << endl;
	cout<< tree->toStringTree(&parser) <<endl;
	

	//kotlin2java object
    Kotlin2Java visitor;
	antlrcpp::Any result = visitor.visit(tree);
	//cout << (std::string)result;
	//writing source code to output.java
	outstream.open("output.java");
	string aresult;
	aresult = result.as<string>();
	//outstream << result ;
	if(outstream.fail()){
		cout<<"file open failed"<<endl;
	}

	outstream.close();
	/*

    
    cout << (string)result;
    outstream.open("output.java");
    cout << (string)result << endl;
    outstream.close();
	*/
	return 0;
}
