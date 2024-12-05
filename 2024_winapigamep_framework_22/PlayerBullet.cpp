#include "pch.h"
#include "PlayerBullet.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Texture.h"
#include "Collider.h"

PlayerBullet::PlayerBullet()
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\Bullet.bmp";
	//m_pTex->Load(path);
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"PlayerBullet", L"Texture\\PlayerBullet.bmp");
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	//ELLIPSE_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2)
		, (int)(vPos.y - height / 2)
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));
	ComponentRender(_hdc);
}

void PlayerBullet::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Enemy")
	{
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void PlayerBullet::StayCollision(Collider* _other)
{
}

void PlayerBullet::ExitCollision(Collider* _other)
{
}