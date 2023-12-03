#include <iostream>
#include <vector>
#include <map>

void translate_input(std::string &input) {
    std::map<std::string, std::string> map{
        {"one", "1"}, {"two", "2"}, {"three", "3"}, 
        {"four", "4"}, {"five", "5"}, {"six", "6"}, 
        {"seven", "7"}, {"eight", "8"}, {"nine", "9"}
    };
    std::size_t found;

    for (const auto& [key, value] : map) {
        if ((found = input.find(key)) != std::string::npos) {
            return translate_input(input.replace(found+1,key.size()-2, value));
        }
    }
}

int main(int argc, char **argv) {
    std::string calibration_value;
    std::vector<int> values;
    int sum_of_calibration_values = 0;

    while (std::cin >> calibration_value && calibration_value.size() > 0) {
        int v = 0;

        // Comment the line below to get part1 results        
        translate_input(calibration_value);
        
        for (char c : calibration_value) {
            if (isdigit(c)) {
                values.push_back(c-'0');
            }
        }

        if (values.size() > 0) {
            v = values.front();
            v *= 10;
            v += values.back();
        }

        sum_of_calibration_values += v;
        values.clear();
    }

    std::cout << "total: " << sum_of_calibration_values << std::endl;
    return 0;
}

