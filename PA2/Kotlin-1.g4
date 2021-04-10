//parser
grammar Kotlin;

prog : packageLine importLine statement* EOF? ;
packageLine : ('package' identifier)? ;
importLine : ('import' identifier)?;
identifier : LETTER ('.' LETTER)* ('.' '*')? ;
statements : statement* ;
statement : function | variable | loop | expression | classDeclare;
function : 'fun' string '(' argument? ')' returnType? body ;
argument : (string|'obj') ':' type (',' (string|'obj') ':' type)* ;
returnType : (':' (type|nullableType))+ ;
type : 'Int' | 'String' | 'Any' | 'Unit' | 'Boolean' | 'Double' ;
nullableType : type '?' ;
body : '=' expression | '{' statements '}' ;
expression : or | and | comparison | addition 
		   | assignment | ifExpr | isExpr | functionCall | returnExpr ;
or : and ('||' and)* ;
and : comparison ('&&' comparison)* ;
comparison : addition (comparisonOperator operand)* ;
comparisonOperator : '>' | '<' | '>=' | '<=' | '==' | '!=' ;
addition : multiplication (addOperand multiplication)* ;
addOperand : '+' | '-' ;
multiplication : operand (multiplicationOperand operand)* ;
multiplicationOperand : '*' | '/' ;
isExpr : string ('is'|NOT 'is') type ;
assignment : operand assignmentOperator operand ;
assignmentOperator : '+=' | '-=' | '*=' | '/=' ;
operand : string | number ;
number : plusNum | minusNum ;
plusNum : INT | REAL ;
minusNum : '-'INT | '-'REAL ;
functionCall :('override fun' | 'abstract fun')? (string '.')? string '(' parameter? (',' parameter)* ')' ;
ifExpr : 'if' '(' expression in? ')' ifbody
	   | 'if' '(' expression  in? ')' ifbody 'else' ifbody ;
ifbody : '{' statements '}' | statement ;
parameter : quote | number | string | expression;
quote : QUOTE;
returnExpr : 'return' expression? ;
variable : classVariable | declaration | postfix | prefix ;
postfix : operand postOperator ;
postOperator : '++' | '--' ;
prefix : postOperator operand ;
declaration : ('var'|'val')? string variableType value ;
variableType : (':' type)? ;
value : ('=' (expression | string | number ))? ;
classVariable : ('var'|'val') string ':' type expression ;
loop : whileLoop | forLoop ;
whileLoop : 'while' '(' expression ')' body ;
forLoop : 'for' '(' (string|number) in ')' body ;
in : ('in'| NOT 'in') expression (range | downto | step)* ;
range : '..' expression ;
downto : 'downTo' expression ;
step : 'step' expression ;
string : (LETTER|'_') ('.'|LETTER|'-'|INT)* ;
classDeclare : 'abstract'? ('class'|'interface') string '(' classArgu ')' classbody ;
classArgu : (('val'|'var') string ':' string ('<' type '>')? ','?)* ;
classbody : (':' expression ','?)* '{' inclass '}' ;
inclass : statements ('=' statements)? ;
//annotation : single | multiLine ;
//single : SINGLEANNOT ;
//multiLine : MULTIANNOT ;


//lexer
WS : [ \n\t\r]+ -> skip ;
SINGLEANNOT : '//' ~[\n\r\b\t]* '\n' -> skip ;
MULTIANNOT : '/*' ~[\r\t\b]* '*/' -> skip ;
QUOTE : '"' ~[\r\b\t\\"]* '"' ;
LETTER : [a-zA-Z]+ ;
INT : [0-9]+ ;
REAL : [0-9]+ '.' [0-9]+ ;
NOT : '!' ;
