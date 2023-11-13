#include <random>
#include <iostream>
#include <algorithm>
#include "file_generator.h"
#include <fstream>
using namespace std;


file_generator::file_generator(const string& file_name, long e_num){
    file.open(file_name,ios::binary | ios::out | ios::trunc);
    if(!file){
        cout<<"Error!\nFile: "<<file_name<<" is not opened"<< endl;
    }
    else {
        elements_num = e_num;
        generate_data();
        file.close();
    }
}


void file_generator::generate_data() {
    for(int i = 0; i < elements_num; i++){
        random_device rd;
        uniform_int_distribution<int> dist(1, 1000);
        int element = dist(rd);
        file.write((char*) &element, sizeof(int));
    }
}

void file_generator::set_elements_num() {

}
