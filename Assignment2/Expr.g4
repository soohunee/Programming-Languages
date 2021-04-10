/* Expr.g4 extended -Modify this for PA#1 */

grammar Expr;

//parser rules
prog  : (assn SCOLON NEWLINE? | expr SCOLON NEWLINE?)*;
expr  : expr(PLUS|MINUS)term
	  | term
      ;
term  : term (MULT|DIV) factor
	  | factor
	  ;
factor: num
	  | LBRACKET expr RBRACKET
	  ;
num   : (SIGNM)?INT
	  | (SIGNP|SIGNM)REAL
	  | ID
	  ;
assn  : ID EQ num
	  ;

//lexer rules
SIGNM : '-' ;
SIGNP : '+' ;
SCOLON : ';' ;
EQ : '=' ;
LBRACKET : '(' ;
RBRACKET : ')' ;	 
MULT : '*' ;
DIV : '/' ;
PLUS : ' + ' ;
MINUS : ' - ' ;
NEWLINE: [\r\n]+ ;
INT: [0-9]+ ;	//should handle negatives
REAL: [0-9]+'.'[0-9]* ; // should handle sign (+/-)
ID: [a-zA-Z]+ ;
WS: [ \t\r\n]+ -> skip ;
