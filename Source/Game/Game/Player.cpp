#include "Player.h"

#include "SpaceGame.h"
#include "Weapon.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"

#include "Framework/Components/PhysicsComponent.h"

#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
void Player::Update(float dt)
{
	GameObject::Update(dt);

	m_fireRate = m_game->GetFireRate();

	if (m_game->heal)
	{
		m_maxHealth += 25;
		m_health = m_maxHealth;
		m_game->heal = false;
	}
	//movement
	//if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_A) && !yogi::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_A) && m_xPos > 0) m_xPos--;
	//if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_D) && !yogi::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_D) && m_xPos < 5) m_xPos++;
	if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_W) && !yogi::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_W) && m_yPos > 0)
	{
		m_yPos--;
		yogi::g_audioSystem.PlayOneShot("moveUp", false);
	}
	if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_S) && !yogi::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_S) && m_yPos < 5)
	{
		m_yPos++;;
		yogi::g_audioSystem.PlayOneShot("moveDown", false);
	}
	//m_transform.position.x = yogi::Wrap(m_transform.position.x, yogi::g_renderer.GetWidth());
	//m_transform.position.y = yogi::Wrap(m_transform.position.y, yogi::g_renderer.GetHeight());


	//float thrust = 0;
	//if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = 1;
	//yogi::vec2 forward = yogi::vec2{0, -1).Rotate(m_transform.rotation;
	//auto physicsComponent = GetComponent<yogi::PhysicsComponent>();
	//physicsComponent->ApplyForce(forward * m_speed * thrust);


	m_fireTimer -= dt;
	//fire weapon
	if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)/* && !yogi::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)*/ && m_fireTimer <= 0)
	{
		yogi::g_audioSystem.PlayOneShot("hitSound1", false);
		m_fireTimer = m_fireRate;
		//create weapon
		yogi::Transform transform{ m_transform.position, yogi::Deg2Rad(90), .5f};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 15.0f, transform);
		weapon->m_tag = "PlayerBullet"; //in the weapon add a timer that the OnCollision method checks, if this timer is less than 0, destroy player.
		weapon->m_game = this->m_game;

		std::unique_ptr<yogi::SpriteComponent> component = std::make_unique<yogi::SpriteComponent>();
		component->m_texture = yogi::g_resources.Get<yogi::Texture>("PlayerBullet.png", yogi::g_renderer);

		weapon->AddComponent(std::move(component));
		m_scene->Add(std::move(weapon));
	}
	if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) yogi::g_time.SetTimeScale(0.5f);
	else yogi::g_time.SetTimeScale(1);  

	m_transform.position.y = (float)g_gridYSpots[m_yPos];
	m_transform.position.x = (float)g_gridXSpots[m_xPos];

	m_game->SetHealth(m_health);


	if (m_health <= 0)
	{
		dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PLAYERDEADSTART);
	}
}

void Player::OnCollision(GameObject* other)
{
	if ((other->m_tag == "EnemyBullet" && other->m_timeTillDamage < 0) || other->m_tag == "Enemy")
	{
		m_health -= other->m_damage;
	}
	if (other->m_tag == "SpecialBullet")
	{
		m_health -= other->m_damage;
	}

}
