//
// Created by Alessandro on 31.08.2024.
//

#ifndef CUSTOM_DOUBLY_LINKED_LIST_H
#define CUSTOM_DOUBLY_LINKED_LIST_H



class custom_doubly_linked_list {
private:
    typedef struct Node {
        Node *prev;
        Node *next;
    } Node;

    typedef struct LinkedList {
        Node *head;
        Node *tail;
    } LinkedList;

public:
    static char *createLinkedList();
    static char *createNode();
    static void append(char *list, char *node);
    static void remove(char *list, char* node);
    static char *get_head(char *list);
    static char *get_tail(char *list);
};



#endif //CUSTOM_DOUBLY_LINKED_LIST_H
