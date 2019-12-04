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
    const start = input[0];
    const end = input[1];
    for (let x = start; x <= end; x++) {
      const arr = this.to6DigitArray(x);

    }
  }

  protected task2(input: number[]): void {
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

  private matchingDigits(x: number[]): boolean {

    return true;
  }

  private neverDecreasing(x: number[]): boolean {
    return true;
  }
}
