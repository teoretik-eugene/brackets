#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    setlocale( LC_ALL,"Russian" );
    /*�������� � �������� ����������: */
    FILE *text;
    if((text = fopen(argv[1], "r"))==NULL){
        printf("ERROR IN OPENING FILE\n");
        exit(1);
    }
    if(argv[2]==NULL){
        printf("ERROR IN ARG 2\n");
        exit(1);
    }

    /*�������� ������ ��������, ��������� �� ������ ������ �����*/

    /*��������� ����� ���������� ������*/
    int count_brackets = 0, ch;
    while((ch=getc(text))!=EOF){
        if(ch=='"'){
            do{
                ch=getc(text);
            }while(ch!='"');
        }
        if(ch=='{' || ch=='}' || ch=='(' || ch==')' || ch=='[' || ch==']')
            count_brackets++;
    }
    rewind(text);

    char *string_br = (char *) malloc(count_brackets+1);//�������� ��� ������ ������

    /*������� � ������ ��� ������, �� ����������� ���������� � ��������*/
    int i = 0;
    while((ch=getc(text))!=EOF){
        if(ch=='"'){
            do{
                ch=getc(text);
            }while(ch!='"');
        }
        if(ch=='{' || ch=='}' || ch=='(' || ch==')' || ch=='[' || ch==']'){
            string_br[i] = ch;
            i++;
        }
    }
    rewind(text);
    string_br[i]='\0';
    printf("%s", string_br);printf("\n");   // ����� ������� �������� �� �����

    printf("��������������: \n");
    /*���������� �� ��������� ������*/
    int br = 0;
    while(argv[2][br]!='\0'){
        /*���������� ������ ������ � ���������*/
        switch(argv[2][br]){

            /*�������� �������� ������*/
            case '{':
                rewind(text);
                int fig_open = 0, fig_close = 0;
                /*�������� �� ����������*/
                int j=0;
                while(string_br[j]!='\0'){
                    if(string_br[j]=='{')
                        fig_open++;

                    if(string_br[j]=='}')
                        fig_close++;
                    j++;
                }
                if(fig_open > fig_close){
                    printf("������ {\n");
                    break;
                }
                if(fig_open < fig_close){
                    printf("������ }\n");
                    break;
                }
                /*
                ���� ��� ������ �������� ��� ������ �������� ������
                �� ���������� �������� �� �����������
                */
                j=0;
                while(string_br[j]!='\0'){
                    if(string_br[j]=='}' && string_br[j-1]=='('){
                        printf("����������� ����: (}");
                        break;
                    }
                    if(string_br[j]=='}' && string_br[j-1]=='['){
                        printf("����������� ����: [}");
                        break;
                    }
                    j++;
                }
            break;

            case '(':

            break;


        }

        br++;
    }

    printf("\n");
    rewind(text);
    printf("\n�������� ����: \n");
    while((ch=getc(text))!=EOF){
        printf("%c", ch);
    }



    return 0;
}
