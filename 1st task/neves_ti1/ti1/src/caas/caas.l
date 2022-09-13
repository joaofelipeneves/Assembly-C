
%{
#include "caas_parser.h"
#include "caas.h"
extern alu_opcode get_alu_opcode(const char* mnemonic);
%}

%option outfile="caas_lexer.c" header-file="caas_lexer.h"

%option yylineno
%option noyywrap


MEMORY            ".data"
CODE            ".code"
REGISTER        r[0-7]
NUMBER          [0-9]+|-[0-9]+
ADDRESS         "("[0-9]+")"
IDENT           [A-Za-z_][A-Za-z0-9_]*
BIN_ALU_MNE     "add"|"sub"|"and"|"or"|"sar"|"sal"
UN_ALU_MNE      "neg"|"not"
MEM_MNE         "mov"
INT_MNE         "int"
SIZE            ".w"|".b"

COMMENT     "#"[^\n\r]*
IGNORE      [ \r\n\t]*
COMMA       ","

%%

{MEMORY}          { return data_directive; }
{CODE}          { return code_directive; }
{NUMBER}		{ sscanf(yytext, "%d", &yylval.num); return number; }
{REGISTER}      { sscanf(yytext, "r%d", &yylval.num); return cpu_register; }

{ADDRESS}		{ sscanf(yytext, "(%d)", &yylval.num); return memory_address; }
{BIN_ALU_MNE}   { yylval.num = get_alu_opcode(yytext); return binary_alu_mnemonic; }
{UN_ALU_MNE}    { yylval.num = get_alu_opcode(yytext); return unary_alu_mnemonic; }
{MEM_MNE}       { yylval.num = get_alu_opcode(yytext); return ls_mnemonic; }
{INT_MNE}       { return int_mnemonic; }

{SIZE}      {
    if (yytext[1] == 'w')
        yylval.num = WORD;
    else
        yylval.num = BYTE;
    return data_size; }

{COMMA}         {  return comma; }
{IGNORE}        { /* ignore */ }
{COMMENT}       { /* also skip comments */ }



%%

int yyerror(const char* msg) {
    fprintf(stderr, "Line %d: %s when parsing %s.\n", yylineno, msg, yytext);
    return 0;
}