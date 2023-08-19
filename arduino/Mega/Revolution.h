class Revolution {
private:
  byte cilindros = 1;          // (pulsos por revolucion = 2 * cylinders / cycles)
  byte tiempos = 4;            // tipo motor
  int refreshInterval = 250;   // milisegundos refresco
  volatile int RPMpulses = 0;  //Variable que almacena los pulsos en bujía
  int maxRevol=20000;                //Variable que almacena maximas revoluciones del motor
  long lastRPMRefresh = 0;

public:


  void addPulse() {
    if (this->RPMpulses > this->maxRevol) {
      this->RPMpulses = 0;
    } else {
      this->RPMpulses++;
    }
  }

long getLastRpmRefresh(){
  return this->lastRPMRefresh;
}
void setLastRpmRefresh(long millis){
  this->lastRPMRefresh = millis;
}
int getRefreshInterval(){
  return this->refreshInterval;
}

  /////////////////////////////////////////////////////
  // FUNCION ENCARGADA DE CALCULAR LAS REVILUCIONES  //
  /////////////////////////////////////////////////////

  int getRPM() {

    int RPM = int(RPMpulses * (60000.0 / float(this->refreshInterval)) * this->tiempos / this->cilindros / 2.0);  // calculate RPM
    this->RPMpulses = 0;  // reset pulse count to 0
    //RPM = min(maxRevol, RPM);  // don't return value larger than 9999

    return RPM;
  }
};