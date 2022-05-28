#pragma once
#include <iostream>

enum class Error
{
    NoError,
    CorruptedArchive
};


class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream& out_;
    
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }
    
    template <typename T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}

	template <typename... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(args...);
	}
	
	
    
private:
	template <typename T>
	Error process(T&& val)
	{
		return toStream(val);
	}

	template <typename T, typename... Args>
	Error process(T&& val, Args&&... args)
	{
		Error err = toStream(val);
		if(err != Error::NoError)
		{
			return err;
		}
		out_ << Separator;
		return process(std::forward<Args>(args)...);
	}
		  
	template <typename T>
	Error toStream(T val)
	{
		return Error::CorruptedArchive;
	}
	
    Error toStream(uint64_t val);
	Error toStream(bool val);

};

class Deserializer
{
	std::istream& in_;
	
public:
	explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }
    
    template <typename T>
	Error load(T& object)
	{
		return object.deserialize(*this);
	}

	template <typename... ArgsT> Error operator()(ArgsT&&... args)
	{
		return process(args...);
	}

	
private:
	
	template <typename T>
	Error process(T&& val)
	{
		return fromStream(val);
	}

	template <typename T, typename... Args>
	Error process(T&& val, Args&&... args)
	{
		Error err = fromStream(val);
		if(err != Error::NoError)
		{
			return err;
		}
		return process(std::forward<Args>(args)...);
	}
		
	template <typename T>
	Error fromStream(T val)
	{
		return Error::CorruptedArchive;
	}

	Error fromStream(uint64_t& val);
	Error fromStream(bool& val);

};

