# YARSLPARER

aka bottommatter yaml parser written in cpp

aka cppp p+ yarmr yarsl parer from using bing to generate a logo lol 

why put frontmatter at the top of ur file vs. at the bottom??????????? and why not write a program to parse said matter in cpp?

![cppyamllogo](https://github.com/saylestyler/bottommatter/assets/20520284/fa01d4ac-6b1e-4625-823b-3bf84f944427)

tyler's c++ playground, also this was just lazily (dirtily, even), copied to my site to be a blog post...

## bottommatter

i've been interested in how yaml parsers work since i got into the static site generator world. i thought for fun i'd make a yaml parser from scratch but put it at the bottom lol. i also wanted to learn c++ since it seems like every bad ass program every made that's super performance-y is written in it. i've made a js version of the c++ scripts i've created to test their speed against one another.

the program? exceedingly simple:

```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string inputFilePath = "large_example_file.md";
    std::string outputFilePath = "output_file_of_bottom_matter.txt";
    std::string marker = "---";
    // inny and outty file stream
    std::ifstream inputFile(inputFilePath);
    std::ofstream outputFile(outputFilePath);

    if (!inputFile.is_open()) {
        std::cerr << "couldn't open input file\n";
        return 1;
    }
    if (!outputFile.is_open()) {
        std::cerr << "couldn't open output file\n";
        return 1;
    }

    // note, bool is a built-in type but string is not (???) weird
    std::string line;
    bool markerFound = false;

    while (std::getline(inputFile, line)) {
        if (line.find(marker) != std::string::npos) {
            markerFound = true;
            continue; // dont include the `---`
        }

        if (markerFound) {
            // write to output file that any other program can read, eg js:
            // fs.readFile(path.join(__dirname, 'output_file.txt'), 'utf8', etc
            outputFile << line << std::endl;
            // also write to stdout for fun aka COUT aka QOOT aka MS QOOTY aka ok im done
            std::cout << line << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();
    return 0;
}
```

## c++ notes

### g++ vs. clang++

both are c++ compilers but come from diff projects and have subtle differences in design/perf/features

g++ = GNU Compiler Collection / gcc (this is what we used for haskell at an old job) is more portable & with extensive support for standards and extensions of c++

clang++ = faster, newer, rich output diagnostics, but both can achieve same speeds at runtime based on the optimization flags that are passed during compilation

(also side note, when u type `g++ --help` or `clang++ --help` the output is so massive that even at tiniest font allowed in iterm, it still has about 3 more pages before reaching the end:)

![beep](https://res.cloudinary.com/cloudimgts/image/upload/v1708829677/cli-upload/s63nyargze8oq8foih5o.png)

programs can be compiled by either of the compilers, but obvi pick n choose one. i've made two versions each with a diff compiler to compare speed. they both read two markdown files, one very large and one super small—10 lines vs 10,000.

1. compiled with g++

- small file execution time = `0.004s`
- large file execution time = `0.025s`

2. compiled with clang++

- small file execution time = `0.004s`
- large file execution time = `0.035s`

3. equivalent program in js

- small file execution time = `0.077s`
- large file execution time = `0.091`

pretty negligible looking if u r not a math person (me) but it's (i hope) 75% faster in c++ than js.

_*but waddabout my 5 million 120k line blog post?*_

heh obvi not gonna happen, but just to see :smirk:

clang++ = `19.5s`; g++ = `20.7s`; node = `33.4s`

66% faster without any flag optimizations during compile time

### -ooptimization flags

both have a trillion flags u can pass to optimize your code; some general ones are the `-0` levels where `-00` = no optimization, but the compiler tries to reduce compilation time; al the way up to `-03` which includes `-01,-02` and then some. And finally the macdaddy is `-0fast` which, it's in the name, and includes 123, and other stuff that may not even be standards compliant!

how do these affect the program u ask? from here on out i'm gonna just use clang++ bc i like the name more lole. optimizations come at the cost of slowing down compile time, introducing unexpected behavior (at the higher levels), and making debuggin harder.

<aside>
the following are just for the 5 million line file
</aside>

```txt
-0: 0.49s

-1: 0.48s (heh)

-2: 0.44s (hehe)

-3: 0.43s (lolllll)

-0fast: 0.43 (welp) (yr girl was expecting instantaneous after reading the docs, but also recongizes this task is p friggin simple, and i assume in complex-er programs it's a noticeable diff)
```

there's also tons more flags, but some ez ones are

*`-march=native`* - generate code optimized for the architecture of machine compiling the code.

*`flto`* - link time optimization; optimizations across all files at link time, vs just one at a time, finding even more ways to optimize.

*`funroll-loops`* - unrolls loops; i learned about this recently on a blog post from a chrome engineer which is just when u take a loop and rather than have `; i++` you do, or rather the compiler does, like `i += 2` which reduces the number of iterations by half; this already happens with `-02` and `-03`; upsides are reducing loop overhead aka checking and incrementing the iterator, better parallelism, better cache util; downsides are code size increasing and diminishing returns at some points, making the code slower rather than faster.

### node

node uses c++ and libuv under the hood for file system operations. it's fun to look at how it does this on the [node github repository](https://github.com/nodejs/node) looking in the `/lib` dir:

![beep](https://res.cloudinary.com/cloudimgts/image/upload/v1708837884/cli-upload/dypuogtb8dl1ptw6lots.png)

### bonus: bottom of the barrel

to create a file with 5 million lines i first just copied and pasted in vim over n over, then used pbcopy <; pbpaste >> - however at some point the clipboard got overloaded. voila, a shell script is born:

```sh
#!/bin/bash
file="large_example_file.md"
lines=5120000

for ((i=1; i<=lines; i++)); do
    echo "This is line $i" >> "$file"
done
```

for shits n giggles i wrote same thing in cpp, and boy was it WAYYYYYYYYY faster:

```cpp
#include <iostream>
#include <fstream>
#include <string>

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
```

the shell file took 1 minute 55 seconds whereas miss cpp did it in 8 seconds... wowwie

### in summary for now

cpp _iz_ way faster, and cooler sounding than the oversaturated js/ts/react/blah. and I might just re-write my lil static site generator that has a yaml parsing section in the build script to be cpp!
