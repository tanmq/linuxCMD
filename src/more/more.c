#include <stdio.h>
#include <unistd.h>
#define PAGELEN 4
#define LINELEN 512

void do_more(FILE*);
int see_more();

int main(int ac, char *av[])
{
    FILE *fp;
    if (ac == 1) {
        do_more(stdin);
    } else {
        while (--ac) {
            if ((fp = fopen( *++av, "r")) != NULL) {
                do_more(fp);
                fclose(fp);
            }
            else {
                exit(1);
            }
        }
    }
}

//read PAGELEN lines, then call see_more() for further instructions
void do_more(FILE *fp)
{
    char line[LINELEN];
    int num_of_lines = 0;
    int reply;

    while (fgets(line, LINELEN, fp)) {
        if (num_of_lines == PAGELEN) {
            reply = see_more();
            if (reply == 0) {
                break;
            }

            num_of_lines -= reply;
        }

        if (fputs (line, stdout) == EOF) {
            exit(1);
        }
        num_of_lines ++;
    }
    
}




int see_more()
{
    int c;
    // This tip will split your content. I have not got a solution.
    printf("\033[7m more?\033[m");
    FILE *fp_tty = fopen("/dev/tty", "r");
    if (fp_tty == NULL) {
        exit(1);
    }

    while ( (c = getc(fp_tty)) != EOF) {
        if (c == 'q') {
            return 0;
        }
        if (c == ' ') {
            return PAGELEN;
        }
        if (c == '\n') {
            return 1;
        }
    }

    return 0;
}
