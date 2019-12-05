import {AbstractDay} from './abstract-day';

export class Day05 extends AbstractDay<number[]> {
  constructor() {
    super();
  }

  getInput(): string {
    return '';
  }

  parseInput(input: string): number[] {
    return [3, 225, 1, 225, 6, 6, 1100, 1, 238, 225, 104, 0, 2, 218, 57, 224, 101, -3828, 224, 224, 4, 224, 102, 8, 223,
      223, 1001, 224, 2, 224, 1, 223, 224, 223, 1102, 26, 25, 224, 1001, 224, -650, 224, 4, 224, 1002, 223, 8, 223, 101,
      7, 224, 224, 1, 223, 224, 223, 1102, 44, 37, 225, 1102, 51, 26, 225, 1102, 70, 94, 225, 1002, 188, 7, 224, 1001,
      224, -70, 224, 4, 224, 1002, 223, 8, 223, 1001, 224, 1, 224, 1, 223, 224, 223, 1101, 86, 70, 225, 1101, 80, 25,
      224, 101, -105, 224, 224, 4, 224, 102, 8, 223, 223, 101, 1, 224, 224, 1, 224, 223, 223, 101, 6, 91, 224, 1001,
      224, -92, 224, 4, 224, 102, 8, 223, 223, 101, 6, 224, 224, 1, 224, 223, 223, 1102, 61, 60, 225, 1001, 139, 81,
      224, 101, -142, 224, 224, 4, 224, 102, 8, 223, 223, 101, 1, 224, 224, 1, 223, 224, 223, 102, 40, 65, 224, 1001,
      224, -2800, 224, 4, 224, 1002, 223, 8, 223, 1001, 224, 3, 224, 1, 224, 223, 223, 1102, 72, 10, 225, 1101, 71, 21,
      225, 1, 62, 192, 224, 1001, 224, -47, 224, 4, 224, 1002, 223, 8, 223, 101, 7, 224, 224, 1, 224, 223, 223, 1101,
      76, 87, 225, 4, 223, 99, 0, 0, 0, 677, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1105, 0, 99999, 1105, 227, 247, 1105, 1,
      99999, 1005, 227, 99999, 1005, 0, 256, 1105, 1, 99999, 1106, 227, 99999, 1106, 0, 265, 1105, 1, 99999, 1006, 0,
      99999, 1006, 227, 274, 1105, 1, 99999, 1105, 1, 280, 1105, 1, 99999, 1, 225, 225, 225, 1101, 294, 0, 0, 105, 1,
      0, 1105, 1, 99999, 1106, 0, 300, 1105, 1, 99999, 1, 225, 225, 225, 1101, 314, 0, 0, 106, 0, 0, 1105, 1, 99999,
      108, 226, 677, 224, 102, 2, 223, 223, 1005, 224, 329, 1001, 223, 1, 223, 1107, 677, 226, 224, 102, 2, 223, 223,
      1006, 224, 344, 1001, 223, 1, 223, 7, 226, 677, 224, 1002, 223, 2, 223, 1005, 224, 359, 101, 1, 223, 223, 1007,
      226, 226, 224, 102, 2, 223, 223, 1005, 224, 374, 101, 1, 223, 223, 108, 677, 677, 224, 102, 2, 223, 223, 1006,
      224, 389, 1001, 223, 1, 223, 107, 677, 226, 224, 102, 2, 223, 223, 1006, 224, 404, 101, 1, 223, 223, 1108, 677,
      226, 224, 102, 2, 223, 223, 1006, 224, 419, 1001, 223, 1, 223, 1107, 677, 677, 224, 1002, 223, 2, 223, 1006, 224,
      434, 101, 1, 223, 223, 1007, 677, 677, 224, 102, 2, 223, 223, 1006, 224, 449, 1001, 223, 1, 223, 1108, 226, 677,
      224, 1002, 223, 2, 223, 1006, 224, 464, 101, 1, 223, 223, 7, 677, 226, 224, 102, 2, 223, 223, 1006, 224, 479, 101,
      1, 223, 223, 1008, 226, 226, 224, 102, 2, 223, 223, 1006, 224, 494, 101, 1, 223, 223, 1008, 226, 677, 224, 1002,
      223, 2, 223, 1005, 224, 509, 1001, 223, 1, 223, 1007, 677, 226, 224, 102, 2, 223, 223, 1005, 224, 524, 1001, 223,
      1, 223, 8, 226, 226, 224, 102, 2, 223, 223, 1006, 224, 539, 101, 1, 223, 223, 1108, 226, 226, 224, 1002, 223, 2,
      223, 1006, 224, 554, 101, 1, 223, 223, 107, 226, 226, 224, 1002, 223, 2, 223, 1005, 224, 569, 1001, 223, 1, 223,
      7, 226, 226, 224, 102, 2, 223, 223, 1005, 224, 584, 101, 1, 223, 223, 1008, 677, 677, 224, 1002, 223, 2, 223,
      1006, 224, 599, 1001, 223, 1, 223, 8, 226, 677, 224, 1002, 223, 2, 223, 1006, 224, 614, 1001, 223, 1, 223, 108,
      226, 226, 224, 1002, 223, 2, 223, 1006, 224, 629, 101, 1, 223, 223, 107, 677, 677, 224, 102, 2, 223, 223, 1005,
      224, 644, 1001, 223, 1, 223, 8, 677, 226, 224, 1002, 223, 2, 223, 1005, 224, 659, 1001, 223, 1, 223, 1107, 226,
      677, 224, 102, 2, 223, 223, 1005, 224, 674, 1001, 223, 1, 223, 4, 223, 99, 226];
  }

  protected task1(input: number[]): void {
    this.runProgram(input);
  }

  protected task2(input: number[]): void {
    this.runProgram(input);
  }

  private runProgram(memory: number[]): void {
    const program = {memory, icp: 0};
    let preIcp = 0;
    let postIcp = 0;
    do {
      preIcp = program.icp;
      this.runInstruction(program);
      postIcp = program.icp;
    } while (preIcp !== postIcp);
  }

  private runInstruction(program: IProgramm): void {
    const icp = program.icp;
    const opCode = program.memory[icp];
    const instCode = opCode % 100;
    const modes = Math.floor(opCode / 100);
    const modeA = this.getDigit(modes, 0);
    const modeB = this.getDigit(modes, 1);

    switch (instCode) {
      case 1: {
        const a = this.resolveParameter(program.memory, program.memory[icp + 1], modeA);
        const b = this.resolveParameter(program.memory, program.memory[icp + 2], modeB);
        const r = program.memory[icp + 3];
        program.memory[r] = a + b;
        program.icp += 4;
        return;
      }
      case 2: {
        const a = this.resolveParameter(program.memory, program.memory[icp + 1], modeA);
        const b = this.resolveParameter(program.memory, program.memory[icp + 2], modeB);
        const r = program.memory[icp + 3];
        program.memory[r] = a * b;
        program.icp += 4;
        return;
      }
      case 3: {
        const r = program.memory[icp + 1];
        program.memory[r] = this.resolveInput();
        program.icp += 2;
        return;
      }
      case 4: {
        const a = this.resolveParameter(program.memory, program.memory[icp + 1], modeA);
        this.resolveOutput(a);
        program.icp += 2;
        return;
      }
      case 99:
        return;
      default:
        throw new Error('Unknown instruction' + instCode);
    }
  }

  private getDigit(x: number, digit: number): number {
    const e = Math.pow(10, digit);
    return Math.floor(x / e) % 10;
  }

  private resolveParameter(program: number[], parameter: number, mode: number): number {
    if (mode === 0) {
      return program[parameter];
    } else if (mode === 1) {
      return parameter;
    } else {
      throw Error('Unexpected parameter mode: parameter=' + parameter + ' mode=' + mode);
    }
  }

  private resolveInput(): number {
    return 1;
  }

  private resolveOutput(x: number) {
    console.log('Program:', x);
  }
}

interface IProgramm {
  memory: number[];
  icp: number;
}
