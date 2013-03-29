%{
#include <stdio.h>

struct Message {
 char * input, * output;
};
    int yylex(void);
    void yyerror(char *);

typedef enum { PAST=-1,PRESENT=0,FUTURE=1} TENSE;

struct TVerb{
    TENSE tense;
};

%}

%union
{
    int iValue;
    char * sValue;
    struct Entity * pEntity;
};

%token INTEGER
%token<sValue> NAME
%token BRACKET_OPEN
%token BRACKET_CLOSE
%token BRACES_OPEN
%token BRACES_CLOSE
%token SEMICOLON
%token COMMA
%token STOP
%token BLANK
%token VERB_IS_PRES
%token VERB_IS_PAST
%token VERB_DO_SINGLE_PAST
%token VERB_DO_SINGLE_PRES
%token WHERE
%type<pEntity> statement
%type<

%%

base :
base STOP base {
              }
| statement { printf("statement");
            }
;

blank : BLANK | blank BLANK
where   : blank WHERE | WHERE blank | blank WHERE blank

subject: NAME
object : NAME
s_etre : VERB_IS_PRES | VERB_IS_PAST
s_do : VERB_DO_SINGLE_PRES | VERB_DO_SINGLE_PAST

s_verb : s_do | s_etre

verb: blank s_verb | s_verb blank| s_verb | blank s_verb blank

active_voice : subject verb object { printf(" Active VOICE " );}

statement: subject verb object { printf( "verb") ; } |
    where verb subject { printf("where"); }

%%

// TODO: -- Active vs Passive voice

void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}

#ifdef __BUILD_LIB__
void parseString(struct Message * m){
yy_scan_string(m->input);
printf("\n<xml>");
printf("<!--Input: %s-->\n",m->input);
yyparse();
printf("\n</xml>");
strcpy(m->output,output);
}
#else
int main(int argc,char * argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <input-string>",argv[1]);
        return 1;
    }
    else
    {
        printf("\n<xml>");
        printf("<!--Input: %s-->\n",argv[1]);
    }
    yy_scan_string(argv[1]);
    yyparse();
    printf("\n</xml>");
    return 0;
}
#endif
