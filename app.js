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

// const http = require('http');

// const hostname = '127.0.0.1';
// const port = 3000;

// const server = http.createServer((req, res) => {
//   res.statusCode = 200;
// //   res.setHeader('Content-Type', 'text/plain');
//   res.end('Hello World');
// });

// server.pos

// server.get((req, res) => {
//     if(req.url == '/dataReceive'){

//     }
// })

// server.listen(port, hostname, () => {
//   console.log(`Server running at http://${hostname}:${port}/`);
// });

const express = require('express');
const server = express();
const ejs = require('ejs');
const bodyParser = require('body-parser');
const token = 'secure';
const nodemailer = require('nodemailer');

var transporter = nodemailer.createTransport({
    service: 'gmail',
    auth: {
      user: 'raahulprem61@gmail.com',
      pass: '9943931111'
    }
  });
  
  var mailOptions = {
    from: 'raahulprem61@gmail.com',
    to: 'sabariiftt@gmail.com',
    subject: 'Notification from Toilet Management System',
    text: 'Your Toilet has to be cleaned'
  };


var sensorData = [
    {gas: 10, smell: 2, RGB: 15, IR: 10},
    {gas: 15, smell: 5, RGB: 5, IR: 1},
];


server.use(bodyParser.json());

var lachu=[
    {name:"sab"}
]
server.use(express.static('public'));
server.set('view engine', 'ejs');


// server.get('/index.html', function (req, res) {
//    res.sendFile( __dirname + "/" + "iot.html" )
// })

server.use(express.json());

server.get('/' , (req, res) => {
    res.send('Hello World')
})

server.post('/dataViewer', (req, res) => {
    const sensorData1 = {
        gas: req.body.gas,
        smell: req.body.smell, 
        RGB: req.body.RGB, 
        IR: req.body.IR
    }   

    if (sensorData1.smell < 10 || sensorData1.IR >25 || sensorData1.gas == "Gas detected"){
        transporter.sendMail(mailOptions, function(error, info){
            if (error) {
              console.log(error);
            } else {
              console.log('Email sent: ' + info.response);
            }
          });

    

    }
    
    sensorData.push(sensorData1);
    res.send(sensorData1);
    var count = sensorData.length;
    console.log(count)
})
server.post('/testdata', (req, res) => {
    const sensorData2 = {
        name:req.body.name
    }   
    lachu.push(sensorData2);
    res.send(sensorData2);
    
})
server.get('/testdata', (req, res) => {
    res.send(lachu)
})
server.get('/dataReceiver', (req, res) => {
    
    var count = sensorData.length -1;
    console.log(count);
    res.render('iot', {
        
        gas: sensorData[count].gas,
        smell: sensorData[count].smell, 
        RGB: sensorData[count].RGB, 
        IR: sensorData[count].IR
    });

})

server.post('/sample', function (req, res) {
    const body = req.body.Body
    res.set('Content-Type', 'text/plain')
    res.send(`You sent: ${body} to Express`)
  })
server.get('/sample', function (req, res) {
const body = req.body.Body
res.set('Content-Type', 'text/plain')
res.send(`You sent: ${body} to Express`)
})


server.get('/dataViewer', (req, res) => {
    res.send(sensorData)
})
server.listen(process.env.PORT||3000, () => console.log('Listening on port 3000....'))



// server.get('/', (req, res) => {
//     // check if verification token is correct
//     if (req.query.token !== token) {
//         return res.sendStatus(401);
//     }

//     // return challenge
//     return res.end(req.query.challenge);
// });


// server.post('/', (req, res) => {
//     // check if verification token is correct
//     if (req.query.token !== token) {
//         return res.sendStatus(401);
//     }

//     // print request body
//     console.log(req.body);

//     // return a text response
//     const data = {
//         responses: [
//             {
//                 type: 'text',
//                 elements: ['Hi', 'Hello']
//             }
//         ]
//     };

//     res.json(data);
// });
// module.exports.arr = sensorData;