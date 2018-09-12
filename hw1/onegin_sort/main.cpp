#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

#define INPUTFILEPATH "./../hamlet.txt"
#define OUTPUTPATH "./../output2"

bool lessEq(std::string &str1, std::string &str2, size_t startIndex = 0) {
    size_t i = startIndex;
    while (i < str1.length() && i < str2.length()) {
        if (str1[i] < str2[i]) {
            return true;
        }
        if (str1[i] > str2[i]) {
            return false;
        }
        i++;
    }
    return (str1.length() <= str2.length());
}

class quickSorter {
public:
    quickSorter() {
        text = {};
        std::ifstream input;
        input.open(INPUTFILEPATH, std::ios::in);
        std::string str;
        while (getline(input, str)) {
            if (str != "") {
                text.push_back(str);
            }
        }
        input.close();
    }

    void sortText() {
        quickSortIteration(0, text.size());
    }

    bool checkSort() {
        for (size_t i = 2; i < text.size(); ++i) {
            if (!lessEq(text[i - 1], text[i])) {
                return false;
            }
        }
        return true;
    }

    void printText() {
        for (std::string &str : text) {
            std::cout << str << std::endl;
        }
    }

    void writeText() {
        std::ofstream output;
        output.open(OUTPUTPATH, std::ios::out);
        for (std::string &str: text) {
            output << str << std::endl;
        }
        output.close();
    }

private:
    std::vector<std::string> text;

/**
 * Данный метод выбирает место очередного пивота.
 * В данной реализации берется медиана трех
 * @param a индекс начала рассматриваемого отрезка
 * @param b индекс конца рассматриваемого отрезка
 * @return индекс элемента, который мы берем опорным
 */
    size_t findPivotPosition(size_t a, size_t b) {
        //return (b + a) / 2;
        size_t pivotPosition = getMedianOfThreeStrings(a, b);
        assert(pivotPosition >= a && pivotPosition < b);
        return pivotPosition;
    }

    bool checkSymbolIsExtremal(size_t* indexes, bool& foundSmallest, size_t ind, size_t pos){
        size_t ind1 = (ind + 1) % 3;
        size_t ind2 = (ind + 2) % 3;
        if(text[indexes[ind]][pos] == text[indexes[ind1]][pos]
           && text[indexes[ind]][pos] == text[indexes[ind2]][pos]){
            return false;
        }
        if(text[indexes[ind]][pos] >= text[indexes[ind1]][pos]
           && text[indexes[ind]][pos] >= text[indexes[ind2]][pos]){
            foundSmallest = false;
            return true;
        }
        if(text[indexes[ind]][pos] <= text[indexes[ind1]][pos]
           && text[indexes[ind]][pos] <= text[indexes[ind2]][pos]){
            foundSmallest = true;
            return true;
        }
        return false;
    }

    bool findSuperfulousSring(size_t* indexes, bool& foundSmallest, size_t& superfuloudIndex, size_t i){
        for(size_t j = 0; j < 2; ++j){
            if(i >= text[indexes[j]].size()) {
                foundSmallest = true;
                superfuloudIndex = j;
                return true;
            }
            if(checkSymbolIsExtremal(indexes, foundSmallest, j, i)){
                superfuloudIndex = j;
                return true;
            }
        }
        return false;
    }

    size_t getMedianOfThreeStrings(size_t a, size_t b){
        if(b == 0){
            return a;
        }
        size_t indexes[] = {a, (a + b)/2, b - 1};
        size_t i = 0;
        size_t superfulousIndex;
        bool foundSmallest = false;
        while(1) {
            if(findSuperfulousSring(indexes, foundSmallest, superfulousIndex, i)){
                std::swap(indexes[superfulousIndex], indexes[2]);
                if(!lessEq(text[indexes[0]], text[indexes[1]])){
                    std::swap(indexes[0], indexes[1]); //Упорядочиваем оставшиеся строки по порядку
                }
                if(foundSmallest){
                    return indexes[0];
                } else {
                    return indexes[1];
                }
            }
            i++;
        };
        return (b + a)/2;
    }

    void changePivot(size_t a, size_t b) {
        size_t pivotPosition = findPivotPosition(a, b);
        assert(pivotPosition < b);
        std::swap(text[a], text[pivotPosition]);
    }

    size_t partition(size_t a, size_t b) {
        changePivot(a, b);
        std::cout<<a<<" "<<b;
        std::string &pivotValue = text[a];
        int i = a + 1, j = b - 1;
        do {
            while (i <= j && lessEq(text[i], pivotValue)) {
                i++;
            }
            while (i <= j && lessEq(pivotValue, text[j])) {
                j--;
            }
            if (j >= i) {
                std::swap(text[i], text[j]);
            }
        } while (j >= i);
        std::swap(text[a], text[j]);
        return j;
    }

    void quickSortIteration(size_t a, size_t b) { //!!!!
        if (a >= b) {
            return;
        }
        size_t pivot = partition(a, b);
        quickSortIteration(a, pivot);
        quickSortIteration(pivot + 1, b);
    }
};

int main() {
    quickSorter sorter;
    sorter.sortText();
    if (sorter.checkSort()) {
        sorter.printText();
        sorter.writeText();
    } else {
        std::cout << "The process failed" << std::endl;
    }
    return 0;
}