#include <stdio.h>
#include <stdarg.h>		
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int my_putstr(char *c){
    char * result = c;
    int counter = 0;
    for(int i = 0; result[i]!='\0'; i++){
        putchar(result[i]);
        counter++;
    }   
    
    return counter;
}

int my_putnbr(unsigned int num, int base){
    int counter = 0;
    static char Representation[]= "0123456789ABCDEF"; 
    int i = 1;
    char num1[50];
    if(num<0){
        num = 4294967296+num;
    }
    
    while(num!=0){
        num1[i++]=Representation[num%base];
        num = num/base;
    }
    while((i-1)>0){
        putchar(num1[i-1]);
        counter++;
        i--;
    }
    return counter;
}
int my_putptr(int c){
    int counter = 0;
    int num = c;
    int *ptr = &num;
    unsigned long w = (unsigned long) ptr;

    int i = 1, t;
    char hexc[15];
    while(w!=0){
        t = w%16;
        if(t<10){
            t=t+48;
        }
        else {
            t=t+55;
        }
        hexc[i++]=t;
        w = w/16;
    }
    while((i-1)>0){
        if (hexc[i-1]>64 && hexc[i-1]<91) {
            hexc[i-1]+=32;
        }
        putchar(hexc[i-1]);
        counter++;
        i--;
    }
    return counter;
}


int my_printf(char * restrict format, ...){
    
    va_list arg; 
	va_start(arg, format); 
    int counter = 0;

    while (*format != '\0') 
    {
        while(*format != '%' && *format != '\0' ){
            putchar(*format);
            counter++;
            format++;
        }
        if (*format=='%') {
            format++;
        }
        if (*format == 'd' || *format == 'i'){
            int c = va_arg(arg, int);
            if(c<0){
                putchar('-');
                c *= -1;
            }
            counter += my_putnbr(c, 10);
            format++;
        }
        else if (*format == 'u') {
            counter += my_putnbr(va_arg(arg, int), 10);
            format++;
        }
        else if(*format == 'o'){
            counter += my_putnbr(va_arg(arg, int), 8);
            format++;
        }
        else if (*format == 'x'){
            counter += my_putnbr(va_arg(arg, int), 16);
            format++;
        }
        else if (*format == 'c') {
            int c = va_arg(arg, int);
            putchar(c);
            counter++;
            format++;
        }
        else if (*format == 's') {
            char *a = va_arg(arg, char*);
            if (a==(char*)NULL) {
                my_putstr("(null)");
            }
            else {
                counter += my_putstr(a);
            }
            format++;
            
        }
        else if (*format == 'p'){
            my_putstr("0x");
            counter += 2;
            counter += my_putptr(va_arg(arg, int));            
            format++;
        }
        
    }
    va_end(arg);
    return counter;
}

int main(){
    int j = my_printf("%s%s%s%s%s\n", "H", "e", "l", "l", "o");
    printf("\nNumber of characters: %d", j);
    return 0;
}