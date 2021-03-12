#include <stdio.h>
#include <stdlib.h>


void read_file(FILE *file);
void count_brackets(FILE *file);
void check_brackets(FILE *file);

int main(int argc, char *argv[])
{
    FILE *fp;
    if((fp=fopen("skobki.txt","r"))==NULL){
        printf("ERROR");
        exit(1);
    }
    else
        printf("DONE\n");


    read_file(fp);printf("\n");
    rewind(fp);
    count_brackets(fp);
    /*
    int sk=0;
    int i=0;
    while(argv[1][i]!='\0'){
        if(argv[1][i]=='{')
            sk++;
        i++;
    }
    printf("\nsk in argument: %d", sk);
    */
    //printf("\n%s", argv[1]);
    return 0;
}

void read_file(FILE *file){
    int ch;
    while((ch=getc(file))!=EOF){
        printf("%c",ch);
    }
}

void count_brackets(FILE *file){
    int ch; int brackets=0;
    while((ch=getc(file))!=EOF){
        if(ch=='{' || ch=='}'){
            brackets++;
        }
    }
    printf("Count { or } brackets: %d",brackets);
}

void check_brackets(FILE *file){
    int fig_bracket=0, circ_bracket=0, square_bracket=0;

}
