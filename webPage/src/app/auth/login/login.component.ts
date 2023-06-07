import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { AuthService } from '../../../service/auth.service';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
  message: string = '';
  email: string = '';
  givenName: string = '';
  nickname: string = '';
  password: string = '';
  public parameter: any;
  public isLogin: boolean;
  public alert$: Observable<string>= null;

  isPhotographer: boolean;
  constructor(
    public router: Router,
    private activateRoute: ActivatedRoute,
    //private authService: AuthService
  ) {
    //this.isLogin = this.authService.isAuth();
  
  }
  async ngOnInit() {
    //const basePath = this.pathLocationStrategy.getBaseHref();
    //const absolutePathWithParams = this.pathLocationStrategy.path();
    //console.log(" absolutePathWithParams ",absolutePathWithParams)
    //console.log("basePath ",basePath)
    /*
    var params = ('' + this.router.url).split("#")[1];
    if (params)
      this.socialLoguin(params.split("&"))

    await this.activateRoute.queryParams.subscribe(params => {
     // console.log(params)
      this.parameter = params;
    });
    //console.log("Esta logueado? ", this.isLogin);
    if (this.isLogin) {
      this.authService.loginPerson$.subscribe((person: any) => {
        if (person) {
          var roles = person['cognito:groups'];
          console.log("Roles " + roles);
          if (roles.indexOf('photographer') >= 0) {
            this.router.navigate(['/photographer']);
          } else {
            this.router.navigate(['/client']);
          };
        }
      });
    }*/
  }

  async onLogin() {
    /*
    this.alert$ = this.authService.errorLogin$;
    await this.authService.login(this.email, this.password);
    this.authService.loginPerson$.subscribe((person: any) => {
      if (person) {
        var roles = person['cognito:groups'];
        if (roles.indexOf('photographer') >= 0) {
          this.router.navigate(['/photographer']);
        } else {
          this.router.navigate(['/client']);
        };
      }
    });

*/

  }
  socialLoguin(params: any) {
    console.log(params.split("&"));
  }
  onSocialLoguin(){
   // this.authService
  }
}


/**
 * https://d3ri3uhvzvztpt.cloudfront.net/login?
 * access_token=eyJraWQiOiI1T0ZadzBoSllcL0VKSXp6U1pGNW80a0QwSmp2TlEwaGhHc0U1bUxPZmRxYz0iLCJhbGciOiJSUzI1NiJ9.eyJzdWIiOiIzNmJkZjNjYS0yNTU0LTRlYTItOGVjZC1hYmE2ZDcxNGM0NzAiLCJjb2duaXRvOmdyb3VwcyI6WyJ1cy1lYXN0LTFfdW1WanFYUlQ4X0dvb2dsZSJdLCJpc3MiOiJodHRwczpcL1wvY29nbml0by1pZHAudXMtZWFzdC0xLmFtYXpvbmF3cy5jb21cL3VzLWVhc3QtMV91bVZqcVhSVDgiLCJ2ZXJzaW9uIjoyLCJjbGllbnRfaWQiOiI2Z2RndnBkZ290ZHFsbGVmdXFiZTJpZTMwbCIsInRva2VuX3VzZSI6ImFjY2VzcyIsInNjb3BlIjoib3BlbmlkIGVtYWlsIiwiYXV0aF90aW1lIjoxNjY1Nzc2NTI4LCJleHAiOjE2NjU3ODAxMjgsImlhdCI6MTY2NTc3NjUyOCwianRpIjoiYmEzMDY5N2UtNWZkZi00MjAzLTk5ODQtMWVlZTBlMjU5NDMyIiwidXNlcm5hbWUiOiJHb29nbGVfMTEzODUwNzgxNzc5NzI4NzE3MzIxIn0.RAktKnbQnY1YJJW-VPMEDRWFJhH2Y2QqnHx4pblmM5dQtDqpjIgYR4XZ9z74gM-armO7VOtKFgy7F6sv4ySBS7FrKL_d5Q5ZP_aHw8rO-uoWN8XLimGSL0aHauNthAKAWDE6hElzzaW_JAuVYRsPr2h7BlaU7WYPwA6FAn6CbnbHyEQGPDgFgwEDqTExgtw1MXUF9XN-tDOoCZ35JyuotvLKWidCA-U_CHab0HBuzWl_rWOb2msHiVyUeWsS6K3LQTQQEydf2KbLqgt3R9mrb4EvII87nKTTjLT4IHWXdpmX0ZXnOeSMuubpKJtuKa7aHzGLa17M1tT5waBUdNPAhA
 * &id_token=
 * eyJraWQiOiJpckZJNHU0S29EaVQwQ3d0akExWVhUakVGYTVQU01sSXBxK2ZtRVRJQllzPSIsImFsZyI6IlJTMjU2In0.eyJhdF9oYXNoIjoiTzAzX0JqWnROVV9wZzdIeHlnZlIzZyIsInN1YiI6IjM2YmRmM2NhLTI1NTQtNGVhMi04ZWNkLWFiYTZkNzE0YzQ3MCIsImNvZ25pdG86Z3JvdXBzIjpbInVzLWVhc3QtMV91bVZqcVhSVDhfR29vZ2xlIl0sImVtYWlsX3ZlcmlmaWVkIjpmYWxzZSwiaXNzIjoiaHR0cHM6XC9cL2NvZ25pdG8taWRwLnVzLWVhc3QtMS5hbWF6b25hd3MuY29tXC91cy1lYXN0LTFfdW1WanFYUlQ4IiwiY29nbml0bzp1c2VybmFtZSI6Ikdvb2dsZV8xMTM4NTA3ODE3Nzk3Mjg3MTczMjEiLCJub25jZSI6IjYzZmdUMGZQTVJpd19nS2xmZWpBdDJOUlo0Q0NyTTBBcV9PdGRKVk52a1o0UnZZNFA5TmRtRXU0eHRWanpxcmFpUU9qMzhHVXJWcU5nS1BZbGEwNldPZWZRTklmLS0wX2ZPNy1jVEdaa0treEt5VkdLVWhIMGJRcmpQalB2RFgtV1VQUjBnb3VTWGJjR3hPcUNLYkZXYzBYUVNvRGpzMm5DSXpHa3RiTGt4OCIsImF1ZCI6IjZnZGd2cGRnb3RkcWxsZWZ1cWJlMmllMzBsIiwiaWRlbnRpdGllcyI6W3sidXNlcklkIjoiMTEzODUwNzgxNzc5NzI4NzE3MzIxIiwicHJvdmlkZXJOYW1lIjoiR29vZ2xlIiwicHJvdmlkZXJUeXBlIjoiR29vZ2xlIiwiaXNzdWVyIjpudWxsLCJwcmltYXJ5IjoidHJ1ZSIsImRhdGVDcmVhdGVkIjoiMTY2NTc3NjUyODUxMyJ9XSwidG9rZW5fdXNlIjoiaWQiLCJhdXRoX3RpbWUiOjE2NjU3NzY1MjgsImV4cCI6MTY2NTc4MDEyOCwiaWF0IjoxNjY1Nzc2NTI4LCJqdGkiOiIwYjhjOGRjNS0zOGFhLTQ4OTQtOGUzYS1jN2Y5OWYwYmU2OTYiLCJlbWFpbCI6InNlYmFzLnNzcC5yYWNlckBnbWFpbC5jb20ifQ.Uh_HhAxub17GEP8iAzUt2YSXN6WSLAzRXTaxZyeTeneYPjaLmQs0dPC7XrdqYp3AZnYq9ZIVHijMzZWs-e_XFvi5tl8s1ALa63K7J9tai6EpT27hA-DpeofDJnwWmBLLNa28ARQqDyP-ewoFV0lsHlxNau4w_l87reFbScbX7zPBo7mahSU-oER62zn_8QBIGW5zFOERxCuQrJku3iLSFRl575nUv8GjA0w34JfzITZgWwUCzJuGDAWdowPZRm19rHGyOcjPDbYKatVqKs9sDyOqgtOYtxMZ_QprbnrStpGy9hSN1vRNbj_f3mFSoIOEvKzKoHzKM1WJdvii_f8LVQ
 * &token_type=Bearer&expires_in=3600
 */