import { Injectable } from '@angular/core';

import { HttpClient, HttpHeaders, HttpParams } from '@angular/common/http';
import { map, catchError } from 'rxjs/operators';
import { AuthenticationDetails, CognitoUser, CognitoUserPool } from 'amazon-cognito-identity-js';
import { BehaviorSubject } from 'rxjs';
import { environment } from 'src/environments/environment';
import { UserCognito ,Person } from '../app/models';

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  private isAuthPriv = false;
  private loginPersonpriv$: BehaviorSubject<UserCognito> = new BehaviorSubject<UserCognito>(null);
  private errorLoginpriv$: BehaviorSubject<string> = new BehaviorSubject<string>(null);
  private cognitoUser: any;
  private userPool: any;
  private poolData = {
    UserPoolId: environment.UserPoolId, // Your user pool id here
    ClientId: environment.ClientId // Your client id here
  };

  constructor(
    private hhtp: HttpClient,
    ) {
    this.userPool = new CognitoUserPool(this.poolData);
  }

  get loginPerson$() {
    return this.loginPersonpriv$.asObservable();
  }
  get errorLogin$(){
    return this.errorLoginpriv$.asObservable();
  }
  isAuth(): boolean {
    if (!this.isAuthPriv) {
      var currentUser = this.userPool.getCurrentUser();
      //console.log(this.userPool.getCurrentUser())
      if (currentUser != null) {
        currentUser.getSession((err: any, session: any) => {
          if (err) {
            alert(err.message || JSON.stringify(err));
          }
          this.isAuthPriv = session.isValid();
          console.log(session);
          if (this.isAuthPriv)
            this.loginPersonpriv$.next(session.idToken.payload);
        });
      }
    }
    return this.isAuthPriv;
  }
  getloginPerson(): Person {
    var token = this.getToken();
    var payload = token.split('.')[1];
    var payloadDecoded = atob(payload);
    var values = JSON.parse(payloadDecoded);
    var user:UserCognito=values;
    this.loginPersonpriv$.next(user)
    return Person.FromJson(values)
  }
  getToken(): string {
    for (let i = 0; i < localStorage.length; i++) {
      if (localStorage.key(i).endsWith(environment.ID_TOKEN) && localStorage.key(i).includes(environment.ClientId)) {
        return localStorage.getItem(localStorage.key(i));
      }
    }
    return null;
  }
  isPhotographer(): boolean {
    var token = this.getToken();
    var payload = token.split('.')[1];
    var payloadDecoded = atob(payload);
    var values = JSON.parse(payloadDecoded);
    var roles = values['cognito:groups'];
    var isPhotographer = roles.indexOf('photographer') < 0 ? false : true;
    return isPhotographer;
  }
  getUserAttribute() {
    console.log(this.cognitoUser)

    /*this.cognitoUser.getUserAttributes(function (err:any, result:any) {
      if (err) {
        alert(err.message || JSON.stringify(err));
        return;
      }
      console.log(result);
    });*/
  }
  async socialLoguin(){
    return this.hhtp.get<any>('https://photoeventqa.auth.us-east-1.amazoncognito.com/oauth2/authorize?identity_provider=Google&redirect_uri=https://d3ri3uhvzvztpt.cloudfront.net/login&response_type=TOKEN&client_id=6gdgvpdgotdqllefuqbe2ie30l&scope=email openid')
    .pipe(
      map(resp => {
      console.log(resp);
      /*var photos: Photo[] = [];
      resp.map((photo: any) => {
        photos.push(Photo.PhotoFromJson(photo))
      });
      this.photospriv$.next(photos);
      */
    }
    ));

  }
  async login(email: string, password: string) {
    // datos del user
    var userData = {
      Username: email,
      Pool: this.userPool
    }
    this.cognitoUser = new CognitoUser(userData);
    // credenciales
    var authData = {
      Username: email,
      Password: password
    }
    var authDetails = new AuthenticationDetails(authData);
    // login
    await this.cognitoUser.authenticateUser(authDetails, {
      onSuccess: (result: any) => {
        var token = result.getIdToken().getJwtToken();
        var payload = token.split('.')[1];
        var payloadDecoded = atob(payload);
        var values = JSON.parse(payloadDecoded);
        var roles = values['cognito:groups'];
        this.loginPersonpriv$.next(values);
      },
      onFailure: (err: any) => {
        this.errorLoginpriv$.next(err.message);
        return (err.message);
      }
    });
  }

  onSignOut(){
    var currentUser = this.userPool.getCurrentUser();
    console.log("CurrentUSer ", currentUser);
    currentUser.signOut();
  }
  
}

/**
 * https://d3ri3uhvzvztpt.cloudfront.net/login#
 * access_token=eyJraWQiOiJTYjNOK2lrMnA3cmlJXC85dWFcL0dhaTRTVitMY29wRE5UWEVcL200M0tcLzNrMD0iLCJhbGciOiJSUzI1NiJ9.eyJzdWIiOiJhNmU5NTY2ZC02YTIwLTQ0NzMtODRiMC0wMjFjMzZkMmJlZTkiLCJjb2duaXRvOmdyb3VwcyI6WyJ1cy1lYXN0LTFfNm84bWtybkE2X0dvb2dsZSJdLCJpc3MiOiJodHRwczpcL1wvY29nbml0by1pZHAudXMtZWFzdC0xLmFtYXpvbmF3cy5jb21cL3VzLWVhc3QtMV82bzhta3JuQTYiLCJ2ZXJzaW9uIjoyLCJjbGllbnRfaWQiOiI0YmRhajk4bHYzYXRqMTg4ZGp2bmkyamY4YyIsInRva2VuX3VzZSI6ImFjY2VzcyIsInNjb3BlIjoib3BlbmlkIGVtYWlsIiwiYXV0aF90aW1lIjoxNjY1NjA5Mzc0LCJleHAiOjE2NjU2MTI5NzQsImlhdCI6MTY2NTYwOTM3NCwianRpIjoiN2MyZDYzMTYtZThmZC00YzhiLThjN2YtOGVmYTYwY2ZhMmUxIiwidXNlcm5hbWUiOiJHb29nbGVfMTE2NDI1MTU2MTA5NTM5MjIwMjMxIn0.OSSzJzK42C0rdETDbWWB3HlxVox7_ATMxwiWCclma50WszV1RY7YapDLD0R0eB7_D6prYtDGxzmhv055dpzln38kopYmzZturkHqJvJN6u8oW2MOImehFNa2ZXlVw9vg9noaRcgO2FtPzVkAg3_rFNIoYgW5BOzjsBYTdLIO4DZKwUC-iDb4kJVDWfhwnUVm-asmQHg_Xpv5DkCIlRbipky095sr4Oet8W4mCQsknDFkPHGsw7yfH_rI2N3MCqM7jiS6cgrwCmVZn8w75-ZE0ZdK-RqldMpOpiv55XVhhJcaiA2MHAtJhJ4xz3nMRRvhE-VusSYSrpC8YiHb64Paug&
 * id_token=eyJraWQiOiIrajhVVmpwaXBKbm5yNDNhMXhUeVdxUFFFUjl0UjhKQWV4SDJqQ2lFRGpZPSIsImFsZyI6IlJTMjU2In0.eyJhdF9oYXNoIjoiQktwUm5jWEo1cjN6X0kyX1VvcXdldyIsInN1YiI6ImE2ZTk1NjZkLTZhMjAtNDQ3My04NGIwLTAyMWMzNmQyYmVlOSIsImNvZ25pdG86Z3JvdXBzIjpbInVzLWVhc3QtMV82bzhta3JuQTZfR29vZ2xlIl0sImVtYWlsX3ZlcmlmaWVkIjpmYWxzZSwiaXNzIjoiaHR0cHM6XC9cL2NvZ25pdG8taWRwLnVzLWVhc3QtMS5hbWF6b25hd3MuY29tXC91cy1lYXN0LTFfNm84bWtybkE2IiwiY29nbml0bzp1c2VybmFtZSI6Ikdvb2dsZV8xMTY0MjUxNTYxMDk1MzkyMjAyMzEiLCJub25jZSI6Im5qNE9QWUtOUlJWVzhMSnVhMnBIS2xSQndrWVlEYmpfbXVpSTFfQlJ4UGQzcGlPNlRoOE93bTZIZWIzVU40ZHNqb2YwVmlhMGlPRVRRcGdOQjZIdDlqZmcxMjdXQ2RkQjZabDdoNWV2NmZZeEtONjk5WF9pS1JrcmxPQ3R3bndudXp5TVVFRy1iN2RaSlhYU19kM2NQZ09TajkzQlpvMWVQaGEzdGVPQUVCOCIsImF1ZCI6IjRiZGFqOThsdjNhdGoxODhkanZuaTJqZjhjIiwiaWRlbnRpdGllcyI6W3sidXNlcklkIjoiMTE2NDI1MTU2MTA5NTM5MjIwMjMxIiwicHJvdmlkZXJOYW1lIjoiR29vZ2xlIiwicHJvdmlkZXJUeXBlIjoiR29vZ2xlIiwiaXNzdWVyIjpudWxsLCJwcmltYXJ5IjoidHJ1ZSIsImRhdGVDcmVhdGVkIjoiMTY2NTYwOTM3NDAyNyJ9XSwidG9rZW5fdXNlIjoiaWQiLCJhdXRoX3RpbWUiOjE2NjU2MDkzNzQsImV4cCI6MTY2NTYxMjk3NCwiaWF0IjoxNjY1NjA5Mzc0LCJqdGkiOiIxZjA1YTY5OS0yMDA0LTRlMTAtOGIzOC1lZDNlMDAwZDZhZGYiLCJlbWFpbCI6InNlYmFzY2FyZG9uYWMxMUBnbWFpbC5jb20ifQ.W3zRRfsFZkhE5tv3GfSab2td0jx1G27W6E7dQEOqhKcUWoE9LPO5lYBBfUeDo0Mn0XksMNz4X8ZLKp4q7kOn4PHLCOE9bSnyORnHiV0ay3wIhlKhY1sPbSPASta0Khw89OKUoMvrCxgkPkPcOQ3p8RQkrela5Mxn88DfouFAQncTBk_3jSR-ogpT62IXUFhciZj7JSJoRbl8KcGpdNTZ6WrNvycFqzCr80at-NKJJDTbG6Qm8T31puILirA_pQiG__GeDldY6jOjk6Ueivg8MG1CTi0dmovjzjdfbydYsywFbD3YaWVQWhwjOAra2B46iNAR5CxNY0xiLXwIW3Vcpg&
 * token_type=Bearer&
 * expires_in=3600
 */