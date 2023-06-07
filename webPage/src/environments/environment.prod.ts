




export const environment = {
  production: true,
  UserPoolId: 'us-east-1_x5vqAwau9', // Your user pool id here
  ClientId: 'fcvmvv7423fitvtc71grach54', // Your client id here
  ACCESS_TOKEN: 'accessToken',
  AUTHORIZATION: 'Authorization',
  ID_TOKEN: 'idToken',
  // WORDPRESS
  wordpress: 'http://photoeventfront.herokuapp.com/wp-json/wp/v2/',
  // APIS
  apiGatewayURI: 'https://8wlkaapjdk.execute-api.us-east-1.amazonaws.com/dev/',

  //PAYU Sanbox
  payU: 'https://sandbox.api.payulatam.com/payments-api/4.0/service.cgi',
  payUCheckout: 'https://sandbox.checkout.payulatam.com/ppp-web-gateway-payu/',
  payUAccount: {
    apiKey: 'Q24dnGUVDXy92W5cOFJ9kszeOf',
    merchantId: '980768',
    accountId: '988766'
  },
  payUForm: {
    merchantId: 0,
    accountId: 0,
    description: "Test PAYU and PhotoEvent",
    currency: "COP",
    responseUrl: "https://d3ri3uhvzvztpt.cloudfront.net/#/client/response",
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
