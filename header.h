#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Snake";
const int unit = 20;

void logSDLError(ostream& os,const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
} // SDL error report

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Texture* loadTexture (string path, SDL_Renderer* renderer){
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str()); // IMG_Load : nạp ảnh với đường dẫn là tên ảnh với tên là 1 string kiểu C (kết thúc bằng rỗng).
    if(loadedSurface == nullptr) {
        cout << "Fail to load chosen picture" << endl;
    } // nếu nạp ảnh thất bại

    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface); // từ ảnh đã nạp -> tạo texture
        if(newTexture == nullptr) cout << "Fail to load chosen picture" << endl; // kiểm tra xem có tạo được texture thành công hay không
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
} // lấy tham số là tên 1 file ảnh và con trỏ renderer đã được khai báo trong chương trình


