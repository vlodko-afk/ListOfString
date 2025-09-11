#include "pch.h"
#include "../Task1/StringList.cpp"

TEST(Test1, TestStringListAdd) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "volodymyr");
    StringListAdd(&List, "dada");
    StringListAdd(&List, "close");
    StringListAdd(&List, "baby");
    StringListAdd(&List, "antony");

    EXPECT_STREQ(List[0], "volodymyr");
    EXPECT_STREQ(List[1], "dada");
    EXPECT_STREQ(List[2], "close");
    EXPECT_STREQ(List[3], "baby");
    EXPECT_STREQ(List[4], "antony");
    
    StringListDestroy(&List);
}
TEST(TestRemove, RemoveExisting) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "volodymyr");
    StringListAdd(&List, "dada");
    StringListAdd(&List, "close");

    ASSERT_EQ(StringListSize(List), 3);

    //remove from middle
    StringListRemove(List, "dada");
    EXPECT_EQ(StringListSize(List), 2);
    EXPECT_STREQ(List[0], "volodymyr");
    EXPECT_STREQ(List[1], "close");

    StringListDestroy(&List);
}

TEST(TestRemove, RemoveNonExisting) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "alpha");
    StringListAdd(&List, "beta");

    ASSERT_EQ(StringListSize(List), 2);

    // remove not exsist element
    StringListRemove(List, "gamma");
    EXPECT_EQ(StringListSize(List), 2);
    EXPECT_STREQ(List[0], "alpha");
    EXPECT_STREQ(List[1], "beta");

    StringListDestroy(&List);
}
TEST(TestRemove, RemoveAllOccurrences) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "x");
    StringListAdd(&List, "y");
    StringListAdd(&List, "x");
    StringListAdd(&List, "z");
    StringListAdd(&List, "x");

    ASSERT_EQ(StringListSize(List), 5);

    // Переконуємося, що всі "x" будуть видалені
    StringListRemove(List, "x");
    EXPECT_EQ(StringListSize(List), 2);
    EXPECT_STREQ(List[0], "y");
    EXPECT_STREQ(List[1], "z");

    StringListDestroy(&List);
}

TEST(TestRemove, RemoveLastElement) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "one");
    StringListAdd(&List, "two");

    StringListRemove(List, "two");
    EXPECT_EQ(StringListSize(List), 1);
    EXPECT_STREQ(List[0], "one");

    StringListDestroy(&List);
}
TEST(Test3, TestStringSize) {
    char** List;
    // test size Nullptr list;
    StringListInit(&List);
    ASSERT_EQ(StringListSize(List), 0);

    //after push
    StringListAdd(&List, "volodymyr");
    StringListAdd(&List, "dada");
    StringListAdd(&List, "close");
    StringListAdd(&List, "baby");
    StringListAdd(&List, "antony");
    int size = StringListSize(List);
    ASSERT_EQ(StringListSize(List), 5);

    //after pop
    StringListRemove(List, "dada");
    ASSERT_EQ(StringListSize(List), 4);

    StringListDestroy(&List);
}

TEST(TestIndexOf, EmptyListOrNull) {
    //nullptr check
    EXPECT_EQ(StringListIndexOf(nullptr, "test"), -1);

    char** List;
    StringListInit(&List);

    // Empty List check
    EXPECT_EQ(StringListIndexOf(List, "anything"), -1);

    StringListDestroy(&List);
}

TEST(TestIndexOf, FindExistingElement) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "volodymyr");
    StringListAdd(&List, "dada");
    StringListAdd(&List, "close");
    StringListAdd(&List, "baby");

    // first element
    EXPECT_EQ(StringListIndexOf(List, "volodymyr"), 0);
    // middle element
    EXPECT_EQ(StringListIndexOf(List, "close"), 2);
    // last element
    EXPECT_EQ(StringListIndexOf(List, "baby"), 3);

    StringListDestroy(&List);
}

TEST(TestIndexOf, NonExistingElement) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "alpha");
    StringListAdd(&List, "beta");

    EXPECT_EQ(StringListIndexOf(List, "gamma"), -1);

    StringListDestroy(&List);
}

TEST(TestIndexOf, DuplicateElements) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "x");
    StringListAdd(&List, "y");
    StringListAdd(&List, "x");
    StringListAdd(&List, "z");

    //Duplicate element, must return position of first element
    EXPECT_EQ(StringListIndexOf(List, "x"), 0);

    StringListDestroy(&List);
}

TEST(TestRemoveDuplicates, EmptyList) {
    char** List;
    StringListInit(&List);

    StringListRemoveDuplicates(List);
    EXPECT_EQ(StringListSize(List), 0);

    StringListDestroy(&List);
}

TEST(TestRemoveDuplicates, NoDuplicates) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "alpha");
    StringListAdd(&List, "beta");
    StringListAdd(&List, "gamma");

    StringListRemoveDuplicates(List);

    EXPECT_EQ(StringListSize(List), 3);
    EXPECT_STREQ(List[0], "alpha");
    EXPECT_STREQ(List[1], "beta");
    EXPECT_STREQ(List[2], "gamma");

    StringListDestroy(&List);
}

TEST(TestRemoveDuplicates, WithDuplicates) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "volodymyr");
    StringListAdd(&List, "dada");
    StringListAdd(&List, "volodymyr");
    StringListAdd(&List, "close");
    StringListAdd(&List, "dada");
    StringListAdd(&List, "close");

    StringListRemoveDuplicates(List);

    EXPECT_EQ(StringListSize(List), 3);
    EXPECT_STREQ(List[0], "volodymyr");
    EXPECT_STREQ(List[1], "dada");
    EXPECT_STREQ(List[2], "close");

    StringListDestroy(&List);
}

TEST(TestRemoveDuplicates, AllDuplicates) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "same");
    StringListAdd(&List, "same");
    StringListAdd(&List, "same");
    StringListAdd(&List, "same");

    StringListRemoveDuplicates(List);

    EXPECT_EQ(StringListSize(List), 1);
    EXPECT_STREQ(List[0], "same");

    StringListDestroy(&List);
}

TEST(TestRemoveDuplicates, MixedPositions) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "x");
    StringListAdd(&List, "y");
    StringListAdd(&List, "x");
    StringListAdd(&List, "z");
    StringListAdd(&List, "y");

    StringListRemoveDuplicates(List);

    EXPECT_EQ(StringListSize(List), 3);
    EXPECT_STREQ(List[0], "x");
    EXPECT_STREQ(List[1], "y");
    EXPECT_STREQ(List[2], "z");

    StringListDestroy(&List);
}

TEST(TestReplaceInStrings, EmptyList) {
    char** List;
    StringListInit(&List);

    StringListReplaceInStrings(List, "a", "b");
    EXPECT_EQ(StringListSize(List), 0);

    StringListDestroy(&List);
}

TEST(TestReplaceInStrings, ReplaceExistingSubstring) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "hello world");
    StringListAdd(&List, "worldwide");
    StringListAdd(&List, "nothing here");

    StringListReplaceInStrings(List, "world", "planet");

    EXPECT_STREQ(List[0], "hello planet");
    EXPECT_STREQ(List[1], "planetwide");
    EXPECT_STREQ(List[2], "nothing here"); 

    StringListDestroy(&List);
}

TEST(TestReplaceInStrings, NoMatches) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "apple");
    StringListAdd(&List, "banana");

    StringListReplaceInStrings(List, "xyz", "zzz");

    EXPECT_STREQ(List[0], "apple");
    EXPECT_STREQ(List[1], "banana");

    StringListDestroy(&List);
}

TEST(TestReplaceInStrings, ReplaceAtBeginningAndEnd) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "catfish");
    StringListAdd(&List, "dogcat");
    StringListAdd(&List, "cat");

    StringListReplaceInStrings(List, "cat", "lion");

    EXPECT_STREQ(List[0], "lionfish"); 
    EXPECT_STREQ(List[1], "doglion");   
    EXPECT_STREQ(List[2], "lion");      

    StringListDestroy(&List);
}

TEST(TestReplaceInStrings, MultipleOccurrencesInDifferentStrings) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "foo bar foo");
    StringListAdd(&List, "foobar");
    StringListAdd(&List, "foo");

    StringListReplaceInStrings(List, "foo", "baz");

    EXPECT_STREQ(List[0], "baz bar foo"); 
    EXPECT_STREQ(List[1], "bazbar");
    EXPECT_STREQ(List[2], "baz");

    StringListDestroy(&List);
}

TEST(TestSort, EmptyListOrNull) {
    StringListSort(nullptr); 

    char** List;
    StringListInit(&List);

    StringListSort(List);
    EXPECT_EQ(StringListSize(List), 0);

    StringListDestroy(&List);
}

TEST(TestSort, ReverseOrder) {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "zeta");
    StringListAdd(&List, "gamma");
    StringListAdd(&List, "beta");
    StringListAdd(&List, "alpha");

    StringListSort(List);
    EXPECT_STREQ(List[0], "alpha");
    EXPECT_STREQ(List[1], "beta");
    EXPECT_STREQ(List[2], "gamma");
    EXPECT_STREQ(List[3], "zeta");

    StringListDestroy(&List);
}