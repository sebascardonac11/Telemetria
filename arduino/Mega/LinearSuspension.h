class LinearSuspension
{
private:
    float valMin = 50.0;
    float valMax = 1024.0;
    int pinInCC = analogRead(A0);

public:
    LinearSuspension(int pinInCC){
        this->pinInCC = pinInCC;
    }
    /**
     * In this function is calcultation the linear sensors.
     */
    float getLinearSensorInfo()
    {

        float distance = 0;
        distance = (pinInCC - valMax) * (70.0) / (valMax - valMin);
        distance = distance * -1;
        return distance;
    }
};