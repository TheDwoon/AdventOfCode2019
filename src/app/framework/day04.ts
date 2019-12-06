import {AbstractDay} from './abstract-day';
import {BehaviorSubject, Observable} from 'rxjs';

export class Day04 extends AbstractDay<number[]> {
  constructor() {
    super();
  }

  getInput(): Observable<string> {
    return new BehaviorSubject('');
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
      if (!this.matchingDigits(arr, (occ) => occ >= 2) || !this.neverDecreasing(arr)) {
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
      if (!this.matchingDigits(arr, (occ) => occ === 2) || !this.neverDecreasing(arr)) {
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

  private matchingDigits(x: number[], ctValidator: (occ: number) => boolean) {
    let n = x[0];
    let occ = 1;
    for (let i = 1; i < 6; i++) {
      if (x[i] === n) {
        occ++;
      } else {
        if (ctValidator(occ)) {
          // something occurred more than twice and is about to change so it matches
          return true;
        } else {
          n = x[i];
          occ = 1;
        }
      }
    }

    return ctValidator(occ);
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
