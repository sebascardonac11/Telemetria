export class Person {

    constructor(
        public id: string,
        public name: string,
        public email: string,
        public phone:string,
        public photos: string,
        public numbers: string,
        public texts: string,
    ) { }
    static FromJson(obj:any){
        return new Person(
        obj['mainkey'],
        obj['given_name'],
        obj['email'],
        obj['phone_number'],
        obj['photo'],
        obj['numbers'],
        obj['texts']
        )
   }

}