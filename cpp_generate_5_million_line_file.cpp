#include <iostream>
#include <fstream>
#include <string>

// generate a file of n line numbers
int main() {
    // only fans stream jk Output File Stream
    // open, write, and create if it don't exist
    std::ofstream file("large_example_file.md");

    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    // long long creates a 64 bits of storage
    const long long numLines = 5120000;
    for (long long i = 1; i <= numLines; ++i) {
        // the << syntax is how u write w/ ofstream
        file << "This is line " << i << std::endl;
    }

    // release the file of its duty; a good p to .close()
    // to free up resources - happens automatically tho?
    file.close();
    std::cout << "Done writing " << numLines << " lines." << std::endl;

    return 0;
}

