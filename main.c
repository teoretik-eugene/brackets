#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    setlocale( LC_ALL,"Russian" );
    /*Открытие и проверка аргументов: */
    FILE *text;
    if((text = fopen(argv[1], "r"))==NULL){
        printf("ERROR IN OPENING FILE\n");
        exit(1);
    }
    if(argv[2]==NULL){
        printf("ERROR IN ARG 2\n");
        exit(1);
    }

    /*Создадим массив символов, состоящий из скобок разных типов*/

    /*Посчитаем общее количество скобок*/
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

    char *string_br = (char *) malloc(count_brackets+1);//Выделяем под массив память

    /*Запишем в массив все скобки, за исключением содержания в кавычках*/
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
    printf("%s", string_br);printf("\n");   // Вывод массива символов на экран

    printf("Предупреждения: \n");
    /*Проходимся по аргументу скобок*/
    int br = 0;
    while(argv[2][br]!='\0'){
        /*Начинается анализ скобок в аргументе*/
        switch(argv[2][br]){

            /*Проверка фигурных скобок*/
            case '{':
                rewind(text);
                int fig_open = 0, fig_close = 0;
                /*Проверка на количество*/
                int j=0;
                while(string_br[j]!='\0'){
                    if(string_br[j]=='{')
                        fig_open++;

                    if(string_br[j]=='}')
                        fig_close++;
                    j++;
                }
                if(fig_open > fig_close){
                    printf("Лишние {\n");
                    break;
                }
                if(fig_open < fig_close){
                    printf("Лишние }\n");
                    break;
                }
                /*
                Если нет лишних открытых или лишних закрытых скобок
                то начинается проверка на пересечение
                */
                j=0;
                while(string_br[j]!='\0'){
                    if(string_br[j]=='}' && string_br[j-1]=='('){
                        printf("Пересечение типа: (}");
                        break;
                    }
                    if(string_br[j]=='}' && string_br[j-1]=='['){
                        printf("Пересечение типа: [}");
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
    printf("\nИсходный файл: \n");
    while((ch=getc(text))!=EOF){
        printf("%c", ch);
    }



    return 0;
}
