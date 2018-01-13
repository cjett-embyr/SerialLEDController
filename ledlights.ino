//define LED pins
const short BLUPIN=11;
const short REDPIN=10;
const short GRNPIN=9;

void setup(){
  //set pins to output mode
  pinMode(REDPIN,OUTPUT);
  pinMode(GRNPIN,OUTPUT);
  pinMode(BLUPIN,OUTPUT);
  //start communication with wifi board
  Serial.begin(115200);

}

void loop() {
  static float R=0;
  static float G=0;
  static float B=0;
  static int targetR = 255;
  static int targetG = 255;
  static int targetB = 255;
  static long targetTime = millis();
  static float deltaR = 0;//255.0/10000.0;
  static float deltaG = 0;//255.0/10000.0;
  static float deltaB = 0;//255.0/10000.0;
  static float lastChange = millis();
  if (Serial.available()){
    String command = Serial.readString();
    targetR = max(0,min(255,command.substring(0,3).toInt()));
    targetG = max(0,min(255,command.substring(3,6).toInt()));
    targetB = max(0,min(255,command.substring(6,9).toInt()));
    long targetMillis = command.substring(9).toInt();
    //Serial.flush();
    //Serial.println("I recieved "+command);
    if (targetMillis == 0){
      R=targetR;
      G=targetG;
      B=targetB;
      //Serial.println("Zeroh!");
      //Serial.println("R: "+String(R)+", G: "+String(G)+", B: "+String(B));
    }
    else
    {
      targetTime=millis()+targetMillis;
      //Serial.println(millis());
      //Serial.println(targetTime);
    }
  }
  if(millis() >= targetTime)
  {
    R=targetR;
    G=targetG;
    B=targetB;
  }
  else
  {
    R+=(targetR-R)/(targetTime-millis());
    G+=(targetG-G)/(targetTime-millis());
    B+=(targetB-B)/(targetTime-millis());
    //static long lastTime = millis();
    //if(millis()-lastTime>10)
    //{
      //Serial.println("R: "+String(R)+", G: "+String(G)+", B: "+String(B)+", "+millis()+", "+targetTime);
      
      //Serial.println("R: "+String((targetR-R)/(targetTime-millis()))+", G: "+String((targetG-G)/(targetTime-millis()))+", B: "+String((targetB-B)/(targetTime-millis())));
      //lastTime=millis();
    //}
  }
  
  analogWrite(REDPIN,R);
  analogWrite(GRNPIN,G);
  analogWrite(BLUPIN,B);
}
