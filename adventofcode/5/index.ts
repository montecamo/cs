const fs = require("fs");

const readData = () =>
  fs.readFileSync("./data.txt").toString().split("\n").filter(Boolean);

type Point = [number, number];
type Line = Point[];
type TMap = number[][];

const range = (start: number, end: number): number[] =>
  start > end
    ? range(end, start).reverse()
    : Array.from(Array(end + 1).keys()).slice(start);

const deepArrayClone = (arr: any) => {
  if (!Array.isArray(arr)) {
    return arr;
  }

  return arr.map(deepArrayClone);
};

const parseEdges = (coordinates: string): [Point, Point] =>
  // @ts-expect-error: ok
  coordinates
    .split(" -> ")
    .map((coordinate) => coordinate.split(",").map(Number));

const buildLine = ([[x1, y1], [x2, y2]]: [Point, Point]): Line => {
  if (x1 === x2) {
    return range(y1, y2).map((y) => [x1, y]);
  }

  if (y1 === y2) {
    return range(x1, x2).map((x) => [x, y1]);
  }

  // part 2
  const r1 = range(x1, x2);
  const r2 = range(y1, y2);

  return r1.map((x, i) => [x, r2[i]]);
};

const drawLine = (map: TMap, line: Line) => {
  const nextMap = deepArrayClone(map);

  line.forEach(([x, y]) => {
    if (nextMap[x] === undefined) {
      nextMap[x] = [];
    }
    if (nextMap[x][y] === undefined) {
      nextMap[x][y] = 0;
    }

    nextMap[x][y] = nextMap[x][y] + 1;
  });

  // console.warn("next", nextMap);
  return nextMap;
};

const part = () => {
  const data = readData();

  const lines: Line[] = data.map(parseEdges).map(buildLine).filter(Boolean);

  const map = lines.reduce<TMap>((acc, line) => {
    return drawLine(acc, line);
  }, []);

  return map.reduce((acc, row) => acc + row.filter((n) => n > 1).length, 0);
};

