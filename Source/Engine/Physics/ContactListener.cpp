#include "ContactListener.h"
#include "Framework/GameObject.h"
#include "Framework/Components/CollisionComponent.h"

namespace yogi
{
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			GameObject* actorA = reinterpret_cast<GameObject*>(fixtureA->GetUserData().pointer);
			GameObject* actorB = reinterpret_cast<GameObject*>(fixtureB->GetUserData().pointer);

			if (actorA->destroyed || actorB->destroyed) return;

			actorA->OnCollisionEnter(actorB);
			actorB->OnCollisionEnter(actorA);
		}
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			GameObject* actorA = reinterpret_cast<GameObject*>(fixtureA->GetUserData().pointer);
			GameObject* actorB = reinterpret_cast<GameObject*>(fixtureB->GetUserData().pointer);

			if (actorA->destroyed || actorB->destroyed) return;

			actorA->OnCollisionExit(actorB);
			actorB->OnCollisionExit(actorA);
		}
	}
}