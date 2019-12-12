import {AbstractDay} from './abstract-day';
import {HttpClient} from '@angular/common/http';
import {Observable} from 'rxjs';

export class Day06 extends AbstractDay<{[planet: string]: [string]}> {
  constructor(private readonly http: HttpClient) {
    super();
  }

  getInput(): Observable<string> {
    return this.http.get('/assets/input06.txt', {responseType: 'text'});
  }

  parseInput(input: string): { [p: string]: [string] } {
    const starMap: {[p: string]: [string]} = {};
    input.split('\n').map(line => line.split(')')).forEach(row => {
      if (row && row.length === 2) {
        const a = row[0];
        const b = row[1];
        if (!starMap[a]) {
          starMap[a] = [b];
        } else {
          starMap[a].push(b);
        }
      }
    });

    return starMap;
  }

  protected task1(starMap: { [p: string]: [string] }): void {
    const visit = [{planet: 'COM', orbits: 0}];
    let orbits = 0;
    while (visit.length > 0) {
      const currentPlanet = visit.splice(0, 1)[0];
      const orbitingPlanets = starMap[currentPlanet.planet];
      if (orbitingPlanets) {
        orbitingPlanets.forEach(planet => {
          visit.push({planet, orbits: currentPlanet.orbits + 1});
          orbits += currentPlanet.orbits + 1;
        });
      }
    }

    console.log('Day 6 > Task 1', orbits);
  }

  protected task2(starMap: { [p: string]: [string] }): void {
    const planets = Object.keys(starMap);
    const reachablePlanets = [...planets.map(planet => starMap[planet])];
    for (let i = 0; i < planets.length; i++) {
      const source = planets[i];
      const destinations = reachablePlanets[i];
      destinations.forEach(dest => {
        if (!starMap[dest]) {
          starMap[dest] = [source];
        } else {
          starMap[dest].push(source);
        }
      });
    }

    let hops;
    const visited = {};
    const visit = [{planet: 'YOU', steps: 0}];
    while (visit.length > 0 && Object.keys(visited).length < 100) {
      const current = visit.splice(0, 1)[0];
      visited[current.planet] = true;

      if (current.planet === 'SAN') {
        hops = current.steps;
        break;
      }

      starMap[current.planet].forEach(next => {
        if (!visited[next]) {
          visit.push({planet: next, steps: current.steps + 1});
        }
      });
    }

    console.log('Day 6 > Task 2', visited, visit);
  }
}
