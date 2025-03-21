#pragma once
enum class LAYER
{
	DEFAULT,
	BACKGROUND,
	PLAYER,
	PROJECTILE,
	ENEMY,
	// UI
	END
};

enum class PEN_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};

enum class BRUSH_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};


enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END,
};

enum class ENEMY_TYPE
{
	Tradian,
	Eleven,
	XSlide,
	Orage,
	Doll,
	BOSS,
	END
};
