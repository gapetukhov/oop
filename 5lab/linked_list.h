#pragma once
#include <memory>
#include <iterator>
#include <iostream>
#include "custom_memory_resources.h"

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        explicit Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::pmr::polymorphic_allocator<std::byte> allocator; 
    size_t list_size;

public:
    explicit DoublyLinkedList(std::pmr::memory_resource* mr)
        : head(nullptr), tail(nullptr), allocator(mr), list_size(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    void push_back(const T& value) {
        Node* new_node = allocate_node(value);
        if (!tail) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        list_size++;
    }

    void remove(const T& value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                deallocate_node(current);
                list_size--;
                return;
            }
            current = current->next;
        }
    }

    size_t size() const { return list_size; }

    class Iterator {
    private:
        Node* current;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(Node* node) : current(node) {}

        T& operator*() { return current->data; }
        T* operator->() { return &current->data; }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
    };
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }

private:
    Node* allocate_node(const T& value) {
        void* memory = allocator.allocate(sizeof(Node));
        return new (memory) Node(value);
    }

    void deallocate_node(Node* node) {
        node->~Node();
        allocator.deallocate(reinterpret_cast<std::byte*>(node), sizeof(Node));
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            deallocate_node(current);
            current = next;
        }
        head = tail = nullptr;
        list_size = 0;
    }
};
