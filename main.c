#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    setlocale( LC_ALL,"Russian" );

    /* Проверка открытого файла: */
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
    printf("%s", argv[2]);printf("\n---------------------\n");

    int ch; // Указатель для перемещения по файлу

    /* Выведем файл в консоль */
    while((ch = getc(text))!= EOF){
        printf("%c", ch);
    }
    printf("\n---------------------\n");
    rewind(text);

    /* Вычисляем количество скобок, за исключением содержания в кавычках */
    int count_brackets = 0;     // Колисество скобок всех типов
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

    /* Создадим и выведем массив символов скобок */
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
    printf("Массив символов: \n");
    printf("%s", string_brackets);
    rewind(text);

    printf("\nПредупреждения: \n");
    /*Проходимся по аргументу скобок*/
    int br = 0;
    while(argv[2][br]!='\0'){
        switch(argv[2][br]){

                    /* Проверка фигурных скобок */
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
            f = 0; int err_f = 0; // err1 служит для фиксации ошибки
            for(int i = 0; fig_string[i]!='\0'; i++){
                if(fig_string[i] == '{'){
                    printf("Не хватает закрывающей }\n");
                    err_f++;
                    break;
                }
                if(fig_string[i] == '}'){
                    printf("Не хватает открывающей {\n");
                    err_f++;
                    break;
                }
            }
            if(err_f>=1)
                break;  // останавливает, если есть проблема с открывающимися или закрываюшимися
                        // скобками
            /*Проверка на пересечение с другими скобками*/
            j=0;
            while(string_brackets[j]!='\0'){
                if(string_brackets[j]=='}' && string_brackets[j-1]=='('){
                    printf("Пересечение типа: (}\n");
                    break;
                }
                if(string_brackets[j]=='}' && string_brackets[j-1]=='['){
                    printf("Пересечение типа: [}\n");
                    break;
                }
                if(string_brackets[j]=='{' && string_brackets[j+1]==')'){   //Добавлен случаи пересечения
                    printf("Пересечение типа: {)\n");       // типа {] и {)
                    break;
                }
                if(string_brackets[j]=='{' && string_brackets[j+1]==']'){
                    printf("Пересечение типа: {]\n");
                    break;
                }
                j++;
            }
        break;
                    /* Проверка круглых скобок */
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

            c = 0; int err_c = 0; // err служит для фиксации ошибки
            for(int i = 0; circ_string[i]!='\0'; i++){
                if(circ_string[i] == '('){
                    printf("Не хватает закрывающей )\n");
                    err_c++;
                    break;// думал break остановит case
                }
                if(circ_string[i] == ')'){
                    printf("Не хватает открывающей (\n");
                    err_c++;
                    break;
                }
            }
            if(err_c>=1)
                break;  // останавливает, если есть проблема с открывающимися или закрываюшимися
                        // скобками

            /* Проверка на пересечение с другими скобками */
            j=0;
            while(string_brackets[j]!='\0'){
                    if(string_brackets[j]==')' && string_brackets[j-1]=='{'){
                        printf("Пересечение типа: {)\n");
                        break;
                    }
                    if(string_brackets[j]==')' && string_brackets[j-1]=='['){
                        printf("Пересечение типа: [)\n");
                        break;
                    }
                    if(string_brackets[j]=='(' && string_brackets[j+1]=='}'){
                        printf("Пересечение типа: (}\n");
                        break;
                    }
                    if(string_brackets[j]=='(' && string_brackets[j+1]==']'){
                        printf("Пересечение типа: (]\n");
                        break;
                    }
                    j++;
            }
        break;

                /* Проверка квадратных скобок */
        case '[':
            j=0;
            int s = 0, n = 0;
            char *square_string = (char *) malloc(square_bracket+1);
            while(string_brackets[j]!='\0'){
                if(string_brackets[j] == '['){
                    square_string[s] = '[';
                    s++;
                    n++;
                }

                if(string_brackets[j] == ']' && square_string[s-1] != '['){
                    square_string[n] = ']';
                    --s;
                    n++;
                }

                if(string_brackets[j] == ']' && square_string[s-1] == '['){
                    square_string[s-1] = ' ';
                    --s;
                }
                j++;
            }

            s = 0; int err_s = 0; // err служит для фиксации ошибки
            for(int i = 0; square_string[i]!='\0'; i++){
                if(square_string[i] == '['){
                    printf("Не хватает закрывающей ]\n");
                    err_s++;
                    break;// думал break остановит case
                }
                if(square_string[i] == ']'){
                    printf("Не хватает открывающей [\n");
                    err_s++;
                    break;
                }
            }
            if(err_s>=1)
                break;  // останавливает, если есть проблема с открывающимися или закрываюшимися
                        // скобками

            /* Проверка на пересечение с другими скобками */
            j=0;
            while(string_brackets[j]!='\0'){
                    if(string_brackets[j]==']' && string_brackets[j-1]=='('){
                        printf("Пересечение типа: (]\n");
                        break;
                    }
                    if(string_brackets[j]==']' && string_brackets[j-1]=='{'){
                        printf("Пересечение типа: {]\n");
                        break;
                    }
                    if(string_brackets[j]=='[' && string_brackets[j+1]=='}'){
                        printf("Пересечение типа: [}\n");
                        break;
                    }
                    if(string_brackets[j]=='[' && string_brackets[j+1]==')'){
                        printf("Пересечение типа: [)\n");
                        break;
                    }
                    j++;
            }
        break;

        }
        br++;
    }
    return 0;
}
