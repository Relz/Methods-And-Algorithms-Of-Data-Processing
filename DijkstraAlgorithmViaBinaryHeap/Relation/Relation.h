class Relation
{
public:
	Relation(unsigned cityId, unsigned distance);
	unsigned GetCityId() const;
	unsigned GetDistance() const;
	bool operator>(Relation const & rhs) const;

private:
	unsigned m_cityId;
	unsigned m_distance;
};
