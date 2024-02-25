#include <iostream>
#include <fstream>
#include <string>

int main() {
    //std::string filePath = "small_example_file.md";
    std::string filePath = "large_example_file.md"; // Specify the path to your file
    std::string marker = "---"; // delimiter
    std::ifstream file(filePath); // read / open the file

    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::string line;
    bool markerFound = false;

    // go line by line through the file
    while (std::getline(file, line)) {
        if (line.find(marker) != std::string::npos) {
            markerFound = true;
            continue; // skips printing marker line
        }
        if (markerFound) { // show content after the marker
            std::cout << line << std::endl;
        }
    }

    file.close();
    return 0;
}

