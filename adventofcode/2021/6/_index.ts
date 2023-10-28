const fs = require("fs");

const readData = () =>
  fs
    .readFileSync("./data-test.txt")
    .toString()
    .split(",")
    .filter(Boolean)
    .map(Number);

class Lanternfish {
  timer: number;

  constructor(timer = 8) {
    this.timer = timer;

    return this;
  }

  tick() {
    this.timer--;
  }

  shouldGiveBirth() {
    return this.timer < 0;
  }

  giveBirth() {
    this.timer = 6;

    return new Lanternfish();
  }
}

const part1 = () => {
  const data: number[] = readData();

  let fishes = data.map((timer) => new Lanternfish(timer));

  for (let i = 0; i < 49; i++) {
    fishes.forEach((fish) => fish.tick());

    const newFishes = fishes
      .filter((fish) => fish.shouldGiveBirth())
      .map((fish) => fish.giveBirth());

    fishes = [...fishes, ...newFishes];
  }

  return fishes.length;
};

console.warn(part1());
