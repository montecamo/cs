class Lanternfish {
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

const calculate = (timers, days) => {
  let fishes = timers.map((timer) => new Lanternfish(timer));

  for (let i = 0; i < days; i++) {
    fishes.forEach((fish) => fish.tick());

    const newFishes = fishes
      .filter((fish) => fish.shouldGiveBirth())
      .map((fish) => fish.giveBirth());

    fishes = [...fishes, ...newFishes];
  }

  return fishes.map(f => f.timer);
};

module.exports = calculate;
