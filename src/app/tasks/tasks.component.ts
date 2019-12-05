import { Component, OnInit } from '@angular/core';
import {Day01} from '../framework/day01';
import {Day02} from '../framework/day02';
import {Day03} from '../framework/day03';
import {Day04} from '../framework/day04';
import {Day05} from '../framework/day05';

@Component({
  selector: 'app-tasks',
  templateUrl: './tasks.component.html',
  styleUrls: ['./tasks.component.css']
})
export class TasksComponent implements OnInit {
  constructor() {
    // new Day01().runDay();
    // new Day02().runDay();
    // new Day03().runDay();
    // new Day04().runDay();
    new Day05().runDay();
  }

  ngOnInit() {
  }
}
