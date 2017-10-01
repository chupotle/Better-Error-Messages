/* Simple ad-hoc scanner for the calculator language.
    Michael L. Scott, 2008-2017.
 */


#include <iostream>
#include "scan.hpp"
using namespace std;
std::string token_image;
token scan() {
        static int c = ' ';
        /* next available char; extra (int) width accommodates EOF */
        int i = 0;          /* index into token_image */
        token_image = "";
        /* skip white space */
        while (isspace(c)) {
                c = std::cin.get();
        }
        if (c == EOF)
                return t_eof;
        if (isalpha(c)) {
                do {
                        token_image+= c;
                        c = std::cin.get();
                } while (isalpha(c) || isdigit(c) || c == '_');
                //token_image[i] = '\0';
                cout << "WOWOW " << token_image << " WOWOW" << "\n";
                if (token_image == "read") return t_read;
                else if (token_image == "write") return t_write;
                else if (token_image == "if") return t_if;
                else if (token_image == "fi") return t_fi;
                else if (token_image == "do") return t_do;
                else if (token_image == "od") return t_od;
                else if (token_image == "check") return t_check;
                else return t_id;
        }
        else if (isdigit(c)) {
                do {
                        token_image[i++] = c;
                        c = std::cin.get();
                } while (isdigit(c));
                token_image[i] = '\0';
                return t_literal;
        } else switch (c) {
                case ':':
                        if ((c = std::cin.get()) != '=') {
                                fprintf(stderr, "error\n");
                                exit(1);
                        } else {
                                c = std::cin.get();
                                return t_gets;
                        }
                        break;

                case '=':
                        if ((c = std::cin.get()) != '=') {
                                fprintf(stderr, "error\n");
                                exit(1);
                        } else {
                                c = std::cin.get();
                                return t_eq;
                        }
                        break;
                case '<':
                        if ((c = std::cin.get()) == '>') {
                                c = std::cin.get();
                                return t_neq;
                        }
                        else if ((c = std::cin.get()) == '=') {
                                c = std::cin.get();
                                return t_leq;
                        }
                        else {
                                c = std::cin.get();
                                return t_lthan;
                        }
                        break;
                case '>':
                        if ((c = std::cin.get()) == '=') {
                                c = std::cin.get();
                                return t_geq;
                        }
                        else {
                                c = std::cin.get();
                                return t_gthan;
                        }
                        break;
                case '$':
                        if ((c = std::cin.get()) != '$') {
                                fprintf(stderr, "error\n");
                                exit(1);
                        } else {
                                c = std::cin.get();
                                return t_eof;
                        }
                        break;

                case '+': c = std::cin.get(); return t_add;
                case '-': c = std::cin.get(); return t_sub;
                case '*': c = std::cin.get(); return t_mul;
                case '/': c = std::cin.get(); return t_div;
                case '(': c = std::cin.get(); return t_lparen;
                case ')': c = std::cin.get(); return t_rparen;
                default:
                        cout << "error\n";
                        exit(1);
                }
}
