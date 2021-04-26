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
    printf("Введенная строка-аргумент:\n");
    printf("%s", argv[2]);printf("\n");

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
    printf("\n");
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
                        printf("Пересечение типа: (}\n");
                        break;
                    }
                    if(string_br[j]=='}' && string_br[j-1]=='['){
                        printf("Пересечение типа: [}\n");
                        break;
                    }
                    j++;
                }
            break;

            /*
                Аналогично работают и остальные проверки для других скобок
            */

            /*Проверка на круглые скобки*/
            case '(':
                rewind(text);
                int circ_open = 0, circ_close = 0;
                //
                /*Проверка на количество*/
                int c=0;
                while(string_br[c]!='\0'){
                    if(string_br[c]=='(')
                        circ_open++;

                    if(string_br[c]==')')
                        circ_close++;
                    c++;
                }
                if(circ_open > circ_close){
                    printf("Лишние (\n");
                    break;
                }
                if(circ_open < circ_close){
                    printf("Лишние )\n");
                    break;
                }
                /*
                Если нет лишних открытых или лишних закрытых скобок
                то начинается проверка на пересечение
                */
                c=0;
                while(string_br[c]!='\0'){
                    if(string_br[c]==')' && string_br[c-1]=='{'){
                        printf("Пересечение типа: {)\n");
                        break;
                    }
                    if(string_br[c]==')' && string_br[c-1]=='['){
                        printf("Пересечение типа: [)\n");
                        break;
                    }
                    c++;
                }
            break;

            /*Проверка на квадратные скобки*/
            case '[':
                rewind(text);
                int square_open = 0, square_close = 0;
                /*Проверка на количество*/
                int s=0;
                while(string_br[s]!='\0'){
                    if(string_br[s]=='[')
                        square_open++;

                    if(string_br[s]==']')
                        square_close++;
                    s++;
                }
                if(square_open > square_close){
                    printf("Лишние [\n");
                    break;
                }
                if(square_open < square_close){
                    printf("Лишние ]\n");
                    break;
                }
                /*
                Если нет лишних открытых или лишних закрытых скобок
                то начинается проверка на пересечение
                */
                s=0;
                while(string_br[s]!='\0'){
                    if(string_br[s]==']' && string_br[s-1]=='{'){
                        printf("Пересечение типа: {]\n");
                        break;
                    }
                    if(string_br[s]==']' && string_br[s-1]=='('){
                        printf("Пересечение типа: (]\n");
                        break;
                    }
                    s++;
                }
            break;
        }
        br++;   // Осуществляет перемещение по argv[2]
    }

    printf("\n");
    rewind(text);
    printf("\nИсходный файл: \n");
    while((ch=getc(text))!=EOF){
        printf("%c", ch);
    }
    return 0;
}
