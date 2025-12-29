#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "header.h"


int main()
{
	setlocale(LC_ALL, "RUS");
	puts("=============== База данных AR/VR движков ===============");
	puts("Выполнила: Филичкина Мария бТИИ-251");
	Engine* database = NULL;
	int count = 0;
	while (1) {
		int operation;
		puts("Меню:");
		puts("1. Загрузка данных из файла");
		puts("2. Просмотр всех записей");
		puts("3. Поиск по платформе и физике");
		puts("4. Сортировка данных по квадратному корню из FPS");
		puts("5. Добавление новой записи");
		puts("6. Сохранение данных в файл");
		puts("7. Генерация тестовых значений");
		puts("0. Выход");
		printf("Введите номер операции:");
		scanf("%d", &operation);
		getchar();

		switch (operation)
		{
		case 1:
			puts("---------------------------------------------");
			puts("Загрузка данных из файла");
			char file_name[30];
			printf("Введите имя файла ");
			fgets(file_name, sizeof(file_name), stdin);
			file_name[strcspn(file_name, "\n")] = 0;
			count = count_data(file_name);
			database = uploading_data(file_name, count, database);
			printf("Загружено %d записей\n", count);
			break;
		case 2:
			puts("---------------------------------------------");
			puts("Просмотр всех записей");
			output_engine(database, count);
			break;
		case 3:
			puts("---------------------------------------------");
			puts("Поиск по платформе и физике");
			char search_platform[100];
			char search_physics;
			puts("Введите платформу для поиска");
			fgets(search_platform, sizeof(search_platform), stdin);
			search_platform[strcspn(search_platform, "\n")] = 0;
			puts("Введите поддержку физики для поиска");
			scanf("%c", &search_physics);
			getchar();
			int search_count = search_platform_physics_count(database, count, search_platform, search_physics);
			Engine* search_array = search_platform_physics_array(database, count, search_platform, search_physics, search_count);
			if (search_array == NULL)
			{
				printf("Записей не найдено\n");
				break;
			}
			printf("=============== Найдено %d записей =================\n", search_count);
			output_engine(search_array, search_count);
			free(search_array);
			break;
		case 4:
			puts("---------------------------------------------");
			puts("Сортировка данных по квадратному корню из FPS");
			if (sort_fps_in_the_square(database, count, compare))
			{
				output_engine(database, count);
			}
			break;
		case 5:
			puts("---------------------------------------------");
			puts("Добавление новой записи:");
			count += 1;
			database = input_engine(database, count);
			puts("Запись успешно добавлена");
			break;
		case 6:
			puts("---------------------------------------------");
			puts("Сохранение данных в файл");
			char fname[30];
			printf("Введите имя файла для сохранения\n");
			fgets(fname, sizeof(fname), stdin);
			fname[strcspn(fname, "\n")] = 0;
			if (saving_data(database, fname, count))
			{
				printf("Сохранено %d записей\n", count);
			}
			break;
		case 7:
			puts("---------------------------------------------");
			puts("Генерация тестовых значений");
			int count_for_test;
			puts("Введите количество записей");
			scanf("%d", &count_for_test);
			int last_count = count;
			count += count_for_test;
			database = (Engine*)realloc(database, count * sizeof(Engine));
			database = test(database, last_count, count);
			output_engine(database, count);
			break;
		case 0:
			free(database);
			puts("Выход из программы...");
			return 0;
		}
	}
}
