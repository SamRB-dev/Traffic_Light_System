// Class - TrafficLights
class TrafficLights {
	public:
  		int digitalPin2G = 2;
		int digitalPin3Y = 3;
		int digitalPin4R = 4;
  		int dPedestrial5R = 5;
  		int dPedestrial6G = 6;
  		int dPushButton = 7;
		int interval_1 = 1000; //30s
		int interval_2 = 600; //3 to 6s
  		int interval_3 = 1000; //30s
  		unsigned long int timeInMilli = 0;
  		char isActive = 'G';
  
    void init() {
      pinMode(this->digitalPin2G, OUTPUT);
      pinMode(this->digitalPin3Y, OUTPUT);
      pinMode(this->digitalPin4R, OUTPUT);
      pinMode(this->dPedestrial5R, OUTPUT);
      pinMode(this->dPedestrial6G, OUTPUT);
      pinMode(this->dPushButton, INPUT);
      Serial.begin(9600);
    }

    void greenSignal(unsigned long int currentTime) {
      auto previousTime = this->timeInMilli;
      Serial.println(this->interval_1);
      digitalWrite(this->digitalPin2G, HIGH);
      digitalWrite(this->dPedestrial5R, HIGH);
      if (currentTime - previousTime >= this->interval_1){
      	digitalWrite(this->digitalPin2G, LOW);
      	digitalWrite(this->dPedestrial5R, LOW);
        this->timeInMilli = currentTime;
      	this->isActive = 'Y';
      }
    }

    void yellowSignal(unsigned long int currentTime) {
      digitalWrite(this->digitalPin3Y, HIGH);
      auto previousTime = this->timeInMilli;
      if (currentTime - previousTime >= this->interval_2) {
      	digitalWrite(this->digitalPin3Y, LOW);
        this->timeInMilli = currentTime;
      	this->isActive = 'R';
      }
    }

    void redSignal(unsigned long int currentTime) {
      auto previousTime = this->timeInMilli;
      digitalWrite(this->digitalPin4R, HIGH);
      digitalWrite(this->dPedestrial6G, HIGH);
      if (currentTime - previousTime >= this->interval_3) {
        digitalWrite(this->digitalPin4R, LOW);
        digitalWrite(this->dPedestrial6G, LOW);
        this->timeInMilli = currentTime;
        this->isActive = 'G';
      }
    }
};

// Object
TrafficLights light;
unsigned long int previousTime = 0;

void setup()
{
  light.init();
}

void loop()
{
  int buttonState = digitalRead(light.dPushButton);
  // Button Pressed
  if (buttonState == HIGH)
    light.interval_1 = 100;
  else
    light.interval_1 = 1000;
  unsigned long currentTime = millis();
  switch(light.isActive) {
    case 'G':
    	light.greenSignal(currentTime);
    	break;
    case 'Y':
    	light.yellowSignal(currentTime);
    	break;
    case 'R':
    	light.redSignal(currentTime);
    	break;
    default:
    	break;
  }
  previousTime = currentTime;
}