// C++ code
class PedestrianController {
	public:
  		int dPedestrial5R = 5;
    	int dPedestrial6G = 6;
  void init() {
  	Serial.begin(9600);
    pinMode(this->dPedestrial5R, OUTPUT);
    pinMode(this->dPedestrial6G, OUTPUT);
  }
  
  void pedestrianRedController(int mode = 1){
    if (mode == 1){
      digitalWrite(this->dPedestrial5R, HIGH);
    } else if (mode == 0){
      digitalWrite(this->dPedestrial5R, LOW);
    }  
  }
  
  void pedestrianGreenController(int mode = 1){
    if (mode == 1){
      digitalWrite(this->dPedestrial6G, HIGH);
    } else if (mode == 0){
      digitalWrite(this->dPedestrial6G, LOW);
    }  
  }

};

// object
PedestrianController plight;

// driver
void setup()
{
  plight.init();
}

void loop()
{
  int dataUART = Serial.read();
  switch(dataUART){
    case 11:
	    plight.pedestrianRedController();
    	break;
    case 10: 
    	plight.pedestrianRedController(0);
    	break;
    case 21:
    	plight.pedestrianGreenController();
    	break;
    case 20:
    	plight.pedestrianGreenController(0);
    	break;
    default:
    	break;
  }
}