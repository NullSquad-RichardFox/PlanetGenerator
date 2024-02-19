#include "epch.h"
#include "UUID.h"

#include <random>


static std::random_device sRandomDevice;
static std::mt19937_64 sEngine(sRandomDevice());
static std::uniform_int_distribution<uint64_t> sUniformDistribution;

FUUID::FUUID()
	:UUID(sUniformDistribution(sEngine)) {}

FUUID::FUUID(uint64_t uuid)
	:UUID(uuid) {}