class LinearSuspension
{
private:
    float valMin = 50.0;
    float valMax = 1024.0;
    uint8_t pinIn = A0;

public:
    LinearSuspension(uint8_t pinIn){
        this->pinIn = pinIn;
    }
    /**
     * In this function is calcultation the linear sensors.
     */
    float getLinearSensorInfo()
    {
        int pinInCC = analogRead(this->pinIn);
        float distance = 0;
        distance = (pinInCC - valMax) * (70.0) / (valMax - valMin);
        distance = distance * -1;
        return distance;
    }
};