#ifndef _sprite_app_H
#define _sprite_app_H

#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector4.h>
#include <vector>
#include <string>

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
}

class SpriteApp : public gef::Application
{
public:
	SpriteApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();

	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;

	float fps_;

	gef::Sprite my_sprite_;						//Main sprite
	gef::Sprite my_sprite_2_;					//Secondary sprite
	
	std::vector<gef::Sprite> multiple_sprites;	//10 sprites
	std::vector<gef::Sprite> sprite_generator;	//Randomly positioned sprites created every half a second

	int instance = 0;
	float timeCounter = 0;
	float spawnTimer = 0;

	std::vector<float> speedXYZ;
	std::vector<float> sprite2_speedXYZ;

	
	//char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	//std::string colour_hex = "0xff";
	//char alpha[2];
	//char red[2];
	//char green[2];
	//char blue[2];

};

#endif // _sprite_app_H
