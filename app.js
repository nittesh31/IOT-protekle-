// function sayHi(name){
//     console.log('Hello' + ' ' + name)
// }

// sayHi('nitee')


// const http = require('http');

// const server = http.createServer((req, res) => {
//     if (req.url == '/'){
//         res.write('Hello Worl');
//         res.end();
//     }
// });

// server.on('connection')
// const port = 3000;

// server.listen(3000)

// console.log('listening on portport')

const http = require('http');

const hostname = '127.0.0.1';
const port = 3000;

const server = http.createServer((req, res) => {
  res.statusCode = 200;
//   res.setHeader('Content-Type', 'text/plain');
  res.end('Hello World');
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});