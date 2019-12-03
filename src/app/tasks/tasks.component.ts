import { Component, OnInit } from '@angular/core';
import {Day01} from '../framework/day01';
import {Day02} from '../framework/day02';

@Component({
  selector: 'app-tasks',
  templateUrl: './tasks.component.html',
  styleUrls: ['./tasks.component.css']
})
export class TasksComponent implements OnInit {
  constructor() {
    new Day01().runDay();
    new Day02().runDay();
  }

  ngOnInit() {
  }
}
