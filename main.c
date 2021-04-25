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
    printf("Введенный аргумент: \n");
    if(!argv[2]){
        printf("Error in bracket-argument\n\n");
    }
    else{
        printf(argv[2]);
        printf("\n");
    }
    printf("Предупреждения: \n");
        int br=0;   // Перемещение по строке
        while (argv[2][br]!='\0'){

            switch(argv[2][br]){
            // Почему fig_open = 32????

            /*Проверка на фигурные скобки*/
            case '{':
                rewind(input);
                int fig_open = 0, fig_close = 0, count_brackets = 0;
                while((ch=getc(input))!=EOF){
                    if(ch=='"'){            // Проверка на кавычки
                        do{
                            ch=getc(input);
                        }while(ch!='"');
                    }
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
                //printf("%d", fig_open); printf("\n");
                //printf("%d", fig_close); printf("\n");
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
                char *string = (char*) malloc(count_brackets+1);    // Уж переделай тогда..
                rewind(input);                                    // ..string на fig
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
                free(string);
                rewind(input);
                break;


            /*Проверка на круглые скобки*/
            case '(':
                // Изначально тут было int m = 0, но выдавало ошибку
                rewind(input);
                int circ_count = 0, circ_open = 0, circ_close = 0;
                while((ch=getc(input))!=EOF){
                    if(ch=='"'){
                        do{
                            ch=getc(input);
                        }while(ch!='"');
                    }

                    if (ch == '{' || ch == '}' || ch == '[' || ch == ']')
                        circ_count++;

                    if(ch == '('){
                        circ_open++;
                        circ_count++;
                    }
                    if(ch == ')'){
                        circ_close++;
                        circ_count++;
                    }
                }
                if(circ_open > circ_close){
                    printf("Лишние (\n");
                    break;
                }
                if(circ_close > circ_open){
                    printf("Лишние )\n");
                    break;
                }

                int m = 0;          // Переменная для символьного массива
                char *circ = (char*) malloc(circ_count+1);
                rewind(input);
                while((ch=getc(input))!=EOF){

                    if(ch=='('){
                        circ[m]='(';        // Ошибка, ( в конце
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
                free(circ);
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

    rewind(input);      // Тут не было rewind и выдавало ошибку

    /*Отображение содержимого файла*/
    printf("\n-------------------------------\n");
    printf("Исходный файл: \n");
    while((ch = getc(input))!=EOF){
        printf("%c", ch);
    }
    rewind(input);

    return 0;
}
