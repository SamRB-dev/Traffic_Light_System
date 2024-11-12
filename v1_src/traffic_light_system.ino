// Class - TrafficLights
class TrafficLights {
	public:
  		int digitalPin2G = 2;
		int digitalPin3Y = 3;
		int digitalPin4R = 4;
		int interval_1 = 30000; // 30s
		int interval_2 = 3000; // 3s
    void init() {
      pinMode(this->digitalPin2G, OUTPUT);
      pinMode(this->digitalPin3Y, OUTPUT);
      pinMode(this->digitalPin4R, OUTPUT);
    }

    void greenSignal() {
      digitalWrite(digitalPin2G, HIGH);
      delay(interval_1);
      digitalWrite(digitalPin2G, LOW);
    }

    void yellowSignal() {
      digitalWrite(digitalPin3Y, HIGH);
      delay(interval_2);
      digitalWrite(digitalPin3Y, LOW);
    }

    void redSignal() {
      digitalWrite(digitalPin4R, HIGH);
      delay(interval_1);
      digitalWrite(digitalPin4R, LOW);
    }
};

// Object
TrafficLights light;

void setup()
{
  light.init();
}

void loop()
{
  // Green Light
  light.greenSignal();
  
  // Yellow Light
  light.yellowSignal();
  
  // Red Light
  light.redSignal();
}