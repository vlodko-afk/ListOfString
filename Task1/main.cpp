#include "StringList.h"
#include <iostream>

int main() {
    char** List;
    StringListInit(&List);

    StringListAdd(&List, "volodymyr");
    StringListAdd(&List, "dada");
    StringListAdd(&List, "close");
    StringListAdd(&List, "baby");
    StringListAdd(&List, "antony");
    char** mylist = nullptr;
    StringListAdd(nullptr, "hello");  // передали nullptr замість valid char** -> crash

    StringListRemoveDuplicates(List);
    StringListSort(List);

    for (int i = 0; i < StringListSize(List); ++i) {
        std::cout << List[i] << std::endl;
    }

    StringListReplaceInStrings(List, "lo", "too");
    StringListRemove(List, "dada");

    for (int i = 0; i < StringListSize(List); ++i) {
        std::cout << List[i] << std::endl;
    }

    StringListDestroy(&List);
    return 0;
}