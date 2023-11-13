#pragma once
#include "string"
#include <vector>
using namespace std;

class solution {
private:
    bool success_flag = false;
    int relative_shift;
public:
    void BalancedMultimodalFusion(const string& start_file_name, long numbers_start_quantity);
    void file_b_array_creation(vector<fstream>& file_arr);
    void start_array_split(vector<fstream>& file_arr, const string& start_file_name, long numbers_start_quantity);
    void file_b_close(vector<fstream>& file_arr);
    void file_c_close(vector<fstream>& file_arr);
    void file_b_open(vector<fstream>& file_arr);
    void file_c_open(vector<fstream>& file_arr);
    void from_b_to_c_split(vector<fstream>& file_arr);
    void from_c_to_b_merge(vector<fstream>& file_arr);
    void binaryToText(const std::string& binaryFilename, const std::string& textFilename);
    bool isFileEmpty(const string& filename);
};

