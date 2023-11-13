#include <iostream>
#include "fstream"
#include "file_generator.h"
#include "solution.h"
#include <chrono>
#include <limits>

using namespace std;

int main() {
    long start_quantity_of_numbers;
    bool exitRequested = false;

    do {
        try {
            cout << "Enter start element quantity (or 1 to exit):\n";
            cin >> start_quantity_of_numbers;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Invalid input. Please enter a valid number.");
            }

            if (start_quantity_of_numbers == 1) {
                cout << "Exiting the program." << endl;
                exitRequested = true;
            }
            else if (start_quantity_of_numbers > numeric_limits<long>::max()) {
                throw overflow_error("Input value is too large.");
            }
            else if (start_quantity_of_numbers < 10) {
                throw underflow_error("Input value is too low.");
            }
            else {
                string start_file_name = "numbers.bin";

                auto start = chrono::high_resolution_clock::now();
                file_generator numbers(start_file_name, start_quantity_of_numbers);
                solution unit1;
                cout << "Sorting...\n";
                unit1.BalancedMultimodalFusion(start_file_name, start_quantity_of_numbers);

                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                cout << "Time: " << duration.count() << " seconds" << endl;
            }
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }
    } while (!exitRequested);

    return 0;
}
