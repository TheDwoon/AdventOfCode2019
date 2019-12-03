export abstract class AbstractDay<T> {

  protected constructor() {
  }

  abstract getInput(): string;
  abstract parseInput(input: string): T;

  runDay() {
    this.runTask1();
    this.runTask2();
  }

  runTask1() {
    const input = this.parseInput(this.getInput());
    this.task1(input);
  }

  runTask2() {
    const input = this.parseInput(this.getInput());
    this.task2(input);
  }

  protected abstract task1(input: T): void;
  protected abstract task2(input: T): void;

  protected stepBarrier(): void {
    // Currently does nothing. Later this should halt the computation until the user wants to continue
  }
}
