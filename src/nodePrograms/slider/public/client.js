var slider = document.getElementById("myRange");
var output = document.getElementById("sliderValue");

var dateID = document.getElementById("myDate");
var dateValue = document.getElementById("dateValue");

var socket = io();

output.innerHTML = slider.value; // Display the default slider value
dateValue.innerHTML = dateID.value; // Display the default slider value

// Update the current slider value (each time you drag the slider handle)
slider.oninput = function() {
  output.innerHTML = this.value;
  console.log(this.value);
	socket.emit('slider', this.value);
}

dateID.oninput = function() {
  dateValue.innerHTML = this.value;
  console.log(this.value);
	socket.emit('date', this.value);
}
