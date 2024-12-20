// Classes
class RequiredAttributes {
  public:
    int digitalPin2G = 5;
    int digitalPin3Y = 6;
    int digitalPin4R = 7;
    int dPedestrial5R = 13;
    int dPedestrial6G = 12;
    int dPushButton = 11;
    int interval_1 = 1000; //30s
    int interval_2 = 500; //3 to 6s
    int interval_3 = 1000; //30s
    unsigned long int timeInMilli = 0;
    char isActive = 'R';
    char currentCycle = 'B';
  
};

class TrafficLights: public RequiredAttributes {
	public:
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
      digitalWrite(this->digitalPin2G, HIGH);
      digitalWrite(this->dPedestrial5R, HIGH);
      if (currentTime - previousTime >= this->interval_1){
      	digitalWrite(this->digitalPin2G, LOW);
      	digitalWrite(this->dPedestrial5R, LOW);
        this->timeInMilli = currentTime;
      	this->isActive = 'Y';
        this->currentCycle = 'F';
      }
    }

    void yellowSignal(unsigned long int currentTime) {
      digitalWrite(this->digitalPin3Y, HIGH);
      auto previousTime = this->timeInMilli;
      if (currentTime - previousTime >= this->interval_2) {
      	digitalWrite(this->digitalPin3Y, LOW);
        this->timeInMilli = currentTime;
        if (this->currentCycle == 'F') 
      		this->isActive = 'R';
        else if (this->currentCycle == 'B')
          	this->isActive = 'G';

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
        this->isActive = 'Y';
        this->currentCycle = 'B';
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
  if (buttonState == HIGH && light.isActive == 'G'){
    light.interval_1 = 100;
    Serial.write(1);
  }
  else {
    light.interval_1 = 1000;
    Serial.write(0);
  }
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