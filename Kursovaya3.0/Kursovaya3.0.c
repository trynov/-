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
        printf("������ �������� ����� ��� ������");
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
        printf("\n\t\t����:\n\n");
        printf("1. �������� ��������                   |\n");
        printf("---------------------------------------|\n");
        printf("2. ��������� � ����                    |\n");
        printf("---------------------------------------|\n");
        printf("3. ��������� �� �����                  |\n");
        printf("---------------------------------------|\n");
        printf("4. ���������� �� �������� �������������|\n");
        printf("---------------------------------------|\n");
        printf("5. ����� �� ��������                   |\n");
        printf("---------------------------------------|\n");
        printf("6. ����� �� ��������                   |\n");
        printf("---------------------------------------|\n");
        printf("7. ���������� �� ��������              |\n");
        printf("---------------------------------------|\n");
        printf("8. ������ ���������� ������            |\n");
        printf("---------------------------------------|\n");
        printf("9. �����                               |\n");
        printf("---------------------------------------|\n");
        printf("��������: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1: {
            printf("���������� �������:");
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
                printf("������� �������� ��� � ���� ������");
                break;
            }
            put_name_struct();
            put_company(array + index);
            }break;

            case 6: {
                int size_for_search, search;
                printf("������� ������� ��������, ������� ������ �����: ");
                scanf("%d", &search);
                size_for_search = rating_count_comp(array, size, search);
                if (size_for_search == 0) {
                    printf("��� �������� � ����� ���������\n");
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
                
                    printf("��� ������ ��������� ������ �������");
                    break;

                }

                put_comapnyes(array, size);


            }break;

            case 9:

            printf("�����...\n");


        };

    } while (choice != 9);
}

int add_company(comp_t* array, int size) {

    for (int i = 0; i < size; i++) {

        printf("��������: ");
        scanf("%s", array->name);
        printf("��������: ");
        scanf("%s", array->description);
        printf("��� ���������: ");
        scanf("%d", &array->foundationYear);
        printf("���������� �����������: ");
        scanf("%d", &array->numEmployees);
        printf("�������� �������������: ");
        scanf("%lf", &array->marketCap);
        printf("������� ������� ��������: ");
        scanf("%d", &array->rating);
        array++;
    }
}

int save_in_file(comp_t* array, int size, char* file_name) {

    FILE* file = fopen(file_name, "wb");
    if (file == NULL) {
        printf("������ �������� ����� ��� ������\n");
        return;
    }

    fprintf(file,"%d\n", size);
    for (int i = 0; i < size; i++) {

        fprintf(file, "%s %s %d %d %d %lf \n", array->name, array->description, array->foundationYear, array->numEmployees, array->rating, array->marketCap);
        array++;
    }
    fclose(file);
    printf("������ ��������� � ����.\n");
}

int from_file(comp_t* array, int size, char* file_name) {

    FILE* file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("������ �������� ����� ��� ������\n");
        return;
    }

    fscanf(file,"%d\n", &size);
    for (int i = 0; i < size; i++) {
        fscanf(file, "%s %s %d %d %d %lf\n", array->name, array->description, &array->foundationYear, &array->numEmployees, &array->rating, &array->marketCap);
        array++;
        
    }
    fclose(file);
    printf("������ ��������� �� �����.\n");

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

    printf("������� �������� ��������, ������� ������ �����:");
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

    printf("\n��������     |      ��������      | ��� ���������  | ���������� ����������� | ������� | �������� ������������� \n");
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

    printf("\n��������     |      ��������      | ��� ���������  | ���������� ����������� | ������� | �������� ������������� \n");
    printf("-------------|--------------------|----------------|------------------------|---------|-----------------------------\n");


}




 

  