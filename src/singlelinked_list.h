#pragma once

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <exception>
#include <stdexcept>

    template <typename Type>
class SingleLinkedList {

    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }
        Type value{};
        Node* next_node = nullptr;
    };

    template <typename ValueType>
    class BasicIterator {
        friend class SingleLinkedList;
        explicit BasicIterator(Node* node);

    public:
        using iterator_category = std::forward_iterator_tag;
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
        [[nodiscard]] reference operator*() const noexcept;
        [[nodiscard]] pointer operator->() const noexcept;

    private:
        Node* node_ = nullptr;
    };

public:
    SingleLinkedList() = default;
    SingleLinkedList(std::initializer_list<Type> values);
    SingleLinkedList(const SingleLinkedList& other);
    SingleLinkedList& operator=(const SingleLinkedList& rhs);
    ~SingleLinkedList();

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

    void PushFront(const Type& val);
    void PushBack(const Type& val);
    void Clear() noexcept;
    [[nodiscard]] size_t Size() const noexcept;
    [[nodiscard]] bool IsEmpty() const noexcept;
    void swap(SingleLinkedList& other) noexcept;

    [[nodiscard]] Iterator before_begin() noexcept;
    [[nodiscard]] ConstIterator cbefore_begin() const noexcept;
    [[nodiscard]] ConstIterator before_begin() const noexcept;

    Iterator InsertAfter(ConstIterator pos, const Type& value);
    void PopFront() noexcept;
    Iterator EraseAfter(ConstIterator pos) noexcept;

    Type& operator[](size_t i);
    const Type& operator[](size_t i) const;

private:
    Node head_;
    size_t size_ = 0;
};

// Реализации методов BasicIterator
template <typename Type>
template <typename ValueType>
SingleLinkedList<Type>::BasicIterator<ValueType>::BasicIterator(Node* node) : node_(node) {}

template <typename Type>
template <typename ValueType>
SingleLinkedList<Type>::BasicIterator<ValueType>::BasicIterator(const BasicIterator<Type>& other) noexcept
    : node_(other.node_) {}

template <typename Type>
template <typename ValueType>
bool SingleLinkedList<Type>::BasicIterator<ValueType>::operator==(const BasicIterator<const Type>& rhs) const noexcept {
    return node_ == rhs.node_;
}

template <typename Type>
template <typename ValueType>
bool SingleLinkedList<Type>::BasicIterator<ValueType>::operator!=(const BasicIterator<const Type>& rhs) const noexcept {
    return !(*this == rhs);
}

template <typename Type>
template <typename ValueType>
bool SingleLinkedList<Type>::BasicIterator<ValueType>::operator==(const BasicIterator<Type>& rhs) const noexcept {
    return node_ == rhs.node_;
}

template <typename Type>
template <typename ValueType>
bool SingleLinkedList<Type>::BasicIterator<ValueType>::operator!=(const BasicIterator<Type>& rhs) const noexcept {
    return !(*this == rhs);
}

template <typename Type>
template <typename ValueType>
typename SingleLinkedList<Type>::template BasicIterator<ValueType>&
SingleLinkedList<Type>::BasicIterator<ValueType>::operator++() noexcept {
//    assert(node_ != nullptr && "Attempt to increment past end");
    node_ = node_->next_node;
    return *this;
}

template <typename Type>
template <typename ValueType>
typename SingleLinkedList<Type>::template BasicIterator<ValueType>
SingleLinkedList<Type>::BasicIterator<ValueType>::operator++(int) noexcept {
//    assert(node_ != nullptr && "Attempt to increment past end");
    auto old_value = *this;
    node_ = node_->next_node;
    return old_value;
}

template <typename Type>
template <typename ValueType>
typename SingleLinkedList<Type>::template BasicIterator<ValueType>::reference
SingleLinkedList<Type>::BasicIterator<ValueType>::operator*() const noexcept {
//    assert(node_ != nullptr && "Dereferencing null iterator");
    return node_->value;
}

template <typename Type>
template <typename ValueType>
typename SingleLinkedList<Type>::template BasicIterator<ValueType>::pointer
SingleLinkedList<Type>::BasicIterator<ValueType>::operator->() const noexcept {
//    assert(node_ != nullptr && "Dereferencing null iterator");
    return &node_->value;
}

// Реализации методов SingleLinkedList
template <typename Type>
SingleLinkedList<Type>::SingleLinkedList(std::initializer_list<Type> values) {
    for (auto it = std::rbegin(values); it != std::rend(values); ++it) {
        PushFront(*it);
    }
}

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList(const SingleLinkedList& other) {
    SingleLinkedList tmp;
    Node** dst = &tmp.head_.next_node;
    for (const auto& value : other) {
        try {
            *dst = new Node(value, nullptr);
            dst = &((*dst)->next_node);
            ++tmp.size_;
        }
        catch (...) {
            tmp.Clear();
            throw;
        }
    }
    swap(tmp);
}

template <typename Type>
SingleLinkedList<Type>& SingleLinkedList<Type>::operator=(const SingleLinkedList& rhs) {
    if (this != &rhs) {
        SingleLinkedList tmp(rhs);
        swap(tmp);
    }
    return *this;
}

template <typename Type>
SingleLinkedList<Type>::~SingleLinkedList() {
    Clear();
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::begin() noexcept {
    return Iterator(head_.next_node);
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::end() noexcept {
    return Iterator(nullptr);
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::begin() const noexcept {
    return cbegin();
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::end() const noexcept {
    return cend();
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::cbegin() const noexcept {
    return ConstIterator(head_.next_node);
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::cend() const noexcept {
    return ConstIterator(nullptr);
}

template <typename Type>
void SingleLinkedList<Type>::PushFront(const Type& val) {
    head_.next_node = new Node(val, head_.next_node);
    ++size_;
}

template <typename Type>
void SingleLinkedList<Type>::PushBack(const Type& val) {
    auto last = cbegin();
    std::advance(last, Size() - 1);
    InsertAfter(last, val);
}


template <typename Type>
void SingleLinkedList<Type>::Clear() noexcept {
    while (head_.next_node != nullptr) {
        Node* tmp = head_.next_node;
        head_.next_node = tmp->next_node;
        delete tmp;
        --size_;
    }
}

template <typename Type>
size_t SingleLinkedList<Type>::Size() const noexcept {
    return size_;
}

template <typename Type>
bool SingleLinkedList<Type>::IsEmpty() const noexcept {
    return size_ == 0;
}

template <typename Type>
void SingleLinkedList<Type>::swap(SingleLinkedList& other) noexcept {
    std::swap(head_.next_node, other.head_.next_node);
    std::swap(size_, other.size_);
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::before_begin() noexcept {
    return Iterator(&head_);
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::cbefore_begin() const noexcept {
    return ConstIterator(const_cast<Node*>(&head_));
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::before_begin() const noexcept {
    return cbefore_begin();
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator
SingleLinkedList<Type>::InsertAfter(ConstIterator pos, const Type& value) {
//    assert(pos.node_ != nullptr && "InsertAfter called with null iterator");
    Node* new_node = new Node(value, pos.node_->next_node);
    pos.node_->next_node = new_node;
    ++size_;
    return Iterator(new_node);
}

template <typename Type>
void SingleLinkedList<Type>::PopFront() noexcept {
//    assert(head_.next_node != nullptr && "List is empty");
    if (head_.next_node != nullptr) {
        Node* first_node = head_.next_node;
        head_.next_node = first_node->next_node;
        delete first_node;
        --size_;
    }
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator
SingleLinkedList<Type>::EraseAfter(ConstIterator pos) noexcept {
//    assert(pos.node_ != nullptr && "EraseAfter called with null iterator");
//    assert(pos.node_->next_node != nullptr && "EraseAfter called at end of list");
    Node* node_to_delete = pos.node_->next_node;
    pos.node_->next_node = node_to_delete->next_node;
    delete node_to_delete;
    --size_;
    return Iterator(pos.node_->next_node);
}

template <typename Type>
Type& SingleLinkedList<Type>::operator[](size_t i)
{
    if (i >= this->size_) {
        throw std::out_of_range("SingleLinkedList out of range");
    }
    auto it = begin();
    std::advance(it, i);
    return *it;
}

template <typename Type>
const Type& SingleLinkedList<Type>::operator[](size_t i) const
{
    return this->operator[](i);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    if(lhs.begin() == rhs.begin()) {
        return true;
    }
    return lhs.Size() == rhs.Size() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs == rhs);
}

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(rhs < lhs);
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return rhs < lhs;
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs < rhs);
}