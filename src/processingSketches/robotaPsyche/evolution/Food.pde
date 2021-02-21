class Food {
  PVector location;

  Food (int x, int y) {
    location = new PVector(x, y);
  }

  PVector getLocation() {
    return (location.copy());
  }

  void display() {
    ellipse(location.x, location.y, 20, 20);
  }
}
