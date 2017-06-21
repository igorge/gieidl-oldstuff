header "pre_include_cpp" 
{
    // gets inserted before the antlr generated includes in the cpp file
    /////////////////////////////////////////////////////////////////////////////
    #include "stdafx.h"
    
    #include <sstream>
    
    #pragma warning( disable : 4267 )
    /////////////////////////////////////////////////////////////////////////////
    //
}

header
{
    // Header here
    typedef std::string string_t;
}

options
{
	language="Cpp";
}

///////////////////////////////////////////////////////////////////////////////
// Lexer
///////////////////////////////////////////////////////////////////////////////
class gieidl_lexer extends Lexer;
options 
{
	defaultErrorHandler=false;
	k=9;
	//exportVocab=MINIP;
	charVocabulary = '\3'..'\377';
}
tokens 
{
	KW_INTERFACE    =   "interface";
	KW_STRUCT       =   "struct";
	KW_CLASS        =   "class";
	
	
	KW_PRIVATE      =   "private";
	KW_PUBLIC       =   "public";
	KW_PROTECTED    =   "protected";
	
	KW_CONST        =   "const";
	
	KW_NAMESPACE    =   "namespace";
	
	
	//NULL_NODE;
	
	//EXPRESSION;
	//AGG_DEF_ACCESS_BLOCK;
	//AGG_PRIVATE_ACCESS_BLOCK;
	//AGG_PUBLIC_ACCESS_BLOCK;
	
	//TYPE_INFO;
	//PTR;
	//CONST_PTR;
	//PTR_BLOCK;
	
	//SYMBOL;
	//CONST_SYMBOL;
	
	//VAR_DEFINATION;
	//FUNC_DEFINITION;
}

{
    //new members here
    private:
}


// lexems

WS
        : (' ' | '\t' | '\n' {newline();} | '\r')+
          {$setType(antlr::Token::SKIP); }
        ;

CPP_COMMENT
        : ( "//" (~'\n')* ) {$setType(antlr::Token::SKIP); }
        ;   

private
ESCAPE
        : '\\'
          ( 'n' { $setText("\n"); }
          | 'r' { $setText("\r"); }
          | 't' { $setText("\t"); }
          | '"' { $setText("\""); }
          )
        ;
             
        
private
DEC_DIGIT
        : ('0'..'9')
        ;

private
DEC_DIGITS
        : (DEC_DIGIT)+
        ;

private
HEX_DIGIT
        : ('A'..'F')| ('a'..'f') | DEC_DIGIT
        ;
        
private
HEX_DIGITS
        : (HEX_DIGIT)+
        ;
        
private
LATIN_LETTER
        :  ('a'..'z') | ('A'..'Z')
        ;
        
IDENTIFIER 
        : (LATIN_LETTER | '_') (LATIN_LETTER | '_' | DEC_DIGIT)*
        ;
        
STRING
        : '"'! (ESCAPE | ~('"'|'\\') )* '"'!
        ;

NUMBER
        : ("0x") => "0x" HEX_DIGITS
        | DEC_DIGITS
        ;        
        
MSGUID
        : HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT '-'
          HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT '-'
          HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT '-'
          HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT '-'
          HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
          HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
        ;        
        
STAR    : '*'
	    ;

PLUS    : '+'
	    ;

MINUS   : '-'
	    ;

DIV	    : '/'
        ;

SEMI    options {paraphrase = ";"; }
        : ';'
	    ;


DCOLON   options {paraphrase = "::"; }
        : "::"
        ;

COLON   options {paraphrase = ":"; }
        : ':' 
        ;	 

COMMA   : ','
        ;
        
DOT     options {paraphrase = "."; } 
        : '.'
        ;

ASSIGN  options {paraphrase = "="; } 
        : '='
        ;

AND     : '&'
        ;

LPAREN  : '('
	    ;
RPAREN  : ')'
	    ; 
        
LCURLY  options {paraphrase = "{"; }
        : '{'
	    ;
RCURLY  options {paraphrase = "}"; }
        : '}'
	    ; 
	    
LBRACK  options {paraphrase = "["; } 
        : '['
        ;	    
RBRACK  options {paraphrase = "]"; } 
        : ']'
        ;	    
        


//preprocessor directrives handling
private
PREPROC_KW_LINE
        : "line"
        ;
private
PREPROC_WS
        : (' '|'\t'|'\r')*
        ;  
private
PREPROC_DIGITS
        : ('0'..'9')+
        ;        

private
PREPROC_STRING
        : '"'! (~('"'))* '"'!
        ; 
        
private
PREPROC_LINE_NO 
        :
          PREPROC_KW_LINE!
          PREPROC_WS!
          l_num:PREPROC_DIGITS     
          PREPROC_WS!
          f_name:PREPROC_STRING
          PREPROC_WS!
          '\n'         
          {
            std::istringstream str( l_num->getText() );
            unsigned int line_no;
            str >> line_no;
            if(!str){GIE_LIB_NOT_IMPLEMENTED;};
            this->setFilename( f_name->getText() );

            //update line number and file name
            inputState->line = line_no;
            
          }
          ;                        
        
PREPROC_DIRECTRIVE
        :   "#"! PREPROC_WS!
            (PREPROC_LINE_NO)!
            { $setType(antlr::Token::SKIP); }
        ;
        