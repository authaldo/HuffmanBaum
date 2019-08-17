#include <iostream>
#include <iomanip>
#include <set>
#include <fstream>

#include "HuffmanNode.hpp"

//#define DEBUG

/**
 * Vergleichsmethode für zwei shared_ptr<HuffmanNode>
 */
auto nodePtrCmp = [](const std::shared_ptr<HuffmanNode> ptr1, const std::shared_ptr<HuffmanNode> ptr2) {
    //Zweistufiger Vergleich, damit auch bei gleicher Zahl von Vorkommen ein Unterschied vorhanden ist
    if(ptr1->getOcc() != ptr2->getOcc()) {
        return ptr1->getOcc() < ptr2->getOcc();
    } else if(ptr1->getDepth() != ptr2->getDepth()){
        return ptr1->getDepth() < ptr2->getDepth();
    } else {
        return false;
    }
};

typedef std::set<std::shared_ptr<HuffmanNode>, decltype(nodePtrCmp)> HuffmanSet;

void displaySet(const HuffmanSet &set);

int main(int argc, const char* argv[]) {
    std::string path = (argc == 2) ? std::string(argv[1]) : "../data.txt";

    //Einlesen und absolute Häufigkeiten bestimmmen
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Problem while opening the file" << std::endl;
        exit(-1);
    }

    std::array<int, 256> counts = {0};
    std::cout << "Zu codierender Text: " << std::endl;
    char c;
    while (file.get(c)) {
        std::cout << c;
        counts[c] += 1;
    }
    file.close();

#ifdef DEBUG
    std::cout << "\nAbsolute Häufigkeiten der Zeichen: " << std::endl;
    for (int i = 32; i < 128; i++) {
        std::cout << std::setw(3) << i << std::setw(2) << "\t[" << static_cast<char>(i) << "]" << ": " << std::setw(4)
                  << counts[i] << std::endl;
    }
#endif

    //Konstruktion des Huffman-Baums
    HuffmanSet set (nodePtrCmp);

    for (unsigned int i = 0; i < counts.size(); i++) {
        if (counts[i] > 0) {
            set.insert(std::make_shared<HuffmanNode>(i, counts[i]));
        }
    }
#ifdef DEBUG
    displaySet(set);
#endif
    while (set.size() > 1) {
        auto it1 = set.begin();
        auto it2 = it1; it2++;
        std::shared_ptr<HuffmanNode> node = std::make_shared<HuffmanNode>(*it1, *it2);
        set.erase(it1);
        set.erase(it2);
        set.insert(node);
#ifdef DEBUG
        displaySet(set);
#endif
    }
    std::map<char, std::string> mapping = (*(set.begin()))->getMapping();
    std::cout << "\n\nBerechnete Codierung: " << std::endl;
    for (auto &p : mapping) {
        std::cout << p.first << " -> " << p.second << std::endl;
    }

    return 0;
}

#ifdef DEBUG
/**
 * Hilfsmethode zur Darstellung des aktuellen Zustands der Knotenmenge
 * @param set
 */
void displaySet(const HuffmanSet &set) {
    for (const auto &s: set) {
        std::cout << s->printNode();
    }
    std::cout << std::endl;
}
#endif