

%{
#include <stdio.h>
#include "structures.h"

void processAssignment(char * subject, struct TVerb * tverb, char* object){
   printf("Subject=\"%s\"",subject);
   printf("Verb=\"%s Tense=%d\"",tverb->name,(int)tverb->tense);
   printf("Object=\"%s\"",object);
}

struct Message {
 char * input, * output;
};
    int yylex(void);
    void yyerror(char *);


%}

%union
{
    int iValue;
    char * sValue;
    struct Entity * pEntity;
    struct TVerb * pVerb;
};

%token INTEGER
%token<sValue> NAME
%type<sValue> subject
%type<sValue> object

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
%type<pVerb> verb
%type<pVerb> s_singular_verb
%type<pVerb> singular_verb
%type<pVerb> s_plural_verb
%type<pVerb> plural_verb
%type<pVerb> s_singular_do
%type<pVerb> s_plural_do
%type<pVerb> s_singular_etre
%type<pVerb> s_plural_etre

%%

base :
base STOP base {
              }
| statement { printf("statement");
            }  | base STOP { printf("statement STOP"); }
;

blank : BLANK | blank BLANK
where   : blank WHERE | WHERE blank | blank WHERE blank

name:  NAME { $$ = $1; } | blank NAME { $$=$2; } | NAME blank { $$=$1; } | blank NAME blank { $$=$2; }
singular_subject: name 

plural_subject: plural_name 

object : NAME { $$ = $1; }

s_singular_etre : VERB_IS_PRES { $$ = createVerb("is",PRESENT); } | VERB_IS_PAST { $$ = createVerb("is",PAST); }
s_singular_do : VERB_DO_SINGLE_PRES { $$ = createVerb("do",PRESENT); } | VERB_DO_SINGLE_PAST { $$ = createVerb("do",PAST); }

s_plural_etre : VERB_IS_PLURAL_PRES { $$ = createVerb("is",PRESENT); } | VERB_IS_PLURAL_PAST { $$ = createVerb("is",PAST); }
s_plural_do : VERB_DO_PLURAL_PRES { $$ = createVerb("do",PRESENT); } | VERB_DO_PLURAL_PAST { $$ = createVerb("do",PAST); }

s_singular_verb : s_singular_do { $$ = $1; } | s_singular_etre { $$= $1;} 
s_plural_verb : s_plural_do { $$ = $1; } | s_plural_etre { $$= $1;} 


singular_verb: blank s_singular_verb { $$ = $2;} 
               | s_singular_verb blank { $$ = $1; } 
               | s_singular_verb { $$ = $1;}
               | blank s_singular_verb blank { $$ = $2;}

plural_verb: blank s_plural_verb { $$ = $2;} | s_plural_verb blank { $$ = $1; } | s_plural_verb { $$ = $1;} | blank s_plural_verb blank { $$ = $2;}

active_voice : 
   singular_subject singular_verb object { processAssignment($1,$2,$3); } |
   plural_subject plural_verb object { processAssignment($1,$2,$3); }

statement: active_voice { printf( "<-- Active Voice -->") ; } |
    where verb singlular_subject { printf("<-- Interrogative -->"); } |
    where verb plural_subject { printf("<-- Interrogative -->"); }

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
