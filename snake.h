#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

struct position {
    int x,y;
};

struct direction {
    int x,y;
};

struct food {
    position foodPos;

    void foodCreation() {
        foodPos.x = rand() % (SCREEN_WIDTH / unit);
        foodPos.y = rand() % (SCREEN_HEIGHT / unit);
    }

    void draw(SDL_Renderer* renderer) {
		SDL_Rect r{unit*foodPos.x, unit*foodPos.y, unit, unit};
		//SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		//SDL_RenderFillRect(renderer, &r);

		SDL_Texture* background = loadTexture("food.png",renderer);
        SDL_RenderCopy(renderer, background, NULL, &r);
    }
};

struct snake {
    position snakePos; // vị trí của đầu rắn
    direction presentDir; // hướng hiện tại của rắn được ghi nhận
    direction changeDir; // hướng mới của rắn được nhập vào bởi bàn phím

    position tail[3000]; // đuôi rắn

    int begining, last; //
    int length = 0;

    int temp = 0;

    bool crash = false;

    void update(int time, struct food& foodPiece) {
		temp += time; // môt biến lưu trữ

		if (temp > 100 - length*3){
			presentDir = changeDir;

			tail[last] = snakePos;

			// đổi hướng rắn theo hướng hiện tại
			snakePos.x += presentDir.x;
			snakePos.y += presentDir.y;

			if (snakePos.x == foodPiece.foodPos.x && snakePos.y == foodPiece.foodPos.y) {
				length += 1;
				begining -= 1;
				foodPiece.foodCreation();
			} // tái tạo đồ ăn sau khi ăn và tăng chiều dài của rắn.

			for (int i = 0; i < length-1; i++) {
				position& tailPos = tail[(begining + i)];
				if (tailPos.x == snakePos.x && tailPos.y == snakePos.y) {
					crash = true;
				}
			}

			begining++;
			last++;

			temp = 0;
		}
	}

	bool insideCheck () {
        if(snakePos.x < (SCREEN_WIDTH / unit) && snakePos.x >= 0 && snakePos.y >= 0 && snakePos.y < (SCREEN_HEIGHT / unit)) return true;
        else return false;
	}

	bool self_killedCheck () {
        /*for (int i = 0; i < length; i++) {
				position& tailPos = tail[(begining + i)];
				if (tailPos.x == snakePos.x && tailPos.y == snakePos.y) {
					return true;
				}
			}
			return false;*/
			return crash;
	}

	void draw(SDL_Renderer* renderer) {

		for (int i = 0; i < length; i++) {
			position& tailPos = tail[(begining + i)];
			SDL_Rect r{unit*tailPos.x, unit*tailPos.y, unit, unit}; // upper left location and width and height.
			//SDL_RenderFillRect(renderer, &r);

			SDL_Texture* background = loadTexture("pattern.png",renderer);
            SDL_RenderCopy(renderer, background, NULL, &r);
		}
		SDL_Rect r{unit*snakePos.x, unit*snakePos.y, unit, unit};

		SDL_Texture* background;

		if(presentDir.x == 0){
            if(presentDir.y == 1) background = loadTexture("head-down.png",renderer);
            if(presentDir.y == -1) background = loadTexture("head-up.png",renderer);
		}
		else if(presentDir.x == 1 && presentDir.y == 0) background = loadTexture("head-right.png",renderer);
		else if(presentDir.x == -1 && presentDir.y == 0) background = loadTexture("head-left.png",renderer);
		else background = loadTexture("head-down.png",renderer);

        //SDL_Texture* background = loadTexture("head.png",renderer);
        SDL_RenderCopy(renderer, background, NULL, &r);

	}
};

position randomLocation() {
    int x1 = rand() % 40 + 1;
    int y1 = rand() % 30 + 1;

    position random;
    random.x = x1;
    random.y = y1;

    return random;
}
