import { Component } from '@angular/core';


import { HttpClient, HttpHeaders } from '@angular/common/http';
import { map, catchError } from 'rxjs/operators';
import { BehaviorSubject, Observable, of, Subject } from 'rxjs';


@Component({
  selector: 'app-poc',
  templateUrl: './poc.component.html',
  styleUrls: ['./poc.component.css']
})
export class PocComponent {

  public data = "Sin datos";
  constructor(
    private http: HttpClient
  ) { }

  async onSAG() {
    console.log("Onloguin")
    this.getLinearSensor().subscribe(
      (msg: string) => {
        console.log(msg)
        this.data = msg;
      }
    );;
  }

  getLinearSensor() {
    let headers = new HttpHeaders();
    headers = headers.set('Referrer-Policy', 'no-referrer');
  
    return this.http.get("192.168.58.102/linearSensor", { responseType: 'text' });

  }

}
