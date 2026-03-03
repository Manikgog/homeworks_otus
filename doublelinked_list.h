#pragma once

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <exception>
#include <algorithm>

template <typename Type>
class DoubleLinkedList {
    // Узел двусвязного списка
    struct Node {
        Node() = default;
        Node(const Type& val, Node* prev, Node* next)
            : value(val)
            , prev_node(prev)
            , next_node(next) {
        }
        Type value{};
        Node* prev_node = nullptr;
        Node* next_node = nullptr;
    };

    template <typename ValueType>
    class BasicIterator {
        friend class DoubleLinkedList;
        explicit BasicIterator(Node* node);

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;

        BasicIterator() = default;
        BasicIterator(const BasicIterator<Type>& other) noexcept;
        BasicIterator& operator=(const BasicIterator& rhs) = default;

        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept;
        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept;
        [[nodiscard]] bool operator==(const BasicIterator<Type>& rhs) const noexcept;
        [[nodiscard]] bool operator!=(const BasicIterator<Type>& rhs) const noexcept;

        BasicIterator& operator++() noexcept;
        BasicIterator operator++(int) noexcept;
        BasicIterator& operator--() noexcept;
        BasicIterator operator--(int) noexcept;
        [[nodiscard]] reference operator*() const noexcept;
        [[nodiscard]] pointer operator->() const noexcept;

    private:
        Node* node_ = nullptr;
    };

public:
    DoubleLinkedList() = default;
    DoubleLinkedList(std::initializer_list<Type> values);
    DoubleLinkedList(const DoubleLinkedList& other);
    DoubleLinkedList& operator=(const DoubleLinkedList& rhs);
    ~DoubleLinkedList();

    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using Iterator = BasicIterator<Type>;
    using ConstIterator = BasicIterator<const Type>;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    [[nodiscard]] Iterator rbegin() noexcept;
    [[nodiscard]] Iterator rend() noexcept;
    [[nodiscard]] ConstIterator rbegin() const noexcept;
    [[nodiscard]] ConstIterator rend() const noexcept;
    [[nodiscard]] ConstIterator crbegin() const noexcept;
    [[nodiscard]] ConstIterator crend() const noexcept;

    void PushFront(const Type& val);
    void PushBack(const Type& val);
    void PopFront() noexcept;
    void PopBack() noexcept;
    void Clear() noexcept;
    [[nodiscard]] size_t GetSize() const noexcept;
    [[nodiscard]] bool IsEmpty() const noexcept;
    void swap(DoubleLinkedList& other) noexcept;

    Iterator Insert(ConstIterator pos, const Type& value);
    Iterator Erase(ConstIterator pos) noexcept;

private:
    Node head_;  // фиктивный узел (перед первым элементом)
    Node tail_;  // фиктивный узел (после последнего элемента)
    size_t size_ = 0;

    void InitEmpty();
};

// Реализации методов BasicIterator
template <typename Type>
template <typename ValueType>
DoubleLinkedList<Type>::BasicIterator<ValueType>::BasicIterator(Node* node) : node_(node) {}

template <typename Type>
template <typename ValueType>
DoubleLinkedList<Type>::BasicIterator<ValueType>::BasicIterator(const BasicIterator<Type>& other) noexcept
    : node_(other.node_) {}

template <typename Type>
template <typename ValueType>
bool DoubleLinkedList<Type>::BasicIterator<ValueType>::operator==(const BasicIterator<const Type>& rhs) const noexcept {
    return node_ == rhs.node_;
}

template <typename Type>
template <typename ValueType>
bool DoubleLinkedList<Type>::BasicIterator<ValueType>::operator!=(const BasicIterator<const Type>& rhs) const noexcept {
    return !(*this == rhs);
}

template <typename Type>
template <typename ValueType>
bool DoubleLinkedList<Type>::BasicIterator<ValueType>::operator==(const BasicIterator<Type>& rhs) const noexcept {
    return node_ == rhs.node_;
}

template <typename Type>
template <typename ValueType>
bool DoubleLinkedList<Type>::BasicIterator<ValueType>::operator!=(const BasicIterator<Type>& rhs) const noexcept {
    return !(*this == rhs);
}

template <typename Type>
template <typename ValueType>
typename DoubleLinkedList<Type>::template BasicIterator<ValueType>&
DoubleLinkedList<Type>::BasicIterator<ValueType>::operator++() noexcept {
    assert(node_ != nullptr && "Attempt to increment past end");
    node_ = node_->next_node;
    return *this;
}

template <typename Type>
template <typename ValueType>
typename DoubleLinkedList<Type>::template BasicIterator<ValueType>
DoubleLinkedList<Type>::BasicIterator<ValueType>::operator++(int) noexcept {
    assert(node_ != nullptr && "Attempt to increment past end");
    auto old_value = *this;
    node_ = node_->next_node;
    return old_value;
}

template <typename Type>
template <typename ValueType>
typename DoubleLinkedList<Type>::template BasicIterator<ValueType>&
DoubleLinkedList<Type>::BasicIterator<ValueType>::operator--() noexcept {
    assert(node_ != nullptr && "Attempt to decrement past begin");
    node_ = node_->prev_node;
    return *this;
}

template <typename Type>
template <typename ValueType>
typename DoubleLinkedList<Type>::template BasicIterator<ValueType>
DoubleLinkedList<Type>::BasicIterator<ValueType>::operator--(int) noexcept {
    assert(node_ != nullptr && "Attempt to decrement past begin");
    auto old_value = *this;
    node_ = node_->prev_node;
    return old_value;
}

template <typename Type>
template <typename ValueType>
typename DoubleLinkedList<Type>::template BasicIterator<ValueType>::reference
DoubleLinkedList<Type>::BasicIterator<ValueType>::operator*() const noexcept {
    assert(node_ != nullptr && node_ != &this->head_ && node_ != &this->tail_ && "Dereferencing null or sentinel iterator");
    return node_->value;
}

template <typename Type>
template <typename ValueType>
typename DoubleLinkedList<Type>::template BasicIterator<ValueType>::pointer
DoubleLinkedList<Type>::BasicIterator<ValueType>::operator->() const noexcept {
    assert(node_ != nullptr && node_ != &this->head_ && node_ != &this->tail_ && "Dereferencing null or sentinel iterator");
    return &node_->value;
}

// Реализации методов DoubleLinkedList
template <typename Type>
void DoubleLinkedList<Type>::InitEmpty() {
    head_.next_node = &tail_;
    tail_.prev_node = &head_;
    head_.prev_node = nullptr;
    tail_.next_node = nullptr;
}

template <typename Type>
DoubleLinkedList<Type>::DoubleLinkedList(std::initializer_list<Type> values) {
    InitEmpty();
    for (auto it = std::rbegin(values); it != std::rend(values); ++it) {
        PushFront(*it);
    }
}

template <typename Type>
DoubleLinkedList<Type>::DoubleLinkedList(const DoubleLinkedList& other) {
    InitEmpty();
    DoubleLinkedList tmp;
    Node* current = other.head_.next_node;
    while (current != &other.tail_) {
        tmp.PushBack(current->value);
        current = current->next_node;
    }
    swap(tmp);
}

template <typename Type>
DoubleLinkedList<Type>& DoubleLinkedList<Type>::operator=(const DoubleLinkedList& rhs) {
    if (this != &rhs) {
        DoubleLinkedList tmp(rhs);
        swap(tmp);
    }
    return *this;
}

template <typename Type>
DoubleLinkedList<Type>::~DoubleLinkedList() {
    Clear();
}

template <typename Type>
typename DoubleLinkedList<Type>::Iterator DoubleLinkedList<Type>::begin() noexcept {
    return Iterator(head_.next_node);
}

template <typename Type>
typename DoubleLinkedList<Type>::Iterator DoubleLinkedList<Type>::end() noexcept {
    return Iterator(&tail_);
}

template <typename Type>
typename DoubleLinkedList<Type>::ConstIterator DoubleLinkedList<Type>::begin() const noexcept {
    return cbegin();
}

template <typename Type>
typename DoubleLinkedList<Type>::ConstIterator DoubleLinkedList<Type>::end() const noexcept {
    return cend();
}

template <typename Type>
typename DoubleLinkedList<Type>::ConstIterator DoubleLinkedList<Type>::cbegin() const noexcept {
    return ConstIterator(head_.next_node);
}

template <typename Type>
typename DoubleLinkedList<Type>::ConstIterator DoubleLinkedList<Type>::cend() const noexcept {
    return ConstIterator(const_cast<Node*>(&tail_));
}

template <typename Type>
typename DoubleLinkedList<Type>::Iterator DoubleLinkedList<Type>::rbegin() noexcept {
    return Iterator(tail_.prev_node);
}

template <typename Type>
typename DoubleLinkedList<Type>::Iterator DoubleLinkedList<Type>::rend() noexcept {
    return Iterator(&head_);
}

template <typename Type>
typename DoubleLinkedList<Type>::ConstIterator DoubleLinkedList<Type>::rbegin() const noexcept {
    return crbegin();
}

template <typename Type>
typename DoubleLinkedList<Type>::ConstIterator DoubleLinkedList<Type>::rend() const noexcept {
    return crend();
}

template <typename Type>
typename DoubleLinkedList<Type>::ConstIterator DoubleLinkedList<Type>::crbegin() const noexcept {
    return ConstIterator(tail_.prev_node);
}

template <typename Type>
typename DoubleLinkedList<Type>::ConstIterator DoubleLinkedList<Type>::crend() const noexcept {
    return ConstIterator(const_cast<Node*>(&head_));
}

template <typename Type>
void DoubleLinkedList<Type>::PushFront(const Type& val) {
    Node* new_node = new Node(val, &head_, head_.next_node);
    head_.next_node->prev_node = new_node;
    head_.next_node = new_node;
    ++size_;
}

template <typename Type>
void DoubleLinkedList<Type>::PushBack(const Type& val) {
    Node* new_node = new Node(val, tail_.prev_node, &tail_);
    tail_.prev_node->next_node = new_node;
    tail_.prev_node = new_node;
    ++size_;
}

template <typename Type>
void DoubleLinkedList<Type>::PopFront() noexcept {
    assert(!IsEmpty() && "List is empty");
    Node* first_node = head_.next_node;
    head_.next_node = first_node->next_node;
    first_node->next_node->prev_node = &head_;
    delete first_node;
    --size_;
}

template <typename Type>
void DoubleLinkedList<Type>::PopBack() noexcept {
    assert(!IsEmpty() && "List is empty");
    Node* last_node = tail_.prev_node;
    tail_.prev_node = last_node->prev_node;
    last_node->prev_node->next_node = &tail_;
    delete last_node;
    --size_;
}

template <typename Type>
void DoubleLinkedList<Type>::Clear() noexcept {
    while (!IsEmpty()) {
        PopFront();
    }
}

template <typename Type>
size_t DoubleLinkedList<Type>::GetSize() const noexcept {
    return size_;
}

template <typename Type>
bool DoubleLinkedList<Type>::IsEmpty() const noexcept {
    return size_ == 0;
}

template <typename Type>
void DoubleLinkedList<Type>::swap(DoubleLinkedList& other) noexcept {
    std::swap(head_.next_node, other.head_.next_node);
    std::swap(tail_.prev_node, other.tail_.prev_node);
    std::swap(size_, other.size_);

    // Обновляем обратные ссылки
    if (head_.next_node != &tail_) {
        head_.next_node->prev_node = &head_;
    }
    if (tail_.prev_node != &head_) {
        tail_.prev_node->next_node = &tail_;
    }

    if (other.head_.next_node != &other.tail_) {
        other.head_.next_node->prev_node = &other.head_;
    }
    if (other.tail_.prev_node != &other.head_) {
        other.tail_.prev_node->next_node = &other.tail_;
    }
}

template <typename Type>
typename DoubleLinkedList<Type>::Iterator
DoubleLinkedList<Type>::Insert(ConstIterator pos, const Type& value) {
    assert(pos.node_ != nullptr && "Insert called with null iterator");
    Node* current = const_cast<Node*>(pos.node_);
    Node* new_node = new Node(value, current->prev_node, current);
    current->prev_node->next_node = new_node;
    current->prev_node = new_node;
    ++size_;
    return Iterator(new_node);
}

template <typename Type>
typename DoubleLinkedList<Type>::Iterator
DoubleLinkedList<Type>::Erase(ConstIterator pos) noexcept {
    assert(pos.node_ != nullptr && pos.node_ != &head_ && pos.node_ != &tail_ && "Erase called with invalid iterator");
    Node* current = const_cast<Node*>(pos.node_);
    Node* next_node = current->next_node;
    current->prev_node->next_node = current->next_node;
    current->next_node->prev_node = current->prev_node;
    delete current;
    --size_;
    return Iterator(next_node);
}

// Операторы сравнения
template <typename Type>
bool operator==(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    if (&lhs == &rhs) {
        return true;
    }
    return lhs.GetSize() == rhs.GetSize() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
bool operator!=(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    return !(lhs == rhs);
}

template <typename Type>
void swap(DoubleLinkedList<Type>& lhs, DoubleLinkedList<Type>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename Type>
bool operator<(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator<=(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    return !(rhs < lhs);
}

template <typename Type>
bool operator>(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    return rhs < lhs;
}

template <typename Type>
bool operator>=(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    return !(lhs < rhs);
}