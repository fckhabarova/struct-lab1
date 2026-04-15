#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Generator {
private:
    int k;
    std::vector<char> alphabetPart; //часть алфавита из которой выбираем буквы
    std::vector<std::string> words; //генерация слов

    std::vector<char> getLastLetters(int n); //возврат букв лат алф

    bool isSumEven(const std::string& word) const; //проверка на четность

//рекурсивная генерация сочетания
    void generateCombinations(int start, int depth, std::string& current);

public:
    Generator() : k(0) {}
    explicit Generator(int k); //запрет неявного преобразования
    
    void generate();
    
    void clear();
    
    int getK() const { return k; }
    const std::vector<char>& getAlphabetPart() const { return alphabetPart; }
    const std::vector<std::string>& getWords() const { return words; }
    
//дружественные функции
    friend std::istream& operator>>(std::istream& in, Generator& gen);
    friend std::ostream& operator<<(std::ostream& out, const Generator& gen);
    
    friend std::ifstream& operator>>(std::ifstream& in, Generator& gen);
    friend std::ofstream& operator<<(std::ofstream& out, const Generator& gen);
    
    friend std::string to_string(const Generator& gen);
    friend bool operator==(const Generator& left, const Generator& right);
    friend bool isValid(const Generator& gen);
};
