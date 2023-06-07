export class Session {
     
     constructor(
          public eventID:string,
          public sessionID:string,
          public date:string,
          public photographer:string,
          public name:string,
          public description:string,
                    ){
          
     }
     static SessionFromJson(obj:any){
          return new Session(
          obj['mainkey'],
          obj['mainsort'],
          obj['date'],
          obj['photographer'],
          obj['name'],
          obj['description']
          )
     }
}

