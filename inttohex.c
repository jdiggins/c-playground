/* John Diggins
 * Give program an int, it gives back hex
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> /* for isatty */

#define ENOUGH_SPACE (sizeof(int) * 2 + 4)
#define LINELEN      1024

void itox(char hexstring[], int n)
{
    int negative = (n < 0 ? 1 : 0);
    if(negative)
        n=0-n;

    int i, j, holdNumber = n, length = (int) sizeof(int) * 2;
    char* buffer = malloc(length + 1);

    for (i = length - 1; i >= 0; i--) {
        if(n == 0)
            break;
        int remainder = n % 16;
        n /= 16;

        if (remainder <= 9)
            buffer[i] = remainder + 48;
        else
            buffer[i] = remainder + 55;

        printf("i: %d buffer: %d\n", i, buffer[i]);
    }
    j = 0;
    if(negative)
        hexstring[j++] = '-';
    hexstring[j++] = '0';
    hexstring[j++] = 'x';

    for ( ; i < length-1; i++, j++) {
        hexstring[j] = buffer[i+1];
    }
    hexstring[j]='\0';
    free(buffer);
}
int my_pow(int m, int n)
{
    int i = 0, p = 1;
    for( ; i < n; i++) {
        p *= m;
    }
    return p;
}
int xtoi (char hexstring[])
{
    int n = 0, i, j, holdInt;
    int length = (unsigned) strlen(hexstring);
    
    for (i = length - 1, j = 0; i >= 0; i--, j++) {
        if (hexstring[i] == 'x')
            break;
        if (hexstring[i] < 58)
            holdInt = hexstring[i]-48;
        else 
            holdInt = hexstring[i]-55;
        n += holdInt * my_pow(16, j);
    }
    if(hexstring[0] == '0')
        n = 0-n;
    return n;
}



int main(int argc, char** argv)
{
    char hexstring[ENOUGH_SPACE], line[LINELEN];
    int n, m;

    while((1)) {
        if(isatty(STDIN_FILENO))
            fputs("Enger an integer> ", stdout);
        
        if(fgets(line, LINELEN, stdin) == NULL)
            return 0;
        
        sscanf(line, "%d", &n);

        printf("\nn: %d", n);

        itox(hexstring, n);
        m = xtoi(hexstring);

        printf("\ninput decimal int   : %d\n", n);
        printf("hex representation  : %s\n", hexstring);
        printf("reconverted decimal : %d\n\n", m);
    }
    return 0;
}