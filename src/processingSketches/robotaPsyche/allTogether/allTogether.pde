// create objects for each ecosystem
MichaelsEcosystem system1 = new MichaelsEcosystem();


void setup(){
  size (1200, 800);
  system1.setup(); // call setup for each ecosystem
}

void draw() {
  background(200);
  system1.draw();// call draw for each ecosystem
}

void mouseClicked() {
  system1.mouseClicked(); // call mouseClicked for each ecosystem
}
