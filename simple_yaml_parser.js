const fs = require('fs');
const readline = require('readline');

const filePath = 'large_example_file.md';
const marker = '---';
const fileStream = fs.createReadStream(filePath);

// read the file line by line by creating interface
// the interface is part of readline, and emits
// a `line` event for every line read in stream
const rl = readline.createInterface({
  input: fileStream,
  crlfDelay: Infinity // this deals w/ file endings - CR LF ('\r\n') = single line break
});

let markerFound = false;

rl.on('line', line => {
  if (line.includes(marker)) {
    markerFound = true;
  } else if (markerFound) {
    console.log(line);
  }
})
