#include "serializer.hpp"
    
Error Serializer::toStream(uint64_t val)
{
	out_ << val;
	return Error::NoError;
}
	
Error Serializer::toStream(bool val)
{
	if(val){
		out_ << "true";
	}
	else{
		out_ << "false";
	}
	return Error::NoError;
}

    
Error Deserializer::fromStream(uint64_t& val)
{
	std::string text;
	in_ >> text;

	uint64_t value;
	try
	{
		value = std::stoull(text);
	}
	catch(std::logic_error& ex)
	{
		return Error::CorruptedArchive;
	}

	val = value;
	return Error::NoError;
}
	
Error Deserializer::fromStream(bool& val)
{
	std::string text;
	in_ >> text;

	if (text == "true")
		val = true;
	else if (text == "false")
		val = false;
	else
		return Error::CorruptedArchive;

	return Error::NoError;
}