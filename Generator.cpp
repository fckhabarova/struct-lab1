#include "Generator.hpp"
#include <algorithm>

Generator::Generator(int _k) : k(_k) {
    if (k > 0) {
        alphabetPart = getLastLetters(k + 4);
    }
}

std::vector<char> Generator::getLastLetters(int n) {
    std::vector<char> letters;
    if (n > 26) n = 26;
    if (n < 1) return letters;
    
    for (int i = 26 - n; i < 26; i++) {
        letters.push_back('a' + i);
    }
    return letters;
}

bool Generator::isSumEven(const std::string& word) const {
    int sum = 0;
    for (char c : word) {
        sum += (c - 'a' + 1);
    }
    return sum % 2 == 0;
}

void Generator::generateCombinations(int start, int depth, std::string& current) {
    if (depth == k) { //нужная длина
        if (isSumEven(current)) { //четность
            words.push_back(current);
        }
        return;
    }
    
    for (size_t i = start; i < alphabetPart.size(); i++) {
        current.push_back(alphabetPart[i]);
        generateCombinations(static_cast<int>(i + 1), depth + 1, current);
        current.pop_back();
    }
}

void Generator::generate() {
    words.clear();
    if (k == 0) return;
    std::string current;
    generateCombinations(0, 0, current);
}

void Generator::clear() {
    words.clear();
    alphabetPart.clear();
    k = 0;
}

//дружественные функции
std::istream& operator>>(std::istream& in, Generator& gen) {
    std::cout << "Введите k: ";
    in >> gen.k;
    
    if (in.fail() || gen.k < 1) {
        in.setstate(std::ios::failbit); //флаг ошибки
        return in;
    }
    
    gen.alphabetPart = gen.getLastLetters(gen.k + 4);
    gen.words.clear(); //очистка старых слов
    
    return in;
}

std::ostream& operator<<(std::ostream& out, const Generator& gen) {
    out << "k = " << gen.k << "\n";
    out << "букв: ";
    for (char c : gen.alphabetPart) {
        out << c << " ";
    }
    out << "\n";
    out << "слова: ";
    for (size_t i = 0; i < gen.words.size(); i++) {
        out << gen.words[i];
        if (i < gen.words.size() - 1) out << " ";
    }
    out << "\n";
    
    return out;
}

std::string to_string(const Generator& gen) {
    return "Generator(k=" + std::to_string(gen.k) +
           ", words=" + std::to_string(gen.words.size()) + ")";
}

//сравнение для генерации по к и по списку
bool operator==(const Generator& left, const Generator& right) {
    if (left.k != right.k) return false;
    if (left.words.size() != right.words.size()) return false;
    
    for (size_t i = 0; i < left.words.size(); i++) {
        if (left.words[i] != right.words[i]) return false;
    }
    return true;
}

bool isValid(const Generator& gen) {
    if (gen.k < 1) return false;
    if (gen.alphabetPart.empty()) return false;
    return true;
}
