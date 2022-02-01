#define PI 3.14159265358979323846 //pi

#include "sprite_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <maths/math_utils.h>

#include <stdlib.h>	//srand, rand
#include <time.h>	//time


SpriteApp::SpriteApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	font_(NULL)
{
}

void SpriteApp::Init()
{
	srand(time(NULL));

	// create a sprite renderer to draw your sprites
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	InitFont();

	//Main sprite
	//my_sprite_.set_position(platform_.width()*0.5f, platform_.height()*0.5f, 0.0f);
	//my_sprite_.set_width(32.0f);
	//my_sprite_.set_height(32.0f);
	//

	////Secondary sprite
	//my_sprite_2_.set_position(platform_.width() * 0.5f, platform_.height() * 0.25f, 0.0f);
	//my_sprite_2_.set_width(32.0f);
	//my_sprite_2_.set_height(32.0f);


	////Multiple sprites
	//float offsetX;

	//for (int i = 0; i < 10; i++)
	//{
	//	multiple_sprites.push_back(gef::Sprite());
	//	multiple_sprites[i].set_width(32.0f);
	//	multiple_sprites[i].set_height(32.0f);

	//	if (i == 0)
	//	{
	//		offsetX = 0.0f;
	//	}

	//	multiple_sprites[i].set_position(multiple_sprites[i].width() + offsetX, platform_.height() * 0.25f, 0.0f);

	//	offsetX += multiple_sprites[i].width() + 5.0f;
	//}

	

	

	//Speed
	speedXYZ = { 1.0f, 1.0f, 0.0f };
	sprite2_speedXYZ = { -0.5f, 1.0f, 0.0f };
}

void SpriteApp::CleanUp()
{
	CleanUpFont();

	// destroy sprite renderer once you've finished using it
	delete sprite_renderer_;
	sprite_renderer_ = NULL;
}

bool SpriteApp::Update(float frame_time)
{
	// frame rate = 1 second / frame_delta_time
	fps_ = 1.0f / frame_time;
	timeCounter += frame_time;
	spawnTimer += frame_time;
	// move the sprite along the x-axis

	//// get a copy of the current position of the sprite
	//gef::Vector4 sprite_position = my_sprite_.position();		//Main sprite
	//gef::Vector4 sprite_2_position = my_sprite_2_.position();	//Secondary sprite

	////// update the x-axis on the COPY of the current position
	////sprite_position.set_x(sprite_position.x() + 1);
	////// update the sprite with the new position
	////my_sprite_.set_position(sprite_position);

	////Alternative sprite position update code done in one line
	//my_sprite_.set_position(sprite_position.x() + speedXYZ[0], sprite_position.y() + speedXYZ[1], sprite_position.z() + speedXYZ[2]);
	//my_sprite_2_.set_position(sprite_2_position.x() + sprite2_speedXYZ[0], sprite_2_position.y() + sprite2_speedXYZ[1], sprite_2_position.z() + sprite2_speedXYZ[2]);



	//Randomly set sprites
	if (spawnTimer >= 0.5){
	sprite_generator.push_back(gef::Sprite());
	sprite_generator[instance].set_width(rand() % 100 + 1);
	sprite_generator[instance].set_height(rand() % 100 + 1);
	
	alpha = rand() % 256;
	blue = rand() % 256;
	green = rand() % 256;
	red = rand() % 256;
	
	//colour_hex = (alpha << 24) | (blue << 16) | (green << 8) | (red);
	//sprite_generator[instance].set_colour(colour_hex);

	sprite_generator[instance].set_colourRGBA(255, 0, 0, 255);

	//Set position in range from -16.0f to 950 for X and in range from -16.0f to 528 for Y
	//*Based on previous testings the object is rendered from the centre instead of left right corner 
	// which means that if a sprite of size 32x32 is rendered at position (0, 0) 
	// its left corners are displayed at X = -16.0f, and Y = +/- 16.0f respectively*
	//If we render a sprite at either the edges of the screen, only a half of the sprite would be visible
	sprite_generator[instance].set_position(rand() % platform_.width() - sprite_generator[instance].width() / 2.0f, rand() % platform_.height() - sprite_generator[instance].height() / 2.0f, 0.0f);

	//While the position of the sprite by X or Y is less than the half size in respective coordinates -> re-randomise
	while ((sprite_generator[instance].position().x() < sprite_generator[instance].width() / 2.0f) || (sprite_generator[instance].position().y() < sprite_generator[instance].height() / 2.0f)) {
		sprite_generator[instance].set_position(rand() % platform_.width() - sprite_generator[instance].width() / 2.0f, rand() % platform_.height() - sprite_generator[instance].height() / 2.0f, 0.0f);
	}

	float divider = rand() % 10 + 1;
	sprite_generator[instance].set_rotation(PI/divider);
		
	instance++;
	spawnTimer = 0;
	}

	//Once the time counter is more or equal to 10
	if (timeCounter >= 10)
	{
		//Destory all sprites at once
		//sprite_generator.erase(sprite_generator.begin(), sprite_generator.end());
		
		//Or destroy one by one and decrease the instance by 1
		sprite_generator.erase(sprite_generator.begin());
		instance--;

		if (sprite_generator.empty())
		{ //Reset the number of instances, spawn timer and time counter
			instance = 0;
			spawnTimer = 0;
			timeCounter = 0;
		}
	}




	return true;
}

void SpriteApp::Render()
{
	// draw all sprites between the Begin() and End() calls
	sprite_renderer_->Begin();

	// draw my sprite here
	//sprite_renderer_->DrawSprite(my_sprite_);
	//sprite_renderer_->DrawSprite(my_sprite_2_);

	/*for (auto it : multiple_sprites)
	{
		sprite_renderer_->DrawSprite(it);
	}*/

	for (auto it : sprite_generator)
	{
		sprite_renderer_->DrawSprite(it);
	}

	DrawHUD();
	sprite_renderer_->End();
}


void SpriteApp::InitFont()
{
	// create a Font object and load in the comic_sans font data
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SpriteApp::CleanUpFont()
{
	// destroy the Font object
	delete font_;
	font_ = NULL;
}

void SpriteApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(650.0f, 510.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xff0000ff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"FPS: %.1f xpos: %.1f",							// string of text to render
			fps_,									// any variables used in formatted text string http://www.cplusplus.com/reference/cstdio/printf/
			my_sprite_.position().x()
			);
	}
}

