// This is an example of a React component that pushes data from the socket
// This is for instructional purposes only and will not compile as other main
// components are missing from the package. To download the complete UI package,
// visit its GitHub repo @ https://github.com/sisyn/react-portfolio-template. :)
SocketListeners() {
  let socket = io('//my-socketio-server.com:1336'); // use existing protocol, change port for your case
  socket.on('connect', function() {
    console.log('Socket.io connected');
  });

  socket.on('update', function(data) {
    console.log('Socket.io pushed update:');
    console.log(data);
    let parsed = {
      self: {
        ms: '',
        mac: '' // MAC Address not necessary, but why not help the NSA out a bit? loljk
      },
      data: {
        light: '',
        humidity: '',
        farenheit: '',
        centigrade: ''
      }
    };
    try {
      parsed = JSON.parse(data);
    } catch(e) {
      console.log('Oops, the socket sent something that was not JSON:');
      console.log(data);
    }

    // Do something with the data now that we're sure its JSON
    this.setState({
      espSocket: parsed
    });
  }.bind(this));
}
