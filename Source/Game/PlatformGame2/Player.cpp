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

	CLASS_DEFINITION(Player)
	
	void Player::Read(const rapidjson::Value& value)
	{
		GameObject::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
	
	bool Player::Initialize()
	{
		GameObject::Initialize();
	
		m_physicsComponent = GetComponent<yogi::PhysicsComponent>();
		//m_spriteAnimComponent = GetComponent<yogi::SpriteAnimRenderComponent>();
	
		return true;
	}
	
	
	void Player::Update(float dt)
	{
		if (m_game->win) return;
		GameObject::Update(dt);
	
	
		//movement
		//float dir = 0;
		if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_A) && !yogi::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_A))
		{
			aimAngle -= 45;
			std::cout << std::to_string(aimAngle) << "\n";
		}
		if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_D) && !yogi::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_D))
		{
			aimAngle += 45;
			std::cout << std::to_string(aimAngle) << "\n";

		}
		if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) hitStrength += 0.25f;
		if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) hitStrength -= 0.25f;

		if (hitStrength > 100.0f) hitStrength = 100.0f;
		if (hitStrength < 0) hitStrength = 0;

		if (aimAngle < 0) aimAngle += 360;
		if (aimAngle > 360) aimAngle -= 360;

		vec2 forward;

		if (aimAngle % 360 == 0) forward = { 1, 0 };
		else if (aimAngle % 360 == abs(45)) forward = { 1, 1 };
		else if (aimAngle % 360 == abs(90)) forward = { 0, 1 };
		else if (aimAngle % 360 == abs(135)) forward = { -1, 1 };
		else if (aimAngle % 360 == abs(180)) forward = { -1, 0 };
		else if (aimAngle % 360 == abs(225)) forward = { -1, -1 };
		else if (aimAngle % 360 == abs(270)) forward = { 0, -1 };
		else if (aimAngle % 360 == abs(315)) forward = { 1, -1 };

		if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE) && groundCount > 0)
		{
			hits++;
			m_physicsComponent->ApplyForce(forward * hitStrength);
		}
	
		//yogi::vec2 velocity = m_physicsComponent->m_velocity;
		//if (std::fabs(velocity.x) > 0.2f)
		//{
		//	//if (dir != 0) m_spriteAnimComponent->flipH = dir < 0;
		//	m_spriteAnimComponent->SetSequence("Run");
		//}
		//else
		//{
		//	m_spriteAnimComponent->SetSequence("Idle");
		//}
		//m_fireTimer -= dt;
		////fire weapon
		//if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)/* && !yogi::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)*/ && m_fireTimer <= 0)
		//{
		//	yogi::g_audioSystem.PlayOneShot("hitSound1", false);
		//	m_fireTimer = m_fireRate;
		//	//create weapon
		//	yogi::Transform transform{ m_transform.position, yogi::Deg2Rad(90), .5f};
		//	std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 15.0f, transform);
		//	weapon->m_tag = "PlayerBullet"; //in the weapon add a timer that the OnCollision method checks, if this timer is less than 0, destroy player.
		//	weapon->m_game = this->m_game;
	
		//	std::unique_ptr<yogi::SpriteComponent> component = std::make_unique<yogi::SpriteComponent>();
		//	component->m_texture = GET_RESOURCE(yogi::Texture, "PlayerBullet.png", yogi::g_renderer);
	
		//	auto collisionComponent = std::make_unique<yogi::CircleCollisionComponent>();
		//	collisionComponent->m_radius = 30.0f;
		//	weapon->AddComponent(std::move(collisionComponent));
	
		//	weapon->AddComponent(std::move(component));
	
		//	weapon->Initialize();
		//	m_scene->Add(std::move(weapon));
		//}
		//if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) yogi::g_time.SetTimeScale(0.5f);
		//else yogi::g_time.SetTimeScale(1);  
	}
	
	
	
	void Player::OnCollisionEnter(GameObject* other)
	{
		if (other->tag == "Ground")
		{
			groundCount++;
		}
		if (other->tag == "Hole")
		{
			m_game->win = true;
		}
	
	}
	
	void Player::OnCollisionExit(GameObject* other)
	{
		if (other->tag == "Ground")
		{
			groundCount--;
		}
	}
}
