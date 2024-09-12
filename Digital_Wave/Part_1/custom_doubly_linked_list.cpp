//
// Created by Alessandro on 31.08.2024.
//

#include "custom_doubly_linked_list.h"

#include <stdlib.h>

char *custom_doubly_linked_list::createNode() {
    const auto node = static_cast<Node *>(malloc(sizeof(Node)));
    node->prev = static_cast<Node *>(malloc(sizeof(Node)));
    node->next = static_cast<Node *>(malloc(sizeof(Node)));
    return reinterpret_cast<char *>(node);
}

char *custom_doubly_linked_list::createLinkedList() {
    const auto list = static_cast<LinkedList *>(malloc(sizeof(LinkedList)));
    list->head = static_cast<Node *>(malloc(sizeof(Node)));
    list->tail = static_cast<Node *>(malloc(sizeof(Node)));
    return reinterpret_cast<char *>(list);
}

void custom_doubly_linked_list::append(char *list, char *node) {
    const auto list_ = reinterpret_cast<LinkedList *>(list);
    const auto node_ = reinterpret_cast<Node *>(node);

    if (get_tail(list) == nullptr) {
        list_->head = node_;
        list_->tail = node_;
    } else {
        list_->tail->next = node_;
        node_->prev = list_->tail;
        list_->tail = node_;
    }
}

void custom_doubly_linked_list::remove(char *list, char *node) {
    const auto list_ = reinterpret_cast<LinkedList *>(list);
    const auto node_ = reinterpret_cast<Node *>(node);

    if (node_ == list_->head)
        list_->head = node_->next;
    else
        node_->prev->next = node_->next;

    if (node_ == list_->tail)
        list_->tail = node_->prev;
    else
        node_->next->prev = node_->prev;

    free(node_);
}

char *custom_doubly_linked_list::get_head(char *list) {
    return reinterpret_cast<char *>(reinterpret_cast<LinkedList *>(list)->head);
}

char *custom_doubly_linked_list::get_tail(char *list) {
    return reinterpret_cast<char *>(reinterpret_cast<LinkedList *>(list)->tail);
}


