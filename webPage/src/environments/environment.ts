// The file contents for the current environment will overwrite these during build.
// The build system defaults to the dev environment which uses `environment.ts`, but if you do
// `ng build --env=prod` or ng build --prod --configuration=production then `environment.prod.ts` will be used instead.
// The list of which env maps to which file can be found in `.angular-cli.json`.

export const environment = {
    production: false,
    UserPoolId: 'us-east-2_SRXGxiTAT', // Your user pool id here
    ClientId: '3pj39oc5h5qt89ctuibq9i30e0', // Your client id here
    ACCESS_TOKEN: 'accessToken',
    AUTHORIZATION: 'Authorization',
    ID_TOKEN:'idToken',
    // WORDPRESS
    wordpress:'http://photoeventfront.herokuapp.com/wp-json/wp/v2/',
    // APIS
    apiGatewayURI :  'https://kczrdq70b1.execute-api.us-east-2.amazonaws.com/dev/',

        //PAYU Sanbox
    payU    :'https://sandbox.api.payulatam.com/payments-api/4.0/service.cgi',
    payUCheckout:'https://sandbox.checkout.payulatam.com/ppp-web-gateway-payu/',
    payUAccount :{
        apiKey:'Q24dnGUVDXy92W5cOFJ9kszeOf',
        merchantId:'980768',
        accountId:'988766'
    },
    payUForm : {
        merchantId: 0,
        accountId: 0,
        description: "Test PAYU and PhotoEvent",
        currency: "COP",
        responseUrl: "https://d3ri3uhvzvztpt.cloudfront.net/client/response",
        test: "1",
        
        signature: "",
        tax: "0",
        taxReturnBase: "0",
        amount: '0',
        buyerEmail: '',
        confirmationUrl: '',
        referenceCode: "PURCHASE-123456",
      }
};


/**
 * https://photoevent   .auth.us-west-2.amazoncognito.com/login?response_type=code&client_id=vm1sp2u6gc1guv9h2k43vd34&redirect_uri=https://d3ri3uhvzvztpt.cloudfront.net/login
 * https://photoeventpro.auth.us-east-1.amazoncognito.com/login?response_type=code&client_id=fcvmvv7423fitvtc71grach54
 * 

            
*/
