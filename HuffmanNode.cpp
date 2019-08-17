//
// Created by dominikauthaler on 16.08.19.
//

#include <iostream>
#include "HuffmanNode.hpp"

/**
 * Konstruktor, erzeugt neuen Node mit entsprechendem Buchstaben und Häufigkeit
 * @param c Buchstabe
 * @param occ Häufigkeit
 */
HuffmanNode::HuffmanNode(char c, unsigned long occ) : c(c), occ(occ), leftTree(nullptr), rightTree(nullptr), depth(0) {
    ;
}

/**
 * Konstruktor, erzeugt neuen Node mit den übergebenen child-Nodes
 * @param left linker Kindknoten
 * @param right rechter Kindknoten
 */
HuffmanNode::HuffmanNode(std::shared_ptr<HuffmanNode> left, std::shared_ptr<HuffmanNode> right) : leftTree(left), rightTree(right), c(255), occ(left->getOcc() + right->getOcc()) {
    depth = std::max(left->getDepth(), right->getDepth()) + 1;
}

/**
 * Getter für das Zeichen des Knotens
 * @return Zeichen des Knotens
 */
char HuffmanNode::getChar() const {
    return c;
}

/**
 * Getter für die Bezeichnung des Knotens (bestehend aus den Zeichen der Kind-Knoten)
 * @return Bezeichnung des Knotens
 */
std::string HuffmanNode::getDescription() const {
    if(leftTree == nullptr && rightTree == nullptr) {
        std::string s = "";
        s += c;
        return s;
    } else {
        return leftTree->getDescription() + rightTree->getDescription();
    }
}

/**
 * Getter für die Häufigkeit des Knotenzeichens
 * @return Häufigkeit
 */
unsigned long HuffmanNode::getOcc() const {
    return occ;
}

/**
 * Getter für das Mapping des (Teil-)Baums, welcher mit dem aufrufenden Knoten beginnt
 * @return Abbildung der Zeichen auf die Codes
 */
auto HuffmanNode::getMapping() const -> std::map<char, std::string> {
    std::map<char, std::string> map;
    std::string prefix = "";
    getMapping(prefix, map);

    return map;
}

/**
 * Hilfsmethode,
 * @param prefix
 * @param map
 */
void HuffmanNode::getMapping(std::string prefix, std::map<char, std::string> &map) const {
    if (leftTree == nullptr && rightTree == nullptr) {
        if (!prefix.empty()) {
            map.insert(std::pair<char, std::string>(this->c, prefix));
        } else {
            map.insert(std::pair<char, std::string>(this->c, std::string("0")));
        }
    } else {
        leftTree->getMapping(prefix + "1", map);
        rightTree->getMapping(prefix + "0", map);
    }
}

/**
 * liefert Beschreibung des Knotens zusammen mit der Häufigkeit
 * @return Informationen des Knotens
 */
std::string HuffmanNode::printNode() const {
    return "(" + getDescription() + ", " + std::to_string(occ) + ")";
}

/**
 * Getter für die Tiefe des Teilbaums
 * @return (Teil-)Baumtiefe
 */
unsigned int HuffmanNode::getDepth() const {
    return depth;
}