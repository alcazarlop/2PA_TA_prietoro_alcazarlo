
#include "sprite.h"

Sprite::Sprite(){
	tex_ = NULL;
}

Sprite::Sprite(const Sprite& copy){
	position_ = copy.position_;
	scale_ = copy.scale_;
	rotation_ = copy.rotation_;
	tex_ = copy.tex_;
}

Sprite::~Sprite(){
	Entity::~Entity();
	tex_->~Texture();
}

void Sprite::loadFromFile(const char* path, SDL_Renderer* renderer){
	tex_ = Texture::CreateTexture();
	tex_->loadFromFile(path, renderer);
}

void Sprite::loadFromBuffer(Uint32 width, Uint32 height, SDL_Renderer* renderer, Uint32* pixel_buffer, Uint32 pitch){
	tex_ = Texture::CreateTexture();
	tex_->loadFromBuffer(width, height, renderer, pixel_buffer, pitch);
}

void Sprite::draw(SDL_Renderer* renderer){
	if(tex_ != NULL && enabled()){
		SDL_FRect dstRect = {position_.x, position_.y, scale_.x * tex_->width(), scale_.y * tex_->height()};
		SDL_RenderCopyExF(renderer, tex_->texture(), NULL, &dstRect, rotation_.y, NULL, SDL_FLIP_NONE);
	}
}

Texture* Sprite::texture() const {
	return tex_;
}

