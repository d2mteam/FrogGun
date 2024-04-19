#include "base/basefuction.h"
#include "base/game_map.h"
#include "base/MainObject.h"
#include "base/ImpTimer.h"
#include "base/BulletObject.h"
#include "base/ThreatsObject.h"
#include "base/LoadAnimation.h"
#include "base/TextObject.h"
#include "base/Random.h"

MainObject p_player;
BaseObject g_background;
BaseObject g_menu_screen;
BaseObject g_gameover_screen;

BaseObject Layout[5];

TTF_Font* font_time = NULL;
TextObject style_;
TextObject gun_type_;
std::fstream save_file;

bool InitData() 
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

	g_window = SDL_CreateWindow("FROG HERO",SDL_WINDOWPOS_UNDEFINED
											   ,SDL_WINDOWPOS_UNDEFINED
											   ,SCREEN_WIDTH
											   ,SCREEN_HEIGHT
											   ,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(g_window == NULL)
	{
		success = false;
		throw std::runtime_error("Can't not creat window \n");
	}
	else
	{
		g_screen = SDL_CreateRenderer (g_window, -1, SDL_RENDERER_ACCELERATED);
		if(g_screen == NULL)
		{
			success = false;
			throw std::runtime_error("Can't not creat render\n");
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen ,RENDER_DRAW_COLOR
											,RENDER_DRAW_COLOR
											,RENDER_DRAW_COLOR
											,RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags)&&imgFlags))
				success=false;
		}
	}
	for(int i = 1; i <= 5; i++)
	{
		Layout[i-1].LoadImg("image//background//"+std::to_string(i)+".png",g_screen);
	}
	if(TTF_Init() == -1)
	{
		success = false;
	}
	if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1)
	{
		throw std::runtime_error("can't not load music\n");
		success = false;
	}
	g_sound_bullet = Mix_LoadWAV("music//soundeffect//laser.wav");
	g_sound_jump = Mix_LoadWAV("music//soundeffect//jump.wav");
	g_sound_pickup = Mix_LoadWAV("music//soundeffect//pickup.wav");
	g_sound_explosion = Mix_LoadWAV("music//soundeffect//explosion.wav");
	for(int i = 0; i < 9; i++)
	{
		g_gameMusic[i] = Mix_LoadMUS(("music//" + music[i]).c_str());
	}
	g_MenuMusic = Mix_LoadMUS("music//TitleTheme.wav");
	font_time = TTF_OpenFont("font//DebugFreeTrial-MVdYB.otf",30);
	if(font_time == NULL)
	{
		throw std::runtime_error("can't not load font\n");
		success = false;
	}
	MainObject::set_sound(g_sound_bullet,g_sound_jump,g_sound_pickup);
	ThreatsObject::set_sound(g_sound_bullet,g_sound_jump);
	return success;
	
}
bool LoadBackground()
{
	bool ret = g_background.LoadImg("image//background.png",g_screen);
	bool ret2 = g_menu_screen.LoadImg("image//menu//menu.png",g_screen);
	if(ret == false)
	{
		throw std::runtime_error("LoadBackground error\n"); 
		return false;
	}
		
	return true;
}
void close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) 
{
	srand((int)time(0));
	ImpTimer fps_timer;
	if(!InitData()) return -1;
	if(!LoadBackground()) return -1;
	bool isCollision = false;
	int time_ = 0;
	int NG_ = 10;
	bool game_quit = false;
	int Map_LV = 1;
	GameMap game_map;
	game_map.LoadMap("map//map01.dat");
	game_map.LoadTiles(g_screen);
	p_player.LoadImg("image//player_right.png",g_screen);
	p_player.set_clips();
	
	p_player.SetPosXY(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	int Dif_ = 0;
	std::vector<ThreatsObject*> threats_list = Random::MakeThreatslist(Dif_,g_screen);
	std::vector<LoadAnimation*> explosion_list;
	
	Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
	Mix_Volume(-1,MIX_MAX_VOLUME / 3);
	Mix_VolumeChunk(g_sound_bullet,MIX_MAX_VOLUME/5);
	Mix_VolumeChunk(g_sound_explosion,MIX_MAX_VOLUME);
	Mix_VolumeChunk(g_sound_jump,MIX_MAX_VOLUME/2);
	
	while(!game_quit)
	{
		bool is_quit = true;
		int kill = 0;
		int px_pos,py_pos,p_heath,p_bullet_size,p_money;
		SDLbasefuction::LoadSaveFile(px_pos,py_pos,p_heath,p_bullet_size,p_money,time_,Dif_,Map_LV);
		int choose_ = SDLbasefuction::MainMenu(g_screen,Dif_,game_quit,is_quit,NG_,g_MenuMusic);
		if(choose_ == START)
		{
			Map_LV = 1;
			p_player.reset();
			time_ = 0;
			Random::ClearThreatsList(threats_list);
			game_map.LoadMap("map//map01.dat");
			game_map.LoadTiles(g_screen);
			NG_++;
			threats_list = Random::MakeThreatslist(Dif_,g_screen);
			is_quit = false;
		}
		if(choose_ == CONTINUE)
		{
			// int px_pos,py_pos,p_heath,p_bullet_size,p_money;
			// SDLbasefuction::LoadSaveFile(px_pos,py_pos,p_heath,p_bullet_size,p_money,time_,Dif_);
			if(Map_LV == 4)
			{
				Random::ClearThreatsList(threats_list);
				threats_list = Random::summonBoss(g_screen);
			}
			game_map.LoadMap("map//map0" + std::to_string(Map_LV) + ".dat");
			p_player.SetPosXY(px_pos,py_pos);
			p_player.set_heath(p_heath);
			p_player.set_bullet_size(p_bullet_size);
			p_player.set_money(p_money);
			is_quit = false;

		}

		// game_map.LoadMap("map//map0" + std::to_string(Map_LV) + ".dat");
		// game_map.LoadTiles(g_screen);
		BulletObject::set_map(game_map.getMap());
		if(is_quit == false)	Mix_PlayMusic(g_gameMusic[SDLbasefuction::Random(0,9)], -1);
		int start_layout_x = 0;
		while(!is_quit)
		{	
			fps_timer.start();
			while(SDL_PollEvent(&g_event) != 0)
			{
				if(g_event.type == SDL_QUIT)
				{
					is_quit = true;
				}
				else if(g_event.type == SDL_KEYDOWN)
				{ 
					if(g_event.key.keysym.sym == SDLK_ESCAPE)
					{
						fps_timer.pause();
						is_quit = SDLbasefuction::PauseMenu(g_screen);
						fps_timer.unpause();
					}
				}
				p_player.HandelInputAction(g_event,g_screen);
			}
			SDL_SetRenderDrawColor(g_screen ,RENDER_DRAW_COLOR
											,RENDER_DRAW_COLOR
											,RENDER_DRAW_COLOR
											,RENDER_DRAW_COLOR);
			SDL_RenderClear(g_screen);
			
			Map map_data = game_map.getMap();
			start_layout_x -= 2; 
			start_layout_x = ((start_layout_x % SCREEN_WIDTH)+SCREEN_WIDTH)%SCREEN_WIDTH;
			for(int i = 0; i < 5; i++)
			{
				Layout[i].SetRect(start_layout_x%SCREEN_WIDTH,0);
				Layout[i].Render(g_screen);
				Layout[i].SetRect((start_layout_x%SCREEN_WIDTH) - SCREEN_WIDTH ,0);
				Layout[i].Render(g_screen);
			}
			
			p_player.SetMapXY(map_data.start_x_,map_data.start_y_);
			p_player.DoPlayer(map_data,g_screen,explosion_list);
			p_player.HandelBullet(g_screen);
			

			p_player.Show(g_screen); 
			//player
			game_map.SetMap(map_data);
			game_map.DrawMap(g_screen);
			//Threat    
			Random::RandomEnemy(threats_list,g_screen,Dif_,p_player.get_x_pos());
			for(int i = 0; i < threats_list.size(); i++)
			{
				ThreatsObject* p_threats = threats_list.at(i);
				p_threats->SetMapXY(map_data.start_x_,map_data.start_y_);
				if( p_threats->EnemyID() >= ThreatsObject::TRAP && p_threats->onground() == false)
				{
					p_threats->ImpMoveType(g_screen);
					p_threats->DoPlayer(map_data);
				}
				if(p_threats->EnemyID() == ThreatsObject::RAMDOM_TRAP && p_threats->onground() == true)
				{
					threats_list.erase(threats_list.begin()+i);
					p_threats->Free();
					if(p_threats != NULL)
					{
						p_threats = NULL;
					}
				}
				if (p_threats != NULL && p_threats->isThreatsActive() == true)
				{		
					p_threats->EnemyStatus(p_player.GetRealRect(),g_screen,map_data);
					p_threats->ImpMoveType(g_screen);
					p_threats->DoPlayer(map_data);
					bool bCol = false;
					SDL_Rect rect_player = p_player.GetRealRect();
					std::vector<BulletObject*> tbullet_list = p_threats->get_bullet_list();
					for(int j = 0; j < tbullet_list.size() ; j++)
					{
						BulletObject* pt_bullet = tbullet_list.at(j);
						bCol = SDLbasefuction::CheckCollision(pt_bullet->GetRect(),rect_player);
						if(bCol == true && pt_bullet->get_is_move() == true)
						{
							LoadAnimation* newExplosion = new LoadAnimation();
							newExplosion->LoadImg("image//explosion.png",g_screen);
							newExplosion->set_clips();
							int px_pos = p_player.get_x_pos();
							int py_pos = p_player.get_y_pos();
							newExplosion->set_x_pos(px_pos);
							newExplosion->set_y_pos(py_pos);
							explosion_list.push_back(newExplosion);
							p_threats->RemoveBullet(j);  
							p_player.DecreaseHeath();
							Mix_PlayChannel(-1,g_sound_explosion,0);
						}
					}
					bool bCol2 =  SDLbasefuction::CheckCollision(p_threats->GetRealRect(),rect_player);
					if(bCol2 == true)
					{
						if(p_threats->EnemyID() < ThreatsObject::NOT_ENEMY || p_threats->EnemyID() == ThreatsObject::RAMDOM_TRAP)
						{
							LoadAnimation* newExplosion = new LoadAnimation();
							newExplosion->LoadImg("image//explosion.png",g_screen);
							newExplosion->set_clips();
							int px_pos = p_player.get_x_pos();
							int py_pos = p_player.get_y_pos();
							newExplosion->set_x_pos(px_pos);
							newExplosion->set_y_pos(py_pos);
							explosion_list.push_back(newExplosion);					
							Mix_PlayChannel(-1,g_sound_explosion,0);

							LoadAnimation* newExplosion1 = new LoadAnimation();
							newExplosion1->LoadImg("image//explosion.png",g_screen);
							newExplosion1->set_clips();
							newExplosion1->set_x_pos(p_threats->get_x_pos());
							newExplosion1->set_y_pos(p_threats->get_y_pos());
							explosion_list.push_back(newExplosion1);
							Mix_PlayChannel(-1,g_sound_explosion,0);				
							isCollision = true;
							p_threats->decreaseHP();
							if(p_threats->get_HP() <= 0)
							{
								if(p_threats->EnemyID() > ThreatsObject::MIMIC && p_threats->EnemyID() < ThreatsObject::NOT_ENEMY)
								{
									isCollision = false;
								}
								threats_list.erase(threats_list.begin()+i);
								p_threats->Free();
								if(p_threats != NULL)
								{
									p_threats == NULL;
								}
								p_player.IncreaseKill();
								kill++;
							//	p_player.IncreaseBullet();
							}
							p_player.DecreaseHeath();
							p_player.set_y_val(-20);
						}
						// if(p_threats->EnemyID() > ThreatsObject::NOT_ENEMY && p_threats->EnemyID() != ThreatsObject::RAMDOM_TRAP)
						// {
						// 	if(p_threats->EnemyID() == ThreatsObject::ITEM_COIN) p_player.IncreaseMoney();
						// 	if(p_threats->EnemyID() == ThreatsObject::ITEM_HEATH) p_player.IncreaseHeath();
						// 	if(p_threats->EnemyID() == ThreatsObject::ITEM_BULLET) p_player.IncreaseBullet();
						// 	threats_list.erase(threats_list.begin()+i);
						// 	p_threats->Free();
						// 	if(p_threats != NULL)
						// 	{
						// 		p_threats == NULL;
						// 	}
						// }	
					}
				}
			}
	//player bullet with enemy
			std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
			for(int r = 0; r < bullet_arr.size(); r++)
			{
				BulletObject* p_bullet = bullet_arr.at(r);
				if(p_bullet != NULL)
				{
					for(int t = 0; t < threats_list.size(); t++)
					{
						ThreatsObject* obj_threat = threats_list.at(t);
						SDL_Rect tRect = obj_threat->GetRealRect();
						SDL_Rect bRect = p_bullet->GetRect();

						bool bCol = SDLbasefuction::CheckCollision(bRect,tRect);
						if(bCol == true && obj_threat->get_type_move() != ThreatsObject::MOVE_TRAP && obj_threat->EnemyID() < ThreatsObject::TRAP)
						{
							Mix_PlayChannel(-1,g_sound_explosion,0);
							LoadAnimation* newExplosion = new LoadAnimation();
							newExplosion->LoadImg("image//explosion.png",g_screen);
							newExplosion->set_clips();
							obj_threat->decreaseHP(p_bullet->get_style()+1);
							int tx_pos = obj_threat->get_x_pos();
							int ty_pos = obj_threat->get_y_pos();
							newExplosion->set_x_pos(tx_pos);
							newExplosion->set_y_pos(ty_pos);
							explosion_list.push_back(newExplosion);
							if(p_bullet->get_style() != BulletObject::WAVE)
								p_player.RemoveBullet(r);	
							if(obj_threat->get_HP() <= 0)
							{

								threats_list.erase(threats_list.begin()+t);
								obj_threat->Free();
								if(obj_threat != NULL)
								{
									obj_threat == NULL;
									p_player.IncreaseKill();
									kill++;
								}
								p_player.IncreaseMoney(obj_threat->getLV());
							}	         
						}
					}
				}
			}
	//Load explosion 
			for(int i = 0; i < threats_list.size(); i++)
			{
				ThreatsObject* p_threats = threats_list.at(i);
				if(p_threats != NULL)
				{
					p_threats->Show(g_screen);
				}
			}

			for(int ex = 0;ex < explosion_list.size(); ex++)
			{
				LoadAnimation* newExplosion = explosion_list.at(ex);
				if(newExplosion != NULL)
				{
					newExplosion->SetMapXY(map_data.start_x_,map_data.start_y_);
					newExplosion->Show(g_screen);
					if(newExplosion->get_animation_loop() > 0)
					{
						newExplosion->Free();
						explosion_list.erase(explosion_list.begin()+ex);
						if(newExplosion != NULL)
						{
							delete newExplosion;
							newExplosion = NULL;
						}
					}
				}
			}
			if(kill >= 6)
			{
				kill %= 6;
				p_player.IncreaseBullet(6 - Dif_);
				p_player.IncreaseHeath(6 - Dif_);
			}

			
			SDLbasefuction::PlayerStatus(p_player.get_money(),p_player.get_bullet_size(),
										p_player.get_heath(),p_player.get_kill(),time_,
										font_time,g_screen,p_player.get_gun_type(),
										p_player.get_style());
		
			SDL_RenderPresent(g_screen);
			int real_imp_time = fps_timer.get_ticks();
			int time_one_frame = 1000/FRAME_PER_SECOND;	
			if(real_imp_time < time_one_frame)
			{
				int delay_time = time_one_frame - real_imp_time;
				SDL_Delay(delay_time);
			}
			if(p_player.get_heath() <= 0)
			{
				time_= 0;
				is_quit = true;
				SDL_Delay(500);
				
				int score = p_player.get_money()/3+ p_player.get_kill();
				
				game_quit = SDLbasefuction::GameOverMenu(g_screen,score);
				p_player.reset();
				NG_ = 0;
			}
			if(is_quit == false)
			{
				int score = p_player.get_money()/3+ p_player.get_kill() + (300 - time_ > 0 ? 300 - time_ : 0);
				int q_ = SDLbasefuction::CheckWin(p_player.get_x_pos(),p_player.get_y_pos(),g_screen,Map_LV,score);
				if(q_ == 1)
				{
					p_player.reset();
					time_ = 0;

					if(Map_LV == 4)
					{
						Random::ClearThreatsList(threats_list);
						threats_list = Random::summonBoss(g_screen);
					}
					else
					{
						Random::ClearThreatsList(threats_list);
						threats_list = Random::MakeThreatslist(Dif_,g_screen);
					}
					is_quit = true;
					NG_ = 0;
				}
				if(q_ == 2)
				{
					Mix_PlayMusic(g_gameMusic[SDLbasefuction::Random(0,9)], -1);
					game_map.LoadMap("map//map0" + std::to_string(Map_LV) + ".dat");
					game_map.LoadTiles(g_screen);
					p_player.reset();
					NG_++;
				}
			}
		}
		Mix_HaltMusic();
		
		//end gameplay loop
		
		if(p_player.get_heath() <= 0)
		{
			p_player.reset();
			time_ = 0;
			Random::ClearThreatsList(threats_list);
			threats_list = Random::MakeThreatslist(Dif_,g_screen);
			game_map.LoadMap("map//map01.dat");
			Map_LV = 1;
			game_map.LoadTiles(g_screen);
			NG_ = 0;
		}
		else 
		{
			SDLbasefuction::SaveGame(p_player.get_x_pos(),p_player.get_y_pos(),
									p_player.get_heath(),p_player.get_bullet_size(),
									p_player.get_money(),time_,Dif_,Map_LV);
		}
	}
	//end Game Loop 
	if(p_player.get_heath() <= 0) 
	{
		NG_ = 0;
	}
	else
	{
		SDLbasefuction::SaveGame(p_player.get_x_pos(),p_player.get_y_pos(),
								p_player.get_heath(),p_player.get_bullet_size(),
								p_player.get_money(),time_,Dif_,Map_LV);
	}
	Random::ClearThreatsList(threats_list);
	close();
	return 0;
}