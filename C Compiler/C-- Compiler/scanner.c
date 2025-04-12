#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "scanner.h"


/*
 * File: scanner.c
 * Author: Jenny Yu
 * Purpose: Called from scanner-driver.c, gets
 * a char from stdin and matches it to the tokens
 * defined in scanner.h.
 * Skips over whitespace and comments.
*/


char* lexeme;
char buf[BUFSIZ];
char* ptr;
int lval;
int line = 1;


/*
 * Gets a character at a time from stdin and try to 
 * match it to a predefined token. Skips over white space 
 * and comments and gets the next character in the input 
 * if available.
*/
int get_token() {
    // Read input from the console
    char ch = getchar();

    // Skip white space
    while(isspace(ch)) {
        //printf("whitespace\n");
        if(ch == '\n') {
            //printf("New line\n");
            line++;
            //printf("Line #: %d\n", line);
        }
        ch = getchar();
    }
    // If EOF, exit
    if(ch == EOF) {
        return EOF;
    }
    

    // Needs to check if / or /*
    if(ch == '/') {
        char next = getchar(); // Get next character to check

        // Next character is *, so comment, skip it
        if(next == '*') {
            while(1) {
                next = getchar(); 
               
                while(1) {
                    // Skip white space
                    while(isspace(next)) {
                        next = getchar();
                    }
                    // Return if EOF
                    if(next == EOF) {
                        return EOF;
                    }
                    
                    // Check if comment ends
                    if(next == '*') {
                        char endComment = getchar();
                        
                        // If end of comment, break
                        if(endComment == '/') {
                            break;
                        }
                        // If not, put char back and keep looking
                        else {
                            ungetc(endComment, stdin);
                        }
                    }
                    next = getchar(); // Keep getting next char
                }
                // Check the char after end of the comment
                ch = getchar();
                
                // Skip white space
                while(isspace(ch)) {
                    if(ch == '\n') {
                        line++;
                    }
                    ch = getchar();
                }
                
                // If newline or EOF, return EOF to exit
                if(ch == EOF) {
                    return EOF;
                }

                // Check for another comment
                if(ch == '/') {
                    next = getchar();
                    
                    // Not another comment, return /
                    if(next != '*') {
                        ungetc(next, stdin);
                        lexeme = "/";
                        return opDIV;
                    }
                }
                // Not another comment or /, break
                else {
                    break;
                }
            }
        }

        // Not comment, unget and return /
        else {
            ungetc(next, stdin);
            lexeme = "/";
            return opDIV;
        }
    }


    // If the character is a digit, get the entire digit
    if(isdigit(ch)) {
        // Save the input from console into buf
        ptr = buf; 
        *ptr++ = ch;
        
        ch = getchar();
        // Get the digit while input isdigit
        while(isdigit(ch)) {
            *ptr++ = ch;
            ch = getchar();
        }

        *ptr = '\0';
        if(ch != EOF) {
            ungetc(ch, stdin);
        }

        // Save the input and return
        lexeme = buf;
        return INTCON;
    }
    // If the character is a letter, get the entire word
    else if(isalpha(ch)) {
        // Save the input from console into buf
        ptr = buf;
        *ptr++ = ch;
        
        ch = getchar();
        // Get the digit while input is digit/alpha or _
        while(isalnum(ch) || ch == '_') {
            *ptr++ = ch;
            ch = getchar();
        }

        *ptr = '\0';
        if(ch != EOF) {
            ungetc(ch, stdin);
        }
        
        // Save the input and return a keyword or identifier
        lexeme = strdup(buf);
        
        if(strcmp(buf, "int") == 0) {
            return kwINT;
        }
        else if(strcmp(buf, "if") == 0) {
            return kwIF;
        }
        else if(strcmp(buf, "else") == 0) {
            return kwELSE;
        }
        else if(strcmp(buf, "while") == 0) {
            return kwWHILE;
        }
        else if(strcmp(buf, "return") == 0) {
            return kwRETURN;
        }
        // Not a keyword, return identifier
        else {
            return ID;
        }
    }
    // Left paren
    else if(ch == '(') {
        lexeme = "(";
        return LPAREN;
    }
    // Right paren
    else if(ch == ')') {
        lexeme = ")";
        return RPAREN;
    }
    // Left curly brace
    else if(ch == '{') {
        lexeme = "{";
        return LBRACE;
    }
    // Right curly brace
    else if(ch == '}') {
        lexeme = "}";
        return RBRACE;
    }
    // Comma
    else if(ch == ',') {
        lexeme = ",";
        return COMMA;
    }
    // Semicolen
    else if(ch == ';') {
        lexeme = ";";
        return SEMI;
    }
    // Needs to check if = or ==
    else if (ch == '=') {
        char next = getchar();

        if(next != '=') {
            // Not ==, put the char back into input, return =
            ungetc(next, stdin);
            lexeme = "=";
            return opASSG;
        }
        else {
            // Is ==, return ==
            lexeme = "==";
            return opEQ;
        }
    }
    // Addition
    else if (ch == '+') {
        lexeme = "+";
        return opADD;
    }
    // Subtraction
    else if (ch == '-') {
        lexeme = "-";
        return opSUB;
    }
    // Multiplication
    else if (ch == '*') {
        lexeme = "*";
        return opMUL;
    }
    // Needs to check if ! or !=
    else if(ch == '!') {
        char next = getchar();

        if(next != '=') {
            // Not !=, put char back, return !
            ungetc(next, stdin);
            lexeme = "!";
            return opNOT;
        }
        else {
            lexeme = "!=";
            return opNE;
        }
    }
    // Needs to check if > or >=
    else if(ch == '>') {
        char next = getchar();

        if(next != '=') {
            // Not >=, put char back, return >
            ungetc(next,stdin);
            lexeme = ">";
            return opGT;
        }
        else {
            lexeme = ">=";
            return opGE;
        }
    } 
    // Needs to check if < or <=
    else if(ch == '<') {
        char next = getchar();

        if(next != '=') {
            // Not <=, put char back, return <
            ungetc(next,stdin);
            lexeme = "<";
            return opLT;
        }
        else {
            lexeme = "<=";
            return opLE;
        }
    } 
    // Needs to check if &&
    else if(ch == '&') {
        char next = getchar();

        if(next != '&') {
            // Not &&, put char back, return UNDEF
            ungetc(next,stdin);
            char undef[2];
            undef[0] = ch;
            undef[1] = '\0';
            lexeme = strdup(undef);
            return UNDEF;
        }
        else {
            lexeme = "&&";
            return opAND;
        }
    } 
    // Needs to check if ||
    else if(ch == '|') {
        char next = getchar();

        if(next != '|') {
            // Not &&, put char back, return UNDEF
            ungetc(next, stdin);
            char undef[2];
            undef[0] = ch;
            undef[1] = '\0';
            lexeme = strdup(undef);
            return UNDEF;
        }
        else {
            lexeme = "||";
            return opOR;
        }
    }
    // Undefined
    else {
        char undef[2];
        undef[0] = ch;
        undef[1] = '\0';
        lexeme = strdup(undef);
        return UNDEF;
    }

}

