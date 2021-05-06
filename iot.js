// sensorData = require('./app')

// document.getElementById("a").innerHTML = sensorData[0].gas
// console.log("hello world")

// const discord = require('discord.js');
// const webHook = new discord.WebhookClient('839818618997178368', 'o28BEc7UtOQgcWa1IPOKo6h6iE_1eY4boNIfZlZeZ_fG79_2FWpoi80E_MxkKhoqEKmV')

// webHook.send('Hey!! there team Protekle')

// https://discord.com/api/webhooks/839818618997178368/o28BEc7UtOQgcWa1IPOKo6h6iE_1eY4boNIfZlZeZ_fG79_2FWpoi80E_MxkKhoqEKmV

var nodemailer = require('nodemailer');

var transporter = nodemailer.createTransport({
  service: 'gmail',
  auth: {
    user: 'raahulprem61@gmail.com',
    pass: '9244331111'
  }
});

var mailOptions = {
  from: 'raahulprem61@gmail.com',
  to: 'sabaripssd@gmail.com',
  subject: 'Sending Email using Node.js',
  text: 'That was easy!'
};

transporter.sendMail(mailOptions, function(error, info){
  if (error) {
    console.log(error);
  } else {
    console.log('Email sent: ' + info.response);
  }
});