var socket = io();


function ledON() {
  console.log ("sending a message to turn on the LED");
  socket.emit('ledON');
}

function ledOFF() {
  console.log ("sending a message to turn off the LED");
  socket.emit('ledOFf');
}

// read the data from the message that the server sent and change the
// background of the webpage based on the data in the message
socket.on('server-msg', function(msg) {
    console.log('msg:', msg);
    switch(msg) {
        case 'light':
            document.body.style.backgroundColor = 'white';
            console.log('white')
            break;
        case 'dark':
            document.body.style.backgroundColor = 'black';
            console.log('black');
            break;
    }
});
