/* Definitions the scanner shares with the parser
    Michael L. Scott, 2008-2017.
*/

typedef enum {t_read, t_write, t_id, t_literal, t_gets, t_if, t_fi, t_do, t_od, t_check, t_ro, t_eq, t_neq, t_lthan, t_gthan, t_leq, t_geq,
                t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof} token;

extern char token_image[100];

extern token scan();
