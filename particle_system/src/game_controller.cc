
#include "game_controller.h"

GameController::GameController(){
	isRunning_ = 0;
	sceneChanger_ = 0;
	wc_ = WindowController();
}

GameController::GameController(const GameController& copy){
	isRunning_ = copy.isRunning_;
	sceneChanger_ = copy.sceneChanger_;
	wc_ = copy.wc_;
}

GameController::~GameController() {}

Sint8 GameController::init(){

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
		SDL_Log("SDL_Init() Failed!: %s\n", SDL_GetError());
		return isRunning_ = -1;
	}

	isRunning_ = wc_.init(1024, 680);

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	ImGui::CreateContext();
  ImGui_ImplSDL2_InitForSDLRenderer(wc_.window());
  ImGui_ImplSDLRenderer_Init(wc_.renderer());

  cube_.init();
  cube_.set_position(Vec3(wc_.width() / 2.0f, wc_.height() / 2.0f, 0.0f));
  cube_.set_scale(Vec3(100.0f, 100.0f, 0.0f));

	return isRunning_ = 1;
}

void GameController::input(SDL_Event* e){
	while(SDL_PollEvent(e)){
		ImGui_ImplSDL2_ProcessEvent(e);
		switch(e->type){
			case SDL_QUIT: isRunning_ = 0; break;
			case SDL_KEYDOWN:
				switch(e->key.keysym.sym){
					case SDLK_ESCAPE: isRunning_ = 0; break; 
					case SDLK_SPACE: 
						if(sceneChanger_ == 0) 
							sceneChanger_ = 1;
						else
							sceneChanger_ = 0;
					break;
				}
			break;
			case SDL_MOUSEBUTTONDOWN: 
				if(emitter_pool_.pool_.size() != 0){
					emitter_pool_.pool_.back().isBound_ = false;
				}
			break;
		}
	}
}

void GameController::update(){

	switch(sceneChanger_){
		case 0:
			for(Uint32 i = 0; i < emitter_pool_.pool_.size(); ++i){
				emitter_pool_.pool_[i].update();
			}
		break;
		case 1:
			cube_.set_rotation(Vec3((float)(SDL_GetTicks() * 0.0016f),(float)(SDL_GetTicks() * 0.0016f),(float)(SDL_GetTicks() * 0.0016f)));
		break;
	}

}

void GameController::draw(){
 	ImGui_ImplSDLRenderer_NewFrame();
  ImGui_ImplSDL2_NewFrame(wc_.window());
  ImGui::NewFrame();
	SDL_SetRenderDrawColor(wc_.renderer(), 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(wc_.renderer());

	switch(sceneChanger_){
		case 0:
		EmitterPoolManager(&emitter_pool_, wc_);
		for(Uint32 i = 0; i < emitter_pool_.pool_.size(); ++i){
			emitter_pool_.pool_[i].draw(wc_);
		}
		break;
		case 1:
			cube_.draw(wc_.renderer());
		break;
	}

	ChangeScene(&sceneChanger_);

  ImGui::Render();
  ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(wc_.renderer());
}

void GameController::quit(){

  ImGui_ImplSDLRenderer_Shutdown();
  ImGui_ImplSDL2_Shutdown();
	SDL_DestroyRenderer(wc_.renderer());
	SDL_DestroyWindow(wc_.window());
	IMG_Quit();
	SDL_Quit();
}

Sint8 GameController::loop(){

	SDL_Event eventHandler;
	srand((unsigned int)time(NULL));

	init();
	while(isRunning_){
		input(&eventHandler);
		update();
		draw();
	}

	quit();
	return isRunning_;
}
