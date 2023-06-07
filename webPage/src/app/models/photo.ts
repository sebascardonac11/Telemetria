export class Photo {

     constructor(
          public event: string,
          public mainsort: string,
          public date: string,
          public photographer: string,
          public session: string,
          public url: string,
          public fileName: string,
          public cost: number,
          public numbers: string,
          public texts: string,
     ) {
     }
     static PhotoFromJson(obj: any) {
          return new Photo(
               obj['Event'],
               obj['PhotoID'],
               obj['Date'],
               obj['Photographer'],
               obj['SessionID'],
               obj['Location'],
               obj['FileName'],
               obj['cost'],
               obj['Numbers'],
               obj['Texts']
          )
     }

     get PhotoID() {
          return this.mainsort
     }
}

