#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    setlocale( LC_ALL,"Russian" );

    /* �������� ��������� �����: */
    FILE *text;
    if((text = fopen(argv[1], "r"))==NULL){
        printf("ERROR IN OPENING FILE\n");
        exit(1);
    }
    if(argv[2]==NULL){
        printf("ERROR IN ARG 2\n");
        exit(1);
    }
    printf("��������� ������-��������:\n");
    printf("%s", argv[2]);printf("\n---------------------\n");

    int ch; // ��������� ��� ����������� �� �����

    /* ������� ���� � ������� */
    while((ch = getc(text))!= EOF){
        printf("%c", ch);
    }
    printf("\n---------------------\n");
    rewind(text);

    /* ��������� ���������� ������, �� ����������� ���������� � �������� */
    int count_brackets = 0;     // ���������� ������ ���� �����
    int fig_bracket = 0, circ_bracket = 0, square_bracket = 0;
    while((ch=getc(text))!=EOF){
        if (ch == '"'){
            do{
                ch = getc(text);
            }while(ch != '"');
        }
        if(ch == '{' || ch == '}'){
            count_brackets++;
            fig_bracket++;
        }
        if(ch == '(' || ch == ')'){
            count_brackets++;
            circ_bracket++;
        }
        if(ch == '[' || ch == ']'){
            count_brackets++;
            square_bracket++;
        }
    }
    rewind(text);

    /* �������� � ������� ������ �������� ������ */
    char *string_brackets = (char *) malloc (count_brackets + 1);
    int j = 0;
    while((ch=getc(text))!=EOF){
        if (ch == '"'){
            do{
                ch = getc(text);
            }while(ch != '"');
        }
        if(ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '[' || ch == ']'){
            string_brackets[j] = ch;
            j++;
        }
    }
    string_brackets[j] = '\0';
    printf("������ ��������: \n");
    printf("%s", string_brackets);
    rewind(text);

    printf("\n��������������: \n");
    /*���������� �� ��������� ������*/
    int br = 0;
    while(argv[2][br]!='\0'){
        switch(argv[2][br]){

                    /* �������� �������� ������ */
        case '{':
            j = 0;
            int f = 0, k = 0;
            char *fig_string = (char *) malloc(fig_bracket+1);
            while(string_brackets[j]!='\0'){
                if(string_brackets[j] == '{'){
                    fig_string[f] = '{';
                    f++;
                    k++;
                }

                if(string_brackets[j] == '}' && fig_string[f-1] != '{'){
                    fig_string[k] = '}';
                    --f;
                    k++;
                }

                if(string_brackets[j]=='}' && fig_string[f-1] == '{'){
                    fig_string[f-1] = ' ';
                    --f;
                }
                j++;
            }
            //fig_string[k+1]='\0';
            //printf("\n");printf("%s", fig_string);printf("\n");
            f = 0; int err_f = 0; // err1 ������ ��� �������� ������
            for(int i = 0; fig_string[i]!='\0'; i++){
                if(fig_string[i] == '{'){
                    printf("�� ������� ����������� }\n");
                    err_f++;
                    break;
                }
                if(fig_string[i] == '}'){
                    printf("�� ������� ����������� {\n");
                    err_f++;
                    break;
                }
            }
            if(err_f>=1)
                break;  // �������������, ���� ���� �������� � �������������� ��� ��������������
                        // ��������
            /*�������� �� ����������� � ������� ��������*/
            j=0;
            while(string_brackets[j]!='\0'){
                if(string_brackets[j]=='}' && string_brackets[j-1]=='('){
                    printf("����������� ����: (}\n");
                    break;
                }
                if(string_brackets[j]=='}' && string_brackets[j-1]=='['){
                    printf("����������� ����: [}\n");
                    break;
                }
                if(string_brackets[j]=='{' && string_brackets[j+1]==')'){   //�������� ������ �����������
                    printf("����������� ����: {)\n");       // ���� {] � {)
                    break;
                }
                if(string_brackets[j]=='{' && string_brackets[j+1]==']'){
                    printf("����������� ����: {]\n");
                    break;
                }
                j++;
            }
        break;
                    /* �������� ������� ������ */
        case '(':
            j=0;
            int c = 0, m = 0;
            char *circ_string = (char *) malloc(circ_bracket+1);
            while(string_brackets[j]!='\0'){
                if(string_brackets[j] == '('){
                    circ_string[c] = '(';
                    c++;
                    m++;
                }

                if(string_brackets[j] == ')' && circ_string[c-1] != '('){
                    circ_string[m] = ')';
                    --c;
                    m++;
                }

                if(string_brackets[j] == ')' && circ_string[c-1] == '('){
                    circ_string[c-1] = ' ';
                    --c;
                }
                j++;
            }

            c = 0; int err_c = 0; // err ������ ��� �������� ������
            for(int i = 0; circ_string[i]!='\0'; i++){
                if(circ_string[i] == '('){
                    printf("�� ������� ����������� )\n");
                    err_c++;
                    break;// ����� break ��������� case
                }
                if(circ_string[i] == ')'){
                    printf("�� ������� ����������� (\n");
                    err_c++;
                    break;
                }
            }
            if(err_c>=1)
                break;  // �������������, ���� ���� �������� � �������������� ��� ��������������
                        // ��������

            /* �������� �� ����������� � ������� �������� */
            j=0;
            while(string_brackets[j]!='\0'){
                    if(string_brackets[j]==')' && string_brackets[j-1]=='{'){
                        printf("����������� ����: {)\n");
                        break;
                    }
                    if(string_brackets[j]==')' && string_brackets[j-1]=='['){
                        printf("����������� ����: [)\n");
                        break;
                    }
                    if(string_brackets[j]=='(' && string_brackets[j+1]=='}'){
                        printf("����������� ����: (}\n");
                        break;
                    }
                    if(string_brackets[j]=='(' && string_brackets[j+1]==']'){
                        printf("����������� ����: (]\n");
                        break;
                    }
                    j++;
            }
        break;

                /* �������� ���������� ������ */
        case '[':
            // �������� ��� ��������
        break;

        }
        br++;
    }
    return 0;
}
