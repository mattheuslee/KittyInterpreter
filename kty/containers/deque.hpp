#pragma once

#include <kty/containers/allocator.hpp>

namespace kty {

/*!
    @brief  Double-ended queue.
            Provides quick insertion and deletion at both ends,
            but at the expense of slow random access. 
            Implemented as a circular doubly linked list with a dummy head node.
*/
template <typename T>
class Deque {

public:
    /*!
        @brief  The node structure that makes up the deque.
    */
    struct Node {
        /** The value stored in the node */
        T value;
        /** The node after this one */
        Node* next;
        /** The node before this one */
        Node* prev;
    };

    /*!
        @brief  Creates an allocator for this deque.

        @param  maxSize
                Maximum size for the deque.
                If the deque using this allocator exceeds this max size,
                undefined behaviour will occur.
        
        @return The allocator to use for this deque.
    */
    static Allocator<Node> create_allocator(int const & maxSize) {
        // +1 because of the dummy head node
        return Allocator<Node>(maxSize + 1);
    }

    /*!
        @brief  Constructor for the deque.

        @param  allocator
                The allocator for the deque nodes.
    */
    Deque(Allocator<Node>& allocator) : allocator_(allocator) {
        size_ = 0;
        head = allocator_.allocate();
        head->next = head;
        head->prev = head;
    }

    /*!
        @brief  Destructor for the deque.
    */
    ~Deque() {
        while (!is_empty()) {
            pop_front();
        }
        allocator_.deallocate(head);
        head = NULL;
    }

    /*!
        @brief  Returns the size of the deque.

        @return The number of elements in the deque.
    */
    int size() {
        return size_;
    }

    /*!
        @brief  Returns true if the deque is empty, false otherwise.

        @return True if the deque is empty, false otherwise.
    */
    bool is_empty() {
        return size_ == 0;
    }

    /*!
        @brief  Pushes a value to the front of the deque.

        @param  value
                The value to push to the front of the deque.
    */
    void push_front(T const & value) {
        // Allocate new node
        Node* toInsert = allocator_.allocate();
        toInsert->value = value;
        Node* next = head->next;
        // Rearrange pointers
        toInsert->next = next;
        toInsert->prev = head;
        next->prev = toInsert;
        head->next = toInsert;
        ++size_;
    }

    /*!
        @brief  Pops value from the front of the deque.
                If there is no value to pop, does nothing.
    */
    void pop_front() {
        if (is_empty()) {
            return;
        }
        Node* toRemove = head->next;
        Node* next = toRemove->next;
        // Rearrange pointers to bypass node to be removed
        head->next = next;
        next->prev = head;
        allocator_.deallocate(toRemove);
        --size_;
    }

    /*!
        @brief  Pushes a value to the back of the deque.

        @param  value
                The value to push to the back of the deque.
    */
    void push_back(T const & value) {
        // Allocate new node
        Node* toInsert = allocator_.allocate();
        toInsert->value = value;
        Node* prev = head->prev;
        // Rearrange pointers
        toInsert->next = head;
        toInsert->prev = prev;
        prev->next = toInsert;
        head->prev = toInsert;
        ++size_;
    }

    /*!
        @brief  Pops value from the back of the deque.
                If there is no value to pop, does nothing.
    */
    void pop_back() {
        if (is_empty()) {
            return;
        }
        Node* toRemove = head->prev;
        Node* prev = toRemove->prev;
        // Rearrange pointers to bypass node to be removed
        head->prev = prev;
        prev->next = head;
        allocator_.deallocate(toRemove);
        --size_;
    }

    /*!
        @brief  Returns a reference to the front element of the deque.
                Has undefined behaviour if the deque is empty.
                
        @return A reference to the element.
    */
    T& front() {
        return head->next->value;
    }

    /*!
        @brief  Returns a reference to the back element of the deque.
                Has undefined behaviour if the deque is empty.

        @return A reference to the element.
    */
    T& back() {
        return head->prev->value;
    }

    /*!
        @brief  Returns a reference to the ith-indexed element of the deque.
                Has undefined behaviour if the deque has less than i elements. 

        @param  i
                The index of the element to retrieve.

        @return A reference to the element.
    */
    T& operator[](int const & i) {
        Node* curr = head->next;
        for (int j = 0; j < i; ++j) {
            curr = curr->next;
        }
        return curr->value;
    }

private:
    Node* head;
    int size_;

    Allocator<Node>& allocator_;

};

} // namespace kty