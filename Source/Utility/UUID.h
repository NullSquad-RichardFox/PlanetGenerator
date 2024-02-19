#pragma once


class FUUID
{
public:
	FUUID();
	FUUID(uint64_t uuid);
	FUUID(const FUUID&) = default;

	operator uint64_t() const { return UUID; }
private:
	uint64_t UUID;
};

namespace std {
	template <typename T> struct hash;

	template<>
	struct hash<FUUID>
	{
		std::size_t operator()(const FUUID& uuid) const
		{
			return (uint64_t)uuid;
		}
	};

}