#include "HashTableList.h"

HashTableList::HashTableList() : size(0), head(nullptr)
{
}

void HashTableList::insertElement(int key, Vertex* vertexToInsert)
{
    HashTableListNode* oneElement = new HashTableListNode;

    if (size == 0)
    {
        head = oneElement;
        oneElement->next = nullptr;
        oneElement->key = key;
        oneElement->vertexInTable = vertexToInsert;
        tail = head;
    }
    else
    {
        tail->next = oneElement;
        oneElement->next = nullptr;
        oneElement->key = key;
        oneElement->vertexInTable = vertexToInsert;
        tail = oneElement;
    }
    size++;
}
