/*
Given three points, P1, P2, P3

P1 is near the top left
P2 is some distance below P1
P3 is off to the right somewhere between the two

Define the vector V to go between P1 and P3
Find VM, the projection of V that lies on the line between P1 and P2


size(200,200);

// Given three points
PVector P1 = new PVector(20, 20);
PVector P2 = new PVector(20, 100);
PVector P3 = new PVector(50, 70);

circle(P1.x, P1.y, 20);
circle(P2.x, P2.y, 20);
circle(P3.x, P3.y, 20);

PVector B = PVector.sub(P2, P1);
pushMatrix();
translate(P1.x, P1.y);
line(0,0, B.x, B.y);
fill(255,0,0);
circle(B.x, B.y, 10);
popMatrix();

PVector V = PVector.sub(P3, P1);
pushMatrix();
translate(P1.x, P1.y);
line(0,0, V.x, V.y);
fill(255,0,0);
circle(V.x, V.y, 10);
popMatrix();

B.normalize();
PVector VM = B.mult(V.dot(B));
pushMatrix();
translate(P1.x, P1.y);
line(0,0, VM.x, VM.y);
fill(255,0,0);
circle(VM.x, VM.y, 10);
popMatrix();
