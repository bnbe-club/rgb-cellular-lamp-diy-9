//
// Basic colorwheel base color picker using HTML5/Javascript
//
const char* html_header =
"<head>"
"<style>"
"body {overflow:hidden;"
"background:black;}"
"</style>"
"</head>"
"<body>"
"<canvas id='wheelCanvas' onclick='getColor(event)'>"
"</canvas>"
"<script type='text/javascript'>"
"var canvas = document.getElementById('wheelCanvas');"
"var context = canvas.getContext('2d');"
"var imageObj = new Image();"
"imageObj.crossOrigin = 'anonymous';"
"var dimension;"
"if(window.innerHeight<window.innerWidth){"
"dimension=window.innerHeight;"
"} else {"
"dimension=window.innerWidth;"
"}"
"imageObj.onload = function() {"
"context.drawImage(imageObj,0,0,600,600,0,0,0.98*dimension,0.98*dimension);"
"};"
"imageObj.src = 'https://upload.wikimedia.org/wikipedia/commons/thumb/6/6d/RGB_color_wheel_360.svg/600px-RGB_color_wheel_360.svg.png';"
"canvas.height=window.innerHeight;"
"canvas.width=window.innerWidth;"
"function getColor(event) {"
"var canvas = document.getElementById('wheelCanvas');"
"var pixelData = canvas.getContext('2d').getImageData(event.offsetX, event.offsetY, 1, 1).data;"
"var form = document.createElement('form');"
"form.action='out';"
"var nr = document.createElement('input');"
"nr.name='R';"
"nr.value=pixelData[0].toString();"
"form.appendChild(nr);"
"var ng = document.createElement('input');"
"ng.name='G';"
"ng.value=pixelData[1].toString();"
"form.appendChild(ng);"
"var nb = document.createElement('input');"
"nb.name='B';"
"nb.value=pixelData[2].toString(); "
"form.appendChild(nb);"
"form.style.display='none';"
"document.body.appendChild(form);"
"form.submit();   "
"}"
"</script>"
"</body>";
