#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h> // Для Sleep

using namespace std;

class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

class Snake {
private:
    vector<Point> body;
    char direction;
    bool growing;
public:
    Snake() {
        body.push_back(Point(10, 10));
        direction = 'r';
        growing = false;
    }

    void changeDirection(char dir) {
        direction = dir;
    }

    void move() {
        Point nextPosition = body[0];
        switch(direction) {
            case 'u': nextPosition.y--; break;
            case 'd': nextPosition.y++; break;
            case 'l': nextPosition.x--; break;
            case 'r': nextPosition.x++; break;
        }
        body.insert(body.begin(), nextPosition);
        if (!growing) {
            body.pop_back();
        } else {
            growing = false;
        }
    }

    bool checkCollisionWithSelf() {
        for (int i = 1; i < body.size(); i++) {
            if (body[0].x == body[i].x && body[0].y == body[i].y) {
                return true;
            }
        }
        return false;
    }

    bool checkCollisionWithBorders(int width, int height) {
        if (body[0].x < 0 || body[0].x >= width || body[0].y < 0 || body[0].y >= height) {
            return true;
        }
        return false;
    }

    void grow() {
        growing = true;
    }

    vector<Point>& getBody() {
        return body;
    }
};

class Food {
public:
    Point position;

    Food() {
        generateNewFood();
    }

    void generateNewFood() {
        position.x = rand() % 20;
        position.y = rand() % 20;
    }
};

class Game {
private:
    Snake snake;
    Food food;
    bool isGameOver;
    const int width = 20;
    const int height = 20;
public:
    Game() : isGameOver(false) {
        srand(time(0));
    }

    void draw() {
        system("cls");
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                bool isDrawn = false;
                if (x == food.position.x && y == food.position.y) {
                    cout << "F";
                    isDrawn = true;
                } else {
                    for (auto& part : snake.getBody()) {
                        if (part.x == x && part.y == y) {
                            cout << "O";
                            isDrawn = true;
                            break;
                        }
                    }
                }
                if (!isDrawn) cout << ".";
            }
            cout << endl;
        }
    }

    void update() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'w': snake.changeDirection('u'); break;
                case 's': snake.changeDirection('d'); break;
                case 'a': snake.changeDirection('l'); break;
                case 'd': snake.changeDirection('r'); break;
            }
        }

        snake.move();

        if (snake.getBody()[0].x == food.position.x && snake.getBody()[0].y == food.position.y) {
            snake.grow();
            food.generateNewFood();
        }

        if (snake.checkCollisionWithSelf() || snake.checkCollisionWithBorders(width, height)) {
            isGameOver = true;
        }
    }

    void run() {
        while (!isGameOver) {
            draw();
            update();
            Sleep(100);
        }
        cout << "Game Over!" << endl;
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
