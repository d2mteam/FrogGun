#include "MainObject.h"
Mix_Chunk* MainObject::sound_bullet_ = NULL;
Mix_Chunk* MainObject::sound_jump_ = NULL;
Mix_Chunk* MainObject::sound_pickup_ = NULL;
MainObject::MainObject(){
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = 0;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	input_type_.dash_ = 0;
	on_ground = false;
	map_x_ = 0;
	map_y_ = 0;
	comeback_time_ = 0;
	money_ = 0;
	load_bullet_ = false;
	bullet_size_ = 6;
	heath_ = 10;
	path_img[WALK_LEFT] = "";
	path_img[WALK_RIGHT] = "";
	path_img[JUMP_LEFT] = "";
	path_img[JUMP_RIGHT] = ""; 
	path_img[JUMP_LEFT] = "";
	path_img[JUMP_RIGHT] = "";

	dash_dir_ = WALK_RIGHT;
	isdash_ = false;
	dash_cooldown_ = 0;

	kill_ = 0;

	double_jump_ = 0;

	style_ = STYLE_1;
	gun_type_ = DEFAULT;

	q_ = false;
	e_ = false; 
	LV_ = 1;
	player_speed_ = PLAYER_SPEED;
	player_jump_speed_ = PLAYER_JUMP_VAL;
	dash_distance_ = DASH_DISTANCE;
	p_ = 0;
}

MainObject::~MainObject()
{
	for(auto p_bullet : p_bullet_list)
	{
		delete p_bullet;
		p_bullet = NULL;
	}
}


bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if(ret == true)
	{
		width_frame_ = rect_.w/FRAME_NUM;
		height_frame_ = rect_.h;
	}
	return ret;
}

void MainObject::set_clips() //frame
{
	if(width_frame_ > 0 && height_frame_ >0) 
	{
		for(int i = 0; i < FRAME_NUM; i++)
			{
				frame_clip_[i].x = i*width_frame_;
				frame_clip_[i].y = 0;
				frame_clip_[i].w = width_frame_;
				frame_clip_[i].h = height_frame_;
			}
	}
}

void MainObject::Show(SDL_Renderer* des)    //Render Character
{
	if(on_ground == true)
	{
		if(status_ == WALK_LEFT)
		{
			LoadImg("image//player_left.png",des);
			dash_dir_ = WALK_LEFT;
		}
		else
		{
			LoadImg("image//player_right.png",des);
			dash_dir_ = WALK_RIGHT;
		}
		
	}
	else
	{
		 if(status_ == WALK_LEFT)
		{
			if(y_val_ <= GRAVITY_SPEED * 2)
			{
				LoadImg("image//jump_left.png",des);
			}
			else
			{
				LoadImg("image//fall_left.png",des);
			}
			dash_dir_ = WALK_LEFT;
		}
		else
		{
			if(y_val_ <= GRAVITY_SPEED * 2)
			{
				LoadImg("image//jump_right.png",des);
			}
			else
			{
				LoadImg("image//fall_right.png",des);
			}
			dash_dir_ = WALK_RIGHT;
		}
	}
	if(input_type_.left_ == 1 || input_type_.right_ == 1)
	{
		frame_++;
	}
	else
	{
		frame_ = 0;
	}
	if(frame_ >= FRAME_NUM)
	{
		frame_ = 0;
	}
	rect_.x = x_pos_ - map_x_;
	rect_.y = y_pos_ - map_y_;

	SDL_Rect* current_clip = &frame_clip_[frame_];

	SDL_Rect  renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void MainObject::HandelInputAction(SDL_Event events,SDL_Renderer* screen) //Control
{

	if(kill_ > 30)
	{
		LV_ = 2;
	}
	if(kill_ > 70)
	{
		LV_ = 3;
	}
	if(kill_ > 100)
	{
		LV_ = 4;
	}

	if(dash_cooldown_ > 0) dash_cooldown_--; 
	if(on_ground == true && double_jump_ == 2)
	{
		double_jump_ = 0;
	}
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
			case  SDLK_d:
			{
				status_ = WALK_RIGHT;
				input_type_.right_ = 1;
				input_type_.left_ = 0;
			}
				break;
			case  SDLK_a:
			{
				status_ = WALK_LEFT;
				input_type_.left_ = 1;
				input_type_.right_ = 0;
			}
				break;
			case  SDLK_w:
			{
				if(on_ground == true)
				{
					Mix_PlayChannel(-1,sound_jump_,0);
					input_type_.jump_ = 1;
					on_ground = false;
				}
				else if(double_jump_ == 1 && on_ground == false)
				{
					Mix_PlayChannel(-1,sound_jump_,0);
					double_jump_ = 2;
					input_type_.jump_ = 1;
				}
			}
				break;
			case SDLK_j:
			{
				if(load_bullet_ == false && bullet_size_ >= gunstyle[gun_type_])
				{
										
					bullet_size_ -= gunstyle[gun_type_];
					int LV = LV_;
					if(style_ == STYLE_4) LV = (LV_ + (style_ == STYLE_4))*2;
					if(style_ == STYLE_2) LV = LV_ - 1; 
					if(gun_type_ == DEFAULT)
					{
						Mix_PlayChannel(-1,sound_bullet_,0);
						for(int j = 0; j < LV; j++)
						{
							BulletObject* p_bullet = new BulletObject();
							p_bullet->set_bullet_dir(status_ == WALK_RIGHT ? BulletObject::DIR_RIGHT : BulletObject::DIR_LEFT);
							if(status_ == WALK_LEFT) p_bullet->LoadImg("image//player//player_bullet_left.png",screen);
							else p_bullet->LoadImg("image//player//player_bullet_right.png",screen);
							p_bullet->SetMapXY(map_x_,map_y_);
							p_bullet->SetPosXY(x_pos_ + (10 + 20*j ) * (status_ == WALK_LEFT ? -1 : 1) + (status_ == WALK_RIGHT)* width_frame_,
											y_pos_ + height_frame_ * 0.3);
							p_bullet->set_x_val(30);
							
							p_bullet->set_is_move(true);
							p_bullet_list.push_back(p_bullet);
						}
					}
					if(gun_type_ == DOUBLE)
					{
						Mix_PlayChannel(-1,sound_bullet_,0);
						for(int j = 0; j < LV; j++)
						{
							
							for(int i = 0; i < 2; i++)
							{
								BulletObject* p_bullet = new BulletObject();
								p_bullet->set_bullet_dir(status_ == WALK_RIGHT ? BulletObject::DIR_RIGHT : BulletObject::DIR_LEFT);
								if(status_ == WALK_LEFT) p_bullet->LoadImg("image//player//player_bullet_left.png",screen);
								else p_bullet->LoadImg("image//player//player_bullet_right.png",screen);
								p_bullet->SetMapXY(map_x_,map_y_);
								p_bullet->SetPosXY(x_pos_ + (10 + 20*j ) * (status_ == WALK_LEFT ? -1 : 1) + (status_ == WALK_RIGHT)* width_frame_
												,y_pos_ + height_frame_ * 0.3 + (i-0.5)*10);
								p_bullet->set_x_val(30);

								p_bullet->set_is_move(true);
								p_bullet_list.push_back(p_bullet);
							}
						}
					}
					if(gun_type_ == WAVE)
					{
						Mix_PlayChannel(-1,sound_bullet_,0);
						for(int j = 0; j < 1; j++)
						{
							BulletObject* p_bullet = new BulletObject();
							p_bullet->set_bullet_dir(status_ == WALK_RIGHT ? BulletObject::DIR_RIGHT : BulletObject::DIR_LEFT);
							if(status_ == WALK_LEFT) p_bullet->LoadImg("image//player//player_bullet_left_2.png",screen);
							else p_bullet->LoadImg("image//player//player_bullet_right_2.png",screen);
							p_bullet->SetMapXY(map_x_,map_y_);
							p_bullet->SetPosXY(x_pos_ + (status_ == WALK_RIGHT) * width_frame_
											,y_pos_);
							p_bullet->set_x_val(40);
							p_bullet->set_style(BulletObject::WAVE);
							p_bullet->set_is_move(true);
							p_bullet->set_bullet_distance(1280);
							p_bullet_list.push_back(p_bullet);
						}
						
					}
					if(gun_type_ == SHORTGUN)
					{
						Mix_PlayChannel(-1,sound_bullet_,0);
						BulletObject* p_bullet = new BulletObject();
						p_bullet->LoadImg("image//player//player_bullet_left_down.png",screen);
						p_bullet->SetMapXY(map_x_,map_y_);
						p_bullet->SetPosXY(x_pos_ + width_frame_,
										y_pos_ + height_frame_ * 0.5);
						p_bullet->set_style(BulletObject::BOUND);
						p_bullet->set_bullet_distance(640);
						p_bullet->set_y_val(30);
						p_bullet->set_is_move(true);
						y_val_ -= 15;
						p_bullet_list.push_back(p_bullet);
					}
					
				}
				load_bullet_ = true;	
			}
				break;
			case SDLK_LSHIFT:
			{   
				if(style_ != STYLE_4)
				{
					if(isdash_ == true && dash_cooldown_ <= 0)
					{
						input_type_.dash_ = 1;
						dash_cooldown_ = DASH_COOLDOWN;
					}
					isdash_ = false;
				} 
			}
				break;  
			case  SDLK_1:
			{
				style_ = STYLE_1;
			}
				break;
			case  SDLK_2:
			{
				style_ = STYLE_2;
			}
				break;
			case  SDLK_3:
			{
				style_ = STYLE_3;
			}
				break;
			case  SDLK_4:
			{
				style_ = STYLE_4;
			}
				break;
			case SDLK_q:
			{
				if(q_ == false)
				{
					gun_type_ = ((gun_type_ - 1)%4+4)%4;
					q_ = true;
				}
			}      
				break;
			case SDLK_e:
			{
				if(e_ == false)
				{
					gun_type_ = ((gun_type_ + 1)%4+4)%4;
					e_ = true;
				} 
			}
				break;
			default:
				break;
			
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
			case  SDLK_d:
			{
				input_type_.right_ = 0;
			}
				break;
			case  SDLK_a:
			{
				input_type_.left_ = 0;
			}
				break;
			case SDLK_w:
			{
				if(on_ground == false && double_jump_ == 0)
				{
					double_jump_ = 1;
				}
			}
				break;
			case SDLK_j:
			{
				load_bullet_ = false;
			}
				break;
			case SDLK_LSHIFT:
				isdash_ = true;
				break;
			case SDLK_q:
			{
				q_ = false; 
			}      
				break;
			case SDLK_e:
			{
				e_ = false; 
			}
			default:
				break;
		}
	}
}

void MainObject::HandelBullet(SDL_Renderer* des)
{
	for(int i = 0; i < p_bullet_list.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list.at(i);
		if(p_bullet != NULL)
		{
			if(p_bullet->get_is_move() == true)
			{
				p_bullet->SetMapXY(map_x_,map_y_);
				p_bullet->HandelMove();
				p_bullet->Render(des);
			}
			else
			{
				p_bullet_list.erase(p_bullet_list.begin() + i);
				if(p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}
}

void MainObject::RemoveBullet(const int& idx)
{
	int size = p_bullet_list.size();
	if( size > 0 && idx < size)
	{
		BulletObject* p_bullet = p_bullet_list.at(idx);
		p_bullet_list.erase(p_bullet_list.begin() + idx);
		if(p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}
void MainObject::DoPlayer(Map& map_data, SDL_Renderer* screen, std::vector<LoadAnimation*>& p_dash)  // Move
{
	switch (style_)
	{
		case STYLE_2:
		{
			player_speed_ = PLAYER_SPEED * 1.5;
			player_jump_speed_ = PLAYER_JUMP_VAL * 1.2 ;
			dash_distance_ = DASH_DISTANCE * 2;
		}
			break;
		case STYLE_4:
		{
			player_speed_ = PLAYER_SPEED/2;
			player_jump_speed_ = PLAYER_JUMP_VAL * 0.8;
			
		}
			break;
		default:
		{
			player_speed_ = PLAYER_SPEED;
			player_jump_speed_ = PLAYER_JUMP_VAL;
			dash_distance_ = DASH_DISTANCE;
		}
			break;
	}
	if(comeback_time_ == 0 )
	{
		x_val_ = 0;
		y_val_ += 0.8;

		if(y_val_ >= MAX_FALL_SPEED )
		{
			y_val_ = MAX_FALL_SPEED;
		}
		if(input_type_.left_ == 1)
		{
			x_val_ -= player_speed_;
		}
		if(input_type_.right_ == 1)
		{
			x_val_ += player_speed_;
		}
		if(input_type_.jump_ == 1)
		{
			if(on_ground == true)
			{
				y_val_ = -player_jump_speed_;
				input_type_.jump_ = 0;
				on_ground = false;
			}
			if(on_ground == false && double_jump_ == 2)
			{
				if(dash_dir_ == WALK_LEFT)
				{
					x_val_ -= player_speed_;
				}
				if(dash_dir_ == WALK_RIGHT)
				{
					x_val_ += player_speed_;
				}
				y_val_ = -player_jump_speed_ * 3/4;
				input_type_.jump_ = 0;
		// 		double_jump_ = 0;
		// //		on_ground = false;
			}
		}
		if(input_type_.dash_ == 1)
		{
			y_val_ = 0;
			int ndash_ = 10;
			for(int i = 0; i < ndash_; i++)
			{
				if(dash_dir_ == WALK_LEFT)
				{
					x_val_ = - dash_distance_/ndash_;
					CheckMap(map_data);
					if(i % 3 == 1)
					{
						LoadAnimation* newDash = new LoadAnimation();
						newDash->set_frame_max(4);
						newDash->LoadImg("image//dash_left.png",screen);
						newDash->set_clips();
						newDash->set_x_pos(x_pos_);
						newDash->set_y_pos(y_pos_);
						p_dash.push_back(newDash);
					}
					
				}
				if(dash_dir_ == WALK_RIGHT)
				{
					x_val_ =  dash_distance_/ndash_;
					CheckMap(map_data);
				 //   LoadAnimation* newDash = new LoadAnimation();
					if(i % 3 == 1)
					{
						LoadAnimation* newDash = new LoadAnimation();
						newDash->set_frame_max(4);
						newDash->LoadImg("image//dash_right.png",screen);
						newDash->set_clips();
						newDash->set_x_pos(x_pos_);
						newDash->set_y_pos(y_pos_);
						p_dash.push_back(newDash);
					}
				}
				status_ = dash_dir_;
			}
			input_type_.dash_ = 0;
			x_val_ = 0;
			isdash_ = false;
			CenterEntityOnMap(map_data);
			return;
		}
		CheckMap(map_data);
		CenterEntityOnMap(map_data);
	}
	if(comeback_time_ > 0)
	{
		on_ground = false;
		comeback_time_ --;
		if(comeback_time_ == 0)
		{
			respawn();
			y_pos_ = 0;
			x_val_ = 0;
			y_val_ = 0;
			if(x_pos_ > 256) x_pos_ -= 256;
			else x_pos_ = 0;
		}
	}
}

void MainObject::CheckMap(Map& map_data) //xu li va cham //gravity
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//Check hoz

	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
	x1 = (x_pos_ + x_val_)/TILE_SIZE;
	x2 = (x_pos_ + x_val_+ width_frame_ - 1)/TILE_SIZE;
	y1 = (y_pos_)/TILE_SIZE;
	y2 = (y_pos_ + height_min - height_frame_*0.2)/TILE_SIZE;

	if(x1 >=0 && x2< MAP_MAX_X && y1 >= 0 && y2 < MAP_MAX_Y)
	{
		if(x_val_ > 0)
		{
			if(map_data.tile[y1][x2] == COIN || map_data.tile[y2][x2] == COIN )
			{
				if(map_data.tile[y1][x2] == COIN ) {map_data.tile[y1][x2] = BLANK_TILE; IncreaseMoney(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y2][x2] == COIN ) {map_data.tile[y2][x2] = BLANK_TILE; IncreaseMoney(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			if(map_data.tile[y1][x2] == HEATH || map_data.tile[y2][x2] == HEATH )
			{
				if(map_data.tile[y1][x2] == HEATH ) {map_data.tile[y1][x2] = BLANK_TILE; IncreaseHeath(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y2][x2] == HEATH ) {map_data.tile[y2][x2] = BLANK_TILE; IncreaseHeath(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			if(map_data.tile[y1][x2] == BULLET || map_data.tile[y2][x2] == BULLET )
			{
				if(map_data.tile[y1][x2] == BULLET ) {map_data.tile[y1][x2] = BLANK_TILE; IncreaseBullet(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y2][x2] == BULLET ) {map_data.tile[y2][x2] = BLANK_TILE; IncreaseBullet(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			else if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE )
			{
				x_pos_ = x2*TILE_SIZE;
				x_pos_ -= width_frame_ + 1 ;
				x_val_ = 0;
			}
		}
		else if(x_val_ < 0)
		{
			if(map_data.tile[y1][x1] == COIN || map_data.tile[y2][x1] == COIN )
			{
				if(map_data.tile[y1][x1] == COIN ) {map_data.tile[y1][x1] = BLANK_TILE; IncreaseMoney(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y2][x1] == COIN ) {map_data.tile[y2][x1] = BLANK_TILE; IncreaseMoney(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			if(map_data.tile[y1][x1] == HEATH || map_data.tile[y2][x1] == HEATH )
			{
				if(map_data.tile[y1][x1] == HEATH ) {map_data.tile[y1][x1] = BLANK_TILE; IncreaseHeath(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y2][x1] == HEATH ) {map_data.tile[y2][x1] = BLANK_TILE; IncreaseHeath(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			if(map_data.tile[y1][x1] == BULLET || map_data.tile[y2][x1] == BULLET )
			{
				if(map_data.tile[y1][x1] == BULLET ) {map_data.tile[y1][x1] = BLANK_TILE; IncreaseBullet(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y2][x1] == BULLET ) {map_data.tile[y2][x1] = BLANK_TILE; IncreaseBullet(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			else if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE )
			{
				x_pos_ = (x1+1)*TILE_SIZE;
				x_val_ = 0;
			}
		}
	}

	//Check ver

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_ +  width_frame_ * 0.2)/TILE_SIZE;
	x2 = (x_pos_ + width_frame_ - width_frame_ * 0.2)/TILE_SIZE;
	y1 = (y_pos_ + y_val_)/TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

	if(x1 >=0 && x2 < MAP_MAX_X && y1 >= 0 && y2 < MAP_MAX_Y)
	{
		if(y_val_ > 0)
		{
			if(map_data.tile[y2][x1] == COIN || map_data.tile[y2][x2] == COIN)
			{
				if(map_data.tile[y2][x1] == COIN ) {map_data.tile[y2][x1] = BLANK_TILE; IncreaseMoney(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y2][x2] == COIN ) {map_data.tile[y2][x2] = BLANK_TILE; IncreaseMoney(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			if(map_data.tile[y2][x1] == HEATH || map_data.tile[y2][x2] == HEATH)
			{
				if(map_data.tile[y2][x1] == HEATH ) {map_data.tile[y2][x1] = BLANK_TILE; IncreaseHeath(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y2][x2] == HEATH ) {map_data.tile[y2][x2] = BLANK_TILE; IncreaseHeath(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			if(map_data.tile[y2][x1] == BULLET || map_data.tile[y2][x2] == BULLET)
			{
				if(map_data.tile[y2][x1] == BULLET ) {map_data.tile[y2][x1] = BLANK_TILE; IncreaseBullet(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y2][x2] == BULLET ) {map_data.tile[y2][x2] = BLANK_TILE; IncreaseBullet(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			else if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
			{
				y_pos_ = y2*TILE_SIZE;   
				y_pos_ -= height_frame_;
				y_val_ = 0; 
				on_ground = true;
			}
		}
		else if(y_val_ < 0)
		{
			if(map_data.tile[y1][x1] == COIN || map_data.tile[y1][x2] == COIN)
			{
				if(map_data.tile[y1][x1] == COIN ) {map_data.tile[y1][x1] = BLANK_TILE; IncreaseMoney(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y1][x2] == COIN ) {map_data.tile[y1][x2] = BLANK_TILE; IncreaseMoney(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			if(map_data.tile[y1][x1] == HEATH || map_data.tile[y1][x2] == HEATH)
			{
				if(map_data.tile[y1][x1] == HEATH ) {map_data.tile[y1][x1] = BLANK_TILE; IncreaseHeath(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y1][x2] == HEATH ) {map_data.tile[y1][x2] = BLANK_TILE; IncreaseHeath(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			if(map_data.tile[y1][x1] == BULLET || map_data.tile[y1][x2] == BULLET)
			{
				if(map_data.tile[y1][x1] == BULLET ) {map_data.tile[y1][x1] = BLANK_TILE; IncreaseBullet(); Mix_PlayChannel(-1,sound_pickup_,0);}
				if(map_data.tile[y1][x2] == BULLET ) {map_data.tile[y1][x2] = BLANK_TILE; IncreaseBullet(); Mix_PlayChannel(-1,sound_pickup_,0);}
			}
			else if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
			{
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		} 
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;
	
	// goc trai goc phai
	if(x_pos_ < 0)
	{
		x_pos_ = 0;
	}
	if(y_pos_ < -TILE_SIZE/2)
	{
		y_pos_ = -TILE_SIZE/2;
		y_val_ = GRAVITY_SPEED; 
	
	}
	else if(x_pos_ + width_frame_ > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width_frame_ -1;
	}
	if(y_pos_ >= map_data.max_y_){
		comeback_time_ = 60;
		DecreaseHeath();
	}
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
	int new_start_x = x_pos_ - (SCREEN_WIDTH*3/8);
	int in = (new_start_x - map_data.start_x_)/15;
	
	map_data.start_x_ += in;

	if(map_data.start_x_ < 0)
	{
		map_data.start_x_ = 0;
	}
	else if( map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}
	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT/2);
	if(map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0;
	}
	else if(map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ -  SCREEN_HEIGHT;
	}
}

SDL_Rect MainObject::GetRealRect() const
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.h = height_frame_;
	rect.w = width_frame_;
	return rect;
}

void MainObject::respawn()
 {
	on_ground = false;
	int time_respawn = 1000;
	while(time_respawn > 0) time_respawn -= 5;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	if(x_pos_ > 256) x_pos_ -= 256;
	else x_pos_ = 0;
}

void MainObject::reset()
{
	LV_ = 1;
	x_pos_ = SCREEN_WIDTH/2;
	y_pos_ = SCREEN_HEIGHT/2;
	x_val_ = 0;
	y_val_ = 0;
	frame_ = 0;
	status_ = 0;
	on_ground = false;
	map_x_ = 0;
	map_y_ = 0;
	int comeback_time_ = 0;
	load_bullet_ = 0;
	bullet_size_ = 6;
	heath_ = 10;
	money_ = 0;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.dash_ = 0;
	dash_cooldown_ = 0;
	kill_ = 0;
	double_jump_ = 0;
	gun_type_ = DEFAULT;
	style_ = STYLE_1;
	player_speed_ = PLAYER_SPEED;
	p_ = 0;
}

void MainObject::set_sound(Mix_Chunk* sound_bullet,Mix_Chunk* sound_jump,Mix_Chunk* sound_pickup)
{
	sound_bullet_ = sound_bullet;
	sound_jump_ = sound_jump;
	sound_pickup_ = sound_pickup;
}