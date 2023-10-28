const part1 = (commands) => {
  let depth = 0;
  let x = 0;

  commands.forEach(({ type, value }) => {
    switch (type) {
      case "forward":
        x += value;
        break;
      case "up":
        depth -= value;
        if (depth < 0) {
          depth = 0;
        }
        break;
      case "down":
        depth += value;
        break;
    }
  });

  return depth * x;
};

const part2 = (commands) => {
  let aim = 0;
  let depth = 0;
  let x = 0;

  commands.forEach(({ type, value }) => {
    switch (type) {
      case "forward":
        x += value;
        depth += aim * value;
        break;
      case "up":
        aim -= value;
        break;
      case "down":
        aim += value;
        break;
    }
  });

  return depth * x;
};

