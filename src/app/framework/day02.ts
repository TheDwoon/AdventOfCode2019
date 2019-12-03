import {AbstractDay} from './abstract-day';

export class Day02 extends AbstractDay<number[]> {
  constructor() {
    super();
  }

  getInput(): string {
    return '';
  }

  parseInput(input: string): number[] {
    return [1, 0, 0, 3, 1, 1, 2, 3, 1, 3, 4, 3, 1, 5, 0, 3, 2, 10, 1, 19, 1, 6, 19, 23, 1, 23, 13, 27, 2, 6, 27, 31, 1,
      5, 31, 35, 2, 10, 35, 39, 1, 6, 39, 43, 1, 13, 43, 47, 2, 47, 6, 51, 1, 51, 5, 55, 1, 55, 6, 59, 2, 59, 10, 63, 1,
      63, 6, 67, 2, 67, 10, 71, 1, 71, 9, 75, 2, 75, 10, 79, 1, 79, 5, 83, 2, 10, 83, 87, 1, 87, 6, 91, 2, 9, 91, 95, 1,
      95, 5, 99, 1, 5, 99, 103, 1, 103, 10, 107, 1, 9, 107, 111, 1, 6, 111, 115, 1, 115, 5, 119, 1, 10, 119, 123, 2, 6,
      123, 127, 2, 127, 6, 131, 1, 131, 2, 135, 1, 10, 135, 0, 99, 2, 0, 14, 0];
  }

  protected task1(input: number[]): void {
    const program = input.map(i => i);
    this.runProgram(program, 12, 2);

    console.log('T2 > Part 1', program[0]);
  }

  protected task2(input: number[]): void {
    let found = false;
    for (let p1 = 0; p1 < 100 && !found; p1++) {
      for (let p2 = 0; p2 < 100 && !found; p2++) {
        const program = input.map(i => i);
        this.runProgram(program, p1, p2);

        if (program[0] === 19690720) {
          console.log('T2 > Part 2', 100 * p1 + p2);
          found = true;
        }
      }
    }
  }

  private runProgram(program: number[], p1: number, p2: number) {
    // prepare program
    program[1] = p1;
    program[2] = p2;

    let icp = 0;
    while (this.executeInstruction(program, icp)) {
      icp += 4;
    }
  }

  private executeInstruction(program: number[], icp: number): boolean {
    const opCode = program[icp];
    const addr1 = program[icp + 1];
    const addr2 = program[icp + 2];
    const addrResult = program[icp + 3];

    if (opCode === 99) {
      return false;
    }

    const i1 = program[addr1];
    const i2 = program[addr2];

    let result = 0;
    switch (opCode) {
      case 1:
        result = i1 + i2;
        break;
      case 2:
        result = i1 * i2;
        break;
      default:
        console.log('We fucked up!');
        return false;
    }

    program[addrResult] = result;
    return true;
  }
}
