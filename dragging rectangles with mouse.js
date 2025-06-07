// https://editor.p5js.org/
// Does the same as the Python code. 

let rect1, rect2;
let dragging = null;
let offsetX = 0;
let offsetY = 0;

function setup() {
  createCanvas(800, 600);
  
  // Määrittele suorakulmiot muodossa {x, y, w, h}
  rect1 = { x: 100, y: 100, w: 150, h: 100 };
  rect2 = { x: 300, y: 200, w: 150, h: 100 };
}

function draw() {
  background(255);

  // Piirrä suorakulmiot
  fill(255, 0, 0);
  rect(rect1.x, rect1.y, rect1.w, rect1.h);

  fill(0, 0, 255);
  rect(rect2.x, rect2.y, rect2.w, rect2.h);
}

function mousePressed() {
  if (isInside(mouseX, mouseY, rect1)) {
    dragging = rect1;
    offsetX = rect1.x - mouseX;
    offsetY = rect1.y - mouseY;
  } else if (isInside(mouseX, mouseY, rect2)) {
    dragging = rect2;
    offsetX = rect2.x - mouseX;
    offsetY = rect2.y - mouseY;
  }
}

function mouseReleased() {
  dragging = null;
}

function mouseDragged() {
  if (dragging !== null) {
    let oldX = dragging.x;
    let oldY = dragging.y;

    dragging.x = mouseX + offsetX;
    dragging.y = mouseY + offsetY;

    if (rectanglesOverlap(rect1, rect2)) {
      dragging.x = oldX;
      dragging.y = oldY;
    }
  }
}

// Apufunktiot
function isInside(x, y, r) {
  return x >= r.x && x <= r.x + r.w &&
         y >= r.y && y <= r.y + r.h;
}

function rectanglesOverlap(a, b) {
  return !(a.x + a.w <= b.x ||
           b.x + b.w <= a.x ||
           a.y + a.h <= b.y ||
           b.y + b.h <= a.y);
}
