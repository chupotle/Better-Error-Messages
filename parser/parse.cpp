/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
    Michael L. Scott, 2008-2017.
 */


#include <iostream>

#include "scan.hpp"
using namespace std;
const char* names[] = {"read", "write", "id", "literal", "gets",
                       "add", "sub", "mul", "div", "lparen", "rparen", "eof"};

static token input_token;

void error () {
        cout<< ("syntax error\n");
        exit (1);
}

void match (token expected) {
        if (input_token == expected) {
                cout << "matched " << names[input_token];
                if (input_token == t_id || input_token == t_literal)
                        cout << ": " << token_image;
                cout << "\n";
                input_token = scan ();
        }
        else error ();
}

void program ();
void stmt_list ();
void stmt ();
void relation();
void expr ();
void expr_tail ();
void term_tail ();
void term ();
void factor_tail ();
void factor ();
void rel_op();
void add_op ();
void mul_op ();

void program () {
        switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
                cout << "predict program --> stmt_list eof\n";
                stmt_list ();
                match (t_eof);
                break;
        default: error ();
        }
}

void stmt_list () {
        switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
                cout << "predict stmt_list --> stmt stmt_list\n";
                stmt ();
                stmt_list ();
                break;
        case t_eof:
                cout << "predict stmt_list --> epsilon\n";
                break;      /*  epsilon production */
        default: error ();
        }
}

void stmt () {
        switch (input_token) {
        case t_id:
                cout << "predict stmt --> id gets expr\n";
                match (t_id);
                match (t_gets);
                relation ();
                break;
        case t_read:
                cout << "predict stmt --> read id\n";
                match (t_read);
                match (t_id);
                break;
        case t_write:
                cout << "predict stmt --> write expr\n";
                match (t_write);
                relation ();
                break;
        case t_if:
                match (t_if);
                relation();
                stmt_list();
                match(t_fi);
                break;
        case t_do:
                match (t_do);
                stmt_list();
                match (t_do);
                break;
        case t_check:
                match (t_check);
                relation();
                break;
        default: error ();
        }
}

void relation() {
        switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
                cout << "predict relation --> expr expr_tail\n";
                expr ();
                expr_tail ();
                break;
        default: error ();
        }
}

void expr () {
        switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
                cout << "predict expr --> term term_tail\n";
                term ();
                term_tail ();
                break;
        default: error ();
        }
}

void expr_tail() {
        switch (input_token) {
        case t_eq:
        case t_neq:
        case t_lthan:
        case t_gthan:
        case t_leq:
        case t_geq:
                rel_op();
                expr();
                break;
        case t_read:
        case t_write:
        case t_if:
        case t_fi:
        case t_do:
        case t_od:
        case t_check:
        case t_eof:
        case t_rparen:
                cout << "predict term_tail --> epsilon\n";
                break; /*  epsilon production */
        }
}

void term_tail () {
        switch (input_token) {
        case t_add:
        case t_sub:
                cout << "predict term_tail --> add_op term term_tail\n";
                add_op ();
                term ();
                term_tail ();
                break;
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
                cout << "predict term_tail --> epsilon\n";
                break;      /*  epsilon production */
        default: error ();
        }
}

void term () {
        switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
                cout << "predict term --> factor factor_tail\n";
                factor ();
                factor_tail ();
                break;
        default: error ();
        }
}

void factor_tail () {
        switch (input_token) {
        case t_mul:
        case t_div:
                cout << "predict factor_tail --> mul_op factor factor_tail\n";
                mul_op ();
                factor ();
                factor_tail ();
                break;
        case t_add:
        case t_sub:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
                cout << "predict factor_tail --> epsilon\n";
                break;      /*  epsilon production */
        default: error ();
        }
}

void factor () {
        switch (input_token) {
        case t_id:
                cout << "predict factor --> id\n";
                match (t_id);
                break;
        case t_literal:
                cout << "predict factor --> literal\n";
                match (t_literal);
                break;
        case t_lparen:
                cout << "predict factor --> lparen expr rparen\n";
                match (t_lparen);
                expr ();
                match (t_rparen);
                break;
        default: error ();
        }
}

void rel_op() {
        switch (input_token) {
        case t_eq:
                cout << "predict rel_op --> eq\n";
                match (t_eq);
                break;
        case t_neq:
                cout << "predict rel_op --> neq\n";
                match (t_neq);
                break;
        case t_lthan:
                cout << "predict rel_op --> lthan\n";
                match (t_lthan);
                break;
        case t_gthan:
                cout << "predict rel_op --> gthan\n";
                match (t_gthan);
                break;
        case t_leq:
                cout << "predict rel_op --> leq\n";
                match (t_leq);
                break;
        case t_geq:
                cout << "predict rel_op --> geq\n";
                match (t_geq);
                break;
        default: error ();
        }
}

void add_op () {
        switch (input_token) {
        case t_add:
                cout << "predict add_op --> add\n";
                match (t_add);
                break;
        case t_sub:
                cout << "predict add_op --> sub\n";
                match (t_sub);
                break;
        default: error ();
        }
}

void mul_op () {
        switch (input_token) {
        case t_mul:
                cout << "predict mul_op --> mul\n";
                match (t_mul);
                break;
        case t_div:
                cout << "predict mul_op --> div\n";
                match (t_div);
                break;
        default: error ();
        }
}

int main () {
        input_token = scan ();
        program ();
        return 0;
}
