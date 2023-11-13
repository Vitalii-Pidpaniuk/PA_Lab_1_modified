#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <iostream>
#include <string>
#include "../lab_1/solution.h"
#include "../lab_1/file_generator.h"
#include <fstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Unittestlab1
{
    TEST_CLASS(Unittestlab1)
    {
    public:

        TEST_METHOD(TestFileBArrayCreation)
        {
            solution unit;
            vector<fstream> file_arr;
            unit.file_b_array_creation(file_arr);
            Assert::IsTrue(file_arr.size() == 6);
        }

        TEST_METHOD(TestIsFileEmpty)
        {
            fstream test_file;
            test_file.open("test_empty_file.bin", ios::binary | ios::out);
            solution unit;
            bool isEmpty = unit.isFileEmpty("test_empty_file.bin");
            test_file.close();
            Assert::IsTrue(isEmpty);
        }

        TEST_METHOD(TestIsResultFileSorted) {
            file_generator numbers("numbers.bin", 1000000);
            solution unit1;
            unit1.BalancedMultimodalFusion("numbers.bin", 1000000);
            fstream test_file;
            test_file.open("result.bin", ios::binary | ios::in);
            bool isSorted = true;
            int ch, prev_element = 0;
            while (test_file.read((char*)&ch, sizeof(int))) {
                if (prev_element > ch) isSorted = false;
            }
            test_file.close();
            Assert::IsTrue(isSorted);
        }
        
    };
}
