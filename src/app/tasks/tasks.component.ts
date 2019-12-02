import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-tasks',
  templateUrl: './tasks.component.html',
  styleUrls: ['./tasks.component.css']
})
export class TasksComponent implements OnInit {
  private readonly t1Input = [62371, 94458, 78824, 57296, 84226,  133256,  101771,  61857,  120186,  132234,  50964,  97800,  81275, 109561,
    145666, 134029, 81625, 61963, 83820, 104210, 62264, 146376, 91889, 116069, 54596, 132877, 70341, 89983, 84627, 51617, 84846, 114416,
    132268, 136516, 104082, 133669, 86585, 96389, 111737, 51954, 132971, 84097, 66260, 133883, 84720, 51985, 61024, 55912, 125334, 69541,
    58806, 56014, 62563, 80799, 67284, 93971, 147238, 114830, 61376, 65096, 73498, 54792, 88590, 63225, 129226, 67872, 55563, 110467, 91120,
    100281, 148236, 121886, 75671, 124736, 90588, 52175, 140673, 71029, 73865, 142021, 140326, 77894, 61245, 96492, 136329, 132967, 83975,
    53082, 56784, 50024, 131154, 138517, 130787, 103334, 104287, 140644, 148945, 58945, 62153, 93488];
  private readonly t2Input = [1, 0, 0, 3, 1, 1, 2, 3, 1, 3, 4, 3, 1, 5, 0, 3, 2, 10, 1, 19, 1, 6, 19, 23, 1, 23, 13, 27, 2, 6, 27, 31, 1, 5,
    31, 35, 2, 10, 35, 39, 1, 6, 39, 43, 1, 13, 43, 47, 2, 47, 6, 51, 1, 51, 5, 55, 1, 55, 6, 59, 2, 59, 10, 63, 1, 63, 6, 67, 2, 67, 10,
    71, 1, 71, 9, 75, 2, 75, 10, 79, 1, 79, 5, 83, 2, 10, 83, 87, 1, 87, 6, 91, 2, 9, 91, 95, 1, 95, 5, 99, 1, 5, 99, 103, 1, 103, 10, 107,
    1, 9, 107, 111, 1, 6, 111, 115, 1, 115, 5, 119, 1, 10, 119, 123, 2, 6, 123, 127, 2, 127, 6, 131, 1, 131, 2, 135, 1, 10, 135, 0, 99, 2,
    0, 14, 0];

  constructor() {
    this.task1();
    this.task2();
  }

  private task1() {
    const s1 = this.t1Input.map(i => Math.floor(i / 3) - 2).reduce((sum, current) => sum + current, 0);
    const s2 = this.t1Input.map(i => this.computeFuelRequired(i)).reduce((sum, current) => sum + current, 0);

    console.log('T1 > Part 1', s1);
    console.log('T1 > Part 2', s2);
  }

  private computeFuelRequired(mass: number) {
    const fuel = Math.floor(mass / 3) - 2;
    if (fuel < 0) {
      return 0;
    } else {
      return fuel + this.computeFuelRequired(fuel);
    }
  }

  private task2() {
    let program = this.t2Input.map(i => i);
    this.runProgram(program, 12, 2);

    console.log('T2 > Part 1', program[0]);

    let found = false;
    for (let p1 = 0; p1 < 100 && !found; p1++) {
      for (let p2 = 0; p2 < 100 && !found; p2++) {
        program = this.t2Input.map(i => i);
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

  ngOnInit() {
  }

}
