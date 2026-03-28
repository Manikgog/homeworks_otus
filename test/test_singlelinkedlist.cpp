#include "../src/singlelinked_list.h"
#include "gtest/gtest.h"




TEST(SingleLinkedList, empty) {
    // Arrange
    SingleLinkedList<int> list;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(list.Size(), 0);
    ASSERT_TRUE(list.IsEmpty());
}


TEST(SingleLinkedList, PushBack) {
    // Arrange
    const size_t count = 10;
    SingleLinkedList<size_t> list;

    // Act
    for (size_t i = 0; i < count; ++i) {
        list.PushBack(i);
    }

    // Assert
    ASSERT_EQ(list.Size(), count);
    ASSERT_FALSE(list.IsEmpty());
    for (size_t i = 0; i < list.Size(); ++i) {
        ASSERT_EQ(list[i], i);
    }

    list.PushBack(100);
    ASSERT_EQ(list[list.Size() - 1], 100);
}



TEST(SingleLinkedList, PushFront) {
    // Arrange
    const size_t count = 10;
    SingleLinkedList<size_t> list;

    // Act
    for (size_t i = 0; i < count; ++i) {
        list.PushBack(i);
    }

    // Assert
    list.PushFront(100);
    ASSERT_EQ(list[0], 100);
    ASSERT_EQ(list.Size(), 11);
}



TEST(SingleLinkedList, pop_back) {
    // Arrange
    SingleLinkedList<size_t> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Act

    // Assert
    auto it = list.begin();
    for (size_t i = 0; i < list.Size()-2; ++i) {
        it++;
    }
    list.EraseAfter(it);
    ASSERT_EQ(list[list.Size() - 1], 9);
    ASSERT_FALSE(list.IsEmpty());
}



TEST(SingleLinkedList, erase) {
    // Arrange
    SingleLinkedList<size_t> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Act

    // Assert
    size_t index_to_erase = 5;
    auto it = list.begin();
    for (size_t i = 0; i < index_to_erase - 1; ++i) {
        it++;
    }
    list.EraseAfter(it);
    ASSERT_EQ(list[5], 6);
    ASSERT_FALSE(list.IsEmpty());
}



TEST(SingleLinkedList, size) {
    // Arrange
    SingleLinkedList<size_t> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Act

    // Assert
    ASSERT_EQ(list.Size(), 11);
    ASSERT_FALSE(list.IsEmpty());
}


TEST(SingleLinkedList, begin) {
    // Arrange
    SingleLinkedList<size_t> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Act

    // Assert
    ASSERT_EQ(*list.begin(), 0);
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(*(++list.begin()), 1);
}


TEST(SingleLinkedList, clear) {
    // Arrange
    SingleLinkedList<size_t> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Act
    list.Clear();
    // Assert
    ASSERT_EQ(list.Size(), 0);
    ASSERT_TRUE(list.IsEmpty());
}


TEST(SingleLinkedList, swap) {
    // Arrange
    SingleLinkedList<size_t> list1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SingleLinkedList<size_t> list2{100, 200, 300};
    // Act
    list1.swap(list2);
    // Assert
    ASSERT_EQ(list1.Size(), 3);
    ASSERT_FALSE(list1.IsEmpty());
    for (size_t i = 0; i < list1.Size(); ++i) {
        ASSERT_EQ(list1[i], (i + 1) * 100);
    }

    ASSERT_EQ(list2.Size(), 11);
    ASSERT_FALSE(list2.IsEmpty());
    for (size_t i = 0; i < list2.Size(); ++i) {
        ASSERT_EQ(list2[i], i);
    }
}


TEST(SingleLinkedList, copy_constructor) {
    // Arrange
    SingleLinkedList<int> original{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Act
    SingleLinkedList<int> copy(original);

    // Assert
    ASSERT_EQ(original.Size(), copy.Size());

    for (size_t i = 0; i < original.Size(); ++i) {
        ASSERT_EQ(original[i], copy[i]);
    }

    copy.PushBack(100);
    ASSERT_EQ(original.Size(), 11);
    ASSERT_EQ(copy.Size(), 12);
    ASSERT_EQ(original[0], copy[0]);
}



TEST(SingleLinkedList, copy_assignment) {
    // Arrange
    SingleLinkedList<int> original{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    SingleLinkedList<int> copy{11, 12, 13, 14, 15};

    // Act
    copy = original;

    // Assert
    ASSERT_EQ(original.Size(), copy.Size());

    for (size_t i = 0; i < original.Size(); ++i) {
        ASSERT_EQ(original[i], copy[i]);
    }

    copy.PushBack(100);
    ASSERT_EQ(original.Size(), 11);
    ASSERT_EQ(copy.Size(), 12);
}

