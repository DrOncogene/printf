#ifndef MAIN_H
#define MAIN_H
int _printf(const char *format, ...);
char *print_str(char *s, char *, char, char *);
char *print_strcap(char *s, char *, char *);
char *print_char(char c, char *);
char *print_int(int num, char *, char *);
char *print_uint(int, char *);
char *print_base(unsigned long int num, unsigned int base, char f,
		char *buff, char *flags);
char *print_p(long unsigned int, char *);
char hex(unsigned num, char flag);
int len(char *s);
unsigned int len_int(unsigned int);
char *save_int(char *, int, unsigned int);
char *save_uint(char *, unsigned int, unsigned int);
char get_format(const char *format, int *);
char *get_flags(const char *format, int);
char *render_flags(char *flags, char *, int);
char *plus_flag(char *);
char *invisible_plus(char *);
char *hash_flag(char *);
#endif
