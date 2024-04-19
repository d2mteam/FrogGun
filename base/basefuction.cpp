#include "basefuction.h"
#include "BaseObject.h"
#include "TextObject.h"
bool SDLbasefuction::CheckCollision(const SDL_Rect& object1,const SDL_Rect& object2) 
{
		int left_a = object1.x;
		int right_a = object1.x + object1.w;
		int top_a = object1.y;
		int bottom_a = object1.y + object1.h;
	
		int left_b = object2.x;
		int right_b = object2.x + object2.w - object2.w*0.1;
		int top_b = object2.y;
		int bottom_b = object2.y + object2.h - object2.w*0.1;
	
	// Case 1: size object 1 < size object 2
		if (left_a > left_b && left_a < right_b)
		{
			if (top_a > top_b && top_a < bottom_b)
			{
				return true;
			}
		}
	
		if (left_a > left_b && left_a < right_b)
		{
			if (bottom_a > top_b && bottom_a < bottom_b)
			{
				return true;
			}
		}
	
		if (right_a > left_b && right_a < right_b)
		{
			if (top_a > top_b && top_a < bottom_b)
			{
				return true;
			}
		}
	
		if (right_a > left_b && right_a < right_b)
		{
			if (bottom_a > top_b && bottom_a < bottom_b)
			{
				return true;
			}
		}
		
		// Case 2: size object 1 < size object 2
		if (left_b > left_a && left_b < right_a)
		{
			if (top_b > top_a && top_b < bottom_a)
			{
				return true;
			}
		}
	
		if (left_b > left_a && left_b < right_a)
		{
			if (bottom_b > top_a && bottom_b < bottom_a)
			{
				return true;
			}
		}
	
		if (right_b > left_a && right_b < right_a)
		{
			if (top_b > top_a && top_b < bottom_a)
			{
				return true;
			}
		}
	
		if (right_b > left_a && right_b < right_a)
		{
			if (bottom_b > top_a && bottom_b < bottom_a)
			{
				return true;
			}
		}
	
		// Case 3: size object 1 = size object 2
		if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
		{
			return true;
		}
	
		return false;
}


bool SDLbasefuction::CheckMousePos(const int& x,const int& y,const SDL_Rect& Obj_)
{
	return (x >= Obj_.x && x <= Obj_.x + Obj_.w && y>= Obj_.y && y <= Obj_.y + Obj_.h);
}

bool SDLbasefuction::LoadSaveFile(int& px_pos,
								int& py_pos,
								int& p_heath,
								int& p_bullet,
								int& p_money,
								int& time_,
								int& Dif_,
								int& Map_LV)
{
	std::ifstream inputFile("save/save.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file for reading\n";
        return false;
    }
    int count = 0;
    if (inputFile >> px_pos) count++;
    if (inputFile >> py_pos) count++;
    if (inputFile >> p_heath) count++;
    if (inputFile >> p_bullet) count++;
    if (inputFile >> p_money) count++;
	if (inputFile >> time_) count++;
	if (inputFile >> Dif_) count++;
	if (inputFile >> Map_LV) count++;
    inputFile.close();

    if (count == 8) {
        return true;
    } else {
        std::cerr << "File does not contain enough values\n";
        return false;
    }
	return true;
}

bool SDLbasefuction::SaveGame(const int& px_pos,
							const int& py_pos,
							const int& p_heath,
							const int& p_bullet,
							const int& p_money,
							const int& time_,
							const int& Dif_,
							const int& Map_LV)
{
	std::ofstream outputFile("save/save.txt");
    if(!outputFile.is_open()) {
        std::cerr << "Failed to open file for writing\n";
        return false;
    }
	outputFile << px_pos << " "
			   << py_pos << " "
			   << p_heath << " "
			   << p_bullet << " " 
			   << p_money << " "
			   << time_ << " "
			   << Dif_ << " "
			   << Map_LV << " ";
	outputFile.close();
	return true;
}

bool SDLbasefuction::PauseMenu(SDL_Renderer* screen)
{
	
	bool is_quit = false;
	SDL_Event event;
	BaseObject ExitButton[2];
	BaseObject ContinueButton[2];
	BaseObject PauseMenu;
	BaseObject MusicButton[2];
	


	ExitButton[0].LoadImg("image//menu//MainMenuButtonUp.png",screen);
	ExitButton[1].LoadImg("image//menu//MainMenuButtonDown.png",screen);
	ContinueButton[0].LoadImg("image//menu//ContinueButtomUp.png",screen);
	ContinueButton[1].LoadImg("image//menu//ContinueButtomDown.png",screen);
	PauseMenu.LoadImg("image//menu//PauseMenu.png",screen);
	MusicButton[0].LoadImg("image//menu//Music-On.png",screen);
	MusicButton[1].LoadImg("image//menu//Music-Off.png",screen);
	

	SDL_Rect Button = PauseMenu.GetRect();
	int xPos = SCREEN_WIDTH/2 - Button.w/2;
	int yPos = SCREEN_HEIGHT/2 - Button.h/2;
	int wMenu = Button.w;
	int hMenu = Button.h;
	PauseMenu.SetRect(xPos,yPos);

	Button = ContinueButton[0].GetRect();
	ContinueButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,yPos + Button.h/4);
	ContinueButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,yPos + Button.h/4);

	Button = ExitButton[0].GetRect();
	ExitButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,yPos + hMenu-Button.h*5/4);
	ExitButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,yPos + hMenu-Button.h*5/4);

	Button = MusicButton[0].GetRect();
	MusicButton[1].SetRect(SCREEN_WIDTH - Button.w * 2,SCREEN_HEIGHT - Button.h);
	MusicButton[0].SetRect(SCREEN_WIDTH - Button.w * 2,SCREEN_HEIGHT - Button.h);


	int MousePosX = 0;
	int MousePosY = 0;
	bool MusicBut =  !(Mix_VolumeMusic(-1)>0);
	while(!is_quit)
	{
		while(SDL_PollEvent(&event) != 0)
		{
			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					is_quit = true;
				}			
			}
			if(event.type == SDL_MOUSEMOTION)
			{
				MousePosX = event.motion.x;
				MousePosY = event.motion.y;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,ExitButton[0].GetRect()) == true)
					{
						is_quit = true;
						return true;
					}
					if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,ContinueButton[0].GetRect()) == true)
					{ 
						is_quit = true;
						return false;
					}
					if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,MusicButton[0].GetRect()) == true)
					{
						MusicBut = !MusicBut;
						if(MusicBut == false)
						{
							Mix_VolumeMusic((MIX_MAX_VOLUME / 5));
							Mix_Volume(-1,(MIX_MAX_VOLUME / 3));
						}
						else
						{
							Mix_VolumeMusic(0);
							Mix_Volume(-1,0);
						}
					}
				}
			}
		}
		PauseMenu.Render(screen);
		if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,ExitButton[0].GetRect()) == true)
		{
			ExitButton[1].Render(screen);
		}
		else
		{
			ExitButton[0].Render(screen);
		}
		if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,ContinueButton[0].GetRect()) == true)
		{
			ContinueButton[1].Render(screen);
		}
		else
		{
			ContinueButton[0].Render(screen);
		}
		MusicButton[MusicBut].Render(screen);
		SDL_RenderPresent(screen);
		SDL_Delay(1000/FRAME_PER_SECOND);
	}
	ContinueButton[0].Free();
	ContinueButton[1].Free();
	ExitButton[0].Free();
	ExitButton[0].Free();
	return false;
}

bool SDLbasefuction::GameOverMenu(SDL_Renderer* screen,const int& high_score)
{
	bool is_quit = false;
	SDL_Event event;
	BaseObject GameOverMenu;
	BaseObject MainMenuButton[2];
	BaseObject ExitButton[2];
	BaseObject MusicButton[2];
	TextObject GameOverText;
	TextObject YourScoreText;
	
	TTF_Font* font_time = NULL;
	TTF_Font* font_time_1 = NULL;
	GameOverMenu.LoadImg("image//menu//GameOverMenu.png",screen);	
	MainMenuButton[0].LoadImg("image//menu//MainMenuButtonUp.png",screen);
	MainMenuButton[1].LoadImg("image//menu//MainMenuButtonDown.png",screen);
	ExitButton[0].LoadImg("image//menu//ExitButtomUp.png",screen);
	ExitButton[1].LoadImg("image//menu//ExitButtomDown.png",screen);
	MusicButton[0].LoadImg("image//menu//Music-On.png",screen);
	MusicButton[1].LoadImg("image//menu//Music-Off.png",screen);


	SDL_Rect Button = MainMenuButton[0].GetRect();
	MainMenuButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 - Button.h/4);
	MainMenuButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 - Button.h/4);
	Button = ExitButton[0].GetRect();
	ExitButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 + Button.h*1.25);
	ExitButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 + Button.h*1.25);
	int MousePosX = 0;
	int MousePosY = 0;	
	font_time = TTF_OpenFont("font//DebugFreeTrial-MVdYB.otf",300);
	font_time_1 = TTF_OpenFont("font//dlxfont_.ttf",50);
	while(!is_quit)
	{
		while(SDL_PollEvent(&event) != 0)
		{

			if(event.type == SDL_MOUSEMOTION)
			{
				MousePosX = event.motion.x;
				MousePosY = event.motion.y;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,MainMenuButton[0].GetRect()) == true)
					{
						is_quit = true;
						TTF_CloseFont(font_time);
						font_time = NULL;
						TTF_CloseFont(font_time_1);
						font_time_1 = NULL;
						return false;
					}
					if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,ExitButton[0].GetRect()) == true)
					{
						is_quit = true;
						return true;
					}
				}
			}
		}
		GameOverMenu.Render(screen);
		if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,MainMenuButton[0].GetRect()) == true)
		{
			MainMenuButton[1].Render(screen);
		}
		else
		{
			MainMenuButton[0].Render(screen);
		}
		if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,ExitButton[0].GetRect()) == true)
		{
			ExitButton[1].Render(screen);
		}
		else
		{
			ExitButton[0].Render(screen);
		}
		
		GameOverText.SetText("Game Over");
		GameOverText.SetColor(TextObject::RED_TEXT);
		GameOverText.LoadFromRenderText(font_time,screen);
		GameOverText.RenderText(screen,100,30);

		std::string high_score_str = "YOURSCORE: " + std::to_string(high_score);
		YourScoreText.SetText(high_score_str);
		YourScoreText.SetColor(TextObject::BLACK_TEXT);
		YourScoreText.LoadFromRenderText(font_time_1,screen);
		YourScoreText.RenderText(screen,400,600);
		SDL_RenderPresent(screen);
		SDL_Delay(100);
	}
	GameOverMenu.Free();
	return true;
}

int SDLbasefuction::Random(int begin,int end)
{
	srand((int)time(0));
	return begin + rand()%(end-begin+1);
}


int SDLbasefuction::MainMenu(SDL_Renderer* screen,int& Dif_,bool& game_quit,bool& is_quit,int &NG_,Mix_Music* MenuMusic)
{
	
	BaseObject StartButton[2];
	BaseObject ExitButton[2];
	BaseObject ContinueButton[2];
	BaseObject RightArrow[2];
	BaseObject LeftArrow[2];
	BaseObject Difficulty[4];
	BaseObject MusicButton[2];
	BaseObject TutorialButton;
	BaseObject  g_menu_screen;
	BaseObject TutorialText;
	//BaseObject Layout[5];
	int start_layout_x = 0;

	// for(int i = 1; i <= 5; i++)
	// {
	// 	Layout[i-1].LoadImg("image//background//"+std::to_string(i)+".png",screen);
	// }

	
	SDL_Event event;
	SDL_Rect Button;
	int MousePosX = 0;
	int MousePosY = 0;
	int menu_quit = false;

	g_menu_screen.LoadImg("image//menu//menu.png",screen);
	StartButton[0].LoadImg("image//menu//StartButtomUp.png",screen);
	StartButton[1].LoadImg("image//menu//StartButtomDown.png",screen);
	ExitButton[0].LoadImg("image//menu//ExitButtomUp.png",screen);
	ExitButton[1].LoadImg("image//menu//ExitButtomDown.png",screen);
	ContinueButton[0].LoadImg("image//menu//ContinueButtomUp.png",screen);
	ContinueButton[1].LoadImg("image//menu//ContinueButtomDown.png",screen);
	RightArrow[0].LoadImg("image//menu//RightArrow.png",screen);
	RightArrow[1].LoadImg("image//menu//RightArrow2.png",screen);
	LeftArrow[0].LoadImg("image//menu//LeftArrow.png",screen);
	LeftArrow[1].LoadImg("image//menu//LeftArrow2.png",screen);
	MusicButton[0].LoadImg("image//menu//Music-On.png",screen);
	MusicButton[1].LoadImg("image//menu//Music-Off.png",screen);
	TutorialButton.LoadImg("image//menu//TutorialButton.png",screen);
	TutorialText.LoadImg("image//menu//TutorialMenu.png",screen);
	Button = StartButton[0].GetRect();
	StartButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2);
	StartButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2);

	Button = ExitButton[0].GetRect();
	ExitButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 + Button.h*2.4);
	ExitButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 + Button.h*2.4);
	
	Button = ContinueButton[0].GetRect();
	ContinueButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 - Button.h*1.2);
	ContinueButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 - Button.h*1.2);
	
	Button = MusicButton[0].GetRect();
	MusicButton[1].SetRect(SCREEN_WIDTH - Button.w * 2,SCREEN_HEIGHT - Button.h*2);
	MusicButton[0].SetRect(SCREEN_WIDTH - Button.w * 2,SCREEN_HEIGHT - Button.h*2);
	
	Button = TutorialButton.GetRect();
	TutorialButton.SetRect(Button.w,SCREEN_HEIGHT - Button.h*2);
	bool TutorialBut = false;
	for(int i = 0; i < 4; i++)
	{
		Difficulty[i].LoadImg("image//menu//"+std::to_string(i)+".png",screen);
		Button = Difficulty[i].GetRect();
		Difficulty[i].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 + Button.h*1.2);
	}
	
	RightArrow[0].SetRect(SCREEN_WIDTH/2 + Button.w/2 + RightArrow[0].GetRect().w/2 ,SCREEN_HEIGHT/2 + Button.h*1.2);
	RightArrow[1].SetRect(SCREEN_WIDTH/2 + Button.w/2 + RightArrow[1].GetRect().w/2 ,SCREEN_HEIGHT/2 + Button.h*1.2);
	LeftArrow[0].SetRect(SCREEN_WIDTH/2 - Button.w/2  - 1.5*LeftArrow[0].GetRect().w ,SCREEN_HEIGHT/2 + Button.h*1.2);
	LeftArrow[1].SetRect(SCREEN_WIDTH/2 - Button.w/2  - 1.5*LeftArrow[1].GetRect().w ,SCREEN_HEIGHT/2 + Button.h*1.2);
	

	Mix_PlayMusic(MenuMusic, -1);
	bool MusicBut =  !(Mix_VolumeMusic(-1)>0);
	while(!menu_quit)
	{	
		SDL_RenderClear(screen);
		start_layout_x += 3;
		start_layout_x %= SCREEN_WIDTH;
		g_menu_screen.Render(screen, NULL);
		// for(int i = 0; i < 5; i++)
		// {
		// 	Layout[i].SetRect(start_layout_x%SCREEN_WIDTH,0);
		// 	Layout[i].Render(screen);
		// 	Layout[i].SetRect((start_layout_x%SCREEN_WIDTH) - SCREEN_WIDTH ,0);
		// 	Layout[i].Render(screen);
		// }
		while(SDL_PollEvent(&event) != 0)
		{
			if(event.type == SDL_MOUSEMOTION)
			{
				MousePosX = event.motion.x;
				MousePosY = event.motion.y;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if(TutorialBut == false)
					{
						if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,StartButton[0].GetRect()) == true)
						{
							menu_quit = true;
	//						SDL_Delay(500);
							return START;
						}
						if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,ExitButton[0].GetRect()) == true)
						{
							menu_quit = true;
							is_quit = true;
							game_quit = true;
							return EXIT;
						}
						if(NG_ > 0 && SDLbasefuction::CheckMousePos(MousePosX,MousePosY,ContinueButton[0].GetRect()) == true)
						{ 
							menu_quit = true;
							return CONTINUE;
						}
						if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,MusicButton[0].GetRect()) == true)
						{
							MusicBut = !MusicBut;
							if(MusicBut == false)
							{
								Mix_VolumeMusic((MIX_MAX_VOLUME / 5));
								Mix_Volume(-1,(MIX_MAX_VOLUME / 3));
							}
							else
							{
								Mix_VolumeMusic(0);
								Mix_Volume(-1,0);
							}
						}
						if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,RightArrow[0].GetRect()) == true)
						{
							Dif_ = ((Dif_+1)%4+4)%4;
						}
						if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,LeftArrow[0].GetRect()) == true)
						{
							Dif_ = ((Dif_-1)%4+4)%4;
						}
					}
					if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,TutorialButton.GetRect()) == true)
					{
						TutorialBut = !TutorialBut;
					}
				}
			}
		}
		if(TutorialBut == false)
		{
			if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,StartButton[0].GetRect()) == true)
			{
				StartButton[1].Render(screen);
			}
			else
			{
				StartButton[0].Render(screen);
			}
			if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,ExitButton[0].GetRect()) == true)
			{
				ExitButton[1].Render(screen);
			}
			else
			{
				ExitButton[0].Render(screen);
			}
			if(NG_ > 0)
			{
				if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,ContinueButton[0].GetRect()) == true)
				{
					ContinueButton[1].Render(screen);
				}
				else
				{
					ContinueButton[0].Render(screen);
				}
			}
			if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,RightArrow[0].GetRect()) == true)
			{
				RightArrow[1].Render(screen);
			}
			else
			{
				RightArrow[0].Render(screen);
			}
			if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,LeftArrow[0].GetRect()) == true)
			{
				LeftArrow[1].Render(screen);
			}
			else
			{
				LeftArrow[0].Render(screen);
			}
			MusicButton[MusicBut].Render(screen);
			Difficulty[Dif_].Render(screen);
		}
		else
		{
			TutorialText.Render(screen);
		}
		TutorialButton.Render(screen);
		SDL_RenderPresent(screen);
		SDL_Delay(30);
	}
	Mix_HaltMusic();
	return 0;
}


void SDLbasefuction::PlayerStatus(const int& money, const int& bullet, 
								const int& heath, const int& kill,int& time,
								TTF_Font* font_time,SDL_Renderer* screen
								,const int& gun_type,const int& style)
{
	BaseObject money_img;
	BaseObject bullet_img;
	BaseObject heath_img;
	BaseObject kill_img;
	TextObject money_;
	TextObject bullet_;
	TextObject heath_;
	TextObject kill_;
	TextObject time_game;
	TextObject style_;
	TextObject gun_type_;

	money_img.LoadImg("image//menu//money_img.png",screen);
	bullet_img.LoadImg("image//menu//bullet_img.png",screen);
	heath_img.LoadImg("image//menu//heath_img.png",screen);
	kill_img.LoadImg("image//menu//kill_img.png",screen);



	std::string str_time = "Time ";
	time += 1000/FRAME_PER_SECOND;
	Uint32 time_val = time/1000;
	std::string str_val = std::to_string(time_val);
	str_time += str_val;
	time_game.SetText(str_time);
	time_game.SetColor(TextObject::WHITE_TEXT);
	time_game.LoadFromRenderText(font_time,screen);
	time_game.RenderText(screen, SCREEN_WIDTH - 200,30);		
//show money
    Uint32 money_val = money;
    std::string str_money = std::to_string(money_val);
    money_.SetText(str_money);
	money_.SetColor(TextObject::BLACK_TEXT);
    money_.LoadFromRenderText(font_time,screen);
    money_.RenderText(screen,70,40);
    money_img.SetRect(20,20);
    money_img.Render(screen);
//show bullet
    Uint32 bullet_val = bullet;
    std::string str_bullet = std::to_string(bullet_val);
    bullet_.SetText(str_bullet);
	bullet_.SetColor(TextObject::BLACK_TEXT);
    bullet_.LoadFromRenderText(font_time,screen);
    bullet_.RenderText(screen,70,100);
    bullet_img.SetRect(20,80);
    bullet_img.Render(screen);
//show heath
    Uint32 heath_val = heath;
    std::string str_heath = "x"+std::to_string(heath_val);
    heath_.SetText(str_heath);
	heath_.SetColor(TextObject::BLACK_TEXT);
    heath_.LoadFromRenderText(font_time,screen);
    heath_.RenderText(screen,70,160);
    heath_img.SetRect(20,140);
    heath_img.Render(screen);
// show kill
    Uint32 kill_val = kill;
    std::string str_kill = std::to_string(kill_val);
    kill_.SetText(str_kill);
	kill_.SetColor(TextObject::BLACK_TEXT);
    kill_.LoadFromRenderText(font_time,screen);
    kill_.RenderText(screen,70,220);
    kill_img.SetRect(20,200);
    kill_img.Render(screen);

	switch (style)
	{
		case STYLE_1:
			style_.SetText("Style 1");
			style_.SetColor(TextObject::RED_TEXT);
			style_.LoadFromRenderText(font_time,screen);
			style_.RenderText(screen,200,30);
			break;
		case STYLE_2:
			style_.SetText("Trickster");
			style_.SetColor(TextObject::BLACK_TEXT);
			style_.LoadFromRenderText(font_time,screen);
			style_.RenderText(screen,200,30);
			break;
		case STYLE_3:
			style_.SetText("Royalguard");
			style_.SetColor(TextObject::WHITE_TEXT);
			style_.LoadFromRenderText(font_time,screen);
			style_.RenderText(screen,200,30);
			break;
		case STYLE_4:
			style_.SetText("SuperGun");
			style_.SetColor(TextObject::BLACK_TEXT);
			style_.LoadFromRenderText(font_time,screen);
			style_.RenderText(screen,200,30);
			break;
		default:
			break;
	}
//show gun_type
	switch (gun_type)
	{
		case DEFAULT:
			gun_type_.SetText("Single");
			gun_type_.SetColor(TextObject::BLACK_TEXT);
			gun_type_.LoadFromRenderText(font_time,screen);
			gun_type_.RenderText(screen,700,30);
			break;
		case DOUBLE:
			gun_type_.SetText("Double");
			gun_type_.SetColor(TextObject::WHITE_TEXT);
			gun_type_.LoadFromRenderText(font_time,screen);
			gun_type_.RenderText(screen,700,30);
			break;
		case WAVE:
			gun_type_.SetText("Giant");
			gun_type_.SetColor(TextObject::RED_TEXT);
			gun_type_.LoadFromRenderText(font_time,screen);
			gun_type_.RenderText(screen,700,30);
			break;
		case SHORTGUN:
			gun_type_.SetText("Down");
			gun_type_.SetColor(TextObject::RED_TEXT);
			gun_type_.LoadFromRenderText(font_time,screen);
			gun_type_.RenderText(screen,700,30);
			break;
		default:
			break;
	}	

    money_img.Free();
    bullet_img.Free();
    heath_img.Free();
    kill_img.Free();
    money_.Free();
    bullet_.Free();
    heath_.Free();
    kill_.Free();
	time_game.Free();
	gun_type_.Free();
	style_.Free();
}

int SDLbasefuction::CheckWin(const int& x_pos,const int& y_pos,SDL_Renderer* screen,int& Map_LV,const int& high_score)
{
	if(x_pos < (MAP_MAX_X - 10) *64) return 0;
	
	SDL_Event event;
	bool is_quit = false;
	TextObject YouWin;
	BaseObject MainMenuButton[2];
	BaseObject NextButton[2];
	BaseObject YouWinMenu;
	TTF_Font* font_time;
	TTF_Font* font_time_1 = NULL;
	TextObject YourScoreText;
	int MousePosX = 0;
	int MousePosY = 0;
	MainMenuButton[0].LoadImg("image//menu//MainMenuButtonUp.png",screen);
	MainMenuButton[1].LoadImg("image//menu//MainMenuButtonDown.png",screen);
	NextButton[0].LoadImg("image//menu//RightArrow.png",screen);
	NextButton[1].LoadImg("image//menu//RightArrow2.png",screen);
	YouWinMenu.LoadImg("image//menu//NextLV.png",screen);
	SDL_Rect Button = MainMenuButton[0].GetRect();
	MainMenuButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 - Button.h/4);
	MainMenuButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 - Button.h/4);
	Button = NextButton[0].GetRect();
	NextButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 + Button.h);
	NextButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 + Button.h);
	font_time = TTF_OpenFont("font//DebugFreeTrial-MVdYB.otf",300);
	font_time_1 = TTF_OpenFont("font//dlxfont_.ttf",50);
	SDL_Delay(500);
	while(!is_quit)
	{
		SDL_RenderClear(screen);
		YouWinMenu.Render(screen, NULL);
		while(SDL_PollEvent(&event) != 0)
		{
			if(event.type == SDL_MOUSEMOTION)
			{
				MousePosX = event.motion.x;
				MousePosY = event.motion.y;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,MainMenuButton[0].GetRect()) == true)
					{
						TTF_CloseFont(font_time);
						font_time = NULL;
						TTF_CloseFont(font_time_1);
						font_time_1 = NULL;
						is_quit = true;
						return 1;
					}
					if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,NextButton[0].GetRect()) == true)
					{
						TTF_CloseFont(font_time);
						font_time = NULL;
						TTF_CloseFont(font_time_1);
						font_time_1 = NULL;
						is_quit = true;
						Map_LV++;
						Map_LV %= 5;
						if(Map_LV == 0) Map_LV = 1;
						return 2;
					}
				}
			}
		}
		if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,MainMenuButton[0].GetRect()) == true)
		{
			MainMenuButton[1].Render(screen);
		}
		else
		{
			MainMenuButton[0].Render(screen);
		}
		if(SDLbasefuction::CheckMousePos(MousePosX,MousePosY,NextButton[0].GetRect()) == true)
		{
			NextButton[1].Render(screen);
		}
		else
		{
			NextButton[0].Render(screen);
		}
		YouWin.SetText("YOU WIN");
		YouWin.SetColor(TextObject::BLACK_TEXT);
		YouWin.LoadFromRenderText(font_time,screen);
		YouWin.RenderText(screen,100,30);


		std::string high_score_str = "YOURSCORE: " + std::to_string(high_score);
		YourScoreText.SetText(high_score_str);
		YourScoreText.SetColor(TextObject::RED_TEXT);
		YourScoreText.LoadFromRenderText(font_time_1,screen);
		YourScoreText.RenderText(screen,400,600);
		SDL_RenderPresent(screen);
	}
	return 2;
}

