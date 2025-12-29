#ifndef FUNCTIONS_H
#define FUNCTIONS_H


//Перечисление для качества графики
typedef enum {
	LOW = 1,
	MEDIUM = 2,
	HIGH = 3,
} Graphics_Quality;


//Структура записи информации о AR/VR движке
struct engine {
	char name[50];
	char target_platform[100];
	float stable_fps;
	char physics_support;
	Graphics_Quality graphics_quality;
	float size_sdk;
	double license_cost;
};

typedef struct engine Engine; //Название структуры для удобства использования

/**
* Подсчитывает количество записей в файле
* @param file_name - имя файла для чтения
* @return количество записей в файле
*/
int count_data(const char* file_name);

/**
* Загружает записи из файла в массив структур
* @param file_name - имя файла для чтения
* @param count - количество записей для загрузки
* @param database - указатель на массив структур
* @return указатель на заполненный массив структур 
*/
Engine* uploading_data(const char* file_name, int count, Engine* database);

/**
* Выводит все записи на экран
* @param count - количество записей в массиве
* @param database - указатель на массив структур
* @return 0 при успехе
*/
int output_engine(Engine* database, int count);

/**
* Добавляет новую запись в массив
* @param database - указатель на массив структур
* @param count - количество записей в массиве
* @return указатель на обновлённый массив структур
*/
Engine* input_engine(Engine* database, int count);

/**
* Сохраняет записи из массива структур в файл
* @param database - указатель на массив структур
* @param fname - имя файла для сохранения
* @param count - количество записей в массиве
* @return указатель на обновлённый массив структур
*/
int saving_data(Engine* database, const char* fname, int count);

/**
* Подсчитывает количество записей, удовлетворяющих критериям поиска
* @param database - указатель на массив структур
* @param count - количество записей в массиве
* @param search_platform - целевая платформа дял поиска
* @param search_physics - нужная поддержка физики
* @return количество найденных записей
*/
int search_platform_physics_count(Engine* database, int count, char* search_platform, char search_physics);

/**
* Находит все записи, удовлетворяющие критериям поиска, и записывает их в новый массив
* @param database - указатель на массив структур
* @param count - количество записей в массиве
* @param search_platform - целевая платформа дял поиска
* @param search_physics - нужная поддержка физики
* @param search_strings - количество найденных записей
* @return указатель на новый массив с найденными записями
*/
Engine* search_platform_physics_array(Engine* database, int count, char* search_platform, char search_physics, int search_strings);

/**
* Функция сравнения для qsort()
* @param a - указатель на первый сравниваемый элемент
* @param b - указатель на второй сравниваемый элемент
* @return -1, если a < b; 1, если a > b; 0, если a = b;
*/
int compare(const void* a, const void* b);

/**
* Сортирует массив по квадратному корню из FPS
* @param database - указатель на массив структур
* @param count - количество записей в массиве
* @param compare - указатель на функцию сравнения
* @return 1 при успешном выполнении
*/
int sort_fps_in_the_square(Engine* database, int count, int (*compare) (const void*, const void*));

/**
* Генерирует тестовые значения
* @param database - указатель на массив структур
* @param last_count - индекс элемента, с которого начинается заполнения
* @param count - количество записей в массиве
* @return указатель на массив структур
*/
Engine* test(Engine* database, int last_count, int count);

#endif