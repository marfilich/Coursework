#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "header.h"



int count_data(const char* file_name)
{
	FILE* out;
	out = fopen(file_name, "rb");
	if (out == NULL)
	{
		printf("Ошибка открытия файла для записи\n");
		return 0;
	}

	fseek(out, 0, SEEK_END);
	int size = ftell(out);
	fclose(out);
	if (size % sizeof(Engine) > 0)
	{
		return size / sizeof(Engine) + 1;
	}
	else {
		return size / sizeof(Engine);
	}
}

Engine* uploading_data(const char* file_name, int count, Engine* database)
{
	FILE* out;
	out = fopen(file_name, "rb");
	if (out == NULL)
	{
		printf("Ошибка открытия файла для чтения\n");
		return 0;
	}

	if (count <= 0)
	{
		printf("Файл пуст\n");
		fclose(out);
		return 0;
	}

	free(database);
	database = (Engine*)malloc(count * sizeof(Engine));
	if (database == NULL)
	{
		printf("Ошибка выделения памяти!\n");
		fclose(out);
		return 0;
	}

	for (int i = 0; i < count; i++)
	{
		fread(database[i].name, sizeof(char), 50, out);
		fread(database[i].target_platform, sizeof(char), 100, out);
		fread(&database[i].stable_fps, sizeof(float), 1, out);
		fread(&database[i].physics_support, sizeof(char), 1, out);
		fread(&database[i].graphics_quality, sizeof(Graphics_Quality), 1, out);
		fread(&database[i].size_sdk, sizeof(float), 1, out);
		fread(&database[i].license_cost, sizeof(double), 1, out);
	}
	fclose(out);
	return database;
}


int output_engine(Engine* database, int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("========= Движок %d ===========\n", i + 1);
		printf("Название: %s\n", database[i].name);
		printf("Целевая платформа: %s\n", database[i].target_platform);
		printf("Стабильный FPS: %f\n", database[i].stable_fps);
		printf("Поддержка физики: %s\n", database[i].physics_support == '+' ? "Да" : "Нет");

		char quality_str[20];
		switch (database[i].graphics_quality) {
		case LOW:
			strcpy(quality_str, "Низкое");
			break;
		case MEDIUM:
			strcpy(quality_str, "Среднее");
			break;
		case HIGH:
			strcpy(quality_str, "Высокое");
			break;
		}

		printf("Качество графики: %s\n", quality_str);
		printf("Размер SDK: %f ГБ\n", database[i].size_sdk);
		printf("Стоимость лицензии: %lf\n", database[i].license_cost);
		puts("------------------------------------------------");
	}
	return 1;
}

Engine* input_engine(Engine* database, int count)
{
	database = (Engine*)realloc(database, count * sizeof(Engine));
	if (database == NULL)
	{
		puts("Ошибка выделения памяти");
		return 0;
	}
	printf("Запись %d\n", count);
	puts("Введите название:");
	fgets(database[count - 1].name, sizeof(database[count - 1].name), stdin);
	database[count - 1].name[strcspn(database[count - 1].name, "\n")] = 0;


	puts("Введите целевую платформу:");
	fgets(database[count - 1].target_platform, sizeof(database[count - 1].target_platform), stdin);
	database[count - 1].target_platform[strcspn(database[count - 1].target_platform, "\n")] = 0;

	puts("Введите стабильный FPS:");
	scanf("%f", &database[count - 1].stable_fps);
	getchar();

	puts("Поддержка физики ('+' - да, '-' - нет):");
	scanf(" %c", &database[count - 1].physics_support);


	int graphics;
	puts("Введите качество графики (1 - Низкое /2 - Среднее /3 - Высокое):");
	scanf("%d", &graphics);
	if (graphics < 1 || graphics > 3) {
		graphics = 0;
	}
	database[count - 1].graphics_quality = (Graphics_Quality)graphics;


	puts("Введите размер SDK:");
	scanf("%f", &database[count - 1].size_sdk);


	puts("Введите стоимость лицензии:");
	scanf("%lf", &database[count - 1].license_cost);
	getchar();
	puts("-----------------------------------------------------------");

	return database;
}

int saving_data(Engine* database, const char* fname, int count)
{
	if (count == 0)
	{
		puts("База данных пуста");
		return 0;
	}

	FILE* out;
	out = fopen(fname, "wb");
	if (out == NULL)
	{
		printf("Ошибка открытия файла для записи\n");
		return 0;
	}

	for (int i = 0; i < count; i++)
	{
		fwrite(database[i].name, sizeof(char), 50, out);
		fwrite(database[i].target_platform, sizeof(char), 100, out);
		fwrite(&database[i].stable_fps, sizeof(float), 1, out);
		fwrite(&database[i].physics_support, sizeof(char), 1, out);
		fwrite(&database[i].graphics_quality, sizeof(Graphics_Quality), 1, out);
		fwrite(&database[i].size_sdk, sizeof(float), 1, out);
		fwrite(&database[i].license_cost, sizeof(double), 1, out);
	}
	fclose(out);
	return 1;
}


Engine* search_platform_physics(Engine* database, int count, char* search_platform, char search_physics, int* search_count)
{
	int search_strings = 0;
	for (int i = 0; i < count; i++)
	{
		if (strstr(database[i].target_platform, search_platform) != NULL && database[i].physics_support == search_physics)
		{
			search_strings += 1;
		}
	}
	*search_count = search_strings;
	if (search_strings == 0)
	{
		return NULL;
	}
	Engine* search_records = (Engine*)malloc(search_strings * sizeof(Engine));
	if (search_records == NULL)
	{
		puts("Ошибка выделения памяти");
		return NULL;
	}
	int index = 0;
	for (int i = 0; i < count; i++)
	{
		if (strstr(database[i].target_platform, search_platform) != NULL && database[i].physics_support == search_physics)
		{
			search_records[index] = database[i];
			index += 1;
		}
	}
	return search_records;
}

int compare(const void* a, const void* b)
{
	Engine* engine_1 = (Engine*)a;
	Engine* engine_2 = (Engine*)b;

	float fps_in_the_square_1 = sqrt(engine_1->stable_fps);
	float fps_in_the_square_2 = sqrt(engine_2->stable_fps);

	if (fps_in_the_square_1 < fps_in_the_square_2)
	{
		return -1;
	}
	else if (fps_in_the_square_1 > fps_in_the_square_2)
	{
		return 1;
	}
	return 0;
}


Engine* test(Engine* database, int last_count, int count)
{
	const char* name[] = { "Unity 2022", "Unreal XR", "ARKit Reality", "ARCore SDK", "AR", "EasyAR", "Unity XR" };
	const char* platform[] = { "Windows", "iOS", "macOS", "Android", "PlayStation" };
	const char physics_support[] = { '+', '-' };


	srand(time(NULL));
	for (int i = last_count; i < count; i++)
	{
		strcpy(database[i].name, name[rand() % 7]);
		strcpy(database[i].target_platform, platform[rand() % 5]);
		database[i].stable_fps = 10 + rand() % 110;
		database[i].physics_support = physics_support[rand() % 2];
		database[i].graphics_quality = 1 + rand() % 3;
		database[i].size_sdk = 10 + rand() % 490 / 10.0f;
		database[i].license_cost = rand() % 10000;
	}
	return database;
}

int sort_fps_in_the_square(Engine* database, int count, int (*compare)(const void*, const void*))
{
	if (count <= 0 || database == NULL)
	{
		puts("База данный пуста. Загрузите данные");
		return 0;
	}
	qsort(database, count, sizeof(Engine), compare);
	return 1;
}