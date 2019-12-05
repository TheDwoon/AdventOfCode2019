import {AbstractDay} from './abstract-day';

export class Day04 extends AbstractDay<number[]> {
  constructor() {
    super();
  }

  getInput(): string {
    return '';
  }

  parseInput(input: string): number[] {
    return [172851, 675869];
  }

  protected task1(input: number[]): void {
    let possibleNumbers = 0;
    const start = input[0];
    const end = input[1];
    for (let x = start; x <= end; x++) {
      const arr = this.to6DigitArray(x);
      if (!this.matchingDigits(arr) || !this.neverDecreasing(arr)) {
        continue;
      }

      possibleNumbers++;
    }

    console.log('T4 > Part 1' , possibleNumbers);
  }

  protected task2(input: number[]): void {
    let possibleNumbers = 0;
    const start = input[0];
    const end = input[1];
    for (let x = start; x <= end; x++) {
      const arr = this.to6DigitArray(x);
      if (!this.matchingDigits(arr) || !this.matchingDigitsSpecial(arr) || !this.neverDecreasing(arr)) {
        continue;
      }

      possibleNumbers++;
    }

    console.log('T4 > Part 2' , possibleNumbers);
  }

  private to6DigitArray(x: number) {
    const res: number[] = [0, 0, 0, 0, 0, 0];
    for (let i = 0; i < 6; i++) {
      res[i] = this.getDigit(x, 5 - i);
    }

    return res;
  }

  private getDigit(x: number, digit: number): number {
    const e = Math.pow(10, digit);
    return Math.floor(x / e) % 10;
  }

  private testNumber(x: number) {
    const arr = this.to6DigitArray(x);
    const match = this.matchingDigitsSpecial(arr);
    console.log('???', x, arr, match);
  }

  private matchingDigits(x: number[]): boolean {
    const hist: number[] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    x.forEach(e => hist[e]++);
    return hist.reduce((prev, curr) => prev > curr ? prev : curr, 0) > 1;
  }

  private matchingDigitsSpecial(x: number[]): boolean {
    let n = x[0];
    let occ = 0;
    for (let i = 1; i < 6; i++) {
      if (x[i] === n) {
        occ++;
      } else {
        if (occ === 2) {
          // something occured twice and is about to change so it matches
          return true;
        } else {
          n = x[i];
          occ = 1;
        }
      }
    }

    return occ === 2;
  }

  private neverDecreasing(x: number[]): boolean {
    for (let i = 0; i < 5; i++) {
      if (x[i] > x[i + 1]) {
        return false;
      }
    }

    return true;
  }
}
