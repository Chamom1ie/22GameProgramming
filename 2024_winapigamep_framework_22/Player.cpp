#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "PlayerBullet.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "InventoryManager.h"
Player::Player()
	: m_pTex(nullptr)
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\planem.bmp";
	//m_pTex->Load(path);
	//m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\planem.bmp");

	/*m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Jiwoo", L"Texture\\jiwoo.bmp");
	this->AddComponent<Collider>();
	AddComponent<Animator>();
	GetComponent<Animator>()->CreateAnimation(L"JiwooFront", m_pTex, Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"JiwooFront", true);*/
}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::TAB))
		ToggleInventory();
	if (!_enable) return;

	Vec2 vPos = GetPos();
	Vec2 dir = { 0,0 };
	//if(GET_KEY(KEY_TYPE::LEFT))
	if (GET_KEY(KEY_TYPE::A))
		dir.x = -1;
	if (GET_KEY(KEY_TYPE::D))
		dir.x = 1;
	if (GET_KEY(KEY_TYPE::W))
		dir.y = -1;
	if (GET_KEY(KEY_TYPE::S))
		dir.y = 1;

	if (timer >= m_atkCooldown && GET_KEY(KEY_TYPE::LBUTTON))
	{
		timer = 0;
		CreateProjectile();
	}
	timer += fDT;
	
	vPos += (dir.Normalize() * fDT) * 200;

	//Vec2 minPos = { (float)(0 + GetSize().x / 2), (float)(((SCREEN_HEIGHT - SCREEN_WIDTH) / 2) + GetSize().y / 2) };
	Vec2 minPos = { 0.f, (float)((SCREEN_HEIGHT - SCREEN_WIDTH) / 2) };
	//Vec2 maxPos = { (float)(SCREEN_WIDTH - GetSize().x / 2), (float)((SCREEN_HEIGHT/2 + SCREEN_WIDTH / 2) - GetSize().y / 2)};
	Vec2 maxPos = { (float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT/2 + SCREEN_WIDTH / 2)};

	float clampedX = std::clamp(vPos.x, minPos.x + GetSize().x / 2, maxPos.x - GetSize().x / 2);
	float clampedY = std::clamp(vPos.y, minPos.y + GetSize().y / 2, maxPos.y - GetSize().y / 2);

	Vec2 realPos = { clampedX, clampedY };
	SetPos(realPos);
}

void Player::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	RECT_RENDER(_hdc, vPos.x, vPos.y
		, vSize.x, vSize.y);
	/*int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();*/
	//::BitBlt(_hdc
	//	, (int)(vPos.x - vSize.x / 2)
	//	, (int)(vPos.y - vSize.y / 2)
	//	, width, height,
	//	m_pTex->GetTexDC()
	//	,0,0,SRCCOPY
	//);
	/*::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2)
		, (int)(vPos.y - height / 2)
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0,width, height, RGB(255,0,255));*/
	ComponentRender(_hdc);
	//::StretchBlt();
	//::AlphaBlend();
	//::PlgBlt();
}

void Player::ToggleInventory()
{
	//if (GET_SINGLE(WaveManager)->IsWaveEnd())
	{
		_enable = !_enable;
		GET_SINGLE(InventoryManager)->ToggleInventory();
	}
}

void Player::CreateProjectile()
{
	int paraCnt = GET_SINGLE(InventoryManager)->GetParaCount();
	int seriCnt = GET_SINGLE(InventoryManager)->GetSeriCount();
	int damage = seriCnt; //ceil((float)seriCnt / paraCnt);
	for (int i = 1; i <= paraCnt; ++i)
	{
		PlayerBullet* pProj = new PlayerBullet;
		Vec2 vPos = GetPos();
		Vec2 mousePos = GET_MOUSEPOS;

		pProj->SetPos(vPos);
		pProj->SetSize({30.f,30.f});

		float betweenAngle = 5.f;
		float projAngle = betweenAngle * (paraCnt - 1);

		Vec2 dir = (mousePos - vPos);

		float radian1 = atan2(dir.y, dir.x);
		float deg = RAD2DEG(radian1) - projAngle / 2;

		float radian2 = DEG2RAD(deg + betweenAngle * i);
		Vec2 dir2 = { cosf(radian2), sinf(radian2) };

		pProj->SetDamage(damage);
		pProj->SetDir(dir2.Normalize());
		pProj->SetName(L"PlayerBullet");
	
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
	}

}