function sendData(led) {
  console.log("thiss is LED");
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("LEDState").innerHTML =
        this.responseText;
    }
  };
  xhttp.open("GET", "setLED?LEDstate=" + led, true);
  xhttp.send();
}
///////////////////////////////////////////
// zu sendende Daten:

//Bewegungsgeschwindigkeit mm/s ? 3 Stellen ?
// Ramping  Modi, 0=linear 1=x^2 2=x^1/2 3=
// Keyframes 
//
//
//

setInterval(function () {
  // Call a function repetatively with 2 Second interval
  getData();
}, 3000); //2000mSeconds update rate

var lastResponse;
// Funktion zur update aller Parameter
function getData() {
  var xhttp = new XMLHttpRequest();
  
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {

      var ResponseText = this.responseText;        //creates ResponsText als Primitve (als String behandelbar)
      // einteilung eines Strings in viele Infos
      //https://developer.mozilla.org/de/docs/Web/JavaScript/Reference/Global_Objects/String
      ///////////////////////////////////////////////////
      //PositionX: [0,1,2,3] in cm 
	  
	  // Ideen:
	  // MotorStatusX, 0=Stehen 1=movingVor 2=movingBack [4]
	  // 
	  // MODUS!!
	  // 
      console.log(ResponseText);


      document.getElementById("Position").innerHTML =
        String(ResponseText[0]+ResponseText[1]+ResponseText[2]+ResponseText[3]+" cm");
		
		if lastResponse[4] != ResponsText[4] {
			
			if (ResponseText[4] == 0) {
				document.getElementById("ButtonL").className="button button-off";
				document.getElementById("ButtonR").className="button button-off";			
			}
			if (ResponseText[4] == 1) {
				document.getElementById("ButtonL").className="button button-on";
				document.getElementById("ButtonR").className="button button-off";			
			}
			if (ResponseText[4] == 2) {
				document.getElementById("ButtonL").className="button button-off";
				document.getElementById("ButtonR").className="button button-on";			
			}
		}
		
		
		
		lastResponse = ResponsText;
    }
  };

  xhttp.open("GET", "getdata", true);
  xhttp.send();
}

function motor(richtung) {
  console.log("motor "+ richtung);
  var xhttp = new XMLHttpRequest();
  
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {

      document.getElementById("ButtonL").className="button button-on";
      
      document.getElementById("MStatusL").innerHTML =
        this.responseText;

      document.getElementById("ButtonR").className="button button-on";

      document.getElementById("MStatusR").innerHTML =
        this.responseText;
    }
  };
  
  xhttp.open("GET", "moveMotor?richtung=" + richtung, true);
  xhttp.send();

}
