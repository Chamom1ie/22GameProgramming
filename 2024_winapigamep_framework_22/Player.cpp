#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Projectile.h"
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
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Jiwoo", L"Texture\\jiwoo.bmp");
	this->AddComponent<Collider>();
	AddComponent<Animator>();
	GetComponent<Animator>()->CreateAnimation(L"JiwooFront", m_pTex, Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"JiwooFront", true);
}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::TAB))
		ShowInventory();

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
	SetPos(vPos);
}

void Player::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	//RECT_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
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

void Player::ShowInventory()
{
	//if (GET_SINGLE(WaveManager)->IsWaveEnd())
	{
		_enable = false;
		GET_SINGLE(InventoryManager)->ToggleInventory();
	}
}

void Player::CreateProjectile()
{
	Projectile* pProj = new Projectile;
	Vec2 vPos = GetPos();
	Vec2 mousePos = GET_MOUSEPOS;

	pProj->SetPos(vPos);
	pProj->SetSize({30.f,30.f});

	pProj->SetDir((mousePos - vPos).Normalize());
	pProj->SetName(L"PlayerBullet");
	
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
}
