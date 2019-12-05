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
    const t0 = performance.now();
    const input = this.parseInput(this.getInput());
    const t1 = performance.now();
    this.task1(input);
    const t2 = performance.now();
    console.log('*** Performance Task 1 ***', 'Input:', t1 - t0, 'ms, Run', t2 - t1, 'ms, Total', t2 - t0, 'ms');
  }

  runTask2() {
    const t0 = performance.now();
    const input = this.parseInput(this.getInput());
    const t1 = performance.now();
    this.task2(input);
    const t2 = performance.now();
    console.log('*** Performance Task 2 ***', 'Input:', t1 - t0, 'ms, Run', t2 - t1, 'ms, Total', t2 - t0, 'ms');
  }

  protected abstract task1(input: T): void;
  protected abstract task2(input: T): void;

  protected stepBarrier(): void {
    // Currently does nothing. Later this should halt the computation until the user wants to continue
  }
}
