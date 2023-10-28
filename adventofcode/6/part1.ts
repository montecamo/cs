const calculate = require("./calculate");

const fs = require("fs");

const readData = () =>
  fs
    .readFileSync("./data.txt")
    .toString()
    .split(",")
    .filter(Boolean)
    .map(Number);

const part1 = () => {
  return calculate(readData(), 80).length;
};

console.warn("part", part1());
