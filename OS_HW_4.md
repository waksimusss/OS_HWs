# Отчет ДЗ №4.
## Работу выполнил Максимов Никита БПИ227
Ожидаемая оценка 9 баллов (пункт 1 + пункт 2).
### Работа с программой и её описание 
Скомпилировать - 'gcc hw4.c', запустить - './a.out'

Программа предложит ввести названия файла из которого будет считываться информация и название файла для записи прочитанной ранее информации. Также программа предложит ввести размер буфера, который ограничивает объем считываемой информации. Если файл записи не существует, то он будет создан.
### Код программы

Для удобства код расположен по ссылке['hw4.c'] 

```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    char input[256]; // Имена файлов
    char output[256];
    int n;

    // Ввод имен и буфера
    printf("Input read-file:\n");
    scanf("%s", input); 
    printf("Input write-file:\n");
    scanf("%s", output);
    printf("Input size of buffer:\n");
    scanf("%d", &n);

    char buffer[n]; // Сам буфер
    int input_descriptor = open(input, O_RDONLY); // Открываем на чтение
    int output_descriptor = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0666); // Открываем для записи/создаем или перезаписываем
    
    //Проверка открытия
    if (input_descriptor == -1) {
        printf("Error with opening read-file\n");
        return 0;
    }

    if (output_descriptor == -1) {
        printf("Error with opening write-file\n");
        return 0;
    }
    // Читаем циклично
    int size = 0;
    while ((size = read(input_descriptor, buffer, n)) != 0) {
        // Проверка
        if (size == -1) {
            printf("Error with reading from file\n");
            return 0;
        }
        // Запись
        size = write(output_descriptor, buffer, size);
        // Иначе
        if (size == -1) {
            printf("Error with writing in file\n");
            return 0;
        }
    }
    // Проверка закрытия
    if (close(input_descriptor)<0) {
        printf("Error with closing read-file\n");
        return 0;
    }
    if (close(output_descriptor)<0) {
        printf("Error with closing write-file\n");
        return 0;
    }
    return 0;
}
```
