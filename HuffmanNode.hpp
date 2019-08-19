/**
 * @file HuffmanBaum.h
 * @author dominikauthaler
 * @date 16.08.19
 * Description here TODO
 */

#include <memory>
#include <map>

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

class HuffmanNode {
public:
    //Konstruktoren
    HuffmanNode(std::shared_ptr<HuffmanNode> left, std::shared_ptr<HuffmanNode> right);
    HuffmanNode(char c, unsigned long occ);

    //Getter
    unsigned long getOcc() const;
    unsigned int getDepth() const;
    char getChar() const;
    std::string getDescription() const;

    //Sonstige Methoden
    std::map<char, std::string> getMapping() const;
    std::string printNode() const;

    std::shared_ptr<HuffmanNode> leftTree;
    std::shared_ptr<HuffmanNode> rightTree;

private:
    char c;
    unsigned long occ;
    unsigned int depth;

    //Hilfsmethode für rekursive Berechnung des Mappings
    void getMapping(const std::string &prefix, std::map<char, std::string> &map) const;
};

#endif //HUFFMAN_NODE_H