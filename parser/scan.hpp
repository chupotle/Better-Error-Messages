/* Definitions the scanner shares with the parser
    Michael L. Scott, 2008-2017.
*/

enum token {t_read, t_write, t_if, t_fi, t_do, t_od, t_check, t_id, t_literal, t_gets, t_ro, t_leq, t_geq,t_eq, t_neq, t_lthan, t_gthan,  t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof};

extern std::string token_image;

extern token scan();
