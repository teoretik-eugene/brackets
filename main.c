#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


int main(int argc, char *argv[])
{
    setlocale( LC_ALL,"Russian" );
    FILE *input;    // Открываем файл для проверки
    if((input = fopen(argv[1], "r"))==NULL){
        printf("ERROR\n");
        exit(1);
    }

    int ch;     // Переменная для считывания файла

    if(!argv[2]){
        printf("Error in bracket-argument\n\n");
    }
    else{
        printf(argv[2]);
        printf("\n");
    }
        int br=0;   // Перемещение по строке
        while (argv[2][br]!='\0'){

            switch(argv[2][br]){
            // Почему fig_open = 32????

            /*Проверка на фигурные скобки*/
            case '{':
                rewind(input);
                int fig_open = 0, fig_close = 0, count_brackets = 0;
                while((ch=getc(input))!=EOF){
                    if(ch=='[' || ch==']' || ch=='(' || ch==')')
                        count_brackets++;

                    if(ch=='{'){
                        fig_open++;
                        count_brackets++;
                    }
                    if(ch=='}'){
                        fig_close++;
                        count_brackets++;
                    }
                }
                if(fig_open > fig_close){
                    printf("Лишние {\n");
                    break;
                }
                else{
                    if(fig_open < fig_close){
                        printf("Лишние }\n");
                        break;
                    }
                }
                char *string = (char*) malloc(count_brackets+1);
                rewind(input);
                int j = 0;
                while((ch=getc(input))!=EOF){
                    if(ch=='{'){
                        string[j]='{';
                        j++;
                    }
                    if(ch=='('){
                        string[j]='(';
                        j++;
                    }
                    if(ch=='['){
                        string[j]='[';
                        j++;
                    }
                    if(ch==')'){
                        string[j]=')';
                        j++;
                    }
                    if(ch==']'){
                        string[j]=']';
                        j++;
                    }
                    if(ch=='}' && (string[j-1]!='(') && (string[j-1]!='[')){
                        string[j]='}';
                        j++;
                    }
                    else{
                        if(ch == '}' && string[j-1] == '('){
                            printf("Пересечение типа: (} в {}\n");
                            break;
                        }
                        if(ch == '}' && string[j-1] == '['){
                            printf("Пересечение типа: [} в {})\n");
                            break;
                        }
                    }
                }
                rewind(input);
                break;

            /*Проверка на круглые скобки*/
            case '(':
                // Изначально тут было int m = 0, но выдавало ошибку
                rewind(input);
                int circ_count = 0;
                while((ch=getc(input))!=EOF){
                    if(ch=='(' || ch == ')')
                        circ_count++;
                }
                int m = 0;
                char *circ = (char*) malloc(circ_count+1);
                rewind(input);
                while((ch=getc(input))!=EOF){
                    if(ch=='('){
                        circ[m]='(';
                        m++;
                    }
                    if(ch=='{'){
                        circ[m]='{';
                        m++;
                    }
                    if(ch=='['){
                        circ[m]='[';
                        m++;
                    }
                    if(ch=='}'){
                        circ[m]='}';
                        m++;
                    }
                    if(ch==']'){
                        circ[m]=']';
                        m++;
                    }
                    if(ch==')' && (circ[m-1]!='{') && (circ[m-1]!='[')){
                        circ[m]=')';
                        m++;
                    }
                    else{
                        if(ch == ')' && circ[m-1] == '{'){
                            printf("Пересечение типа: {) в ()\n");
                            break;
                        }
                        if(ch == ')' && circ[m-1] == '['){
                            printf("Пересечение типа: [) в ()\n");
                            break;
                        }
                    }
                }
                rewind(input);
                break;

            case '[':
                while((ch=getc(input))!=EOF){
                rewind(input);
                break;
            }
        }
        br++;
    }

    /*Отображение содержимого файла*/
    printf("Исходный файл: \n");
    while((ch = getc(input))!=EOF){
        printf("%c", ch);
    }
    rewind(input);

    return 0;
}




