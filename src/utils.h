#ifndef     __UTILS_H
#define     __UTILS_H


#define CHAR_NULL		'\0'



void printStr(const char * str);
void printValHex(uint64_t val, uint32_t padNum, char * prefix, char * suffix);
void printValDec(uint32_t val, char * prefix, char * suffix);
int strcmp(const char * str1, const char * str2);
uint32_t strToHex32(char * str);


#endif    /* __UTILS_H */

