const fs = require("fs");

const data = fs
  .readFileSync(process.argv[2])
  .toString()
  .split("\n")
  .filter(Boolean);

let name = "";
let prev = "";
let log = "";

data.forEach((s) => {
  if (!prev) {
    prev = s;
    return;
  }

  if (prev[0] !== s[0] && prev[0] === "r") {
    name += String.fromCharCode(Number(s.match(/needle: (\d*)/)[1]));
    name += "  ";
    log += s.match(/letter: (\d+)/)[1];
    log += " ";
  }

  prev = s;
});

console.log(name);
console.log(log);
