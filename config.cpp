const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

const float xCamera = WINDOW_WIDTH / 2;
const float yCamera = 300;
const float distScreen = 500;

sf::Vector3f camera = {-distScreen, xCamera - WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - yCamera};

sf::Vector3f light = {200.0, -400.0, 800.0};

const int light_power = 110;

Plane plane({0.0, 0.0, 1.0}, 0.0);
Sphere sp1(-100.0, 0.0, 80.0, 80.0, Color(56, 123, 76));
Sphere sp2(-200.0, -80.0, 40.0, 40.0, Color(173, 34, 87));
std::vector<Shape*> shapes = {&plane, &sp1, &sp2};