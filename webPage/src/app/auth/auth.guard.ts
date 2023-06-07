import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivate, RouterStateSnapshot, Router } from '@angular/router';

import { AuthService } from '../../service/auth.service';

@Injectable({
  providedIn: 'root',
})
export class AuthGuard implements CanActivate {

    constructor(private router: Router,private authService: AuthService) {}
    canActivate(
            route: ActivatedRouteSnapshot,
            state: RouterStateSnapshot): boolean
            {
                var isAuth = this.authService.isAuth();
                if(!isAuth) {
                    this.router.navigate(['/']);
                    return false;
                }
                return true;
            }
}
