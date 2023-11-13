#include "solution.h"
#include "file_generator.h"
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <utility>
#include <limits>
using namespace std;

void solution::BalancedMultimodalFusion(const string& start_file_name, long numbers_start_quantity){
    vector<fstream> file_arr(6);
    file_b_array_creation(file_arr);
    start_array_split(file_arr, start_file_name, numbers_start_quantity);
    while(!success_flag)
    {
        from_b_to_c_split(file_arr);
        if(!success_flag) {from_c_to_b_merge(file_arr);}
        else break;
    }
//    binaryToText("result.bin", "result.txt");
}


void solution::file_b_array_creation(vector<fstream> &file_arr){
    fstream file_b1, file_b2, file_b3, file_c1, file_c2, file_c3;

    file_arr.push_back(std::move(file_b1));
    file_arr.push_back(std::move(file_b2));
    file_arr.push_back(std::move(file_b3));
    file_arr.push_back(std::move(file_c1));
    file_arr.push_back(std::move(file_c2));
    file_arr.push_back(std::move(file_c3));

}

void solution::start_array_split(vector<fstream>& file_arr, const string& start_file_name, long numbers_start_quantity){
    file_b_open(file_arr);
    vector<int> sub_array;
    fstream start_file;
    int number, prev_number = -100, file_step = 0;
    start_file.open(start_file_name, ios::binary | ios::in);
    while(start_file.read((char*)&number, sizeof(int)))
    {
        sub_array.push_back(number);
        if(sub_array.size()==numbers_start_quantity/10)
        {
            if(sub_array.back() < prev_number)
            {
                file_step++;
                file_step = file_step%3;
            }
            sort(sub_array.begin(), sub_array.end());
            for(int i : sub_array)
            {
                file_arr[file_step].write((char*) &i, sizeof(int));
            }
            prev_number = sub_array.back();
            sub_array.clear();
        }
    }
    file_b_close(file_arr);
}

void solution::file_b_close(vector<fstream>& file_arr){

    for (int i = 0; i < 3; ++i) {
        file_arr[i].close();
    }
}

void solution::file_c_close(vector<fstream>& file_arr){
    for (int i = 3; i < 6; ++i) {
        file_arr[i].close();
    }
}

void solution::file_b_open(vector<fstream>& file_arr){
    file_arr[0].open("b1.bin", ios::binary | ios::out | ios::trunc);
    file_arr[1].open("b2.bin", ios::binary | ios::out | ios::trunc);
    file_arr[2].open("b3.bin", ios::binary | ios::out | ios::trunc);
}

void solution::file_c_open(vector<fstream>& file_arr){
    file_arr[3].open("c1.bin", ios::binary | ios::out | ios::trunc);
    file_arr[4].open("c2.bin", ios::binary | ios::out | ios::trunc);
    file_arr[5].open("c3.bin", ios::binary | ios::out | ios::trunc);
}

void solution::from_b_to_c_split(vector<fstream>& file_arr) {

    file_arr[0].open("b1.bin", ios::binary | ios::in | ios::out);
    file_arr[1].open("b2.bin", ios::binary | ios::in | ios::out);
    file_arr[2].open("b3.bin", ios::binary | ios::in | ios::out);

    file_c_open(file_arr);

    if(file_arr[0].is_open()&&file_arr[1].is_open()&&file_arr[2].is_open()&&file_arr[3].is_open()&&file_arr[4].is_open()&&file_arr[5].is_open())
    {
        int number, num1, num2, num3;
        if(isFileEmpty("b2.bin") && isFileEmpty("b3.bin")){
            success_flag = true;
            fstream result_file;
            result_file.open("result.bin", ios::binary | ios::out | ios::trunc);
            if (result_file.is_open()) {
                while(file_arr[0].read((char*)&number,sizeof(int)))
                {
                    result_file.write((char*) &number,sizeof(int));
                }

                result_file.close();
            } else {
                cout << "Result file opening error" <<endl;
            }
        }
        else {

            int file_step = 3;
            int temp_element = -1000000;

            file_arr[0].read((char*) &num1, sizeof(int));
            file_arr[1].read((char*) &num2, sizeof(int));
            file_arr[2].read((char*) &num3, sizeof(int));

            while(!file_arr[0].eof() || !file_arr[1].eof() || !file_arr[2].eof()){
                int min_value = std::numeric_limits<int>::max();

                if (!file_arr[0].eof()) min_value = min(min_value, num1);
                if (!file_arr[1].eof()) min_value = min(min_value, num2);
                if (!file_arr[2].eof()) min_value = min(min_value, num3);

                if (!file_arr[0].eof() && num1 == min_value) file_arr[0].read((char*) &num1, sizeof(int));
                else if (!file_arr[1].eof() && num2 == min_value) file_arr[1].read((char*) &num2, sizeof(int));
                else if (!file_arr[2].eof() && num3 == min_value) file_arr[2].read((char*) &num3, sizeof(int));

                if (temp_element > min_value) {
                    if (file_step == 5) file_step = 3;
                    else file_step++;
                }
                file_arr[file_step].write((char*) &min_value, sizeof(int));
                temp_element = min_value;
            }
        }
        file_c_close(file_arr);
        file_b_close(file_arr);
    }
    else
    {
        cout<<"\nFile b opening error!\n";
        return;
    }
}

void solution::from_c_to_b_merge(vector<fstream> &file_arr) {
    file_arr[3].open("c1.bin", ios::binary | ios::in | ios::out);
    file_arr[4].open("c2.bin", ios::binary | ios::in | ios::out);
    file_arr[5].open("c3.bin", ios::binary | ios::in | ios::out);

    file_b_open(file_arr);

    if(file_arr[0].is_open()&&file_arr[1].is_open()&&file_arr[2].is_open()&&file_arr[3].is_open()&&file_arr[4].is_open()&&file_arr[5].is_open())
    {
        int number, num1, num2, num3;
        if(isFileEmpty("c2.bin") && isFileEmpty("c3.bin")){
            success_flag = true;
            fstream result_file;
            result_file.open("result.bin", ios::binary | ios::out | ios::trunc);
            if (result_file.is_open()) {
                while(file_arr[3].read((char*)&number,sizeof(int)))
                {
                    result_file.write((char*) &number,sizeof(int));
//                    cout<<number<<endl;
                }

                result_file.close();
            } else {
                cout << "Result file opening error" <<endl;
            }
        }
        else {

            int file_step = 0;
            int temp_element = -1000000;

            file_arr[3].read((char*) &num1, sizeof(int));
            file_arr[4].read((char*) &num2, sizeof(int));
            file_arr[5].read((char*) &num3, sizeof(int));

            while(!file_arr[3].eof() || !file_arr[4].eof() || !file_arr[5].eof()){
                int min_value = std::numeric_limits<int>::max();

                if (!file_arr[3].eof()) min_value = min(min_value, num1);
                if (!file_arr[4].eof()) min_value = min(min_value, num2);
                if (!file_arr[5].eof()) min_value = min(min_value, num3);

                if (!file_arr[3].eof() && num1 == min_value) file_arr[3].read((char*) &num1, sizeof(int));
                else if (!file_arr[4].eof() && num2 == min_value) file_arr[4].read((char*) &num2, sizeof(int));
                else if (!file_arr[5].eof() && num3 == min_value) file_arr[5].read((char*) &num3, sizeof(int));

                if (temp_element > min_value) {
                    if (file_step == 2) file_step = 0;
                    else file_step++;
                }
                file_arr[file_step].write((char*) &min_value, sizeof(int));
//                cout<<min_value<<endl;
                temp_element = min_value;
            }
        }
        file_c_close(file_arr);
        file_b_close(file_arr);
    }
    else
    {
        cout<<"\nFile opening error!\n";
        return;
    }
}

void solution::binaryToText(const std::string& binaryFilename, const std::string& textFilename) {
    ifstream binaryFile(binaryFilename, ios::binary | ios::in);
    if (!binaryFile) {
        cout << "Bin file opening error" << endl;
        return;
    }

    ofstream textFile(textFilename);
    if (!textFile) {
        cout << "Text file opening error" << endl;
        return;
    }

    int ch;
    while (binaryFile.read((char*)&ch,sizeof(int))) {
        textFile << ch <<endl;
    }

    binaryFile.close();
    textFile.close();
}

bool solution::isFileEmpty(const string& filename) {
    ifstream file(filename, ios::ate);
    return file.tellg() == 0;
}