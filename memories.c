#include <stdio.h>
#include <stdlib.h>


/**
 * main - Entry point of the program
 *
 * 
 *    gcc -Wall -Wextra -Werror main.c  -c
 * 
 *  size -A main.o
 * 

objdump -M intel -j .text -d main.o
 
 * 
 * Return: 0 every time.
 */

// https://medium.com/@SravanthiSinha/all-about-the-virtual-memory-1c8a3cf306b7

short toto = 7;

double this_is_bss;

int main(void)
{
    static char* str = "SUPINFO";
    
    
    char *p = (char*)malloc(sizeof(char));

    
    
    while(1) {
        
        sleep(1);
    }
    
    
  return (0);
}
