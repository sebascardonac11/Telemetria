import { Component, OnInit } from '@angular/core';
import { Iuser } from './../../models/iuser';
import { environment } from 'src/environments/environment';
import { Router } from '@angular/router';
import { CognitoUserPool, CognitoUserAttribute } from 'amazon-cognito-identity-js';
import { FormControl, FormGroup, Validators } from '@angular/forms';

@Component({
  selector: 'app-signup',
  templateUrl: './signup.component.html',
  styleUrls: ['./signup.component.css']
})
export class SignupComponent implements OnInit {

    Form = new FormGroup({
      email: new FormControl('', Validators.required),
      givenName: new FormControl('', Validators.required),
      lastName: new FormControl('', Validators.required),
      phone_number: new FormControl('', Validators.required),
      password: new FormControl('', Validators.required)
    });
     ngOnInit(): void {}
    constructor(private router: Router) {}

    onRegister(): void {
      console.log(this.Form.value.email);

      
      var poolData = {
      	UserPoolId: environment.UserPoolId, // Your user pool id here
      	ClientId: environment.ClientId // Your client id here
      };
     var userPool = new CognitoUserPool(poolData);
     // set attributes
     var attrList = [];
         var iuser: Iuser = {
           email: this.Form.value.email,
           //last_name:this.lastName,
           given_name: this.Form.value.givenName,
           nickname: this.Form.value.email,
           phone_number:"+57"+this.Form.value.phone_number,
         }
         for (let key in iuser) {
           var attrData = {
             Name: key,
             Value: iuser[key]
           }
           var attr = new CognitoUserAttribute(attrData);
           attrList.push(attr);
           }
           console.log(attrList)
           // sign up
               userPool.signUp(this.Form.value.email, this.Form.value.password, attrList, [], (err, result) => {
                 if (err) {
                   alert(err.message || JSON.stringify(err));
                   return;
                 }
                 var newUser = result.user;
                 console.log(JSON.stringify(newUser));
                 alert('Te hemos enviado un correo para activar tu cuenta');
                 this.router.navigate(['/login']);
               });
               
     }
}
