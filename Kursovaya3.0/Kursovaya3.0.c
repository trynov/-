#define _CRT_SECURE_NO_DEPRECATE
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Company {
    char name[100];
    char description[500];
    int foundationYear;
    int numEmployees;
    double marketCap;
    int rating;
};

typedef struct Company comp_t;

int add_company(comp_t*, int);
int save_in_file(comp_t*, int, char*);
int from_file(comp_t*, int, char*); 
int find_name(comp_t*, int);
void put_company(comp_t*);
int compare_marketCap(const void*, const void*);
int put_comapnyes(comp_t*, int);
comp_t* find_rating(comp_t*, int, int,int);
int rating_count_comp(comp_t*, int, int);
void sort_shaker(comp_t*, int);
void put_name_struct();


int main() {

    setlocale(LC_ALL, "RUS");
    system("chcp 1251");
    char fname[] = "database.txt";
    FILE* file;
    if ((file = fopen(fname, "rb")) == NULL) {
        printf("Ошибка открытия файла для записи");
        return 0;
    }

    int choice;
    comp_t* array = 0;
    int size;
    fscanf(file, "%d\n", &size);
    fclose(file);
    array = malloc(sizeof(comp_t) * size);
    int index, flag = 0;
    
    do {
        printf("\n\t\tМеню:\n\n");
        printf("1. Добавить компанию                   |\n");
        printf("---------------------------------------|\n");
        printf("2. Сохранить в файл                    |\n");
        printf("---------------------------------------|\n");
        printf("3. Загрузить из файла                  |\n");
        printf("---------------------------------------|\n");
        printf("4. Сортировка по рыночной капитализации|\n");
        printf("---------------------------------------|\n");
        printf("5. Поиск по названию                   |\n");
        printf("---------------------------------------|\n");
        printf("6. Поиск по рейтингу                   |\n");
        printf("---------------------------------------|\n");
        printf("7. Сортировка по рейтингу              |\n");
        printf("---------------------------------------|\n");
        printf("8. Чтение записанных данных            |\n");
        printf("---------------------------------------|\n");
        printf("9. Выход                               |\n");
        printf("---------------------------------------|\n");
        printf("Выберите: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1: {
            printf("Количество записей:");
            scanf("%d", &size);
            array = malloc(sizeof(comp_t) * size);
            add_company(array, size);
            flag++;
            }break;

            case 2: {
            save_in_file(array, size, fname);
            }break;

            case 3: {
            from_file(array, size, fname);
            flag++;
            }break;

            case 4: {
            qsort(array, size, sizeof(comp_t), compare_marketCap);
            put_comapnyes(array, size);
            }break;

            case 5: {
            index = find_name(array, size);
            if (index == -1) {
                printf("Данного названия нет в базе данных");
                break;
            }
            put_name_struct();
            put_company(array + index);
            }break;

            case 6: {
                int size_for_search, search;
                printf("Введите рейтинг компании, которую хотите найти: ");
                scanf("%d", &search);
                size_for_search = rating_count_comp(array, size, search);
                if (size_for_search == 0) {
                    printf("Нет компаний с таким рейтингом\n");
                    break;
                }
                put_comapnyes(find_rating(array, size, search, size_for_search),size_for_search);
            }break;

            case 7: {
                sort_shaker(array, size);
                put_comapnyes(array, size);

            }break;

            case 8: {
                if (!flag) {
                
                    printf("Для начала заполните массив данными");
                    break;

                }

                put_comapnyes(array, size);


            }break;

            case 9:

            printf("Выход...\n");


        };

    } while (choice != 9);
}

int add_company(comp_t* array, int size) {

    for (int i = 0; i < size; i++) {

        printf("Название: ");
        scanf("%s", array->name);
        printf("Описание: ");
        scanf("%s", array->description);
        printf("Год основания: ");
        scanf("%d", &array->foundationYear);
        printf("Количество сотрудников: ");
        scanf("%d", &array->numEmployees);
        printf("Рыночная капитализация: ");
        scanf("%lf", &array->marketCap);
        printf("Введите рейтинг компании: ");
        scanf("%d", &array->rating);
        array++;
    }
}

int save_in_file(comp_t* array, int size, char* file_name) {

    FILE* file = fopen(file_name, "wb");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи\n");
        return;
    }

    fprintf(file,"%d\n", size);
    for (int i = 0; i < size; i++) {

        fprintf(file, "%s %s %d %d %d %lf \n", array->name, array->description, array->foundationYear, array->numEmployees, array->rating, array->marketCap);
        array++;
    }
    fclose(file);
    printf("Данные сохранены в файл.\n");
}

int from_file(comp_t* array, int size, char* file_name) {

    FILE* file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи\n");
        return;
    }

    fscanf(file,"%d\n", &size);
    for (int i = 0; i < size; i++) {
        fscanf(file, "%s %s %d %d %d %lf\n", array->name, array->description, &array->foundationYear, &array->numEmployees, &array->rating, &array->marketCap);
        array++;
        
    }
    fclose(file);
    printf("Данные загружены из файла.\n");

}


void put_company(comp_t* array) {

    fprintf(stdout, "%12s | %18s | %14d | %22d | %7d | %2.lf \n", array->name, array->description, array->foundationYear, array->numEmployees, array->rating, array->marketCap);

}

int compare_marketCap(const void* av, const void* bv) {

    const comp_t* b = av, * a = bv;
    if (a->marketCap < b->marketCap) return -1;
    if (a->marketCap > b->marketCap) return 1;
    return 0;

}

int find_name(comp_t* array, int size) {

    char poisk_name[30];

    printf("Введите название компании, которую хотите найти:");
    scanf("%s", poisk_name);


    for (int i = 0; i < size; i++) {
        if (!strcmp(array[i].name, poisk_name)) {
            return i;
        }

    }
    return -1;
    
}

comp_t* find_rating(comp_t* array, int size, int search,int count) {

    comp_t* search_rating;
    int next_i = 0;
    search_rating = malloc(sizeof(comp_t) * count);

    for (int i = 0; i < count; i++) {
        for (int j = next_i; j < size; j++) {
            if (array[j].rating == search) {
                search_rating[i] = array[j];
                next_i = j + 1;
                break;
            }
        }
    }
    return search_rating;
}

int rating_count_comp(comp_t* array, int size,int search) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array->rating == search) {
            count++;
        }
        array++;
    }
    return count;
}

int put_comapnyes(comp_t* array, int size) {

    printf("\nНазвание     |      Описание      | Год основания  | Количество сотрудников | Рейтинг | Рыночная капитализация \n");
    printf("-------------|--------------------|----------------|------------------------|---------|-----------------------------\n");
    for (int i = 0; i < size; i++) {

        put_company(array);
        printf("-------------|--------------------|----------------|------------------------|---------|-----------------------------\n");
        array++;
    
    }
    return size;
}

void sort_shaker(comp_t* array, int size) {
    int iLeft = 0;
    int iRight = size - 1;
    comp_t temp;

    while (iLeft <= iRight) {
        for (int j = iLeft; j < iRight; j++) {
            if (array[j].rating > array[j + 1].rating) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
        iRight--;

        for (int j = iRight; j > iLeft; j--) {
            if (array[j].rating < array[j - 1].rating) {
                temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
        }
        iLeft++;
    }
}

void put_name_struct() {

    printf("\nНазвание     |      Описание      | Год основания  | Количество сотрудников | Рейтинг | Рыночная капитализация \n");
    printf("-------------|--------------------|----------------|------------------------|---------|-----------------------------\n");


}




 

  