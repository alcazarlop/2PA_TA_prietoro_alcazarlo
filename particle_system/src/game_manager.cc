
#include "game_manager.h"

GameManager::GameManager() {
	window_ = NULL;
	renderer_ = NULL;
	width_ = 0;
	height_ = 0;
	mouseX_ = 0;
	mouseY_ = 0;
}

GameManager::~GameManager() {}

Sint8 GameManager::init(Uint32 width, Uint32 height){

	window_ = SDL_CreateWindow("Particle System", SDL_WINDOWPOS_CENTERED,	SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
	if(window_ == NULL){
		SDL_Log("SDL_CreateWindow() Failed!: %s", SDL_GetError());
		return -1;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if(renderer_ == NULL){
		SDL_Log("SDL_CreateRenderer() Failed!: %s", SDL_GetError());
		return -1;
	}

	width_ = width;
	height_ = height;

	return 1;
}

void GameManager::quit(){
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

SDL_Window* GameManager::window() const {
	return window_;
}

SDL_Renderer* GameManager::renderer() const {
	return renderer_;
}

Uint32 GameManager::width() const {
	return width_;
}

Uint32 GameManager::height() const {
	return height_;
}

int GameManager::mouseX() const {
	return mouseX_;
}

int GameManager::mouseY() const {
	return mouseY_;
}

void GameManager::setMouseState() {
	SDL_GetMouseState(&mouseX_, &mouseY_);
}

bool GameManager::BoxCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2){
	if(y1 + h1 < y2 || y1 > y2 + h2 || x1 + w1 < x2 || x1 > x2 + w2 ) 
		return false;
	return true;
}

