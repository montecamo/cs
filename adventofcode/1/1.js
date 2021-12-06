const part1 = (depths) => {
  let count = 0;
  let prev = depths[0];

  for (let i = 1; i < depths.length; i++) {
    if (depths[i] > prev) {
      count++;
    }

    prev = depths[i];
  }

  return count;
};

const groups = (depths) => {
  const sums = [];

  let a, b, c;

  for (let i = 0; i < depths.length - 2; i++) {
    a = depths[i];
    b = depths[i + 1];
    c = depths[i + 2];

    sums.push(a + b + c);
  }

  return sums;
};

const part2 = (data) => {
  const depths = groups(data);
  let count = 0;
  let prev = depths[0];

  for (let i = 1; i < depths.length; i++) {
    if (depths[i] > prev) {
      count++;
    }

    prev = depths[i];
  }

  return count;
};
