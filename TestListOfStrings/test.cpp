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
TEST(Test2, TestStringSize) {
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