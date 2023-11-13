#pragma once
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
using namespace std;

class file_generator{
    long elements_num;
    vector<int> file_data;
    string file_name;
    fstream file;

    void generate_data();

public:
    file_generator(const string& file_name, long e_num);
    void set_elements_num();
};
