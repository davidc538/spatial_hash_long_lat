#include "SpatialHash.hpp"

#include <cmath>

SpatialHash::SpatialHash(double cell_size_meters)
{
	this->cell_size_meters = cell_size_meters;

	cell_size_degrees = MetersToDegrees(cell_size_meters);
}

std::string SpatialHash::ComputeHash(double longitude, double latitude)
{
	double long_round, lat_round;

	long_round = NearestMultiple(longitude, cell_size_degrees);
	lat_round = NearestMultiple(latitude, cell_size_degrees);

	std::string retVal = std::to_string(long_round) + "," + std::to_string(lat_round);

	return retVal;
}

std::vector<std::string> SpatialHash::
	GetHashesForCellsInRange(double longitude, double latitude, double meters)
{
	std::vector<std::string> retVal;

	double
		range_degrees = MetersToDegrees(meters),
		min_longitude = longitude - (range_degrees / 2.0f),
		max_longitude = longitude + (range_degrees / 2.0f),
		min_latitude = latitude - (range_degrees / 2.0f),
		max_latitude = latitude + (range_degrees / 2.0f),
		i, j;

	for (i = min_longitude; i < max_longitude; i += cell_size_degrees)
		for (j = min_latitude; j < max_latitude; j += cell_size_degrees)
			if (DistanceInMeters(i, j, longitude, latitude) < meters)
				retVal.push_back(ComputeHash(i, j));

	return retVal;
}

static double NearestMultiple(double N, double M)
{
	double retVal = fmod(N, M);
	retVal = N - retVal;
	return retVal;
}

static double DistanceInMeters(double long1, double lat1, double long2, double lat2)
{
	double
		i = long2 - long1,
		j = lat2 - lat1,
		dist;

	i = DegreesToMeters(abs(i));
	j = DegreesToMeters(abs(j));

	i *= i;
	j *= j;

	dist = sqrt(i + j);

	return dist;
}

