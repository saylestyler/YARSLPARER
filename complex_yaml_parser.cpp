#include <iostream>
#include <sys/mman.h> // For memory-mapped file functions
#include <sys/stat.h> // For file size retrieval
#include <fcntl.h> // For file descriptor functions
#include <unistd.h> // For close()
#include <cstring> // For strstr()

int main() {
    // const char* filePath = "small_example_file.md";
    const char* filePath = "large_example_file.md";
    int fd = open(filePath, O_RDONLY); // open in readonly mode

    if (fd == -1) {
        std::cerr << "Failed to open file\n"; return 1;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) { // get info abt file size
        std::cerr << "Failed to get file stats\n"; close(fd); return 1;
    }

    // memory mapping the file:
    // this came up when i was reading about both 
    // optimizing node, and it then came up for every other
    // programming language i came across, py, go, zig, etc.
    // can interact with files as if they were loaded into mem
    char* addr = static_cast<char*>(mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
    if (addr == MAP_FAILED) {
        std::cerr << "Failed to memory-map the file\n"; close(fd); return 1;
    }

    const char* marker = "---";
    char* markerPos = strstr(addr, marker); 
    if (markerPos != NULL) {
        // print contents after marker
        std::cout.write(markerPos + strlen(marker), sb.st_size - (markerPos - addr) - strlen(marker));
    } else {
        std::cout << "Marker not found\n";
    }

    munmap(addr, sb.st_size); // unmap file from mem
    close(fd); // close file descriptor
    return 0;
}

