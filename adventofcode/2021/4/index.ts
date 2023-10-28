const fs = require("fs");

const readData = () =>
  fs.readFileSync("./data.txt").toString().split("\n\n").filter(Boolean);

const range = (end: number): number[] => Array.from(Array(end).keys());
const sum = (...args: number[]) => args.reduce((acc, num) => acc + num);

type Axis = number[];
type Board = Axis[];

const parseBoard = (board: string): Board =>
  board
    .split("\n")
    .filter(Boolean)
    .map((row) => row.trim().split(/\s+/).map(Number));

const invertBoard = (board: Board): Board =>
  range(board.length).map((index) => board.map((axis) => axis[index]));

const isAxisWon = (axis: Axis, numbers: number[]): boolean =>
  axis.every((n) => numbers.includes(n));

const isBoardWon = (board: Board, numbers: number[]) => {
  const predicate = (axis: Axis) => isAxisWon(axis, numbers);

  return board.some(predicate) || invertBoard(board).some(predicate);
};

const findBoardUnmarked = (board: Board, numbers: number[]): number[] =>
  board.map((axis) => axis.filter((n) => !numbers.includes(n))).flat();

const part1 = () => {
  const data = readData();

  const boards: Board[] = data.slice(1).map(parseBoard);
  const allNumbers = data[0].split(",").map(Number);

  for (let i = 0; i < allNumbers.length; i++) {
    const numbers = allNumbers.slice(0, i + 1);

    const wonBoards = boards.filter((board) => isBoardWon(board, numbers));

    if (wonBoards.length) {
      return sum(...findBoardUnmarked(wonBoards[0], numbers)) * numbers[i];
    }
  }

  throw new Error("No winners");
};

const part2 = () => {
  const data = readData();

  const allNumbers = data[0].split(",").map(Number);
  let boards: Board[] = data.slice(1).map(parseBoard);

  for (let i = 0; i < allNumbers.length; i++) {
    const numbers = allNumbers.slice(0, i + 1);

    const wonBoards = boards.filter((board) => isBoardWon(board, numbers));

    if (wonBoards.length === boards.length) {
      return sum(...findBoardUnmarked(wonBoards[0], numbers)) * numbers[i];
    }

    boards = boards.filter((board) => !wonBoards.includes(board));
  }

  throw new Error("No winners");
};
