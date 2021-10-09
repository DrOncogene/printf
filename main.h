#ifndef MAIN_H
#define MAIN_H
int _printf(const char *format, ...);
char *print_str(char *s, char *, char);
char *print_strcap(char *s, char *);
char *print_char(char c, char *);
char *print_int(int num, char *);
char *print_uint(int, char *);
int print_base(long unsigned int, unsigned int, char, char *, unsigned int);
char *print_p(long unsigned int, char *);
char hex(unsigned num, char flag);
int len(char *s);
unsigned int len_int(unsigned int);
char *save_int(char *, int, unsigned int);
char *save_uint(char *, unsigned int, unsigned int);
#endif
