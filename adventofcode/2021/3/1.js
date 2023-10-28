const fs = require("fs");

const readData = () =>
  fs.readFileSync("./data.txt").toString().split("\n").filter(Boolean);

const findCommon = (data) =>
  data.filter(Boolean).length >= data.length / 2 ? 1 : 0;

const findLeast = (data) => findCommon(data) ^ 1;

const part1 = () => {
  const data = readData();

  let gamma = "";
  let epsilon = "";

  for (let i = 0; i < data[0].length; i++) {
    let nums = [];

    for (let j = 0; j < data.length; j++) {
      nums.push(Number(data[j][i]));
    }

    gamma += findCommon(nums);
    epsilon += findLeast(nums);
    nums = [];
  }

  return parseInt(gamma, 2) * parseInt(epsilon, 2);
};

const part2 = () => {
  const data = readData();

  const helper = (position, numbers, criteria) => {
    if (numbers.length === 1) return numbers[0];

    const bit = criteria(numbers.map((n) => n[position]).map(Number));

    return helper(
      position + 1,
      numbers.filter((n) => Number(n[position]) === bit),
      criteria
    );
  };

  const oxygen = helper(0, data, findCommon);
  const co2 = helper(0, data, findLeast);

  return parseInt(oxygen, 2) * parseInt(co2, 2);
};
