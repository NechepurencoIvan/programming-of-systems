#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <utility>
#include <functional>
#include <assert.h>

/**
 * Считывает исходный текст в массив
 * @param buffer массив с текстом
 * @param filename название файла
 * @return размер считанного фрагмента
 */
long readText(char *&buffer, char* filename){
    std::ifstream infile (filename, std::ifstream::binary);
    infile.seekg (0, infile.end);
    long size = infile.tellg();
    infile.seekg (0);

    buffer = new char[size];
    infile.read (buffer,size);

    return size;
}

/**
 * Экономично переписывает текст в другой файл
 * @param text массив с текстом
 * @param size его размер
 * @param filename название файла
 */
void rewriteText(char* text, size_t size, char* filename){
    std::ofstream outfile (filename,std::ofstream::binary);
    outfile.write (text, size);
    outfile.close();
}

/**
 * записывает переупорядоченный текст
 * @param starts массив с указателями на строки в нужном порядке
 * @param starts_size размер starts
 * @param filename файл, в который пишем
 */
void writeText(char** starts, size_t starts_size, char* filename){
    std::ofstream ofstream (filename, std::ofstream::out);
    for(long i = 0; i < starts_size; ++i) {
            ofstream << starts[i] << std::endl;
    }
    ofstream.close();
}

/**
 * разделяет текст на строки
 * @param text текст
 * @param size размер текста
 * @param starts массив, в котором будут храниться строки
 * @return рказмер получившегося массива
 */
size_t splitText(char* text, size_t size, char**& starts){
    size_t starts_size = 1;
    for(long ind = 0; ind < size; ++ind){
        if(text[ind] == '\n'){
            starts_size++;
        }
    }
    starts = new char*[starts_size];

    starts[0] = text;
    size_t ind = 1;
    for(long i = 0; i < size; ++i) {
        if (text[i] == '\n') {
            starts[ind] = text + i + 1;
            ind++;
            text[i] = '\0';
        }
    }
    return starts_size;
}

/**
 * Делает обработку массива строк:
 * убирает пробелы в начале, убирает пустые строки
 * @param starts массив со строками
 * @param starts_size его размер
 */
void clearStarts(char** starts, size_t& starts_size){
    for(size_t i = 0; i < starts_size; ++i){
        while(starts[i][0] == ' '){
            starts[i]++;
        }
    }
    size_t ind = 0;
    while(ind < starts_size){
        if(strlen(starts[ind]) == 0) {
            std::swap(starts[ind], starts[starts_size - 1]);
            starts_size--;
        } else {
            ind++;
        }
    }
}

/**
 * проверяет, завершается ли на данном символе строка
 * @param a проверяемый символ
 * @return true, если a - завершающий
 */
bool isFinishingSymbol(char a){
    return (a == '\0' || a == '\n');
}

/**
 * Компаратор для упорядочивания по алфавиту
 */
struct alphabetComparator {
    bool operator()(char* a, char* b) const
    {
        size_t ind = 0;
        while(a[ind] != '\0' && b[ind] != '\0' ||
                a[ind] != '\n' && b[ind] != '\n'){
            if(a[ind] < b[ind]){
                return true;
            }
            if(b[ind] < a[ind]){
                return false;
            }
            ind++;
        }
        return isFinishingSymbol(a[ind]);
    }
};

/**
 * Ищет последний буквенный символ строки
 * @param a строка текста
 * @return индекс нужного символа
 */
size_t getLastLetter(char* a) {
    size_t ind = strlen(a);
    while (ind > 0) {
        if ((('A' <= a[ind-1]) && (a[ind-1] <= 'Z')) ||
            (('a' <= a[ind-1]) && (a[ind-1] <= 'z'))) {
            return ind;
        }
        ind--;
    }
    return 1;
}

/**
 * сортирует по рифме
 */
struct cramboComparator {
    bool operator()(char* a, char* b) const
    {
        assert(strlen(a) >= 1 && strlen(b) >= 1);
        size_t ind1 = getLastLetter(a);
        size_t ind2 = getLastLetter(b);
        while(ind1 > 0 && ind2 > 0){
            ind1--;
            ind2--;
            if(a[ind1] < b[ind2]){
                return true;
            }
            if(a[ind1] > b[ind2]){
                return false;
            }
        }
        return (ind1 == 0);
    }

};

/**
 * Делаем словарь по нужному нам порядку
 * @tparam T компаратор, по которому текаст сортируется
 * @param starts массив из строк текста
 * @param starts_size его длинва
 * @param filename название файла, в который производим запись отсортированного текста
 */
template <typename T>
void makeDictioary(char** starts, size_t starts_size, char* filename){
    T comparator;
    char** starts_sorted = new char* [starts_size];
    std::memcpy(starts_sorted, starts, starts_size * sizeof(starts[0]));
    std::sort(starts_sorted, starts_sorted + starts_size, comparator);
    writeText(starts_sorted, starts_size, filename);
    delete[] starts_sorted;
}

int main () {
    char* text = nullptr;
    long size = readText(text, "./../hamlet.txt");
    rewriteText(text, size, "./../hamlet(copy).txt");
    char** starts = nullptr;
    size_t starts_size = splitText(text, size, starts);
    clearStarts(starts, starts_size);
    makeDictioary<alphabetComparator>(starts, starts_size, "./../hamlet_ecyclopedy.txt");
    makeDictioary<cramboComparator>(starts, starts_size, "./../hamlet_cramo_ecyclopedy.txt");
    delete[] starts;
    delete[] text;
    return 0;
}
