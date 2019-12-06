import { Component, OnInit } from '@angular/core';
import {Day01} from '../framework/day01';
import {Day02} from '../framework/day02';
import {Day03} from '../framework/day03';
import {Day04} from '../framework/day04';
import {Day05} from '../framework/day05';
import {Day06} from '../framework/task06';
import {HttpClient} from '@angular/common/http';

@Component({
  selector: 'app-tasks',
  templateUrl: './tasks.component.html',
  styleUrls: ['./tasks.component.css']
})
export class TasksComponent implements OnInit {
  constructor(private readonly http: HttpClient) {
    // new Day01().runDay();
    // new Day02().runDay();
    // new Day03().runDay();
    // new Day04().runDay();
    // new Day05().runDay();
    new Day06(http).runDay();
  }

  ngOnInit() {
  }
}
