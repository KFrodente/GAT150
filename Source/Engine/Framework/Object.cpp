#include "Object.h"


namespace yogi
{
	/*CLASS_DEFINITION(Object)*/

	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);
	}
}