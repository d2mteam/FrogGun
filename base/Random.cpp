#include "Random.h"

std::vector<ThreatsObject*> Random::MakeThreatslist(const int& Difficulty_, SDL_Renderer* screen)
{
	std::vector<ThreatsObject*> list_threats;

	
	// int enemy_num_ = (Difficulty_ + 1)*20;
	// ThreatsObject* enemy_ = new ThreatsObject[enemy_num_];
	// for(int i = 0; i < 20; i++ )
	// {
	// 	ThreatsObject* p_threats = (enemy_ + i);
	// 	if(p_threats != NULL)
	// 	{
	// 		p_threats->SetThreatType(8,0.8,8,0,true);
	// 		p_threats->set_path("image//enemy_image//threat_level.png","image//enemy_image//threat_level.png");
	// 		p_threats->LoadImg("image//enemy_image//threat_level.png",screen);
	// 		p_threats->set_clips();
	// 		p_threats->set_x_pos(SCREEN_WIDTH * 2 + (i-1) * MAP_MAX_X*64/enemy_num_ + SDLbasefuction::Random(0,MAP_MAX_X*64/enemy_num_));
	// 		p_threats->set_y_pos(256);
	// 		p_threats->set_HP(3+Difficulty_);
	// 		p_threats->setLV(3+Difficulty_);

	// 		list_threats.push_back(p_threats);
	// 	}
	// }
	int trunk_num_ = (Difficulty_ + 1)*15;
	trunk* trunk_ = new trunk[trunk_num_];
	for(int i = 0; i < trunk_num_; i++ )
	{
		trunk* p_threats = (trunk_ + i);
		if(p_threats != NULL)
		{
			p_threats->SetThreatType(8,0.8,8,3,true);
			p_threats->set_path("image//enemy_image//trunk//trunk_run_left.png",
							   	"image//enemy_image//trunk//trunk_run_right.png",
								"image//enemy_image//trunk//trunk_attack_left.png",
								"image//enemy_image//trunk//trunk_attack_right.png");
			p_threats->LoadImg("image//enemy_image//trunk//trunk_run_left.png",screen);
			p_threats->set_clips();
			p_threats->set_x_pos(SCREEN_WIDTH * 2 + (i-1) * MAP_MAX_X*64/trunk_num_ + SDLbasefuction::Random(0,MAP_MAX_X*64/trunk_num_));
			p_threats->set_y_pos(256);
			
			p_threats->set_HP(4+Difficulty_);
			p_threats->setLV(4+Difficulty_);
			list_threats.push_back(p_threats);
		}
	}

	int move_enemy_num_ = (Difficulty_ + 1)*30;
	ThreatsObject* move_enemy_ = new ThreatsObject[move_enemy_num_];
	for(int i = 0; i < move_enemy_num_; i++)
	{
		ThreatsObject* p_threats = (move_enemy_ + i);
		if(p_threats != NULL)
		{
			p_threats->SetThreatType(16,0.8,8,3,(Difficulty_>Easy));
			p_threats->set_path("image//enemy_image//threat_left.png","image//enemy_image//threat_right.png");
			p_threats->LoadImg("image//enemy_image//threat_left.png",screen);
			p_threats->set_clips();
			p_threats->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);

			p_threats->set_x_pos(SCREEN_WIDTH * 2 + (i-1) * MAP_MAX_X*64/move_enemy_num_ + SDLbasefuction::Random(0,MAP_MAX_X*64/move_enemy_num_));
			p_threats->set_y_pos(256);
			p_threats->set_HP(2+Difficulty_/2);
			p_threats->setLV(2+Difficulty_/2);

			list_threats.push_back(p_threats);
		}
	}

	int slime_num_ = (Difficulty_ + 1)*40;
	slime* slime_ = new slime[slime_num_];
	for(int i = 0; i < slime_num_; i++)
	{
		slime* p_threats = (slime_ + i);
		if(p_threats != NULL)
		{
			p_threats->SetThreatType(10,0.8,8,2,(Difficulty_>Easy));
			p_threats->set_path("image//enemy_image//slime_left.png","image//enemy_image//slime_right.png");
			p_threats->LoadImg("image//enemy_image//slime_left.png",screen);
			p_threats->set_clips();
			p_threats->set_type_move(slime::MOVE_IN_SPACE_THREAT);

			p_threats->set_x_pos(SCREEN_WIDTH * 2 + (i-1) * MAP_MAX_X*64/slime_num_ + SDLbasefuction::Random(0,MAP_MAX_X*64/slime_num_));
			p_threats->set_y_pos(256);
			p_threats->set_HP(2+Difficulty_/2);
			p_threats->setLV(2+Difficulty_/2);
			list_threats.push_back(p_threats);
		}
	}	



	int spikes_enemy_num_ = (Difficulty_/2 + 1)*40;
	ThreatsObject* spikes_enemy_ = new ThreatsObject[spikes_enemy_num_];
	for(int i = 0; i < spikes_enemy_num_; i++)
	{
		ThreatsObject* p_threats = (spikes_enemy_ + i);
		if(p_threats != NULL)
		{
			p_threats->SetThreatType(1,8,16,0,false);
			p_threats->set_path("image//enemy_image//spikes.png","image//enemy_image//spikes.png");
			p_threats->LoadImg("image//enemy_image//spikes.png",screen);
			p_threats->set_clips();
			p_threats->set_type_move(ThreatsObject::TRAP);
			p_threats->set_x_pos(SCREEN_WIDTH + 64*(i%2) + (i/2+1)*(SCREEN_WIDTH*2+(i/2)*64));
			p_threats->set_y_pos(200);
			p_threats->set_HP(1000);
			p_threats->setLV(1000);
			list_threats.push_back(p_threats);
		}
	}
	
	
	
	int	bat_num_ = (Difficulty_/3 + 1)*40; 
	bat* bat_ = new bat[bat_num_];
	for(int i = 0; i < bat_num_; i++)
	{
		bat* p_threats = (bat_ + i);
		if(p_threats != NULL)
		{

			p_threats->SetThreatType(7,0,0,8,true);
			p_threats->LoadImg("image//enemy_image//bat_left.png",screen);
			p_threats->set_clips();

			p_threats->set_x_pos(SCREEN_WIDTH*2 + i * (MAP_MAX_X*64 - SCREEN_WIDTH * 3)/bat_num_);
			p_threats->set_y_pos(SDLbasefuction::Random(50,200));

			int pos_left = p_threats->get_x_pos() - 300;
			int pos_right = p_threats->get_x_pos() + 300;
			p_threats->SetAnimationPos(pos_left,pos_right);
			p_threats->set_HP(3+Difficulty_/2);
			p_threats->setLV(1+Difficulty_/2);
			list_threats.push_back(p_threats);
		}
	}
	
	
	int trap_num_ = (Difficulty_/2 + 1)*40; 
	trap* trap_ = new trap[trap_num_];
	for(int i = 0; i < trap_num_; i++)
	{
		trap* p_threats = (trap_ + i);
		if(p_threats != NULL)
		{
			p_threats->SetThreatType(8,8,16,3,false);
			p_threats->set_path("image//enemy_image//saw.png","image//enemy_image//saw.png");
			p_threats->LoadImg("image//enemy_image//saw.png",screen);
			p_threats->set_clips();
			p_threats->set_type_move(ThreatsObject::MOVE_TRAP);

			p_threats->set_x_pos(SCREEN_WIDTH*2  + (i-1) * MAP_MAX_X*64/trap_num_ + SDLbasefuction::Random(0,MAP_MAX_X*64/trap_num_));
			p_threats->set_y_pos(200);
			p_threats->set_HP(1000);
			p_threats->setLV(1000);
			list_threats.push_back(p_threats);
		}
	}
	
	int rino_num_ = (Difficulty_ + 1)*15;
	rino* rino_ = new rino[rino_num_];
	for(int i = 0; i < rino_num_; i++)
	{
		rino* p_threats = (rino_ + i);
		if(p_threats != NULL)
		{
			p_threats->SetThreatType(6,0.8,8,7,false);
			p_threats->LoadImg("image//enemy_image//rino_left.png",screen);
			p_threats->set_clips();
			p_threats->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
			p_threats->set_x_pos(SCREEN_WIDTH * 2 + (i-1) * MAP_MAX_X*64/rino_num_ + SDLbasefuction::Random(0,MAP_MAX_X*64/rino_num_));
			p_threats->set_y_pos(256);
			p_threats->set_HP(3+Difficulty_/2);
			p_threats->setLV(3+Difficulty_/2);
			list_threats.push_back(p_threats);
		}
	}	

	return list_threats;
}
void Random::ClearThreatsList(std::vector<ThreatsObject*>& threats_list)
{
	for(int i=0; i < threats_list.size(); i++)
	{
		ThreatsObject* p_threat = threats_list.at(i);
		if(p_threat != NULL)
		{
			p_threat->Free();
			p_threat = NULL;
		}
	}
	threats_list.clear();
}
void  Random::RandomEnemy(std::vector<ThreatsObject*>& threats_list, SDL_Renderer* screen, const int& Dif_, const int& x_pos_)
{
	static int random_time;
	if(random_time < 0 && Dif_ > Easy)	random_time = SDLbasefuction::Random((6-Dif_)*100,(6-Dif_)*120);
	random_time --;
	if(random_time == 0)
	{
		ThreatsObject* p_threats = new ThreatsObject();
		if(SDLbasefuction::Random(0,10) < 7)
		{
			p_threats->SetThreatType(4,1,8,0,false);
			p_threats->set_type_move(ThreatsObject::RAMDOM_TRAP);
			p_threats->set_path("image//enemy_image//fall_fat_bird.png","image//enemy_image//fall_fat_bird.png");
			p_threats->LoadImg("image//enemy_image//fall_fat_bird.png",screen);
		}
		else
		{
			p_threats->SetThreatType(1,2,8,0,false);
			p_threats->set_type_move(ThreatsObject::RAMDOM_TRAP);
			p_threats->set_path("image//enemy_image//fall_spikes.png","image//enemy_image//fall_spikes.png");
			p_threats->LoadImg("image//enemy_image//fall_spikes.png",screen);
		}
		p_threats->set_clips();
		
		p_threats->set_x_pos(x_pos_ + SDLbasefuction::Random(-50,100));
		p_threats->set_y_pos(SDLbasefuction::Random(0,200));
		p_threats->set_HP(1);
		p_threats->setLV(0);
		threats_list.push_back(p_threats);
	}  	
}

std::vector<ThreatsObject*> Random::summonBoss(SDL_Renderer* screen)
{
	std::vector<ThreatsObject*> list_threats;
	skull* skull_boss = new skull();
	skull_boss->SetThreatType(8,0,0,2,true);
	skull_boss->LoadImg("image//enemy_image//skull_boss.png",screen);
	skull_boss->set_x_pos(1024);
	skull_boss->set_clips();
	skull_boss->set_HP(100);
	skull_boss->setLV(200);
	list_threats.push_back(skull_boss);
	return list_threats;
}