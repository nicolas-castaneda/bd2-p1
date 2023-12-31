#ifndef AVL_INDEX_HPP
#define AVL_INDEX_HPP

#include "../index.hpp"
#include "avl_index_header.hpp"
#include "avl_index_node.hpp"

template<typename KEY_TYPE = default_data_type>
class AVLIndex : public Index<KEY_TYPE>
{
    AVLIndexHeader header;
    std::string indexFileName;
    std::fstream file;

    void initFile();

    void initIndex();

    void insert(physical_pos cPointer, AVLIndexNode<KEY_TYPE> &cNode, AVLIndexNode<KEY_TYPE> &iNode, Response &response);

    void balance(physical_pos nodePointer);

    void leftRotation(physical_pos nodePointer);

    void rightRotation(physical_pos nodePointer);

    bool isBalanced(physical_pos nodePointer);

    int balancingFactor(physical_pos nodePointer);

    void updateHeigth(physical_pos nodePointer);
    
    long height(physical_pos nodePointer);

    AVLIndexNode<KEY_TYPE> search(physical_pos currentPointer, AVLIndexNode<KEY_TYPE> &cNode, Data<KEY_TYPE> &item);

    physical_pos maxNode(physical_pos nodePointer);

    bool erase(physical_pos cPointer, physical_pos pPointer, AVLIndexNode<KEY_TYPE> &cNode, Data<KEY_TYPE> item, Response &response);

    void fixValue(physical_pos cPointer, AVLIndexNode<KEY_TYPE> &cNode, Data<KEY_TYPE> &item1, AVLIndexNode<KEY_TYPE> &tempNode);

    void displayPretty(const std::string &prefix, physical_pos cPointer, bool isLeft);

    void rangeSearch(physical_pos cPointer, AVLIndexNode<KEY_TYPE> &cNode, Response &response, Data<KEY_TYPE> &begin, Data<KEY_TYPE> &end);

public:
    AVLIndex(std::string _indexFileName)
    {
        this->indexFileName = _indexFileName;
        initIndex();
    }

    AVLIndex(
        std::string _table_name,
        std::string _attribute_name,
        bool PK = false
    ) {
        this->table_name = _table_name;
        this->attribute_name = _attribute_name;
        this->index_name = "AVL";
        this->indexFileName = _table_name + "_" + _attribute_name + "_" + this->index_name + ".bin";
        this->duplicatesFilename = _table_name + "_" + _attribute_name + "_" + this->index_name + "_duplicateFile.bin";
        this->PK = PK;
        initIndex();
    }

    std::string get_index_name() override;

    Response add(Data<KEY_TYPE> data, physical_pos raw_pos) override;

    Response search(Data<KEY_TYPE> item) override;

    Response erase(Data<KEY_TYPE> item) override;

    Response rangeSearch(Data<KEY_TYPE> start, Data<KEY_TYPE> end) override;

    void displayPretty();

    void printDuplicateFile() { this->template printFile<AVLIndexNode<KEY_TYPE>>(this->duplicatesFilename); }

    void printIndexFile() { this->template printFileWithHeader<AVLIndexHeader, AVLIndexNode<KEY_TYPE>>(this->indexFileName); }
};

#include "avl_index.tpp"

#endif // AVL_INDEX_HPP