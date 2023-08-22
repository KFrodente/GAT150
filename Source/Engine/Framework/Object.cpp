#include "Object.h"


namespace yogi
{
	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);
	}
}