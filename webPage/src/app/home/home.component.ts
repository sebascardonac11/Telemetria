import { Component, OnInit } from '@angular/core';
import { MatDialog } from '@angular/material/dialog';
import { Router } from '@angular/router';
import { LoginComponent } from '../auth/login/login.component';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit{

  constructor( public dialog: MatDialog, private router: Router) {
  //  this.loginPerson$=this.auth.loginPerson$;
  }
  ngOnInit(): void {
    const dialogRef = this.dialog.open(LoginComponent);
  }
}
