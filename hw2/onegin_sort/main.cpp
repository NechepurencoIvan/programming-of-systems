#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <assert.h>

#define INPUTFILEPATH "./../hamlet.txt"


long readText(char *&buffer){
    std::ifstream infile (INPUTFILEPATH,std::ifstream::binary);

    infile.seekg (0, infile.end);
    long size = infile.tellg();
    infile.seekg (0);

    buffer = new char[size];
    infile.read (buffer,size);

    return size;
}

void rewriteText(char* text, size_t size, char* filename){
    std::ofstream outfile (filename,std::ofstream::binary);
    outfile.write (text, size);
    outfile.close();
}

void writeText(std::vector<char*>& text, char* filename){
    std::ofstream ofstream (filename, std::ofstream::out);
    for(char* string : text) {
        ofstream << string << std::endl;
    }
    ofstream.close();

}

void splitText(char* text, size_t size, std::vector<char*>& starts){
    starts.push_back(text);
    for(long i = 0; i < size; ++i) {
        if (text[i] == '\n') {
            starts.push_back(text + i + 1);
            text[i] = '\0';
        }
    }
}

void clearStarts(std::vector<char*>& starts){
    for(char*& string : starts){
        while(string[0] == ' '){
            string++;
        }
    }
    size_t ind = 0;
    while( ind < starts.size()){
        if(strlen(starts[ind]) == 0) {
            std::swap(starts[ind], starts[starts.size() - 1]);
            starts.pop_back();
        } else {
            ind++;
        }
    }
}

bool isFinishingSymbol(char a){
    return (a == '\0' || a == '\n');
}

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

size_t getLastLetter(char* a) {
    size_t ind = strlen(a);
    while (ind > 0) {
        ind--;
        if (a[ind] != '.' && a[ind] != ',' &&
            a[ind] != '!' && a[ind] != '?') {
            return ind + 1;
        }
    }
    return 1;
}

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

void makeDictioary(std::vector<char*>& starts){
    alphabetComparator comparator;
    std::vector<char*> alphabetSorted = starts;
    std::sort(alphabetSorted.begin(), alphabetSorted.end(), comparator);
    writeText(alphabetSorted,"./../hamlet_encyclopedy");
}


void makeCramoDictioary(std::vector<char *> &starts){
    cramboComparator comparator;
    std::vector<char*> cramboSorted = starts;
    std::sort(cramboSorted.begin(), cramboSorted.end(), comparator);
    writeText(cramboSorted,"./../hamlet_crambo_dictionary");
}

int main () {
    char* text = nullptr;
    long size = readText(text);
    rewriteText(text, size, "./../hamlet(copy).txt");
    std::vector<char*> starts = {};
    splitText(text, size, starts);
    clearStarts(starts);
    makeDictioary(starts);
    makeCramoDictioary(starts);
    delete[] text;//!!!!не чистица
    return 0;
}
