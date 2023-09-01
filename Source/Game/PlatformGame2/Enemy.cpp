#include "Enemy.h"
#include "Player.h"

#include "PlatformGame2.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/CollisionComponent.h"
#include "Framework/Components/CircleCollisionComponent.h"

#include "Framework/Components/PhysicsComponent.h"

#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"

namespace yogi
{

	CLASS_DEFINITION(Enemy)
	
	void Enemy::Read(const rapidjson::Value& value)
	{
		GameObject::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
	
	bool Enemy::Initialize()
	{
		GameObject::Initialize();
	
		m_physicsComponent = GetComponent<yogi::PhysicsComponent>();
	
		return true;
	}
	
	
	void Enemy::Update(float dt)
	{
		GameObject::Update(dt);
	
	
		//movement
		float dir = 0;
	
		//vec2 forward = vec2{ 1, 0 };
	
		///*Player* player = m_scene->GetGameObject<Player>();
		//if (player)
		//{
		//	yogi::vec2 direction = player->transform.position - transform.position;
		//	m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		//}*/
	
		//m_physicsComponent->ApplyForce(forward * speed * dir);
	
		//bool onGround = (groundCount > 0);
		//if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_J) && !yogi::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_J) && onGround) {
		//	yogi::vec2 up = yogi::vec2{ 0, -1 };
		//	m_physicsComponent->SetVelocity(up * jump);
		//}
		
	}
	
	
	
	void Enemy::OnCollisionEnter(GameObject* other)
	{
		if (other->tag == "Player")
		{
			g_PlatformGame2.m_state = PlatformGame2::eState::GAMEOVER;
		}
	
	}
	
	void Enemy::OnCollisionExit(GameObject* other)
	{
	}
}
