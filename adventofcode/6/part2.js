const fs = require("fs");
const { Worker } = require("worker_threads");
const _ = require("lodash");

const readData = () =>
  fs
    .readFileSync("./data-test.txt")
    .toString()
    .split(",")
    .filter(Boolean)
    .map(Number);

const calculate = (timers, days) =>
  new Promise((resolve, reject) => {
    const worker = new Worker("./worker.js", {
      workerData: {
        days,
        timers,
      },
    });

    worker.on("message", resolve);
    worker.on("error", reject);
  });

const data = readData();

const DAYS_CHUNK = 64;
const part2 = async (timers, days) => {
  if (days === 0) return timers.length;

  console.warn(days);

  const nextChunks = await Promise.all(
    _.chunk(timers, 10).map((p) => calculate(p, DAYS_CHUNK))
  );

  return Promise.all(
    nextChunks.map((chunk) => part2(chunk, days - DAYS_CHUNK))
  ).then(_.sum);
};

part2(data, 256).then(console.warn);

// Promise.all(promises)
//   .then((s) => _.sum(s))
//   .then(console.warn);
//calculate(timers).then((p) => console.warn(p.length));
