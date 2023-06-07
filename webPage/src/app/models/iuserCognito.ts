export type UserCognito = {
    [cognito in 'groups']: string;
} & {
    sub: string; 
    given_name: string;
    last_name: string;
    nickname: string;
    phone_number: string;
    email_verified: string;
    email:string;
    iss: string;
    "cognito:username": string;
    origin_jti: string;
    aud: string;
    event_id: string;
    token_use: string;

};
/**
 * {
    "sub": "e35c5f6c-3d14-419d-acd6-703c2f58f814",
    "cognito:groups": [
        "client"
    ],
    "email_verified": true,
    "iss": "https://cognito-idp.us-west-2.amazonaws.com/us-west-2_VCd4MZ9X8",
    "phone_number_verified": false,
    "cognito:username": "sebascardonac84",
    "given_name": "Sebastian2",
    "origin_jti": "aba269cf-41e0-4e51-9a48-921ac40455c2",
    "aud": "vm1sp2u6gc1guv9h2k43vd34",
    "event_id": "4d28ca80-5b26-4f1d-878d-d24634112607",
    "token_use": "id",
    "auth_time": 1665157124,
    "nickname": "sebascardonac84",
    "phone_number": "+573147138768",
    "exp": 1665160724,
    "iat": 1665157124,
    "jti": "4bb01762-58a1-42a6-82c2-42863930c26f",
    "email": "sebas.ssp.racer@gmail.com"
}
 */