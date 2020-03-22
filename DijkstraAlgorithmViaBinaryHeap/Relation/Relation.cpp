#include "Relation.h"

Relation::Relation(unsigned cityId, unsigned distance)
	: m_cityId(cityId)
	, m_distance(distance)
{}

unsigned Relation::GetCityId() const
{
	return m_cityId;
}

unsigned Relation::GetDistance() const
{
	return m_distance;
}

bool Relation::operator>(Relation const & rhs) const
{
	return m_distance > rhs.m_distance;
}
