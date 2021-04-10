/* Kotlin Basic Syntax */
grammar Kotlin;

//parser rules
prog : packageList* importList? statement? EOF ;
packageList : 'package' identifier ('.' identifier)* ;
importList : 'import' identifier ('.' identifier|'.' '*')* ;
identifier : Letter (Letter | number)* ;
number : plusNum | minusNum ;
plusNum : Digit ('.' Digit*)? ;
minusNum : '-' Digit ('.' Digit)? ;
statement : statementContent+ ;
statementContent : assignment | functionDeclare | classDeclare | interfaceDeclare ;
assignment : 'override'? ('val' | 'var') identifier (':' type | (':' type)? 'get()'? '=' expression) ;
type : 'Int' '?'?
     | 'Unit' '?'?
     | 'Any' '?'?
     | 'String' '?'?
     | 'Double' '?'?
     | 'Boolean' '?'?
     | listType
     ;
listType : 'List' '<' type '>' ;
assignmentExpression : variableName '=' expression ;
functionDeclare : 'override'? 'fun' identifier '(' functionDeclareArgument? ')' (':' type)? (parenthesizedBody | '=' expression)
                | 'abstract' 'fun' identifier '(' functionDeclareArgument? ')' (':' type)?
                ;
functionDeclareArgument : identifier (':' type)?
                        | functionDeclareArgument ',' identifier (':' type)?
                        ;
functionCall : (identifier | type) ('(' functionCallArgument? ')'| parenthesizedBody) ('.' (functionCall | variableName))?
             ;
functionCallArgument : expression (',' expression)* ;
classDeclare : 'abstract'? 'class' identifier ('(' classDeclareArgument? ')')? classInheritance? parenthesizedBody ;
classDeclareArgument : ('val' | 'var')? variableName ':' type '?'?
                     | classDeclareArgument ',' ('val' | 'var') variableName ':' type '?'?
                     ;
classInheritance : ':' (functionCall (',' identifier)? | identifier) ;
interfaceDeclare : 'interface' identifier parenthesizedBody ;
statementBody : bodyContent
              | parenthesizedBody
              ;
parenthesizedBody : '{' body? '}' ;
body : bodyContent+ ;
bodyContent : functionDeclare
            | functionCall
            | ifExpression
            | forStatement
            | whileStatement
            | assignment
            | returnStatement
            | expression
            ;
ifExpression : 'if' '(' condition ')' statementBody 'else' statementBody
             | 'if' '(' condition ')' statementBody
             ;
forStatement : 'for' '(' variableName 'in' (variableName | range) ')' statementBody ;
whileStatement : 'while' '(' condition ')' statementBody ;
returnStatement : 'return' expression? ;
expression : stringLiteral
           | assignmentExpression
           | ifExpression
           | parenthesizedBody
           | '(' additiveExpression ')'
           | additiveExpression
           | operatorAssignment
           | functionCall
           | condition
           | range
           | variableName
           ;
stringLiteral : QUOTE ;
additiveExpression : additiveExpression ('+' | '-' ) additiveExpression
                   | multiplicativeExpression
                   ;
multiplicativeExpression : multiplicativeExpression ('*' | '/') multiplicativeExpression
                         | fixExpression
                         ;
fixExpression : functionCall
              | prefix
              | postfix
              | variableName
              | number
              | '(' expression ')'
              | operatorFixExpression
              ;
prefix : ('++'|'--') variableName ;
postfix : variableName ('++'|'--') ;
operatorFixExpression : ('+' | '-') fixExpression ;
operatorAssignment : additiveExpression ('+=' | '-=' | '*=' | '/=' ) additiveExpression ;
condition : (conditionExpression | type) conditionOperator (conditionExpression | type)
          | condition logicalOperator condition
		  ;
logicalOperator : '&&' | '||' ;
conditionOperator : '>' | '<' | '==' | '<=' | '>=' | 'is' | 'in'
                  | notConditionOperator
                  ;
notConditionOperator : '!' conditionOperator | '!=' ;
conditionExpression : stringLiteral
                    | ifExpression
                    | variableName
                    | functionCall
                    | range
                    | '(' additiveExpression ')'
                    | additiveExpression
                    ;
range : rangeExpression ('..' | 'downTo') rangeExpression ('step' rangeExpression)?;
variableName : identifier ('[' expression ']')? ('.' (functionCall | variableName))? ;
rangeExpression : variableName
                | functionCall
                | '(' additiveExpression ')'
                | additiveExpression
                ;

//lexer rules
WhiteSpace : [ \n\r\t]+ -> skip ;
SingleAnnot : '//' ~[\n\r\b\t]* '\n' -> skip ;
MultiAnnot : '/*' ~[\r\t\b]* '*/' -> skip ;
QUOTE : '"' ~[\r\b\t\\"]* '"' ;
Letter : [a-zA-Z]+ ;
Digit : [0-9]+ ;
